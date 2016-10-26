#include<stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

#define FILE_NAME "emp.DAT"
#define TEMP_FILE_NAME "temp.DAT"

COORD coord = {0,0}; 

void gotoxy(int x,int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void moveLocation(int x, int y){
	int defaultX = 30;
	int defaultY = 10;
	gotoxy(defaultX + x, defaultY + y);
}

int getChoice(){
	system("cls");
	moveLocation(0,0);
    printf("1. Add Record");
    moveLocation(0,2);
    printf("2. List Records");
    moveLocation(0,4);
    printf("3. Modify Records");
    moveLocation(0,6);
    printf("4. Delete Records");
    moveLocation(0,8);
    printf("5. Exit");
    moveLocation(0,10);
    printf("Your Choice: "); 
    fflush(stdin);
    return getche();
}

int main(){
	FILE *fp, *ft; 		
	char another, choice;
	
	/** structure to employee */
	struct emp{
		char name[50];
		int age;
		float salary;
	} e;
    
    char empname[50]; 

    long int recsize; 

    /** 
	*	Opening file if exits or creating new file 
    */
    fp = fopen(FILE_NAME,"rb+");
    
    if(fp == NULL)
    {
        fp = fopen(FILE_NAME,"wb+");
        if(fp == NULL)
        {
            printf("Cannot open the file");
            exit(1);
        }
    }

    recsize = sizeof(e);

   
    
    while(1)
    {
    	choice = getChoice();
        
        switch(choice)
        {
        case '1':  // Add Record
            system("cls");
            fseek(fp,0,SEEK_END); 
            another = 'y';
            while(another == 'y')  
            {
                printf("\nEnter name: ");
                scanf("%s",e.name);
                printf("\nEnter age: ");
                scanf("%d", &e.age);
                printf("\nEnter basic salary: ");
                scanf("%f", &e.salary);

                fwrite(&e,recsize,1,fp); 

                printf("\nAdd another record(y/n) ");
                fflush(stdin);
                another = getche();
            }
            break;
        case '2': // List Record
            system("cls");
            rewind(fp); 
            while(fread(&e,recsize,1,fp)==1)  
            {
                printf("\n%s %d %.2f",e.name,e.age,e.salary); 
            }
            getch();
            break;

        case '3':  // Modify Record 
            system("cls");
            another = 'y';
            while(another == 'y')
            {
                printf("Enter the employee name to modify: ");
                scanf("%s", empname);
                rewind(fp);
                while(fread(&e,recsize,1,fp)==1)
                {
                    if(strcmp(e.name,empname) == 0)
                    {
                        printf("\nEnter new name,age and basic salary: ");
                        scanf("%s%d%f",e.name,&e.age,&e.salary);
                        fseek(fp,-recsize,SEEK_CUR); 
                        fwrite(&e,recsize,1,fp);
                        break;
                    }
                }
                printf("\nModify another record(y/n)");
                fflush(stdin);
                another = getche();
            }
            break;
        case '4': // Delete Record
            system("cls");
            another = 'y';
            while(another == 'y')
            {
                printf("\nEnter name of employee to delete: ");
                scanf("%s",empname);
                ft = fopen(TEMP_FILE_NAME,"wb");  
                rewind(fp);
                while(fread(&e,recsize,1,fp) == 1)
                {
                    if(strcmp(e.name,empname) != 0)
                    {
                        fwrite(&e,recsize,1,ft);
                    }
                }
                fclose(fp);
                fclose(ft);
                remove(FILE_NAME);
                rename(TEMP_FILE_NAME,FILE_NAME);
                fp = fopen(FILE_NAME, "rb+");
                printf("Delete another record(y/n)");
                fflush(stdin);
                another = getche();
            }
            break;
        case '5': // Exit Program
            system("cls");
            moveLocation(0,5);
            fclose(fp);  
            printf("Bye././. Have a nice day");
            moveLocation(0,7);
            
            exit(0); 
        }
    }
	
	
	return 0;
}
