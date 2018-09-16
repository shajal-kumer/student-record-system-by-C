#include<stdio.h>
#include<string.h>
#include <windows.h>
#include <stdlib.h>

/// structure that represent a student
struct student{
    char ID[50];
    char name[20];
    char dept[20];
    char semester[20];
    char parName[30];
    char address[50];
};

/// structure variable creation
struct student stu;

/// Global variable
int choice, id;
int xAxis = 15;

///set the coordinate to 0, 0 (top-left corner of window);
COORD coord = {0,0};
void gotoxy(int x, int y){
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/// Line forground and background color
void SetColorAndBackground(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}

/// Print Heading function
void print_heading(const char st[]){
    printf("   ");
    SetColorAndBackground(31,28);
    printf("  %s",st);
    SetColorAndBackground(14,35);
}

/// conditionCheck Function Prototype
void conditionCheck();

/// Menu Print Function Prototype
void menuPrint();

/// Add Student Function Prototype
void addStudent();

/// Search Student Function Prototype
void searchStudent();

/// Modify Student Function Prototype
void modifyStudent();

/// Delete Student Function Prototype
void deleteStudent();

///  show list Function Prototype
void showList();

/// ExitmainShow Function prototype
void ExitmainShow();

/// Main Function
int main() {

/// call set color and background function
SetColorAndBackground(15, 35);


/// Call menu print function
menuPrint();

/// call condition check function
conditionCheck();



return 0;
}

/// conditionCheck Function
void conditionCheck() {
    if(choice == 1) {
        system("cls");
        addStudent();
    } else if(choice == 2) {
        system("cls");
        searchStudent();
    } else if(choice == 3) {
        system("cls");
        modifyStudent();
    } else if(choice == 4) {
        system("cls");
        deleteStudent();
    } else if(choice == 5) {
        system("cls");
        showList();
    }else if(choice == 0) {
        printf("               You Choice for Exit Program.\n\n");
    } else {
        printf("               Please Choice the Right Number: ");
        scanf("%d", &choice);
        conditionCheck();
    }
}

/// Menu Print Function
void menuPrint() {
    system("cls");
    gotoxy(20, 4);printf("  WELCOME TO STUDENT RECORD SYSTEM  ");
    gotoxy(xAxis, 5);printf("  Varendra University, Rajshahi, Bangladesh  ");
    gotoxy(30, 6);printf("  Estd: 2012  ");
    gotoxy(20, 8);printf("  Copyright By Shajal Kumer Sarker  ");

    gotoxy(xAxis, 12);printf("MAIN MENU\n");
    gotoxy(xAxis, 14);printf("====================\n");
    gotoxy(xAxis, 16);printf("1. Add Student\n");
    gotoxy(xAxis, 18);printf("2. Search Student\n");
    gotoxy(xAxis, 20);printf("3. Modify Student Record\n");
    gotoxy(xAxis, 22);printf("4. Delete Student Record\n");
    gotoxy(xAxis, 24);printf("5. Show Lists\n");
    gotoxy(xAxis, 26);printf("0. Exit\n");
    gotoxy(xAxis, 28);printf("====================\n");
    gotoxy(xAxis, 30);printf("Enter Your Choice: ");
    scanf("%d", &choice);
}

/// Add Student Records Function
void addStudent() {
    system("cls");
    print_heading("Add Record  \n\n");
    char s_id[15];
    int flag = 0;

    FILE *fp;
    fp = fopen("record.txt","ab+");
    if(fp == NULL){
        MessageBox(0,"Error in Opening file!","Warning",0);
        printf("Error File");

    }else {
        for(;;){
            printf("     To exit enter Blank space in the ID input\n");
            printf("     ID: ");
            fflush(stdin);
            gets(s_id);

            if(strcmp(s_id,"")==0 || strcmp(s_id," ")==0) {
               fclose(fp);
               ExitmainShow();
               break;
            }

            rewind(fp);
            while(fread(&stu,sizeof(stu),1,fp) == 1) {
               if(strcmp(s_id,stu.ID) == 0){
                    printf("     The ID is already exits. Please enter new ID.\n\n");
                    flag = 1;
                    break;
                }
            }
            if(flag == 0) {
                fflush(stdin);
                strcpy(stu.ID, s_id);
                printf("     Name: ");gets(stu.name);
                printf("     Dept: ");gets(stu.dept);
                printf("     Semester: ");gets(stu.semester);
                printf("     Parent's Name: ");gets(stu.parName);
                printf("     Address: ");gets(stu.address);

                fwrite(&stu, sizeof(stu), 1, fp);
                printf("     The record is successfully added\n\n");
            }

            flag = 0;

        }

    }
}

/// searchStudent function
void searchStudent(){
    system("cls");
    print_heading("Search Record  \n\n");
    char s_id[15];
    int isFound = 0;
    gotoxy(5,2);printf("Enter ID to Search: ");
    fflush(stdin);
    gets(s_id);

    FILE *fp;
    fp = fopen("record.txt","r");
    while(fread(&stu,sizeof(stu),1,fp) == 1){
        if(strcmp(s_id,stu.ID) == 0){
            isFound = 1;
            break;
        }
    }
    if(isFound == 1){
        gotoxy(5,4);printf("The record is Found");
        gotoxy(5,6);printf("ID: %s", stu.ID);
        gotoxy(5,8);printf("Name: %s", stu.name);
        gotoxy(5,10);printf("Dept: %s", stu.dept);
        gotoxy(5,12);printf("Semester: %s", stu.semester);
        gotoxy(5,14);printf("Parent's Name: %s", stu.parName);
        gotoxy(5,16);printf("Address: %s\n\n", stu.address);
        ExitmainShow();
    }else{
        gotoxy(5,4);printf("Sorry, No record found in the database.\n\n");
        ExitmainShow();
    }
    fclose(fp);
}

/// showlist function
void showList() {

            system("cls");
            FILE *fp;
            fp = fopen("record.txt","rb");

            if(fread(&stu,sizeof(stu),1,fp)==1) {
                rewind(fp);
                while(fread(&stu,sizeof(stu),1,fp)==1)
                {
                    printf("\n==============================\n");
                    printf("     ID: %s\n", stu.ID);
                    printf("     Name: %s\n", stu.name);
                    printf("     Dept: %s\n", stu.dept);
                    printf("     Semester: %s\n", stu.semester);
                    printf("     Parent's Name: %s\n", stu.parName);
                    printf("     Address: %s\n", stu.address);
                }
                } else {
                    gotoxy(5,2);printf("Sorry, No record found in the database.\n");
                }
             ExitmainShow();
}

/// modifyStudent function
void modifyStudent() {
    system("cls");
    print_heading("Modify Record  \n\n");
    char s_id[15];
    int isFound = 0;
    gotoxy(5,2);printf("Enter ID to Modify: ");
    fflush(stdin);
    gets(s_id);

    FILE *fp;
    fp = fopen("record.txt","rb+");
    while(fread(&stu, sizeof(stu),1,fp) == 1){
        if(strcmp(s_id, stu.ID) == 0){

            fflush(stdin);
            gotoxy(5,4);printf("ID: ");gets(stu.ID);
            gotoxy(5,6);printf("Name: ");gets(stu.name);
            gotoxy(5,8);printf("Dept: ");gets(stu.dept);
            gotoxy(5,10);printf("Semester: ");gets(stu.semester);
            gotoxy(5,12);printf("Parent's Name: ");gets(stu.parName);
            gotoxy(5,14);printf("Address: ");gets(stu.address);
            gotoxy(5,16);printf("Record is modified.\n");

            fseek(fp, sizeof(stu), SEEK_CUR);
            fwrite(&stu,sizeof(stu), 1, fp);
            isFound = 1;
            ExitmainShow();
            break;
        }
    }
    if(!isFound){
        gotoxy(5, 4);printf("Sorry, No record found in the database.\n\n");
        ExitmainShow();
    }
    fclose(fp);
}

/// deleteStudent function
void deleteStudent() {

    system("cls");
    print_heading("Delete Record  \n\n");
    char s_id[15];
    gotoxy(5,2);printf("Enter ID to Delete: ");
    fflush(stdin);
    gets(s_id);
    int flag = 0;

    FILE *fp, *temp;
    fp = fopen("record.txt","rb");
    temp = fopen("temp.txt", "wb");

    rewind(fp);
    while(fread(&stu,sizeof(stu),1,fp) == 1) {
       if(strcmp(s_id,stu.ID) == 0){
            flag = 1;
            break;
        }else {
            gotoxy(5,4);printf("Can not find the ID in database!\n");
            break;
        }
    }

    if(flag == 1) {
        rewind(fp);
        while(fread(&stu, sizeof(stu),1,fp) == 1){
            if(strcmp(s_id, stu.ID) != 0){
                fwrite(&stu,sizeof(stu),1,temp);

            }
        }
        gotoxy(5,4);printf("The record is successfully deleted.\n");
    }
    fclose(fp);
    fclose(temp);
    remove("record.txt");
    rename("temp.txt","record.txt");

    ExitmainShow();
}

/// Show EXit and Main Menu Option
void ExitmainShow() {
int num;
printf("\n     Enter the Choice:\n");
printf("     1. Main Menu\n");
printf("     2. Exit\n");
printf("     Choice: ");
scanf("%d", &num);
if(num == 1) {
    system("cls");
    main();
} else if(num == 0) {
    exit(0);
}

}




