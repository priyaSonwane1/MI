// <------------------------------------------------------------CVFS (Customise Virtual File System)----------------------------------------------------------------->

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
// #include<io.h>

#define MAXINODE 50                     // Max file will be 50
 
#define READ 1
#define WRITE 2

#define MAXFILESIZE 2048                // maximum file size will be 2048 (1024 + 1024)

#define REGULAR 1                       // Example txt file
#define SPECIAL 2                       // Example folder

//  lseek function
#define START 0
#define CURRENT 1
#define END 2

/*
--------------------------------------------------------------------------------------------------------------------------------------------------------------------

    The HardDisk gets divided into 4 parts
    1>  BOOT Block (BB) 
        how to start OS , this syntax is written in BOOT Block (OR) The BOOT Block provides instructions for starting the OS.
    2>  Super Block (SB)
        On Super Block all the whole information persent hardisk is in record form (OR) On Super Block, all the data on the hard disk is saved in record form.
    3>  Disk Incode List Block (DILB)
        All the iNode are connected in the form of LinkedList
    4>  Data Block (DB)
        The acutal data of inside the file is present in Data Block (OR) The file's actual data is present.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------
My project is virtual project ,So In is project , we not used the BOOT Block because the boot block is used to start the OS , but your OS is already started to start
the project (After starting the OS this project will start)
--------------------------------------------------------------------------------------------------------------------------------------------------------------------
Data Block seprate is not avaiable , but indirectly it is avaiable [create file ()]
--------------------------------------------------------------------------------------------------------------------------------------------------------------------

*/ 
typedef struct superblock       // Size of superblock is 8 bytes
{
    int TotalInodes ;
    int FreeInode ;
}SUPERBLOCK , *PSUPERBLOCK ;

typedef struct inode        // Size of inode is 94 bytes (7 int = 28 , 2 pointer = 16 , 50 char = 50 == 94 )
{
    char FileName[50];          // The name of file                       (for example Demo.txt)
    int InodeNumber ;           // the file gets an iNode Number          (for example iNode Number is 11)
    int FileSize ;              // The total file size gets allocated     (for example we buy a book  then the file toatl pages are 200 similary the total file size is 13 byte)
    int FileActualSize ;        // The size of written data into the file (for example we written "Jay Ganesh..." into the then the file size is 13 byte)
    int FileType ;              // File type is 1 i.e is REGULAR          (#define REGULAR 1)
    char *Buffer ;              // it points to the address of actual data written i.e, "Jay Ganesh..."
    int LinkCount ;             // 1
    int ReferenceCount ;        // 1
    int permission ;            // 777                                    (read , Write , Execute)
    struct inode *next ;
}INODE , *PINODE , **PPINODE ;

typedef struct filetable
{
    int readoffset ;
    int writeoffset ;
    int count ;                 // it is always 1
    int mode ;                  // In which mode we want to open the file READ(1) , WRITE(2) , READ+WRITE(3)
    PINODE ptrinode ;
}FILETABLE , *PFILETABLE ;

typedef struct ufdt
{
    PFILETABLE ptrfiletable ;
}UFDT ;

UFDT UFDTArr[50] ;              // Array of structure
SUPERBLOCK SUPERBLOCKobj ;
PINODE head = NULL ;

