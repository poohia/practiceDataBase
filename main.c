#include "tools.c"



int main(int argc, string argv[])
{
    char* elem1 = argv[1];
    if(strcasecmp(CREATEBDD ,elem1) == 0)
        createNewBdd(argc, argv);
    else if(strcasecmp(SHOWBDD ,elem1) == 0)
        showBdd();
    else if(strcasecmp(CREATETABLE ,elem1) == 0)
        createNewTable(argc, argv);
    else if(strcasecmp(SHOWTABLE ,elem1) == 0)
        showTable(argc, argv);
    else if(strcasecmp(DESCRIBETABLE ,elem1) == 0)
        describeTable(argc, argv);
    else if(strcasecmp(INSERTTABLE ,elem1) == 0)
        insertTable(argc, argv);
    else if(strcasecmp(SELECTTABLE ,elem1) == 0)
        selectTable(argc, argv);
    else
        debug(ERRORCOMMANDELINE);
    return 0;
}

