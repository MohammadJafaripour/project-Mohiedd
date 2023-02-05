#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/////////////////////////
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>
///////////////////////
int createfilenum=0;
char *rootAddress = "C:/Users/Public/Documents/root/";
///////////////////////
char **INP_ARG(char *);


char *substr(const char *String, long int last )
{
    long int  first=1;
    long int Tool = last - 1;
    char *dest = calloc(sizeof(char) , (Tool + 1));
    
    while ( first < last)
    {
        *dest = *(String + first);
        dest++;
        first++;
    }
    *dest = NULL;
    return dest - Tool;
}



char *AddressComplete(char *Fname)//
{
   // if (recievedPath[1] != ':' && (recievedPath[2] != '/' || recievedPath[2] != '\\'))
   // {
    
        char Comp[1024];
        strcpy(Comp, rootAddress);
        strcat(Comp, Fname);
        strcpy(Fname, Comp);
    //}
}
void Folder(const char *path)//
{
    if (CreateDirectory(path, NULL)!='\0')
    {
        return;
    }
}
char *Quotation(char *Array)//

{
    char Q='"';
    if (Array[0] == Q)
    {
        strcpy(Array, substr(Array,  strlen(Array) - 1));
    }
    return Array;
}
bool Existance(char *filename)//
{
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}





/// Functions ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/// 
int StrNew(char* Kol, char* Joze)
{
    return strstr(Kol, Joze) - Kol;
}
char *createFile(char *FileName)
{
    Folder(FileName);
    FileName = AddressComplete(FileName);
    FILE *file;
    file = fopen(FileName, "a");
    

    if (file == NULL)
    {

        return "Failed to create the file.\n";
    }
    else
    {
        fputs("\0", file);
        static char createfile[] = "";
        sprintf(createfile, "File  created .\n");
        return (createfile);
    }
}

char *removestr(char *File, int RemoveLine, int pos, int size, char Jahat)
{
    if (!Existance(File))
    {
        return "The File Could not be  found!";
    }
    FILE *file;
    file = fopen(File, "r");
    char *Array = (char *)malloc(512);
    Array[0] = 0;
   long  int Line = 1,Harf=0;
   char A='\0';
    
    char OneLine[512];
    while (fgets(OneLine, 511, file)!=NULL)
    {
        if (Line != RemoveLine)
        {
            strcat(Array, OneLine);
        }
        else
        {
            
            while (OneLine[Harf] != A)
            {
                char Ch[2] = {OneLine[Harf], '\0'};
                if (Harf < pos - 1 || Harf > pos - 2 + size)
                {
                    strcat(Array, Ch);
                }
                Harf++;
            }
        }
        Line++;
    }

    fclose(file);
    file = fopen(File, "w");
    fputs(Array, file);
    fclose(file);
    return "Chars have been removed!";
}
char *insertstr(char *fileName, char *ArrayToGet, int InsertLine, int pos)//
{
    InsertLine--;
    pos--;
    if (!Existance(fileName))
        return "The File could not be found!";

    FILE *Filef = fopen(fileName, "r");

    char String[2048] = "\0";
    char A='\0',B='\\',C='n',D='\"';
    long int l1 = 0;
    while (ArrayToGet[l1] != A)
    {

        while (ArrayToGet[l1] == B)
        {

            if (ArrayToGet[l1 + 1] == C)
            {
                strcat(String, "\n\0");
            }
             else if (ArrayToGet[l1 + 1] == D)
            {
                strcat(String, "\"\0");
            }

            else if (ArrayToGet[l1 + 1] == B)
            {
                strcat(String, "\\\0");
            }

           

            l1 += 2;
        }

        if (ArrayToGet[l1] == A)
        {
            break;
        }
        char Ch[2] = {ArrayToGet[l1], A};
        strcat(String, Ch);
        l1++;
    }

    char file[4096];
    file[0] = '\0';
    long int X=0;
    while( X < InsertLine)
    {
        char oneLiner[1024];
        if (fgets(oneLiner, 1024, Filef) == NULL)
        {
            strcat(file, "\n");
        }
        else if (fgets(oneLiner, 1024, Filef) != NULL)
        {
            strcat(file, oneLiner);
        }
        X++;
    }

    char oneLiner[4096];
    if (fgets(oneLiner, 4096, Filef) == NULL)
    {
        long int X2;
        while ( X2 <= pos)
        {
            
            strcat(file, " ");
            X2++;
        }

        strcat(file, String);
        fclose(Filef);

        Filef = fopen(fileName, "w");
        fputs(file, Filef);
        fclose(Filef);

        return "The String was inserted!";
    }

    int len = strlen(oneLiner) - 1;
    if (len < pos)
    {
        strncat(file, oneLiner, len);
        for (int i = 1; i <= pos - len; i++)
        {
            strcat(file, " ");
        }
        strcat(file, String);
        strcat(file, "\n");
    }

    else if (len>=pos)
    {
        strncat(file, oneLiner, pos);
        strcat(file, String);
        strcat(file, oneLiner + pos);
    }

   
     char restOfText[2048];
    while(fgets(restOfText, 2048, Filef) != NULL){
       
        strcat(file, restOfText);
    }

    fclose(Filef);

    Filef = fopen(fileName, "w");
    fputs(file, Filef);
    fclose(Filef);

    return "The string was inserted!";
}