void man(char *name)            // man : manual
{
    if(name == NULL) return ;

    if(strcmp(name,"create") == 0)                                              // strcmp : string compare
    {
        printf("Description : used to create new regular file\n");
        printf("Usage : create File_name Permission\n");
    }
    else if(strcmp(name,"read") == 0)
    {
        printf("Description : used to read data from regular file\n");
        printf("Usage : read File_name No_Of_Bytes_To_Read\n");
    }
    else if(strcmp(name,"write") == 0)
    {
        printf("Description : used to write into regular file\n");
        printf("Usage : write File_name\n After this enter the data that we want to write\n");
    }
    else if(strcmp(name,"ls") == 0)
    {
        printf("Description : used to list all information of file\n");
        printf("Usage : ls\n");
    }
    else if(strcmp(name,"stat") == 0)
    {
        printf("Description : used to display information of file\n");
        printf("Usage : stat File_name \n");
    }
    else if(strcmp(name,"fstat") == 0)
    {
        printf("Description : used to display information of file\n");
        printf("Usage : stat File_Descriptor\n");
    }
    else if(strcmp(name,"truncate") == 0)
    {
        printf("Description : used to remove data from file\n");
        printf("Usage : truncate File_name \n");
    }
    else if(strcmp(name,"open") == 0)
    {
        printf("Description : used to open existing file\n");
        printf("Usage : open File_name mode\n");
    }
    else if(strcmp(name,"close") == 0)
    {
        printf("Description : used to close opened file\n");
        printf("Usage : close File_name\n");
    }
    else if(strcmp(name,"closeall") == 0)
    {
        printf("Description : used to close all opned file\n");
        printf("Usage : closeall\n");
    }
    else if(strcmp(name,"lseek") == 0)
    {
        printf("Description : used to change file offset\n");
        printf("Usage : lseek File_Name ChangeInOffset StartPoint\n");
    }
    else if(strcmp(name,"rm") == 0)
    {
        printf("Description : used to delete the file\n");
        printf("Usage : rm File_Name\n");
    }
    else
    {
        printf("ERROR : No manual entry available.\n");
    }
}

void DisplayHelp()                      // To guide the user we written the display 
{
    printf("ls : To List out all files\n");
    printf("cls : To clear console\n");
    printf("open : To open the file\n");
    printf("close : To close the file\n");
    printf("closeall : To close all opened files\n");
    printf("read : To Read the contents into file\n");
    printf("write : To Write contents into file\n");
    printf("exit : To Terminate file system\n");
    printf("stat : To Display information of files using name\n");
    printf("fstat : To Display information of files using file descriptor\n");   
    printf("truncate : To Remove all data from file\n");
    printf("rm : To Delet the file\n");
}

int GetFDFromName(char *name)
{
    int i = 0 ;

    while(i < 50 )
    {
        if(UFDTArr[i].ptrfiletable != NULL)
            if(strcmp((UFDTArr[i].ptrfiletable->ptrinode->FileName),name)==0)
                break ;
        i++ ;
    }

    if(i == 50)     return -1 ;
    else        return i ;
}

PINODE GET_Inode(char * name)
{
    PINODE temp = head ;
    int i = 0 ;

    if(name == NULL)
        return NULL ;

    while(temp != NULL)
    {
        if(strcmp(name,temp->FileName)== 0)
            break ;
        temp = temp->next ;
    }
    return temp ;
}

//  CreateDILB() : It will create LinkedList of iNOdes
void CreateDILB()                    
{
    int i = 1 ;
    PINODE newn = NULL ;
    PINODE temp = head ;

    while(i <= MAXINODE)
    {
        newn = (PINODE)malloc(sizeof(INODE));

        newn->LinkCount = 0 ;
        newn->ReferenceCount = 0 ;
        newn->FileType = 0 ;
        newn->FileSize = 0 ;

        newn->Buffer = NULL ;
        newn->next = NULL ;

        newn->InodeNumber = i ;

        if(temp == NULL)
        {
            head = newn ;
            temp = head ;
        }
        else
        {
            temp->next = newn ;
            temp = temp->next ;
        }
        i++ ;
    }
    printf("DILB created successfully\n");
}

void InitisliseSuperBlock()
{
    int i = 0 ;
    while(i < MAXINODE)
    {
        UFDTArr[i].ptrfiletable = NULL ;
        i++ ;
    }

    SUPERBLOCKobj.TotalInodes = MAXINODE ;                              
    SUPERBLOCKobj.FreeInode = MAXINODE ;
}

