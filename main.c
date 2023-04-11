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
void editaccdetails();
void change_info_staff(int accid);
void changepassword(int idnum);
int readpass_idnum();
void update_passkeys(int maxdata);
void changepassword_staff(int userid);
void changebalance(int n);


typedef struct DateOfBirth{
    unsigned int day;
    unsigned int month;
    unsigned int year;
}DOB;

typedef struct Account{
    unsigned int id;
    char name[50];
    long long int ctzn;
    char sex;
    DOB dob;
    char phonenum[11];
    double dep_amt;
}acc;

typedef struct Password{
    unsigned int nbid;
    char passkey[33];
}pass;

void createpass(acc);


acc A[500];
pass P[500];

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
        fflush(stdin);
        printf("\n\t\tPlease enter a valid option: ");
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
    home();
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

    scanf(" %lld", &S.ctzn);

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
    strupr(S.name);

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


    do {
        printf("\n\t\tEnter your Phone Number: ");
        getchar();
        scanf("%32s", S.phonenum);
        int i = 0;
        while(S.phonenum[i] != '\0') {
            if(isdigit(S.phonenum[i]) == 0) {
                printf("\n\t\tPhone Numbers should be 10  digits long with numeric characters only! Please try again.\n");
                break;
            }
            i++;
        }
        if(S.phonenum[i] == '\0'){
            break;
            }
    }while(1 || strlen(S.phonenum) != 10);


    do{printf("\n\t\tPlease enter deposit amount (Must be greater than 1000): ");
    scanf(" %lf", &S.dep_amt);
    if(S.dep_amt<1000){
        printf("\n\t\tEnter valid amount (i.e Higher than 1000):");
    }
    }while(S.dep_amt<1000);

    createpass(S);

    fprintf(datafp, "%u:%s`%lld`%c`%u`%u`%u`%s`%lf\n", S.id, S.name, S.ctzn, S.sex, S.dob.day, S.dob.month, S.dob.year, S.phonenum, S.dep_amt);
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
    fflush(stdin);
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
    printf("\t\t\t\t\t|         Prayojan Puri        |\t\t\t\t\t\n");
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
    while(fscanf(readdatafp, "%u:%[^`]`%lld`%c`%u`%u`%u`%[^`]`%lf\n", &A[i].id, A[i].name, &A[i].ctzn, &A[i].sex, &A[i].dob.day, &A[i].dob.month, &A[i].dob.year, A[i].phonenum, &A[i].dep_amt) != EOF){
        i++;
    }


    fclose(readdatafp);
    return i;
}

int readpass_idnum(){

    FILE *readpassfp;

    readpassfp = fopen("passwords.txt", "r");

    if(readpassfp==NULL){
        printf("\t\tNo account created yet!");
        return 0;
    }
    int i = 0;
    while(fscanf(readpassfp, "NB%u:%[^\n]\n", &P[i].nbid, P[i].passkey) != EOF){
        i++;
    }


    fclose(readpassfp);
    return i;
}



void createpass(acc Spass){
    header();

    FILE *pwfp;
    pass P;
    P.nbid = Spass.id;
    pwfp = fopen("passwords.txt", "a+");

    if(pwfp==NULL){
        pwfp = fopen("passwords.txt", "w+");
    }

    printf("\n\n\t\tYour userid for this Account is: NB%u.\n", P.nbid);
    printf("\n\n\t\tPlease note that your user ID for this account will be required for any future transactions.");

    char password[33] = {};
    do {
        printf("\n\n\t\tCreate a password for the account NB%u (8-32 letters): ", P.nbid);
        scanf("%32s", password);
        int i = 0;
        while(password[i] != '\0') {
            if(isspace(password[i])) {
                printf("Password cannot contain spaces. Please try again.\n");
                break;
            }
            i++;
        }
        if(password[i] == '\0'){
            break;
            }
    }while(1 || strlen(password)<8 || strlen(password)>32);
    strcpy(P.passkey, password);
    fprintf(pwfp, "NB%u:%s\n", P.nbid, P.passkey);

    fclose(pwfp);
}


void header(){
    system("cls");
    printf("\t\t\t\t\t\t  The NCIT Bank!\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t<---------------->\t\t\t\t\t\n");
}


