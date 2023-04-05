#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>


int home();
void logged_in(int);
void create_main();
void staff();
void contact();

void header();
void login();
void userlogin(int);
int readdata_idnum();
void staffopt();
void viewidsorted();
void viewnamesorted();
void readpass(int accid);
void check_details(int account_number);
void change_info();
void update_info(int maxdata);


typedef struct DateOfBirth{
    unsigned int day;
    unsigned int month;
    unsigned int year;
}DOB;

typedef struct Account{
    unsigned int id;
    char name[50];
    unsigned long int ctzn;
    char sex;
    DOB dob;
    double dep_amt;
}acc;

void createpass(acc);


acc A[500];

int main(){

    home();
    return 0;
}



int home(){
    system("cls");
    int option;

    printf("\t\t--------------------------------------------------------------------------------------------------\n");
    printf("\t\t|\t\t\t\t  Welcome to The NCIT Bank!\t\t\t\t\t |\n");
    printf("\t\t|\t\t\t\t\t\t\t\t\t\t\t\t |\n");
    printf("\t\t|\t\t\t\t\t\t\t\t\t\t\t\t |\n");
    printf("\t\t|\t\t\t\t\t\t\t\t\t\t\t\t |\n");
    printf("\t\t|\t\t\t\t1. Log-in with Existing Account\t\t\t\t\t |\n");
    printf("\t\t|\t\t\t\t2. Create New Account\t\t\t\t\t\t |\n");
    printf("\t\t|\t\t\t\t3. Log-in as Banking Staff\t\t\t\t\t |\n");
    printf("\t\t|\t\t\t\t4. Contact Us\t\t\t\t\t\t\t |\n");
    printf("\t\t|\t\t\t\t5. Exit\t\t\t\t\t\t\t\t |\n");
    printf("\t\t|\t\t\t\t\t\t\t\t\t\t\t\t |\n");
    printf("\t\t|\t\t\t\t\t\t\t\t\t\t\t\t |\n");
    printf("\t\t|\t\t\t\t\t\t\t\t\t\t\t\t |\n");
    printf("\t\t--------------------------------------------------------------------------------------------------\n");

    do{
        printf("\t\tPlease enter a valid option: ");
        scanf(" %d", &option);
    }while(option<1 || option >5);

    switch(option){
        case 1:
            login();
            break;

        case 2:
            create_main();
            break;

        case 3:
            staff();
            break;

        case 4:
            contact();
            break;

        case 5:
            exit(0);
    }
return 0;
}



void login(){
    header();
    int id=0, flag=0;
    unsigned int userid;
    getchar();
    printf("\n\t\tEnter your userid: ");
    scanf("NB%u", &userid);
    int max = readdata_idnum();
    for(int i=0; i<max; i++){
        
        if(userid == A[i].id){
            flag = 1;
            id = A[i].id;
            break;
        }
    }

    if(flag==1){
        getchar();
        printf("\n\t\tEnter password for NB%d: ", id);
        readpass(id);
    }
    else{
        printf("%d", id);
        printf("\n\t\tUser does not exist. Create an account first.");
        getch();
        home();
    }

}