int CreateFile(char *name , int permission)
{
    int i = 3 ;             
    PINODE temp = head ;

    if((name == NULL) || (permission == 0) || (permission > 3))
        return -1 ;                                             // Error code

    if(SUPERBLOCKobj.FreeInode == 0)
        return -2 ;                                             // Error code   

    (SUPERBLOCKobj.FreeInode)--;

    if(GET_Inode(name) != NULL)
        return -3 ;                                             // Error code                     
         
    while(temp != NULL)
    {
        if(temp->FileType == 0)                                // if filetype is 1 then the inode is used if fileType is 0 then the inode is unused (#define REGULAR 1 , #define SPECIAL 2 )
            break ;
        temp = temp->next ;
    }

    while(i<50)
    {
        if(UFDTArr[i].ptrfiletable == NULL)
            break ;
        i++ ;
    }

    UFDTArr[i].ptrfiletable = (PFILETABLE)malloc(sizeof(FILETABLE));

    UFDTArr[i].ptrfiletable->count = 1 ;
    UFDTArr[i].ptrfiletable->mode = permission ;
    UFDTArr[i].ptrfiletable->readoffset = 0 ;
    UFDTArr[i].ptrfiletable->writeoffset = 0 ;

    UFDTArr[i].ptrfiletable->ptrinode = temp ;

    strcpy(UFDTArr[i].ptrfiletable->ptrinode->FileName,name);
    UFDTArr[i].ptrfiletable->ptrinode->FileType = REGULAR ;
    UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount = 1 ;
    UFDTArr[i].ptrfiletable->ptrinode->LinkCount = 1 ;
    UFDTArr[i].ptrfiletable->ptrinode->FileSize = MAXFILESIZE ;
    UFDTArr[i].ptrfiletable->ptrinode->FileActualSize = 0 ;
    UFDTArr[i].ptrfiletable->ptrinode->permission = permission ;
    UFDTArr[i].ptrfiletable->ptrinode->Buffer = (char *)malloc(MAXFILESIZE);        //[ (Gives the memory(RAM)) To write the acutall data into file ]  ---> DATA BLOCK (DB) 

    return i ;
}

// rm_File("Demo.txt")
int rm_File(char * name)
{
    int fd = 0 ;

    fd = GetFDFromName(name);
    if(fd == -1)
        return -1 ;

    (UFDTArr[fd].ptrfiletable->ptrinode->LinkCount)-- ;

    if(UFDTArr[fd].ptrfiletable->ptrinode->LinkCount == 0)
    {
        UFDTArr[fd].ptrfiletable->ptrinode->FileType = 0 ;
        // free(UFDTArr[fd].ptrfiletable->ptrinode->Buffer);
        free(UFDTArr[fd].ptrfiletable);
    }

    UFDTArr[fd].ptrfiletable = NULL ;
    (SUPERBLOCKobj.FreeInode)++ ;
}

int ReadFile(int fd , char *arr , int iSize)
{
    int read_size = 0 ;

    if(UFDTArr[fd].ptrfiletable == NULL)    return -1 ;

    if(UFDTArr[fd].ptrfiletable->mode != READ && UFDTArr[fd].ptrfiletable->mode != READ + WRITE)  return -2 ;

    if(UFDTArr[fd].ptrfiletable->ptrinode->permission != READ &&  UFDTArr[fd].ptrfiletable->ptrinode->permission != READ + WRITE) return -2;

    if(UFDTArr[fd].ptrfiletable->readoffset == UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize)  return -3 ;

    if(UFDTArr[fd].ptrfiletable->ptrinode->FileType != REGULAR) return -4;

    read_size = (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) - (UFDTArr[fd].ptrfiletable->readoffset);
    if(read_size < iSize)
    {
        strncpy(arr,(UFDTArr[fd].ptrfiletable->ptrinode->Buffer) + (UFDTArr[fd].ptrfiletable->readoffset),read_size);

        UFDTArr[fd].ptrfiletable->readoffset = UFDTArr[fd].ptrfiletable->readoffset + read_size ;
    }
    else
    {
        strncpy(arr,(UFDTArr[fd].ptrfiletable->ptrinode->Buffer) + (UFDTArr[fd].ptrfiletable->readoffset),iSize);

        (UFDTArr[fd].ptrfiletable->readoffset) = (UFDTArr[fd].ptrfiletable->readoffset) + iSize ;
    }

    return iSize ;
}

