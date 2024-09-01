#ifndef BANKHEADER_H // This is the header guard to prevent the header file from being included multiple times.
#define BANKHEADER_H 


// This is the structure of the bank account details.
struct bankAccount
{
    char account_holder_name[60], email[60], contact_number[15];
    int account_number;
    float balance;

};


// Declaration of the function prototypes which is used in the bank.c file.
void saveAccountToFile(char *acc_name, int acc_no, char *email, char *phone_no, float balance);

void unsaveAccountToFile(char *acc_name, int acc_no, char *email, char *phone_no, float balance);

int accountExists(char *acc_name, int acc_no, char *email);

void createAccount(char *acc_name, int acc_no, char *email, char *phone_no, float balance);

void closeAccount(char *acc_name, char *email, char *phone_no);

void deposit(char *acc_name, int acc_no, char *email, char *phone_no, float balance);

void withdraw(char *acc_name, int acc_no, char *email, char *phone_no, float balance);

void checkBalance(char *acc_name, int acc_no, char *email, char *phone_no);

void updateAccount(char *acc_name, char *email);

void transferAmount(char *acc_name, int acc_no,char *email, char *phone_no, float balance, char *acc_name2, int acc_no2,char *email2, char *phone_no2);

void viewAccountInformation(char *acc_name, char *email);

#endif