void create_main(){
    FILE *datafp;
    header();
    acc S;

    datafp = fopen("data.txt", "a+");

    if(datafp==NULL){
        datafp = fopen("data.txt", "w+");
        S.id = 0;
    }
    
    S.id = readdata_idnum() + 1;
    
    printf("\n\t\tEnter your Citizenship ID:");

    scanf(" %lu", &S.ctzn);
    
    for(unsigned int i=0; i<S.id; i++){
        if(S.ctzn == A[i].ctzn){
            printf("\t\tAn account with this Citizenship ID is already created!");
            getch();
            home();
        }
    }

    do{
    printf("\n\t\tEnter your full name: ");
    getchar();
    gets(S.name);}while(strlen(S.name)<1);
    

    do{printf("\n\t\tEnter your sex (M or m for Male F or f for Female): ");
    scanf(" %c", &S.sex);
    S.sex = toupper(S.sex);
    if(S.sex!='M' && S.sex!='F'){
        printf("\n\t\tProvide valid response!");
    }
    }while(S.sex!='M'&& S.sex!='F');


    printf("\n\t\tEnter your Date of birth in specified format:\n");
    
    do{getchar();
    printf("\n\t\tEnter Date(Eg. 01 or 31): ");
    scanf(" %u", &S.dob.day);
    if(S.dob.day > 31 || S.dob.day<1){
        printf("\n\t\tEnter valid Date!");
    }
    }while(S.dob.day>31 || S.dob.day<1);


    do{getchar();
    printf("\n\t\tEnter Month(Eg. 1 for January): ");
    scanf(" %u", &S.dob.month);
    if(S.dob.month > 12 || S.dob.month<1){
        printf("\n\t\tEnter valid Month!");
    }
    }while(S.dob.month > 12 || S.dob.month<1);

    
    do{printf("\n\t\tEnter Year(Eg. 2002): ");
    scanf(" %u", &S.dob.year);
    if(S.dob.year < 1900 || S.dob.year > 2004){
        printf("\n\t\tEnter valid Year!");
    }
    }while(S.dob.year < 1900 || S.dob.year > 2004);


    do{printf("\n\t\tPlease enter deposit amount (Must be greater than 1000): ");
    scanf(" %lf", &S.dep_amt);
    if(S.dep_amt<1000){
        printf("\n\t\tEnter valid amount (i.e Higher than 1000):");
    }
    }while(S.dep_amt<1000);

    createpass(S);

    fprintf(datafp, "%u:%s`%lu`%c`%u`%u`%u`%lf\n", S.id, S.name, S.ctzn, S.sex, S.dob.day, S.dob.month, S.dob.year, S.dep_amt);
    fclose(datafp);

    home();
}



void staff(){

    header();

    FILE *spwfp;
    char staffp[33];
    char userstaffp[33];
    spwfp = fopen("staffp.txt", "r");

    if(spwfp==NULL){
        spwfp = fopen("staffp.txt", "w+");
        getchar();
        printf("\t\tCreate a staff Password: ");
        fgets(staffp, 33, stdin);
        fprintf(spwfp, "staff:%s", staffp);
        fclose(spwfp);
        staff();
    } 

    spwfp = fopen("staffp.txt", "r");
    fscanf(spwfp, "staff:%s", staffp);

    printf("\t\tEnter the password to get access: ");

    gets(userstaffp);
    
    if(strcmp(staffp, userstaffp)!=0){
            printf("\t\tThe provided password is incorrect.");
            getch();
            home();
    }

    staffopt();

    fclose(spwfp);
}



void contact(){
    header();
    printf("\n\n\t\t\t\t\t--------------------------------\t\t\t\t\t\n");
    printf("\t\t\t\t\t|       Anish Kumar Neupane    |\t\t\t\t\t\n");
    printf("\t\t\t\t\t--------------------------------\t\t\t\t\t\n");
    printf("\t\t\t\t\t--------------------------------\t\t\t\t\t\n");
    printf("\t\t\t\t\t--------------------------------\t\t\t\t\t\n");
    printf("\n\n\n\n\t\tEnter any key to return...");
    getch();
    home();
}



int readdata_idnum(){

    FILE *readdatafp;

    readdatafp = fopen("data.txt", "r");
    
    if(readdatafp==NULL){
        printf("\t\tNo account created yet!");
        return 0;
    }
    int i = 0;
    while(fscanf(readdatafp, "%u:%[^`]`%lu`%c`%u`%u`%u`%lf\n", &A[i].id, A[i].name, &A[i].ctzn, &A[i].sex, &A[i].dob.day, &A[i].dob.month, &A[i].dob.year, &A[i].dep_amt) != EOF){
        i++;
    }
    

    fclose(readdatafp);
    return i;
}



