#ifndef TOOLS
#define TOOLS

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>


// createbdd -n nameOfNewBdd
#define CREATEBDD "createbdd"
// showdatabases
#define SHOWBDD "showdatabases"
// createtable -n nameOfBdd -nt nameOfTable -c col1 -c col2 -c col3 -c col4 -c colN
#define CREATETABLE "createtable"
// showtables -n nameOfBdd
#define SHOWTABLE "showtables"
// describetable -n nameOfBdd -nt nameOfTable
#define DESCRIBETABLE "describetable"
// inserttable -n nameOfBdd -nt nameOfTable -v val1 -v val2 -v val3 -v val4
#define INSERTTABLE "inserttable"
// selecttable -n nameOfBdd  -nt nameOfTable
#define SELECTTABLE "selecttable"


#define SEPARATEURCOLONNE ";"
#define SEPARATEURLIGNE "$"


#define OPTIONNAMEBDD "-n"
#define OPTIONNAMETABLE "-nt"
#define OPTIONCOLTABLE "-c"
#define OPTIONROWVALUE "-v"

#define ERRORCOMMANDELINE "erreur dans la ligne de commande"
#define ERRORCREATEBDD "impossible de crée la base de donnée"
#define ERRORCREATETALBE "impossible de crée la table"
#define ERRORINSERTTABLE "impossible d'insérer dans la table    "


#define OUTPUTBDDCREATED "la base de donnée a bien été crée"
#define OUTPUTTABLECREATED "la table a bien été crée"
#define OUTPUTTABLEINSERED "les valeurs ont bien été insérer dans la table"



#define TAILLE_MAX 1000

typedef char* string;

struct string_list {
    //struct string_list *prev;
    struct string_list *next;
    string value ;
};


typedef struct string_list *liststring;


string NameOfBdd = NULL;
string NameOfTable = NULL;

void createNewBdd(int argc, string argv[]);
void showBdd();
void createNewTable(int argc, string argv[]);
void showTable(int argc, string argv[]);
void describeTable(int argc, string argv[]);
void insertTable(int argc, string argv[]);
void selectTable(int argc, string argv[]);

int extractNameOfTable(string nameFile);
int verifyIfFileExist(string path, int createThis);

void getBdd(int argc, string argv[]);
void getTableOfBdd(int argc, string argv[]);
string getValueArgument(int argc, char* argv[], char* option);
liststring getValuesArgument(int argc, char* argv[], char* option);
int sizeListString(liststring list);
char *strcopy(char* src);

string concat_string(string s1,string s2);

void debug(string msg);
void debugI(int i);
void debugC(char c);
#endif // TOOLS