char *cat(char *address)//
{
    FILE *file;
    char line[256];

    if (!Existance(address))
        return "The File does not exist!!!";
    file = fopen(address, "r");
    if(file != NULL){}
    else if (file == NULL)
    {
        return ("Sth went Wrong!");
    }

    char *Array = calloc(256,sizeof(char));
    
    while (fgets(line, 256, file))
    {
        strcat(Array, line);
    }

    fclose(file);

    return Array;
}
char *copystr(char *File, int Copyline, int pos, int size, char Jahat)//
{
    FILE *file = fopen(File, "r");
    char line[512];
    if (!Existance( File))
        {return "The File does not exist!!!";}
    char *Array = calloc(512,sizeof(char));
    Array[0] = 0;
    int Line = 1;
    while (fgets(line, 256, file))
    {
        if (Copyline == Line)
        {
            if (Jahat == 'f')
            {
               long  int looper=pos - 1;
                while ( looper < size + pos - 1)
                {
                    char c[2] = {line[looper],'\0'};
                    strcat(Array, c);
                    looper++;
                }
            }
            else if (Jahat == 'b')
            {
                size++;
                long int looper2=pos - size+1;;
                while ( looper2 < pos)
                {

                    char c[2] = {line[looper2],'\0'};
                    strcat(Array, c);
                    looper2++;
                    
                }
                
               // printf("%d",size);
            }
        }
        Line++;
    }
   // printf("%c\n",Jahat);
    const char *output = Array;
    const size_t len = strlen(output) + 1;
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), output, len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
    return "Text successfully copied to clipboard!";
}
char *cutstr(char *File, int Cutline, int pos, int size, char Jahat)
{
    if (!Existance(File))
        return "The File does not exist!";
    copystr(File, Cutline, pos, size, Jahat);
    removestr(File, Cutline, pos, size, Jahat);
    return "Text was  cut to the clipboard!";
}
char *pastestr(char *File, int Pasteline, int pos)
{
    if (!Existance(File))
        return "ERROR! File does not exist!";
    char *output = calloc(128,sizeof(char));
    //output[0] = 0;
    /////////internet///
    OpenClipboard(0);
    output = GetClipboardData(CF_TEXT);
    CloseClipboard();
    /////internet/////////////
    insertstr(File, output, Pasteline, pos);
    return "Text has been pasted!!!";
}
char *grep(char **files, char *pattern, int options)
{
    char *output = calloc(2048,sizeof(char));
    

   long int printIt = 0,count = 0, list = 0;
    
    if (options==0)
    {
        printIt = 1;
        
    }
    else if (options==1)
    {
        count = 1;
        
    }
    else if (options==2)
    {
        list = 1;
        
    }

    
    

    long int filenum = 0,_l=0;
    FILE *fileopen;
    while (files[filenum])
    {

        
            

            fileopen = fopen(files[filenum], "r");

            char *Oneline = calloc(256,sizeof(char));
            
            while (fgets(Oneline, 128, fileopen))
            {

                if (strstr(Oneline, Quotation(pattern)) != NULL)
                {
                    if (printIt>0)
                    {
                        strcat(output, files[filenum]);
                        strcat(output, " :\n//////////////////////\n ");

                        strcat(output, Oneline);
                        strcat(output, " \n ");
                        if (Oneline[strlen(Oneline) - 1] != '\n')
                        {
                            strcat(output, "\n");
                        }
                    }
                    else if (list>0)
                    {
                        strcat(output, files[filenum]);
                        strcat(output, "\n");

                        break;
                    }
                    _l++;
                }
                
            }
       

        filenum++;
    }
    fclose(fileopen);
    if (count>0)
    {
        char *Tedad = calloc(128,sizeof(char));
        sprintf(Tedad, "%d", _l);
        strcat(output, Tedad);
        strcat(output, "\n\n");
    }

    return output;
}
/*char *find(char *address, char *str, int Kalame, int at, int count, int all)
{
    
    if (Kalame)
    {
        FILE *file = fopen(address, "r");
        char *line = calloc(256,8);
        long long int Tool = 0,counter=0;
        int List[2048] = {0};
        
        while (fgets(line, 256, file))

        {
            char *MMA = strtok(line, " ");

            while (MMA != NULL)
            {
                if (!strcmp(MMA, str))
                {
                    List[counter] = Tool + 1;
                    counter++;
                }
                Tool++;

                MMA = strtok(NULL, " ");
            }
        }
        if (count)
        {
            char *output = calloc(256, 1);
            sprintf(output, "%d", counter);
            return output;
        }
        if (counter <= 0)
        {
            return "None";
        }

        else if (at)
        {
            
         if (all)
        {
            char *output = calloc(128 * 16, 1);
            char *X = calloc(128, 1);
            sprintf(X, "%d", List[0]);
            strcat(output, X);
            int i=0;
            while ( i < counter)
            {
                sprintf(X, ", %d", List[i]);
                strcat(output, X);
                i++;
            }
            return output;
        }
       else if (counter < at)
            {
                return "At more than Possible!";
            }
            char *output = calloc(128, 1);
            sprintf(output, "%i", List[at - 1]);
            return output;
        }
        else
        {
            char *output = calloc(128, 1);
            sprintf(output, "%d", List[0]);
            return output;
        }
    }
    if (!Kalame)
    {
        char *data = cat(address);
        int strSize = strlen(str);
        int;
        int List[1024] = {0};
       
        long int firstFound = 0, Tool = 0 , counter = 0;
        if (!StrNew(data, str))
        {
            firstFound = 1;
            counter++;
            List[0] = 0;
        }
        char *MMA = strtok(data, str);

        while (MMA != NULL)
        {
            if (!((MMA[0] == '\n' || MMA[0] == ' ') && strlen(MMA) == 1))
            {
                
                Tool += strlen(MMA);
                List[counter++] = Tool + 1;
                Tool += strSize;
            }
            MMA = strtok(NULL, str);
        }
        // counter--;
        if (firstFound && counter != 1)
           { counter--;}
        if (counter > 1)
            {counter--;}
        if (count)
        {
            char *output = calloc(128, 1);
            sprintf(output, "%d", counter);
            return output;
        }
        else if (counter <= 0)
        {
            return "None!";
        }
        else if (at)
        {
            if (counter < at)
            {
                return "At exeeded!";
            }
            char *output = calloc(128, 1);
            sprintf(output, "%d", List[at - 1] + 1);
            return output;
        }

        else if (all)
        {
            char *output = calloc(256 * 16, 1);
            char *X = calloc(256, 1);
            sprintf(X, "%d", List[0] + 1);
            strcat(output, X);
            int i=1;
            while( i < counter)
            {
                sprintf(X, ", %d", List[i] + 1);
                strcat(output, X);
                i++;
            }
            return output;
        }
        else
        {
            char *output = calloc(256, 1);
            sprintf(output, "%d", List[0] + 1);
            return output;
        }
    }
}
char *replace(char *address, char *str1, char *str2, int at, int all)
{
    long int size1 = strlen(str1);
    if (at)
    {
        int charPos = atoi(find(address, str1, 0, at, 0, 0));
        charPos--;
        printf("%i", charPos);
        char *data = calloc(4096, 1);
        strcpy(data, cat(address));

        long int line = 1, pos = 1, cntr = 0, i = 0;
        while (cntr < charPos)
        {
            pos++;
            if (data[i] == '\n')
            {

                line++;
                pos = 1;
                cntr -= 2;
            }
            cntr++;
            i++;
            
        }
        removestr(address, line, pos, size1, 'f');
        insertstr(address, str2, line, pos);
        if (!all)
            return "Replaced";
    }
    if (!!strcmp(find(address, str1, 0, 0, 0, 0), "No results!"))
    {
        replace(address, str1, str2, 0, 1);
    }
    return "String has been replaced!";
}*/