void createpass(acc Spass){
    header();

    FILE *pwfp;
    
    pwfp = fopen("passwords.txt", "a+");

    if(pwfp==NULL){
        pwfp = fopen("passwords.txt", "w+");
    }    

    printf("\n\n\t\tYour userid for this Account is: NB%u.\n", Spass.id);    
    printf("\n\n\t\tPlease note that your user ID for this account will be required for any future transactions.");
    
    char password[33] = {};
    do{printf("\n\n\t\tCreate a password for the account NB%u (8-32 letters): ", Spass.id);
    getchar();
    gets(password);
    if(strlen(password)<8 || strlen(password)>32){
        printf("\n\t\tInvalid Password!");
    }
    }while(strlen(password)<8 || strlen(password)>32);

    
    fprintf(pwfp, "NB%u:%s\n", Spass.id, password);

    fclose(pwfp);
}


void header(){
    system("cls");    
    printf("\t\t\t\t\t\t  The NCIT Bank!\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t<---------------->\t\t\t\t\t\n");
}


void staffopt(){
    header();
    
    int option1=0;

    printf("\n\t\t1. Sort all Accounts by ID");
    printf("\n\t\t2. Sort all Accounts by Name");
    printf("\n\t\t3. Edit Account details");
    printf("\n\t\t4. Delete Account");
    printf("\n\t\t5. Change Staff password");
    printf("\n\t\t6. Log Out");
    do{
        printf("\n\t\tPlease enter a valid option: ");
        scanf("%d", &option1);
    }while(option1<1 || option1 >6);

    switch(option1){
        case 1:
            viewidsorted();
            break;

        case 2:

            break;

        case 3:

            break;

        case 4:

            break;

        case 5:
            break;

        case 6:
            home();
            break;
    }
}


void viewidsorted(){
    header();
    int maxid=readdata_idnum();

    for(int i=0; i<maxid; i++){
        printf("\t\t%u:%s`%lu`%c`%u`%u`%u`%lf\n", A[i].id, A[i].name, A[i].ctzn, A[i].sex, A[i].dob.day, A[i].dob.month, A[i].dob.year, A[i].dep_amt);
    }

    getch();
    home();
}




void viewnamesorted();

void readpass(int accid){
    FILE *pwfp;
    
    pwfp = fopen("passwords.txt", "r");

    if(pwfp==NULL){
        printf("Error checking password!");
        getch();
        home();
    }    
    
    char passwordinp[33] = {}, passworddata[33];
    
    gets(passwordinp);

    int checkid;
    while(fscanf(pwfp, "NB%d:%s\n",&checkid, passworddata ) != EOF){
        if(checkid==accid){
            if(strcmp(passworddata, passwordinp)==0){
                printf("\n\t\tYou have successfully logged in!");
                getch();
                logged_in(accid-1);
            }
            else{
                printf("\n\t\tWrong Password! Try Again? Y/y or N/n: ");
                char try;
                scanf("%c", &try);
                try = tolower(try);
                if(try=='y'){
                    login();
                }
                else{
                    getch();
                    home();
                }
            }
        }
    }

    fclose(pwfp);
}

void logged_in(int account_id){
    header();
    double deposit=0, withdraw =0; 
    int option1=0;
    int max = readdata_idnum();

    printf("\n\t\t1. Check My Details");
    printf("\n\t\t2. Change My Account Information");
    printf("\n\t\t3. Deposit Cash");
    printf("\n\t\t4. Withdraw Cash");
    printf("\n\t\t5. Change password");
    printf("\n\t\t6. Log Out");
    do{
        printf("\n\t\tPlease enter a valid option: ");
        scanf("%d", &option1);
    }while(option1<1 || option1 >6);

    switch(option1){
        case 1:
            check_details(account_id);
            break;

        case 2:
            change_info(account_id);
            break;

        case 3:
            header();
            printf("\n\t\tEnter the amount you want to deposit:\t");
            scanf("%lf", &deposit);
            A[account_id].dep_amt += deposit;
            printf("\n\t\tAmount has been deposited successfully!");
            update_info(max);
            getch();
            logged_in(account_id);
            break;

        case 4:
            header();
            printf("\n\t\tEnter the amount you want to withdraw:\t");
            scanf("%lf", &withdraw);
            if(withdraw>A[account_id].dep_amt){
                printf("\t\tWithdraw amount more than the balance in account!");
                getch();
                logged_in(account_id);
            }
            printf("\n\t\tAmount has been withdrawn successfully!");
            A[account_id].dep_amt -= withdraw;
            update_info(max);
            getch();
            logged_in(account_id);
            break;

        case 5:
            header();
            getch();
            logged_in(account_id);
            break;

        case 6:
            home();
            break;
    }
}