void staffopt(){
    header();
    char staffp[33];
    FILE *spwfp;
    int option1=0;

    printf("\n\t\t1. Sort all Accounts by ID");
    printf("\n\t\t2. Sort all Accounts by Name");
    printf("\n\t\t3. Edit Account details");
    printf("\n\t\t4. Change Staff password");
    printf("\n\t\t5. Log Out");
    do{
        printf("\n\t\tPlease enter a valid option: ");
        scanf("%d", &option1);
    }while(option1<1 || option1 >5);

    switch(option1){
        case 1:
            viewidsorted();
            break;

        case 2:
            viewnamesorted();
            break;

        case 3:
            editaccdetails();
            break;

        case 4:
            spwfp = fopen("staffp.txt", "w+");
            fflush(stdin);
            printf("\t\tCreate a staff Password: ");
            fgets(staffp, 33, stdin);
            fprintf(spwfp, "staff:%s", staffp);
            fclose(spwfp);
            break;

        case 5:
            home();
            break;
    }
    staffopt();
}


void viewidsorted(){
    header();
    int maxid=readdata_idnum();

    for(int i=0; i<maxid; i++){
        printf("\t\t%u:%s`%lld`%c`%u`%u`%u`%s`%lf\n", A[i].id, A[i].name, A[i].ctzn, A[i].sex, A[i].dob.day, A[i].dob.month, A[i].dob.year, A[i].phonenum, A[i].dep_amt);
    }

    getch();
    staffopt();
}




void viewnamesorted(){
    header();
    acc Temp, SortA[100];
    int maxid=readdata_idnum();

    for(int i=0; i<maxid; i++){
        SortA[i] = A[i];
    }

    for(int i=0; i<maxid; i++){
        for(int j=i+1; j<maxid; j++){
            if(strcmp(SortA[j].name, A[i].name)<0){
                Temp = SortA[i];
                SortA[i] = SortA[j];
                SortA[j] = Temp;
            }
        }
    }

    for(int i=0; i<maxid; i++){
        printf("\t\t%u:%s`%lld`%c`%u`%u`%u`%s`%lf\n", SortA[i].id, SortA[i].name, SortA[i].ctzn, SortA[i].sex, SortA[i].dob.day, SortA[i].dob.month, SortA[i].dob.year, SortA[i].phonenum, SortA[i].dep_amt);
    }

    getch();
    staffopt();
}

void readpass(int accid){

    char passwordinp[33] = {};

    do {
        scanf("%32s", passwordinp);

        int i = 0;
        while(passwordinp[i] != '\0') {
            if(isspace(passwordinp[i])) {
                printf("Password cannot contain spaces. Please try again.\n");
                break;
            }
            i++;
        }
        if(passwordinp[i] == '\0') break;
    }while(1);

    int maxpass = readpass_idnum();
    for(int i=0; i<maxpass; i++){
        if(accid == (int)P[i].nbid){
            if(strcmp(P[i].passkey, passwordinp)==0){
                printf("\n\t\tYou have successfully logged in!");
                getch();
                logged_in(accid-1);
            }
            else{
                fflush(stdin);
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
            break;
        }
    }
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
            update_info(max);
            printf("\n\t\tAmount has been deposited successfully!");
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
            A[account_id].dep_amt -= withdraw;
            update_info(max);
            printf("\n\t\tAmount has been withdrawn successfully!");
            getch();
            logged_in(account_id);
            break;

        case 5:
            header();
            changepassword(account_id);
            logged_in(account_id);
            break;

        case 6:
            home();
            break;
    }
    logged_in(account_id);
}

void check_details(int account_number){

    header();
    printf("\t\tYour Account Details are shown below:\n\n");
    printf("\t\tCitizenship ID: %lld\n", A[account_number].ctzn);
    printf("\t\tName: %s\n", A[account_number].name);
    printf("\t\tSex: %c\n", A[account_number].sex);
    printf("\t\tDOB: %u/%u/%u\n", A[account_number].dob.year, A[account_number].dob.month, A[account_number].dob.day);
    printf("\t\tPhone Number: %s\n", A[account_number].phonenum);
    printf("\t\tBalance: Rs. %.2lf\n", A[account_number].dep_amt);
    getch();
    logged_in(account_number);
}