int WriteFile(int fd , char *arr , int iSize)
{
    if(((UFDTArr[fd].ptrfiletable->mode) != WRITE) && ((UFDTArr[fd].ptrfiletable->mode) != READ+WRITE))return -1;

    if(((UFDTArr[fd].ptrfiletable->ptrinode->permission) != WRITE) && ((UFDTArr[fd].ptrfiletable->ptrinode->permission) != READ+WRITE)) return -1;

    if((UFDTArr[fd].ptrfiletable->writeoffset) == MAXFILESIZE ) return -2 ;

    if((UFDTArr[fd].ptrfiletable->ptrinode->FileType) != REGULAR ) return -3 ;

    strncpy((UFDTArr[fd].ptrfiletable->ptrinode->Buffer) + (UFDTArr[fd].ptrfiletable->writeoffset),arr,iSize);

    (UFDTArr[fd].ptrfiletable->writeoffset) = (UFDTArr[fd].ptrfiletable->writeoffset) + iSize ;

    (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) = (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) + iSize ;

    return iSize  ;
}

int OpenFile(char *name , int mode)
{
    int i = 0 ;
    PINODE temp = NULL ;

    if(name == NULL || mode <= 0)
        return -1;

    temp = GET_Inode(name);
    if(temp == NULL)
        return -2;

    if(temp->permission < mode)
        return -3;

    while(i<50)
    {
        if(UFDTArr[i].ptrfiletable == NULL)
            break ;
        i++ ;
    }

    UFDTArr[i].ptrfiletable = (PFILETABLE)malloc(sizeof(FILETABLE));
    if(UFDTArr[i].ptrfiletable == NULL)         return -1;
    UFDTArr[i].ptrfiletable->count = 1;
    UFDTArr[i].ptrfiletable->mode = mode ;
    if(mode == READ + WRITE)
    {
        UFDTArr[i].ptrfiletable->readoffset = 0 ;
        UFDTArr[i].ptrfiletable->writeoffset = 0 ;
    }
    else if(mode == READ)
    {
        UFDTArr[i].ptrfiletable->readoffset = 0 ;
    }
    else if(mode == WRITE)
    {
        UFDTArr[i].ptrfiletable->writeoffset = 0 ;
    }
    UFDTArr[i].ptrfiletable->ptrinode = temp ;
    (UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount)++ ;

    return i ;
}

void CloseFileByName(int fd)
{
    UFDTArr[fd].ptrfiletable->readoffset = 0 ;
    UFDTArr[fd].ptrfiletable->writeoffset = 0 ;
    (UFDTArr[fd].ptrfiletable->ptrinode->ReferenceCount)-- ;
}

int CloseFileByName(char *name)
{
    int i = 0 ;
    i = GetFDFromName(name);
    if(i == -1)
        return -1;

    UFDTArr[i].ptrfiletable->readoffset = 0 ;
    UFDTArr[i].ptrfiletable->writeoffset = 0 ;
    (UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount)-- ;

    return 0;
}

void CloseAllFile()
{
    int i = 0 ;
    while( i< 50)
    {
        if(UFDTArr[i].ptrfiletable != NULL)
        {
            UFDTArr[i].ptrfiletable->readoffset = 0 ;
            UFDTArr[i].ptrfiletable->writeoffset = 0 ;
            (UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount)-- ;
            break;
        }
        i++;
    }
}