void check_details(int account_number){
    
    header();
    printf("\t\tYour Account Details are shown below:\n\n");
    printf("\t\tCitizenship ID: %lu\n", A[account_number].ctzn);
    printf("\t\tName: %s\n", A[account_number].name);
    printf("\t\tSex: %c\n", A[account_number].sex);
    printf("\t\tDOB: %u/%u/%u\n", A[account_number].dob.year, A[account_number].dob.month, A[account_number].dob.day);
    printf("\t\tBalance: Rs. %.2lf\n", A[account_number].dep_amt);
    getch();
    logged_in(account_number);
}

void change_info(int accid){
    int option2;
    int max = readdata_idnum();
    char Name1[50] ={};
    long unsigned int CTZN;
    char Sex;
    unsigned int Day, Month, Year;
    

    header();
    printf("\n\t\tWhat information would you like to change?");
    printf("\n\t\t1. Name");
    printf("\n\t\t2. Citizenship ID");
    printf("\n\t\t3. Sex");
    printf("\n\t\t4. DOB");
    printf("\n\t\t5. Return\n");
    do{
        printf("\n\t\tPlease enter a valid option: ");
        scanf("%d", &option2);
    }while(option2<1 || option2 >5);

    switch (option2)
    {
    case 1:
        do{
            getchar();
            printf("\t\tUpdate your full name:\t");
            gets(Name1);
        }while(strlen(Name1)<1);
        strcpy(A[accid].name, Name1);
        update_info(max);
        break;
    
    case 2:
        printf("\t\tUpdate the Citizenship ID: ");
        scanf(" %lu", &CTZN);
        A[accid].ctzn = CTZN;
        update_info(max);
        break;

    case 3:
        do{printf("\n\t\tEnter your sex:\n\t\t(M or m for Male F or f for Female): ");
        scanf(" %c", &Sex);
        Sex = toupper(Sex);
        if(Sex!='M' && Sex!='F'){
            printf("\n\t\tProvide valid response!");
        }
        }while(Sex!='M' && Sex!='F');
        A[accid].sex = Sex;
        update_info(max);
        break;
    
    case 4:
        printf("\n\t\tEnter your Date of birth in specified format:\n");
    
        do{getchar();
        printf("\n\t\tEnter Date(Eg. 01 or 31): ");
        scanf(" %u", &Day);
        if(Day > 31 || Day<1){
            printf("\n\t\tEnter valid Date!");
        }
        }while(Day>31 || Day<1);
        A[accid].dob.day = Day;


        do{getchar();
        printf("\n\t\tEnter Month(Eg. 1 for January): ");
        scanf(" %u", &Month);
        if(Month > 12 || Month<1){
            printf("\n\t\tEnter valid Month!");
        }
        }while(Month > 12 || Month<1);
        A[accid].dob.month = Month;

        
        do{printf("\n\t\tEnter Year(Eg. 2002): ");
        scanf(" %u", &Year);
        if(Year < 1900 || Year > 2004){
            printf("\n\t\tEnter valid Year!");
        }
        }while(Year < 1900 || Year > 2004);
        A[accid].dob.year = Year;
        update_info(max);

    case 5:
        logged_in(accid);
    }

    change_info(accid);
}

void update_info(int maxdata){
    FILE *updatefp;
    updatefp = fopen("data.txt", "w");
    fclose(updatefp);
    updatefp = fopen("data.txt", "a+");
    for(int i=0; i<maxdata; i++){
        fprintf(updatefp, "%u:%s`%lu`%c`%u`%u`%u`%lf\n", A[i].id, A[i].name, A[i].ctzn, A[i].sex, A[i].dob.day, A[i].dob.month, A[i].dob.year, A[i].dep_amt);
    }
    fclose(updatefp);
}