char * sync(char **Argomanha)
{
    char *Command = Argomanha[0];
    char*PrevCreatefile;
    if (!strcmp(Command, "createfile"))//
    {
        
        char fileAddress[] = "";
        char*Address=Argomanha[2];
        char* _file=Argomanha[1];
       // if(createfilenum>2){if( PrevCreatefile==Argomanha[2]){return "file already exists.";}}
        if (Argomanha[2][0] == '"')
            {
                strcpy(Address, substr(Address,  strlen(Address) - 1));
            } 
            PrevCreatefile=Argomanha[2];
            if (!strcmp(_file, "-file"))
            {
                strcpy(fileAddress, Address);
            }
       
        return (createFile(fileAddress));
    }
    
    else if (!strcmp(Command, "insertstr"))
    {
        
        char *address = calloc(128,sizeof(char));
        int Insertline = 0, pos = 0;
        char *str = calloc(128,sizeof(char));
        char*A=Argomanha[1],B=Argomanha[2],C=Argomanha[3],D=Argomanha[4],E=Argomanha[5],F=Argomanha[6];
        //
      
       for (int i = 1; Argomanha[i + 1] != NULL&&Argomanha[i] != NULL ; i += 2)
        {
            char *Aval = Argomanha[i],Dovom = Argomanha[i + 1];

            Dovom = Quotation(Dovom);

            if (!strcmp(Aval, "-file"))
            {
                strcpy(address, Dovom);
            }
            else if (!strcmp(Aval, "-str"))
            {
                strcpy(str, Dovom);
            }
            else if (!strcmp(Aval, "-pos"))
            {
                sscanf(Dovom, "%i:%i", &Insertline, &pos);
            }
        }
        return insertstr(AddressComplete(address), str, Insertline, pos+1);
    }
    else if (!strcmp(Command, "cat"))
    {
        
        char *address = malloc(128);
        //
        char *Aval = Argomanha[1];
            char *Dovom = Argomanha[2];
            if (!strcmp(Aval, "-file"))
            {
                strcpy(address, Dovom);
            }

            Dovom = Quotation(Dovom);

            if (!strcmp(Aval, "-file"))
            {
                strcpy(address, Dovom);
            }
        
        return cat(AddressComplete(address));
    }
    else if (!strcmp(Command, "removestr"))
    {

        
        char *address = malloc(128);
        int removeline = 0, pos = 0;
        long long size = 0;
        char Jahat = 'a';

        //
        int i = 1;
       
        while ( Argomanha[i] != NULL && Argomanha[i + 1] != NULL)
        {
            char *Aval = Argomanha[i];
            char *Dovom = Argomanha[i + 1];

            Dovom = Quotation(Dovom);

            if (!strcmp(Aval, "-file"))
            {

                strcpy(address, Dovom);
            }
            else if (!strcmp(Aval, "-size"))
            {
                size = atoll(Dovom);
            }
            else if (!strcmp(Aval, "-pos"))
            {
                sscanf(Dovom, "%i:%i", &removeline, &pos);
            }
           
            i+=2;
        }
         Jahat=Argomanha[i][1];
       
        return removestr(AddressComplete(address), removeline, pos+1, size, Jahat);
    }
    else if (!strcmp(Command, "copystr"))
    {
        
        char *address = malloc(256);
        int Copyline = 0, pos = 0;
        long long size = 0;
        char A='a';
        char Jahat = A;

        //
        int i = 1;

        while (Argomanha[i + 1] != NULL && Argomanha[i] != NULL  )
        {
            char *Aval = Argomanha[i];
            char *Dovom = Argomanha[i + 1];

            Dovom = Quotation(Dovom);

            if (!strcmp(Aval, "-file"))
            {

                strcpy(address, Dovom);
            }
            else if (!strcmp(Aval, "-size"))
            {
                size = atoi(Dovom);
            }
            else if (!strcmp(Aval, "-pos"))
            {
                sscanf(Dovom, "%i:%i", &Copyline, &pos);
            }
           
             i += 2;
        }

        if (!strcmp(Argomanha[i], "-b"))
        {
            Jahat = 'b';
        }
       else if (!strcmp(Argomanha[i], "-f"))
        {
            Jahat = 'f';
        }

        return copystr(AddressComplete(address), Copyline, pos+1, size, Jahat);
    }
else if (!strcmp(Command, "cutstr"))
    {
        
        char *address = malloc(128);
        int Cutline = 0, pos = 0, size = 0;
        char p='p';
        char Jahat = p;
        //
        int i = 1;
        

        while ( Argomanha[i] != NULL && Argomanha[i + 1] != NULL)
        {
            char *Aval = Argomanha[i];
            char *Dovom = Argomanha[i + 1];

            Dovom = Quotation(Dovom);

            if (!strcmp(Aval, "-file"))
            {
                strcpy(address, Dovom);
            }
            if (!strcmp(Aval, "-size"))
            {
                sscanf(Dovom, "%i", &size);
            }
            else if (!strcmp(Aval, "-pos"))
            {
                sscanf(Dovom, "%d:%d", &Cutline, &pos);
            }
            i += 2;
        }
        char b='b',f='f';
        if (!strcmp(Argomanha[i], "-b"))
        {
            Jahat = b;
        }
        if (!strcmp(Argomanha[i], "-f"))
        {
            Jahat = 'f';
        }
        return cutstr(AddressComplete(address), Cutline, pos, size+1, Jahat);
    }
    else if (!strcmp(Command, "pastestr"))
    {
        
        char *address = malloc(128);
        long long int pasteline = 0, pos = 0;
        //
        long long int i=1;
        while (   Argomanha[i + 1] != NULL&& Argomanha[i] != NULL)
        {
            char *Aval = Argomanha[i];
            char *Dovom = Argomanha[i + 1];

            Dovom = Quotation(Dovom);

            if (!strcmp(Aval, "-file"))
            {
                strcpy(address, Dovom);
            }
            else if (!strcmp(Aval, "-pos"))
            {
                sscanf(Dovom, "%d:%d", &pasteline, &pos);
            }
            i += 2;
        }
        return (pastestr(AddressComplete(address), pasteline, pos+1));
    }
 
    else if (!strcmp(Command, "grep"))
    {

        
        char *inp = calloc(256,sizeof(char));
        int _ds = 0;
        char **List = calloc(64 , sizeof(char *));
        //
        int Tedadfile = 0;
        if (!strcmp("-str", Argomanha[1]))
        {
            strcpy(inp, Argomanha[2]);
            int i = 4;
            while (Argomanha[i] != NULL)
            {
                *(List + Tedadfile) = AddressComplete(Quotation(Argomanha[i]));
                Tedadfile++;
                i++;
            }
        }
        else
        {
            if (!strcmp("-c", Argomanha[1]))
            {
                _ds = 1;
            }
            else if (!strcmp("-l", Argomanha[1]))
            {
                _ds = 2;
            }

            strcpy(inp, Argomanha[3]);
            int i = 5;
            while (Argomanha[i] != NULL)
            {
                *(List + Tedadfile) = AddressComplete(Quotation(Argomanha[i]));
                Tedadfile++;
                i++;
            }
        }
        *(List + Tedadfile) = NULL;
        

        
        return grep(List, inp, _ds);
    }
    /*else if (!strcmp(Command, "find"))
    {
        
        char *address = calloc(128,1);
        char *str = calloc(128,1);
        int byword = 0, at = 0, count = 0, all = 0;

        
        int i=1;
        while (Argomanha[i] != NULL && Argomanha[i + 1] != NULL)
        {
            char *Aval = Argomanha[i];
            char *Dovom = Argomanha[i + 1];

            Dovom = Quotation(Dovom);

            if (!strcmp(Aval, "-file"))
            {
                strcpy(address, Dovom);
            }
            if (!strcmp(Aval, "-str"))
            {
                strcpy(str, Dovom);
            }
            i+=2;
        }
         i = 5;
        while (Argomanha[i] != NULL)
        {
            // printf("-{%s}-\n", Argomanha[i]);
            if (!strcmp(Argomanha[i], "-count"))
            {
                count = 1;
            }
            if (!strcmp(Argomanha[i], "-at"))
            {
                sscanf(Argomanha[i + 1], "%i", &at);
                i++;
            }
             if (!strcmp(Argomanha[i], "-byword"))
            {
                byword = 1;
            }
            if (!strcmp(Argomanha[i], "-all"))
            {
                all = 1;
            }


            i++;
        }
        return find(AddressComplete(address), str, byword, at, count, all);
    }
        else if (!strcmp(Command, "replace"))
    {
        
        char *address = malloc(128);
        char *str1 = malloc(128);
        char *str2 = malloc(128);
        int at = 0, all = 0;
        int i=1;
        while ( Argomanha[i] != NULL && Argomanha[i + 1] != NULL)
        {
            char *Aval = Argomanha[i];
            char *Dovom = Argomanha[i + 1];

            Dovom = Quotation(Dovom);

            if (!strcmp(Aval, "-file"))
            {
                strcpy(address, Dovom);
            }
            if (!strcmp(Aval, "-str1"))
            {
                strcpy(str1, Dovom);
            }
            if (!strcmp(Aval, "-str2"))
            {
                strcpy(str2, Dovom);
            }
            i += 2;
        }
         i = 5;
        while (Argomanha[i] != NULL)
        {

            if (!strcmp(Argomanha[i], "-at"))
            {
                sscanf(Argomanha[i + 1], "%d", &at);
                i++;
            }
            else if (!strcmp(Argomanha[i], "-all"))
            {
                all = 1;
            }

            i++;
        }
        return replace(AddressComplete(address), str1, str2, at, all);
    }*/
    
}