int LseekFile(int fd , int size , int from)
{
    if((fd<0) || (from > 2))       return -1;
    if(UFDTArr[fd].ptrfiletable == NULL)     return -1;

    if((UFDTArr[fd].ptrfiletable->mode == READ) || (UFDTArr[fd].ptrfiletable->mode == READ+WRITE))
    {
        if(from == CURRENT)
        {
            if(((UFDTArr[fd].ptrfiletable->readoffset) + size) > UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize)      return -1;
            if(((UFDTArr[fd].ptrfiletable->readoffset) + size) < 0)      return -1;
            (UFDTArr[fd].ptrfiletable->readoffset) = (UFDTArr[fd].ptrfiletable->readoffset) + size ;
        }
        else if(from == START)
        {
            if(size > (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize))     return -1;
            if(size < 0)        return -1;
            (UFDTArr[fd].ptrfiletable->readoffset) = size ;
        }
        else if(from == END)
        {
            if(size > (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) + size > MAXFILESIZE)     return -1;
            if(((UFDTArr[fd].ptrfiletable->readoffset) + size) < 0)      return -1;
            (UFDTArr[fd].ptrfiletable->readoffset) = (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) + size ;
        }
    }
    else if(UFDTArr[fd].ptrfiletable->mode == WRITE)
    {
        if(from == CURRENT)
        {
            if(((UFDTArr[fd].ptrfiletable->writeoffset) + size) > MAXFILESIZE)  return -1;
            if(((UFDTArr[fd].ptrfiletable->writeoffset) + size) < 0)        return -1;
            if(((UFDTArr[fd].ptrfiletable->writeoffset) + size) > (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize))
            (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) = (UFDTArr[fd].ptrfiletable->writeoffset) + size;
            (UFDTArr[fd].ptrfiletable->writeoffset) = (UFDTArr[fd].ptrfiletable->writeoffset) + size ;
        }
        else if(from == START)
        {
            if(size > MAXFILESIZE) return -1;
            if(size < 0)    return -1;
            if(size > (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize))
                    (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) = size ;
            (UFDTArr[fd].ptrfiletable->writeoffset) = size ;
        }
        else if(from == END)
        {
            if((UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) + size > MAXFILESIZE)       return -1;
            if(((UFDTArr[fd].ptrfiletable->writeoffset) + size) < 0 ) return -1;
            (UFDTArr[fd].ptrfiletable->writeoffset) = (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) + size;
         }
    }
}

void ls_file()
{
    int i = 0 ;
    PINODE temp = head ;

    if(SUPERBLOCKobj.FreeInode == MAXINODE)
    {
        printf("Error : There are no files\n");
        return;
    }

    printf("\nFile Name\tInode number\tFile size\tLink count\n");
    printf("-----------------------------------------------------------\n");
    while(temp != NULL)
    {
        if(temp->FileType != 0)
        {
            printf("%s\t\t%d\t\t%d\t\t%d\n",temp->FileName,temp->InodeNumber,temp->FileActualSize,temp->LinkCount);
        }
        temp = temp->next ;
    }
    printf("-----------------------------------------------------------\n");
}

int fstat_file(int fd)
{
    PINODE temp = head ;
    int i = 0 ;

    if(fd < 0)      return -1;

    if(UFDTArr[fd].ptrfiletable == NULL)        return -2;

    temp = UFDTArr[fd].ptrfiletable->ptrinode ;

    printf("\n----------------Statistical information about file---------------\n");
    printf("File name : %s\n",temp->FileName);
    printf("Inode Number %d\n",temp->InodeNumber);
    printf("File size : %d\n",temp->FileSize);
    printf("Actual File size : %d\n",temp->FileActualSize);
    printf("Link count : %d\n",temp->LinkCount);
    printf("Reference count : %d\n",temp->ReferenceCount);

    if(temp->permission == 1)
            printf("File Permission : Read Only\n");
    else if(temp->permission == 2)
            printf("File Permission : Write\n");
    else if(temp->permission == 3)
            printf("File Permission : Read & Write\n");
    printf("----------------------------------------------------------------\n\n");

    return 0;
}

