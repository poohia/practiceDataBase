#include "tools.h"

void createNewBdd(int argc, string argv[])
{
    //debug("createNewBdd()");
    getBdd(argc, argv);
    if(NameOfBdd == NULL )
        debug(ERRORCOMMANDELINE);
    else
    {
        if(mkdir(concat_string("./data/", NameOfBdd),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0)
            debug(OUTPUTBDDCREATED);
        else
            debug(ERRORCREATEBDD) ;
    }

}


void createNewTable(int argc, string argv[])
{
    //debug("createNewTable()");
    getTableOfBdd(argc, argv);

    if(NameOfTable == NULL || NameOfBdd == NULL)
        debug(ERRORCOMMANDELINE);
    else
    {
        FILE *fichier = NULL;
        //debug(concat_string(concat_string(concat_string("data/",NameOfBdd),"/table_"),NameOfTable));
        //char* path = concat_string(concat_string(concat_string("data/",NameOfBdd),"/table_"),NameOfTable);
        string path = concat_string(concat_string(concat_string(concat_string("data/",NameOfBdd),"/"),NameOfTable),"_table.txt");
        // char* path = concat_string("/home/dev0/Documents/jordanazoulaybdd/data/jordan/",NameOfTable);
        // char* path = "/home/dev0/Documents/jordanazoulaybdd/data/jordan/test1";
        fichier = fopen(path,"w");

        if(fichier == NULL)
        {
            debug(ERRORCREATETALBE);
        }
        else
        {
            liststring list = getValuesArgument(argc, argv,OPTIONCOLTABLE);
            liststring tmp = list ;
            while(tmp != NULL)
            {

                if(tmp->value != NULL)
                    fputs(concat_string(tmp->value,SEPARATEURCOLONNE),fichier);
                tmp = tmp->next;
            }
            fclose(fichier);
            debug(OUTPUTTABLECREATED);
        }
    }
}

void showBdd()
{
    //debug("showBdd()");
    struct dirent *lecture;
    DIR *rep;
    rep = opendir( "./data" );
    while ((lecture = readdir(rep))) {
        if (strcmp(lecture->d_name, ".") == 0 || strcmp(lecture->d_name, "..") == 0)
            continue;
        else
            printf(" - %s \n", lecture->d_name);
    }
    closedir(rep);
}




void showTable(int argc, string argv[])
{
    //debug("showTable()");
    getTableOfBdd(argc, argv);

    if(NameOfBdd == NULL )
        debug(ERRORCOMMANDELINE);
    else
    {
        struct dirent *lecture;
        DIR *rep;
        rep = opendir(concat_string("./data/",NameOfBdd));
        while ((lecture = readdir(rep))) {
            if(extractNameOfTable(lecture->d_name) == 0)
                printf(" - %s \n",lecture->d_name);
            /*
            if (strcmp(lecture->d_name, ".") == 0 || strcmp(lecture->d_name, "..") == 0)
                continue;
            else
                debug(lecture->d_name);*/
        }
        closedir(rep);
    }
}

void describeTable(int argc, string argv[])
{
    //debug("describeTable()");
    getTableOfBdd(argc, argv);
    if(NameOfTable == NULL || NameOfBdd == NULL)
        debug(ERRORCOMMANDELINE);
    else
    {
        FILE *fichier = NULL;
        string path = concat_string(concat_string(concat_string(concat_string("data/",NameOfBdd),"/"),NameOfTable),"_table.txt");
        fichier = fopen(path,"r");

        if(fichier == NULL)
        {
            debug(ERRORCREATETALBE);
        }
        else
        {


            // debug(fgets());
            char chaine[TAILLE_MAX] = "";
            fgets(chaine,TAILLE_MAX,fichier);
            string token = strtok(chaine,SEPARATEURCOLONNE);

            while(token != NULL)
            {
                debug(token);
                token = strtok(NULL,SEPARATEURCOLONNE);
            }
            fclose(fichier);
        }
    }
}

void insertTable(int argc, string argv[])
{
    // debug("insertTable()");
    getTableOfBdd(argc, argv);
    if(NameOfTable == NULL || NameOfBdd == NULL)
        debug(ERRORCOMMANDELINE);
    else
    {
        string path = concat_string(concat_string(concat_string(concat_string("data/", NameOfBdd), "/"),NameOfTable),".txt");

        // pathTable permet de savoir si la table existe , si seulement il y a son fichier _table.txt
        string pathTable = concat_string(concat_string(concat_string(concat_string("data/",NameOfBdd),"/"),NameOfTable),"_table.txt");

        if(verifyIfFileExist(path, 0) == 0 && verifyIfFileExist(pathTable,1) == 0)
        {
            FILE *fichier = NULL;

            fichier = fopen(path,"a+");

            if(fichier == NULL)
                debug(ERRORINSERTTABLE);
            else
            {

                liststring rows = getValuesArgument(argc, argv, OPTIONROWVALUE);
                FILE *fichierTable = NULL;
                fichierTable = fopen(pathTable,"r");
                if(fichierTable == NULL)
                    debug(ERRORINSERTTABLE);
                else
                {

                    int sizeTable = 0, j = 1, sizeList = 0, k = 0;
                    //sizeList est le nombre d'argument
                    sizeList = sizeListString(rows);
                    char chaine[TAILLE_MAX] = "";
                    fgets(chaine,TAILLE_MAX,fichierTable);
                    string token = strtok(chaine,SEPARATEURCOLONNE);

                    while(token != NULL)
                    {
                        //sizeTable est le nombre de colonne de la table
                        sizeTable++;
                        token = strtok(NULL,SEPARATEURCOLONNE);
                    }
                    fclose(fichierTable);
                    // si le nombre d'argument n'est pas égale au nombre de colonnes
                    if(sizeList != sizeTable)
                        debug(ERRORINSERTTABLE);
                    else
                    {
                        string currentVal = "";
                        for(k ; k <  sizeTable; k ++)
                        {

                            if(j == sizeTable)
                                currentVal =concat_string(concat_string(currentVal, rows->value),SEPARATEURLIGNE);
                            else
                            {
                                currentVal = concat_string(concat_string(currentVal, rows->value),SEPARATEURCOLONNE);
                                j++;
                            }

                            rows = rows->next;
                        }
                        //debug(currentVal);
                        (fputs(currentVal,fichier) != EOF)? debug(OUTPUTTABLEINSERED) : debug(ERRORINSERTTABLE);


                        fclose(fichier);
                    }


                }
            }
        }
        else
            debug(ERRORINSERTTABLE);
    }
}

void selectTable(int argc, string argv[])
{
    //debug("selectTable()");
    debug("\n");
    getTableOfBdd(argc, argv);
    if(NameOfTable == NULL || NameOfBdd == NULL)
        debug(ERRORCOMMANDELINE);
    else
    {
        string path = concat_string(concat_string(concat_string(concat_string("data/",NameOfBdd),"/"),NameOfTable),"_table.txt");
        string path2 = concat_string(concat_string(concat_string(concat_string("data/",NameOfBdd),"/"),NameOfTable),".txt");
        FILE* fichier;
        FILE * fichier2;
        fichier = fopen(path, "r");
        fichier2 = fopen(path2,"r");
        if(fichier == NULL && fichier2 == NULL)
            debug(ERRORCOMMANDELINE);
        else
        {
            char chaine[TAILLE_MAX] = "";
            fgets(chaine,TAILLE_MAX,fichier);
            string token = strtok(chaine,SEPARATEURCOLONNE);

            while(token != NULL)
            {
                printf("|%s\t|",token);
                token = strtok(NULL,SEPARATEURCOLONNE);
            }
            fclose(fichier);
            debug("\n");
            fgets(chaine,TAILLE_MAX,fichier2);
            int i, j=0 ;
            char selectValue[TAILLE_MAX] = "";
            for(i = 0 ; i < strlen(chaine); i++)
            {
                char currentValue = chaine[i];
                switch(currentValue)
                {
                case ';':
                    printf("|%s\t|",selectValue);
                    j=0;
                    break;
                case '$':
                    printf("%s\n",selectValue);
                    j=0;
                    break;
                default:
                    selectValue[j] = currentValue;
                    selectValue[j+1] = "\0";
                    j++;
                    break;
                }
            }
        debug("\n");
        }
    }
}
string getValueArgument(int argc, string argv[], string option)
{
    string result = NULL;
    int i ;
    for( i = 2 ; i < argc  ; i++)
    {
        if(strcasecmp(argv[i], option) == 0  && argv[i+1] != NULL)
            if( argv[i+1][0] != '-' && result == NULL)
                result = argv[i+1];
    }
    return result;
}



void getBdd(int argc, string argv[])
{
    NameOfBdd = getValueArgument(argc, argv, OPTIONNAMEBDD);
}


void getTableOfBdd(int argc, string argv[])
{
    NameOfBdd = getValueArgument(argc, argv, OPTIONNAMEBDD);
    NameOfTable  = getValueArgument(argc, argv, OPTIONNAMETABLE);
}
liststring getValuesArgument(int argc, string argv[], string option)
{
    liststring firstValue = malloc(sizeof(liststring));

    int i ;
    int firstInit = 1;
    for( i = 2 ; i < argc   ; i++)
    {
        liststring currentValue;
        if( firstInit == 1)
            currentValue = firstValue;
        else
            currentValue = malloc(sizeof(liststring));

        currentValue->value = NULL;
        currentValue->next = NULL;

        if(strcasecmp(argv[i], option) == 0  && argv[i+1] != NULL)
            if( argv[i+1][0] != '-')
            {
                if(firstInit == 1)
                {
                    currentValue->value = argv[i+1];
                    firstInit = 0;
                }
                else
                {

                    currentValue->value = argv[i+1];
                    liststring tmp = firstValue;
                    while(tmp->next != NULL)
                    {
                        tmp = tmp->next;
                    }
                    tmp->next = currentValue;

                }

            }
            else if(firstInit == 0) free(currentValue);
    }
    /*  debug(firstValue->next->next->next->value);
    while( firstValue->next != NULL)
    {
       // debug(firstValue->value);
        firstValue = firstValue->next;
    }*/
    return firstValue;

}


void debug(string msg)
{
    printf("%s\n",msg);
}


void debugI(int i)
{
    printf("%d\n",i);
}


void debugC(char c)
{
    printf("%c\n",c);
}


string concat_string(string s1, string s2)
{
    string s3=NULL;
    s3=(string )malloc((strlen(s1)+strlen(s2))*sizeof(char));
    strcpy(s3,s1);
    strcat(s3,s2);
    return s3;
}



int extractNameOfTable(string nameFile)
{

    int test = 1;
    int i ;
    for(i = 0 ; i < strlen(nameFile) && test == 1; i++)
    {
        if(nameFile[i] == '_')
        {
            if(strlen(nameFile) >= (i+8))
                if(nameFile[i+1] == 't')
                    if(nameFile[i+2] == 'a')
                        if(nameFile[i+3] == 'b')
                            if(nameFile[i+4]  == 'l')
                                if(nameFile[i+5]  == 'e')
                                    if(nameFile[i+6]  == '.')
                                        if(nameFile[i+7]  == 't')
                                            if(nameFile[i+8]== 'x')
                                                if(nameFile[i+9]  == 't')
                                                    test = 0;

        }
    }
    if(test == 0)
    {
        nameFile = strtok(nameFile,"_");
        // nameFile = "toto";
    }
    return test;
}







int verifyIfFileExist(string path, int createThis)
{
    int tmp = 0;
    FILE *fichier;
    fichier = fopen(path,"r");
    if(fichier == NULL)
    {
        if(createThis == 0)
        {
            fichier = fopen(path, "w");
            if(fichier == NULL)
                tmp = 1;
            else
                fclose(fichier);
        }
        else
            tmp = 1;
    }
    return tmp;
}


int sizeListString(liststring list)
{
    int i = 1;
    liststring tmp = list;
    while(list->next != NULL)
    {
        i++;
        list = list->next ;
    }
    list = tmp;


    return i;
}




char* strcopy(char *src)
{
    int i;
    char* dest = malloc(sizeof(src));
    for(i = 0; src[i] != "\0"; i++)
    {
        dest[i] = src[i];
    }
    return dest;
}