int main()
{
    Folder(rootAddress);
    
    while (1)
    {
        
        char* line = malloc(1024);
        gets(line);
        
        char* *Argoman = INP_ARG(line);
        char* put = malloc(1024);
        put = sync(Argoman);
        puts(put);
    }
} 
char **INP_ARG(char *Line)
{
    char **list;
    list = calloc(128 , sizeof(char *));
    long long int len = strlen(Line);
    char *CurrentArg = calloc(len , 16);

    int InsideChar = 0, currNumOfArgs = 0,Quotations = 0,i=0;
    
    while (i < len)
    {
        char currChar = Line[i];
        if (currNumOfArgs == 0)
        {
            if (currChar == ' ')
            {
                *(CurrentArg + InsideChar) = NULL;
                *(list + currNumOfArgs) = CurrentArg;
                CurrentArg = calloc(len,16);
                currNumOfArgs++;
                InsideChar = 0;
            }
            else if(currChar != ' ')
            {
                *(CurrentArg + InsideChar) = currChar;
                InsideChar++;
            }
        }
        else if(currNumOfArgs != 0)
        {

            if (currChar == ' ' && (!(Quotations % 2)))
            {
                *(CurrentArg + InsideChar) = NULL;
                *(list + currNumOfArgs) = CurrentArg;
                CurrentArg = calloc(len,16);
                InsideChar = 0;
                currNumOfArgs++;

                Quotations = 0;
                
            }
            else
            {
                if (currChar == '"' && Line[i - 1] != '\\')
                {
                    *(CurrentArg + InsideChar) = '\"';
                    Quotations++;
                }
                else
                {
                    *(CurrentArg + InsideChar) = currChar;
                }

                InsideChar++;
            }
        }
        i++;
    }
    if (strlen(CurrentArg) > 0)
    {
        *(CurrentArg + InsideChar) = NULL;
        *(list + currNumOfArgs) = CurrentArg;
         currNumOfArgs++;
        InsideChar = 0;
        CurrentArg = calloc(len,16);
       
    }
    *(list + currNumOfArgs) = NULL;
    free(CurrentArg);
    return list;
}