int stat_file(char *name)
{
    PINODE temp = head ;
    int i = 0 ;

    if(name == NULL)    return -1;

    while(temp != NULL)
    {
        if(strcmp(name,temp->FileName) == 0)
                break ;
        temp = temp->next ;
    }

    if(temp == NULL)        return -2;

    printf("\n----------------Statistical information about file---------------\n");
    printf("File name : %s\n",temp->FileName);
    printf("Inode Number %d\n",temp->InodeNumber);
    printf("File size : %d\n",temp->FileSize);
    printf("Actual File size : %d\n",temp->FileActualSize);
    printf("Link count : %d\n",temp->LinkCount);
    printf("Reference count : %d\n",temp->ReferenceCount);

    if(temp->permission == 1)
            printf("File Permission : Read Only\n");
    else if(temp->permission == 2)
            printf("File Permission : Write\n");
    else if(temp->permission == 3)
            printf("File Permission : Read & Write\n");
    printf("----------------------------------------------------------------\n\n");

    return 0 ;
}

int truncate_File(char *name)
{
    int fd = GetFDFromName(name);
    if(fd == -1)
            return -1;

    memset(UFDTArr[fd].ptrfiletable->ptrinode->Buffer,0,1024);
    UFDTArr[fd].ptrfiletable->readoffset = 0 ;
    UFDTArr[fd].ptrfiletable->writeoffset = 0 ;
    UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    char *ptr = NULL ;
    int ret = 0 , fd = 0 , count = 0 ;

    //   2D Array   , 1D Array , 1D Array
    char command[4][80],str[80],arr[1024];
    // str[80] is used to take input(Command) from the user. and break into munltipal parts

    //  This two function is directly called without any condition Because this functions set's the Data Structure
    InitisliseSuperBlock();
    CreateDILB();

    while(1)                        // uncondtional loop
    {
        fflush(stdin);              // flush standard input device buffer
        strcpy(str,"");             

        printf("\n VFS : >");

        fgets(str,80,stdin);       //scanf("%[^'\n']s",str);

        /*
            sscanf mean accepting input only in form of string i.e, sscanf(stringscanf) and divides into token's
            then get the tokens in sscanf function.
            To store the token we created coommand[4][80] Array .(4 Rows and 80 coloums) where 80 is ,at a time 80 char we can write in one coloum

            Count is used to store the value that how much token is generated
        */ 
        count = sscanf(str,"%s %s %s",command[0],command[1],command[2],command[3]);

        if(count == 1)
        {
            if(strcmp(command[0],"ls") == 0)        // strcmp : string compare
            {
                ls_file();
            }
            else if(strcmp(command[0],"closeall") == 0)
            {
                CloseAllFile();
                printf("All files closed Successfully\n");
                continue;
            }
            else if(strcmp(command[0],"cls") == 0)
            {
                system("cls");
                continue;
            }
            else if(strcmp(command[0],"help") == 0)
            {
                DisplayHelp();
                continue;
            }
            else if(strcmp(command[0],"exit") == 0)
            {
                printf("Terminating the Virtual File System\n");
                break;
            }
            else
            {
                printf("\nERROR : Command not found !!!\n");
                continue;
            }
        }
        else if(count == 2)
        {
            if(strcmp(command[0],"stat") == 0)
            {
                ret = stat_file(command[1]);
                if(ret == -1)
                        printf("ERROR : Incorrect parameters\n");
                if(ret == -2)
                        printf("ERROR : There is no such file\n");
                continue;
            }
            else if(strcmp(command[0],"fstat") == 0)
            {
                ret = fstat_file(atoi(command[1]));                                 // atoi ( ASCII to Integer)
                if(ret == -1)
                        printf("ERROR : Incorrect parameters\n");
                if(ret == -2)
                        printf("ERROR : There is no such file\n");
                continue;
            }
            else if(strcmp(command[0],"close") == 0)
            {
                ret = CloseFileByName(command[1]);
                if(ret == -1)
                        printf("ERROR : There is no such file\n");
                continue;
            }
            else if(strcmp(command[0],"rm") == 0)
            {
                ret = rm_File(command[1]);
                if(ret == -1)
                        printf("ERROR : There is no such file\n");
                continue;
            }
            else if(strcmp(command[0],"man") == 0)
            {
                man(command[1]);
            }
            else if(strcmp(command[0],"write") == 0)
            {
                fd = GetFDFromName(command[1]);
                if(fd == -1)
                {
                    printf("ERROR : Incorrect parameters\n");
                    continue;
                }
                printf("Enter the data :\n");
                scanf("%[^\n]",arr);

                ret = strlen(arr);
                if(ret == 0)
                {
                    printf("ERROR : Incorrect parameters\n");
                    continue;
                }
                ret = WriteFile(fd,arr,ret);
                if(ret == -1)
                    printf("ERROR : Permission denied\n");
                if(ret == -2)
                    printf("ERROR : There is no sufficient memory to write\n");
                if(ret == -3)
                    printf("ERROR : It is not regular file\n");
            }
            else if(strcmp(command[0],"truncate") == 0)
            {
                ret = truncate_File(command[1]);
                if(ret == -1)
                        printf("ERROR : Incorrect parameters\n");
            }
            else
            {
                printf("\nERROR : Command not found !!!\n");
                continue;
            }      
        }
        else if(count == 3)
        {
            if(strcmp(command[0],"create") == 0)
            {
                ret = CreateFile(command[1],atoi(command[2]));
                if(ret >= 0)
                        printf("File is successfully created with file descriptor : %d\n",ret);
                if(ret == -1)
                        printf("ERROR : Incorrect parameters\n");
                if(ret == -2)
                        printf("ERROR : There is no inodes\n");
                if(ret == -3)
                        printf("ERROR : File already exist\n");
                if(ret == -4)
                        printf("ERROR : Memory allocation failure\n");
                continue;
            }
            else if(strcmp(command[0],"open") == 0)
            {
                ret = OpenFile(command[1],atoi(command[2]));
                if(ret >= 0)
                        printf("File is successfully opened with file descriptor : %d\n",ret);
                if(ret == -1)
                        printf("ERROR : Incorrect parameters\n");
                if(ret == -2)
                        printf("ERROR : File not present\n");
                if(ret == -3)
                        printf("ERROR : Permission denied\n");
                continue;
            }
            else if(strcmp(command[0],"read") == 0)
            {
                fd = GetFDFromName(command[1]);
                if(fd == -1)
                {
                    printf("ERROR : Incorrect parameters\n");
                    continue;
                }
                ptr = (char *)malloc(sizeof(atoi(command[2]))+1);
                if(ptr == NULL)
                {
                    printf("ERROR : Memory allocation failure\n");
                    continue;
                }
                ret = ReadFile(fd,ptr,atoi(command[2]));
                if(ret == -1)
                        printf("ERROR : File not existing\n");
                if(ret == -2)
                        printf("ERROR : Permission denied\n");
                if(ret == -3)
                        printf("ERROR : Reached at end of file\n");
                if(ret == -4)
                        printf("ERROR : It is not regular file\n");
                if(ret == 0)
                        printf("ERROR : File empty\n");
                if(ret > 0)
                {
                    write(2,ptr,ret);
                }
                continue;
            }
            else
            {
                printf("\nERROR : Command not found!!!\n");
                continue;
            }
        }
        else if(count == 4)
        {
            if(strcmp(command[0],"lssek") == 0)
            {
                fd = GetFDFromName(command[1]);
                if(fd == -1)
                {
                    printf("Error : Incorrect parameter\n");
                    continue;
                }
                ret = LseekFile(fd,atoi(command[2]),atoi(command[3]));
                if(ret == -1)
                {
                    printf("ERROR : Unable to perform lseek\n");
                }
            }
            else
            {
                printf("\nERROR : Command not found!!!\n");
                continue;
            }
        }
        else
        {
            printf("\nERROR : Command not found !!!\n");
            continue;
        }
    }
    return 0 ;
}

/*
----------------------------------------------------------------------------------------------------------------------------------------------------------------------

    OUTPUT

    DILB created successfully

    VFS : >create MI.txt 3
    File is successfully created with file descriptor : 0

    VFS : >ls

    File Name       Inode number    File size       Link count
    -----------------------------------------------------------
    MI.txt          1               0               1
    -----------------------------------------------------------

    VFS : >exit
    Terminating the Virtual File System

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

*/