void change_info(int accid){
    int option2;
    int max = readdata_idnum();
    char number[15] , Name1[50] ={};
    long long int CTZN;
    char Sex;
    unsigned int Day, Month, Year;


    header();
    printf("\n\t\tWhat information would you like to change?");
    printf("\n\t\t1. Name");
    printf("\n\t\t2. Citizenship ID");
    printf("\n\t\t3. Sex");
    printf("\n\t\t4. DOB");
    printf("\n\t\t5. Phone Number");
    printf("\n\t\t6. Return\n");
    do{
        printf("\n\t\tPlease enter a valid option: ");
        scanf("%d", &option2);
    }while(option2<1 || option2 >6);

    switch (option2)
    {
    case 1:
        header();
        do{
            getchar();
            printf("\t\tUpdate your full name:\t");
            gets(Name1);
        }while(strlen(Name1)<1);
        strupr(Name1);
        strcpy(A[accid].name, Name1);
        update_info(max);
        printf("\t\tName has been updated successfully!");
        getch();
        break;

    case 2:
        header();
        printf("\t\tUpdate the Citizenship ID: ");
        scanf(" %lld", &CTZN);
        A[accid].ctzn = CTZN;
        update_info(max);
        printf("\t\tCitizenship ID has been updated successfully!");
        getch();
        break;

    case 3:
        header();
        do{printf("\n\t\tEnter your sex:\n\t\t(M or m for Male F or f for Female): ");
        scanf(" %c", &Sex);
        Sex = toupper(Sex);
        if(Sex!='M' && Sex!='F'){
            printf("\n\t\tProvide valid response!");
        }
        }while(Sex!='M' && Sex!='F');
        A[accid].sex = Sex;
        update_info(max);
        printf("\t\tSex has been updated successfully!");
        getch();
        break;

    case 4:
        header();
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
        printf("\t\tDOB has been updated successfully!");
        getch();
        break;

    case 5:
        header();
        do {
            printf("\n\t\tEnter your Phone Number: ");
            getchar();
            scanf("%32s", number);
            int i = 0;
            while(number[i] != '\0') {
                if(isdigit(number[i]) == 0) {
                    printf("\n\t\tPhone Numbers should be 10  digits long with numeric characters only! Please try again.\n");
                    break;
                }
                i++;
            }
            if(number[i] == '\0'){
                break;
                }
        }while(1 || strlen(number) != 10);
        strcpy(A[accid].phonenum, number);
        update_info(max);
        change_info(accid);
        printf("\t\tPhone Number has been updated successfully!");
        getch();
        break;

    case 6:
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
        fprintf(updatefp, "%u:%s`%lld`%c`%u`%u`%u`%s`%lf\n", A[i].id, A[i].name, A[i].ctzn, A[i].sex, A[i].dob.day, A[i].dob.month, A[i].dob.year, A[i].phonenum, A[i].dep_amt);
    }
    fclose(updatefp);
}

void editaccdetails(){
    header();
    int options;
    printf("\n\t\tType the account number for which you would like to change the details.\n\t\t");
    int max = readdata_idnum(), changeacc;
    do{
        scanf(" %d", &changeacc);
        if(changeacc>max){
            printf("\n\t\tEnter Valid Account Number!");
        }
    }while(changeacc>max);

    header();
    printf("\n\t\tWhat would you like to make changes to?\n\t\t1. Personal Information\n\t\t2. Password\n\t\t3. Balance\n\t\t4. Return\n\t\t");

    do{
        scanf(" %d", &options);
    }while(options>4 || options<1);

    switch (options)
    {
    case 1:
        change_info_staff(changeacc-1);
        break;

    case 2:
        changepassword_staff(changeacc-1);
        break;

    case 3:
        changebalance(changeacc-1);
        break;

    case 4:
        staffopt();
        break;
    }

    staffopt();

}

void change_info_staff(int accid){
    int option2;
    int max = readdata_idnum();
    char Name1[50] ={}, number[15];
    long long int CTZN;
    char Sex;
    unsigned int Day, Month, Year;


    header();
    printf("\n\t\tWhat information would you like to change?");
    printf("\n\t\t1. Name");
    printf("\n\t\t2. Citizenship ID");
    printf("\n\t\t3. Sex");
    printf("\n\t\t4. DOB");
    printf("\n\t\t5. Phone Number");
    printf("\n\t\t6. Return\n");
    do{
        printf("\n\t\tPlease enter a valid option: ");
        scanf("%d", &option2);
    }while(option2<1 || option2 >6);

    switch (option2)
    {
    case 1:

        header();
        do{
            getchar();
            printf("\t\tProvide the full name:\t");
            gets(Name1);
        }while(strlen(Name1)<1);
        strupr(Name1);
        strcpy(A[accid].name, Name1);
        update_info(max);
        printf("\n\t\tThe name has been updated!");
        getch();
        break;

    case 2:
        header();
        printf("\t\tProvide the Citizenship ID: ");
        scanf(" %lld", &CTZN);
        A[accid].ctzn = CTZN;
        update_info(max);
        printf("\n\t\tThe Citizenship ID has been updated!");
        getch();
        break;

    case 3:
        header();
        do{printf("\n\t\tProvide the sex:\n\t\t(M or m for Male F or f for Female): ");
        scanf(" %c", &Sex);
        Sex = toupper(Sex);
        if(Sex!='M' && Sex!='F'){
            printf("\n\t\tProvide valid response!");
        }
        }while(Sex!='M' && Sex!='F');
        A[accid].sex = Sex;
        update_info(max);
        printf("\n\t\tThe sex has been updated!");
        break;

    case 4:
        header();
        printf("\n\t\tProvide the Date of birth in specified format:\n");

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
        printf("\n\t\tThe Date of Birth has been updated!");
        getch();
        break;

    case 5:
        header();
        do {
            printf("\n\t\tEnter your Phone Number: ");
            getchar();
            scanf("%32s", number);
            int i = 0;
            while(number[i] != '\0') {
                if(isdigit(number[i]) == 0) {
                    printf("\n\t\tPhone Numbers should be 10  digits long with numeric characters only! Please try again.\n");
                    break;
                }
                i++;
            }
            if(number == '\0'){
                break;
                }
        }while(1 || strlen(number) != 10);
        strcpy(A[accid].phonenum, number);
        update_info(max);
        printf("\n\t\tThe Phone Number has been updated!");
        getch();
        break;


    case 6:
        editaccdetails();
    }

    update_info(max);
}

void changepassword(int idnum){
    header();
    int max = readpass_idnum();
    char pass[50] = {};
    char newpass[50] = {};
    getchar();
    printf("\n\t\tProvide the current password: ");
    gets(pass);
    do {
        printf("\n\t\tProvide the new password: ");
        scanf("%32s", newpass);
        int i = 0;
        while(newpass[i] != '\0') {
            if(isspace(newpass[i])) {
                printf("Password cannot contain spaces. Please try again.\n");
                break;
            }
            i++;
        }
        if(newpass[i] == '\0'){
            break;
            }
    }while(1 || strlen(newpass)<8 || strlen(newpass)>32);
    if(strcmp(pass, P[idnum].passkey) != 0){
        printf("\n\t\tWrong password!\n");
        getch();
        changepassword(idnum);
    }
    else{
        strcpy(P[idnum].passkey, newpass);
        update_passkeys(max);
    }
}

void update_passkeys(int maxdata){
    FILE *updatepassfp;
    updatepassfp = fopen("passwords.txt", "w");
    fclose(updatepassfp);
    updatepassfp = fopen("passwords.txt", "a+");
    for(int i=0; i<maxdata; i++){
        fprintf(updatepassfp, "NB%u:%s\n", P[i].nbid, P[i].passkey);
        }
    fclose(updatepassfp);
}

void changepassword_staff(int userid){
    header();
    int max = readpass_idnum();
    char newpass[50] = {};
    getchar();
    do {
        printf("\n\t\tProvide the new password: ");
        fgets(newpass, 32, stdin);
        int i = 0;
        while(newpass[i] != '\0') {
            if(isspace(newpass[i])) {
                printf("Password cannot contain spaces. Please try again.\n");
                break;
            }
            i++;
        }
        if(newpass[i] == '\0'){
            break;
            }
    }while(1 || strlen(newpass)<8 || strlen(newpass)>32);
    strcpy(P[userid].passkey, newpass);
    update_passkeys(max);

}

void changebalance(int n){
    double balance;
    int max = readdata_idnum();
    printf("\n\t\tEnter the new Balance:\t");
    scanf("%lf", &balance);
    A[n].dep_amt = balance;
    update_info(max);
    printf("\n\t\tAmount has been deposited successfully!");
}
