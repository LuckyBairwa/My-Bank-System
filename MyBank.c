#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "bankHeader.h"

// ----> Function declaration for saving the account details in the file. and this function works successfully.
void saveAccountToFile(char *acc_name, int acc_no, char *email, char *phone_no, float balance)
{
    FILE *file = fopen("accounts.txt", "a");

    // It checks the file is open or not.
    if (file == NULL)
    {
        system("cls");
        printf("Error: Can't open the file.\n");
        return; // It will return the control to the main function.
    }

    // It will save the account details in the file.
    fprintf(file, "Name: %s\nAccount Number: %d\nEmail: %s\nContact Number: %sBalance: %.2f\n\n\n\n", acc_name, acc_no, email, phone_no, balance);

    // It will close the file.
    fclose(file);
    system("cls");

    // Confirmation message
    system("cls");
    system("color a");
    printf("Greetings: Account details saved to file successfully!\n");
    printf("\n\nPress any key to continue ...");
    getch();
    system("color 7");
    system("cls");
}

// ----> Function declaration for check the account is exists or not in the file, and this funcion also works successfully and used in the createAccount function.
int accountExists(char *acc_name, int acc_no, char *email)
{
    char file_acc_name[60], file_email[60], file_phone_no[15];
    int file_acc_no;
    float file_balance;

    // Opening the file in the read mode.
    FILE *file = fopen("accounts.txt", "r");

    if (file == NULL)
    {
        system("cls");
        system("color 4");
        printf("Error: Can't open the file.\n");
        printf("\n\nPress any key to continue ...");
        getch();
        system("color 7");
        system("cls");
        return 0; // It will return the control to the main function.
    }

    while (fscanf(file, "Name: %s\nAccount Number: %d\nEmail: %s\nContact Number: %s\nBalance: %f\n\n\n\n", file_acc_name, &file_acc_no, file_email, file_phone_no, &file_balance) == 5)
    {
        if (strcmp(acc_name, file_acc_name) == 0 && acc_no == file_acc_no && strcmp(email, file_email) == 0)
        {
            fclose(file);
            return 1; // It tells that the account is exists.
        }
    }

    fclose(file);
    return 0; // It tells that the account is not exists.
}

// ----> Function declaration for creating an account in which we will copying the account details using strcpy function in the structure.
void createAccount(char *acc_name, int acc_no, char *email, char *phone_no, float balance)
{

    // Firstly checks the account is exists or not.
    if (accountExists(acc_name, acc_no, email))
    {
        system("cls");
        system("color 4");
        printf("Error: An account with this number or email already exists.\n");
        printf("\n\nPress any key to continue ...");
        getch();
        system("color 7");
        system("cls");
        return;
    }
    else
    {

        struct bankAccount newAccount;

        // Copying the account details in the structure.
        strcpy(newAccount.account_holder_name, acc_name);
        strcpy(newAccount.email, email);
        strcpy(newAccount.contact_number, phone_no);
        newAccount.account_number = acc_no;
        newAccount.balance = balance;

        // Saving the account details in the file.
        saveAccountToFile(newAccount.account_holder_name, newAccount.account_number, newAccount.email, newAccount.contact_number, newAccount.balance);
    }
}

// ----> Function declaration for un-saving the account details from the file which is used in the closeAccount function.
void unsaveAccountToFile(char *acc_name, int acc_no, char *email, char *phone_no, float balance)
{
    FILE *file = fopen("accounts.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL)
    {
        system("cls");
        system("color 4");
        printf("Error: Can't open the file.\n");
        printf("\n\nPress any key to continue ...");
        getch();
        system("color 7");
        system("cls");
        return;
    }

    char file_acc_name[60], file_email[60], file_phone_no[15];
    int file_acc_no;
    float file_balance;

    while (fscanf(file, "Name: %s\nAccount Number: %d\nEmail: %s\nContact Number: %s\nBalance: %f\n\n\n\n", file_acc_name, &file_acc_no, file_email, file_phone_no, &file_balance) == 5)
    {
        if (!(strcmp(acc_name, file_acc_name) == 0 && acc_no == file_acc_no && strcmp(email, file_email) == 0 && strcmp(phone_no, file_phone_no) == 0))
        {
            // It will copy the all unmatching account details in the temp file.
            fprintf(tempFile, "Name: %s\nAccount Number: %d\nEmail: %s\nContact Number: %s\nBalance: %.2f\n\n\n\n", file_acc_name, file_acc_no, file_email, file_phone_no, file_balance);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("accounts.txt");             // It will remove the accounts.txt file.
    rename("temp.txt", "accounts.txt"); // It will rename the temp.txt to the accounts.txt file.

    system("cls");
    system("color a");
    printf("Message: Account deleted successfully!\n");
    printf("\n\nPress any key to continue ...");
    getch();
    system("color 7");
    system("cls");
}

// ----> Function declaration for close account form the file in which we will use the unsaveAccountToFile function.
void closeAccount(char *acc_name, char *email, char *phone_no)
{
    char file_acc_name[60], file_email[60], file_phone_no[15];
    int file_acc_no;
    float file_balance;
    int flag = 0;

    // Opening the file in the read mode.
    FILE *file = fopen("accounts.txt", "r");

    if (file == NULL)
    {
        system("cls");
        system("color 4");
        printf("Error: Can't open the file.\n");
        printf("\n\nPress any key to continue ...");
        getch();
        system("color 7");
        system("cls");
        return;
    }

    while (fscanf(file, "Name: %s\nAccount Number: %d\nEmail: %s\nContact Number: %s\nBalance: %f\n\n\n\n", file_acc_name, &file_acc_no, file_email, file_phone_no, &file_balance) == 5)
    {
        if (strcmp(acc_name, file_acc_name) == 0 && strcmp(email, file_email) == 0 && strcmp(phone_no, file_phone_no) == 0)
        {
            flag = 1;
            break;
        }
    }

    fclose(file);

    if (flag)
    {
        unsaveAccountToFile(acc_name, file_acc_no, email, phone_no, file_balance);
    }
    else
    {
        system("cls");
        system("color 4");
        printf("Error: Account not found with the provided details.\n");
        printf("\n\nPress any key to continue ...");
        getch();
        system("color 7");
        system("cls");
    }
}

// ----> Function declaration for deposit the amount in the account.
void deposit(char *acc_name, int acc_no, char *email, char *phone_no, float balance)
{
    char file_acc_name[60], file_email[60], file_phone_no[15];
    int file_acc_no;
    float file_balance;
    int account_found = 0;

    FILE *file = fopen("accounts.txt", "r");
    FILE *tempfile = fopen("temp.txt", "w");

    if (file == NULL || tempfile == NULL)
    {
        system("cls");
        system("color 4");
        printf("Error: Can't open the file.\n");
        printf("\n\nPress any key to continue ...");
        getch();
        system("color 7");
        system("cls");
        return;
    }

    while (fscanf(file, "Name: %s\nAccount Number: %d\nEmail: %s\nContact Number: %s\nBalance: %f\n\n\n\n", file_acc_name, &file_acc_no, file_email, file_phone_no, &file_balance) == 5)
    {
        if (strcmp(acc_name, file_acc_name) == 0 && acc_no == file_acc_no && strcmp(email, file_email) == 0 && strcmp(phone_no, file_phone_no) == 0)
        {
            account_found = 1;
            file_balance += balance;
            system("cls");
            system("color a");
            printf("Message: Amount deposited successfully! New Balance: %.2f\n", file_balance);
            printf("\n\nPress any key to continue ...");
            getch();
            system("color 7");
            system("cls");
        }

        fprintf(tempfile, "Name: %s\nAccount Number: %d\nEmail: %s\nContact Number: %s\nBalance: %.2f\n\n\n\n", file_acc_name, file_acc_no, file_email, file_phone_no, file_balance);
    }

    fclose(file);
    fclose(tempfile);

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!account_found)
    {
        system("cls");
        system("color 4");
        printf("Error: Account not found with the provided details.\n");
        printf("\n\nPress any key to continue ...");
        getch();
        system("color 7");
        system("cls");
    }
}

// ----> Function declaration for withdraw the amount from the account.
void withdraw(char *acc_name, int acc_no, char *email, char *phone_no, float balance)
{
    char file_acc_name[60], file_email[60], file_phone_no[15];
    int file_acc_no;
    float file_balance;
    int account_found = 0;

    FILE *file = fopen("accounts.txt", "r");
    FILE *tempfile = fopen("temp.txt", "w");

    if (file == NULL || tempfile == NULL)
    {
        system("cls");
        system("color 4");
        printf("Error: Can't open the file.\n");
        printf("\n\nPress any key to continue ...");
        getch();
        system("color 7");
        system("cls");
        return;
    }

    while (fscanf(file, "Name: %s\nAccount Number: %d\nEmail: %s\nContact Number: %s\nBalance: %f\n\n\n\n", file_acc_name, &file_acc_no, file_email, file_phone_no, &file_balance) == 5)
    {
        if (strcmp(acc_name, file_acc_name) == 0 && acc_no == file_acc_no && strcmp(email, file_email) == 0 && strcmp(phone_no, file_phone_no) == 0)
        {
            if (file_balance >= balance)
            {
                file_balance -= balance;
                system("cls");
                system("color a");
                printf("Message: Amount withdraw successfully! New Balance: %.2f\n", file_balance);
                printf("\n\nPress any key to continue ...");
                getch();
                system("color 7");
                system("cls");
                account_found = 1;
            }
            else
            {
                system("cls");
                printf("Error: Insufficient balance.\n");
                account_found = -1;
            }
        }
        fprintf(tempfile, "Name: %s\nAccount Number: %d\nEmail: %s\nContact Number: %s\nBalance: %.2f\n\n\n\n", file_acc_name, file_acc_no, file_email, file_phone_no, file_balance);
    }

    fclose(file);
    fclose(tempfile);

    if (account_found == 1)
    {
        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
    }
    else
    {
        remove("temp.txt"); // It will remove the temp.txt file if the account is not found or Insufficient balance.
    }

    if (account_found == 0)
    {
        system("cls");
        system("color 4");
        printf("Error: Account not found with the provided details.\n");
        printf("\n\nPress any key to continue ...");
        getch();
        system("color 7");
        system("cls");
    }
}

// ----> Function declaration for check the balance of the account.
void checkBalance(char *acc_name, int acc_no, char *email, char *phone_no)
{
    char file_acc_name[60], file_email[60], file_phone_no[15];
    int file_acc_no;
    float file_balance;

    FILE *file = fopen("accounts.txt", "r");

    if (file == NULL)
    {
        system("cls");
        system("color 4");
        printf("Error: Can't open the file.\n");
        printf("\n\nPress any key to continue ...");
        getch();
        system("color 7");
        system("cls");
        return;
    }

    while (fscanf(file, "Name: %s\nAccount Number: %d\nEmail: %s\nContact Number: %s\nBalance: %f\n\n\n\n", file_acc_name, &file_acc_no, file_email, file_phone_no, &file_balance) == 5)
    {
        if (strcmp(acc_name, file_acc_name) == 0 && acc_no == file_acc_no && strcmp(email, file_email) == 0 && strcmp(phone_no, file_phone_no) == 0)
        {
            fclose(file);
            system("cls");
            system("color a");
            printf("Message: Your current balance is: %.2f\n", file_balance);
            printf("\n\nPress any key to continue ...");
            getch();
            system("color 7");
            system("cls");
            return;
        }
    }

    system("cls");
    system("color 4");
    fclose(file);
    printf("Error: Account not found with the provided details.\n\n\n");
    system("color 7");
    system("cls");
}

// ----> Function declaration for transfer the specific amount from one account to another account.
void transferAmount(char *acc_name, int acc_no, char *email, char *phone_no, float balance, char *acc_name2, int acc_no2, char *email2, char *phone_no2)
{
    char file_acc_name[60], file_phone_no[15], file_email[60];
    int file_acc_no;
    float file_balance;
    int source_account_found = 0, destination_account_found = 0;

    FILE *file = fopen("accounts.txt", "r");
    FILE *tempfile = fopen("temp.txt", "w");

    if (file == NULL || tempfile == NULL)
    {
        system("cls");
        system("color 4");
        printf("Error: Can't open the file.\n");
        printf("\n\nPress any key to continue ...");
        getch();
        system("color 7");
        system("cls");
        return;
    }

    while (fscanf(file, "Name: %s\nAccount Number: %d\nEmail: %s\nContact Number: %s\nBalance: %f\n\n\n\n", file_acc_name, &file_acc_no, file_email, file_phone_no, &file_balance) == 5)
    {
        if (strcmp(acc_name, file_acc_name) == 0 && acc_no == file_acc_no && strcmp(email, file_email) == 0 && strcmp(phone_no, file_phone_no) == 0)
        {
            source_account_found = 1;

            if (file_balance >= balance)
            {
                file_balance -= balance;
            }
            else
            {
                system("cls");
                system("color 4");
                printf("Error: Insufficient balance in the source account.\n");
                fclose(file);
                fclose(tempfile);
                remove("temp.txt");
                printf("\n\nPress any key to continue ...");
                getch();
                system("color 7");
                system("cls");
                return;
            }
        }

        if (strcmp(acc_name2, file_acc_name) == 0 && acc_no2 == file_acc_no && strcmp(email2, file_email) == 0 && strcmp(phone_no2, file_phone_no) == 0)
        {
            destination_account_found = 1;
            file_balance += balance;
        }

        fprintf(tempfile, "Name: %s\nAccount Number: %d\nEmail: %s\nContact Number: %s\nBalance: %.2f\n\n\n\n", file_acc_name, file_acc_no, file_email, file_phone_no, file_balance);
    }
    fclose(file);
    fclose(tempfile);

    if (source_account_found && destination_account_found)
    {
        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
        system("cls");
        system("color a");
        printf("Message: Amount transferred successfully!\n");
        printf("\n\nPress any key to continue ...");
        getch();
        system("color 7");
        system("cls");
    }
    else
    {
        remove("temp.txt");
        if (!source_account_found)
        {
            system("cls");
            system("color 4");
            printf("Error: Source account not found!.\n");
            printf("\n\nPress any key to continue ...");
            getch();
            system("color 7");
            system("cls");
        }
        if (!destination_account_found)
        {
            system("cls");
            system("color 4");
            printf("Error: Destination account not found!.\n");
            printf("\n\nPress any key to continue ...");
            getch();
            system("color 7");
            system("cls");
        }
    }
}

// ----> Function declaration for view the account information.
void viewAccountInformation(char *acc_name, char *email)
{
    char file_acc_name[60], file_email[60], file_phone_no[15];
    int file_acc_no;
    float file_balance;
    int account_found = 0;

    FILE *file = fopen("accounts.txt", "r");

    if (file == NULL)
    {
        system("cls");
        system("color 4");
        printf("Error: Can't open the file.\n");
        printf("\n\nPress any key to continue ...");
        getch();
        system("color 7");
        system("cls");
        return;
    }

    while (fscanf(file, "Name: %s\nAccount Number: %d\nEmail: %s\nContact Number: %s\nBalance: %f\n\n\n\n", file_acc_name, &file_acc_no, file_email, file_phone_no, &file_balance) == 5)
    {
        if (strcmp(acc_name, file_acc_name) == 0 && strcmp(email, file_email) == 0)
        {
            account_found = 1;

            // Showing the account information.
            // Account found, print the details
            system("cls");
            system("color a");
            printf("Account Information:\n");
            printf("---------------------------\n");
            printf("Name: %s\n", file_acc_name);
            printf("Account Number: %d\n", file_acc_no);
            printf("Email: %s\n", file_email);
            printf("Contact Number: %s\n", file_phone_no);
            printf("Balance: %.2f\n", file_balance);
            printf("---------------------------\n");
            printf("\n\nPress any key to continue ...");
            getch();
            system("color 7");
            system("cls");
        }
    }
    fclose(file);
    if (!account_found)
    {
        system("cls");
        system("color 4");
        printf("Error: Account not found with the provided details.\n");
        printf("\n\nPress any key to continue ...");
        getch();
        system("color 7");
        system("cls");
    }
}

// <----> Function declaration for update the account information.
void updateAccount(char *acc_name, char *email)
{
    char file_acc_name[60], file_email[60], file_phone_no[15], account_choice;
    int file_acc_no, account_found = 0, change = 0, choice;
    float file_balance;

    FILE *file = fopen("accounts.txt", "r");
    FILE *tempfile = fopen("temporary.txt", "w");

    if (file == NULL || tempfile == NULL)
    {
        system("cls");
        system("color 4");
        printf("Error: Can't open the file.\n");
        printf("\n\nPress any key to continue ...");
        getch();
        system("color 7");
        system("cls");
        return;
    }

    while (fscanf(file, "Name: %s\nAccount Number: %d\nEmail: %s\nContact Number: %s\nBalance: %f\n\n\n\n", file_acc_name, &file_acc_no, file_email, file_phone_no, &file_balance) == 5)
    {
        if (strcmp(acc_name, file_acc_name) == 0 && strcmp(email, file_email) == 0)
        {
            // char account_choice;
            account_found = 1;

            do
            {
                system("cls");
                system("color a");
                printf("Update Account Information:\n");
                printf("-----------------------------------\n");
                printf("1. Update Name\n");
                printf("2. Update Email\n");
                printf("3. Update Contact Number\n");
                printf("4. Update All Details (Not Allowed)\n");

                printf("\nEnter your choice: ");
                scanf("%d", &choice);
                getchar(); // clear the new line left in the buffer.

                if (choice == 4)
                {

                    system("cls");
                    system("color 6");
                    printf("Warning: You can't edit all the details at once, but you can close your account and create a new one.\n");

                    printf("\nWould you like to close your account? (y/n): ");
                    char account_choice;
                    scanf("%c", &account_choice);
                    getchar(); // clear the newline.

                    if (account_choice == 'y' || account_choice == 'Y')
                    {
                        closeAccount(acc_name, email, file_phone_no);
                        fclose(file);
                        fclose(tempfile);
                        remove("accounts.txt");
                        break;

                        // createAccount(acc_name, file_acc_no, email, file_phone_no, file_balance);
                    }
                    else if (account_choice == 'n' || account_choice == 'N')
                    {
                        system("cls");
                        system("color a");
                        printf("Message: Account not closed.\nThanks for using our service.\n");
                        printf("\n\nPress any key to continue ...");
                        getch();
                        system("color 7");
                        system("cls");
                        break;
                    }
                    else
                    {
                        system("cls");
                        system("color 4");
                        printf("Error: Invalid choice. Please try again.\n");
                        printf("\n\nPress any key to continue ...");
                        getch();
                        system("color 7");
                        system("cls");
                        continue;
                    }
                }
                else if (choice == 1 && change < 2)
                {
                    system("cls");
                    system("color a");
                    printf("Enter the new name: ");
                    getchar(); // clear the newline.
                    fgets(file_acc_name, sizeof(file_acc_name), stdin);
                    file_acc_name[strcspn(file_acc_name, "\n")] = '\0';
                    change++;
                }
                else if (choice == 2 && change < 2)
                {
                    system("cls");
                    system("color a");
                    printf("Enter the new email: ");
                    getchar(); // clear the newline.
                    fgets(file_email, sizeof(file_email), stdin);
                    file_email[strcspn(file_email, "\n")] = '\0';
                    change++;
                }
                else if (choice == 3 && change < 2)
                {
                    system("cls");
                    system("color a");
                    printf("Enter the new contact number: ");
                    getchar();
                    fgets(file_phone_no, sizeof(file_phone_no), stdin);
                    file_phone_no[strcspn(file_phone_no, "\n")] = '\0';
                    change++;
                }
                else if (change >= 2)
                {
                    char account_choice;
                    system("cls");
                    system("color 6");
                    printf("Warning: You can't change more than two details.\n");
                    printf("\n\nPress any key to continue ...");
                    getch();
                    system("color 7");
                    system("cls");
                    break;
                }
                else
                {
                    system("cls");
                    system("color 4");
                    printf("Error: Invalid choice. Please try again.\n");
                    printf("\n\nPress any key to continue ...");
                    getch();
                    system("color 7");
                    system("cls");
                }
                if (change < 2)
                {
                    printf("\nWould you like to change anything else? (y/n): ");
                    char continue_choice;
                    scanf("%c", &continue_choice);
                    getchar(); // Clear the newline left by scanf
                    if (continue_choice == 'n' || continue_choice == 'N')
                    {
                        break;
                    }
                    else if (continue_choice == 'y' || continue_choice == 'Y')
                    {
                        system("cls");
                        system("color 4");
                        printf("Error: Invalid choice. Please try again.\n");
                        printf("\n\nPress any key to continue ...");
                        getch();
                        system("color 7");
                        system("cls");
                        break;
                    }
                }

            } while (change < 2);

            if (choice == 4 && (account_choice == 'y' || account_choice == 'Y'))
            {
                continue;
            }
        }

        fprintf(tempfile, "Name: %s\nAccount Number: %d\nEmail: %s\nContact Number: %s\nBalance: %.2f\n\n\n\n", file_acc_name, file_acc_no, file_email, file_phone_no, file_balance);
    }

    fclose(file);
    fclose(tempfile);

    if (account_found)
    {
        remove("accounts.txt");
        rename("temporary.txt", "accounts.txt");

        if (choice == 4 && (account_choice == 'y' || account_choice == 'Y'))
        {
            char new_acc_name[60], new_email[60], new_phone_no[15];
            int new_acc_no;
            printf("Enter the new account name: ");
            fgets(new_acc_name, sizeof(new_acc_name), stdin);
            new_acc_name[strcspn(new_acc_name, "\n")] = '\0';
            printf("Enter the new email: ");
            fgets(new_email, sizeof(new_email), stdin);
            new_email[strcspn(new_email, "\n")] = '\0';
            printf("Enter the new contact number: ");
            fgets(new_phone_no, sizeof(new_phone_no), stdin);
            new_phone_no[strcspn(new_phone_no, "\n")] = '\0';
            printf("Enter the new account number: ");
            scanf("%d", &new_acc_no);
            getchar();

            createAccount(new_acc_name, file_acc_no, new_email, new_phone_no, file_balance);
        }
        else
        {
            system("cls");
            system("color a");
            printf("Greetings: Account updated successfully!\n");
            printf("\n\nPress any key to continue ...");
            getch();
            system("color 7");
            system("cls");
            remove("accounts.txt");
            rename("temporary.txt", "accounts.txt");
        }
    }
    else
    {
        system("cls");
        system("color 4");
        printf("Error: Account not found with the provided details.\n");
        printf("\n\nPress any key to continue ...");
        getch();
        system("color 7");
        system("cls");
        remove("temporary.txt");
    }
}

void main()
{
    int choice;
    char acc_name[60], email[60], phone_no[15];
    int acc_no;
    float balance;

    system("cls");
    system("color a");
    printf("\n\n\t\t\tWelcome to the Lucky's Bank System\n\n\n");
    printf("Select the option given below: \n\n");
    printf("---------------------------------------\n");
    printf("1. Create Account\n");
    printf("2. Delete Account\n");
    printf("3. Check Balance\n");
    printf("4. Deposit Amount\n");
    printf("5. Withdraw Amount\n");
    printf("6. Transfer Amount\n");
    printf("7. View Account Information\n");
    printf("8. Update Account\n");
    printf("9. Exit\n");
    printf("---------------------------------------\n");
    printf("\n\nEnter your choice: ");
    scanf("%d", &choice);
    getchar();

    switch (choice)
    {
    // Case 1 is for creating the account is completed and it works successfully.
    case 1:
        system("cls");
        printf("Enter the account name: ");
        fgets(acc_name, sizeof(acc_name), stdin);
        acc_name[strcspn(acc_name, "\n")] = '\0';
        printf("Enter the email: ");
        fgets(email, sizeof(email), stdin);
        email[strcspn(email, "\n")] = '\0';
        printf("Enter the contact number: ");
        fgets(phone_no, sizeof(phone_no), stdin);
        printf("Enter the balance: ");
        scanf("%f", &balance);
        printf("Enter the account number: ");
        scanf("%d", &acc_no);
        createAccount(acc_name, acc_no, email, phone_no, balance);
        break;

    // Case 2 is for deleting the account is completed and it works successfully without an error.
    case 2:
        system("cls");
        printf("Enter the account name: ");
        fgets(acc_name, sizeof(acc_name), stdin);
        acc_name[strcspn(acc_name, "\n")] = '\0';
        printf("Enter the email: ");
        fgets(email, sizeof(email), stdin);
        email[strcspn(email, "\n")] = '\0';
        printf("Enter the contact number: ");
        fgets(phone_no, sizeof(phone_no), stdin);
        phone_no[strcspn(phone_no, "\n")] = '\0';
        closeAccount(acc_name, email, phone_no);
        break;

    // Case 3 is for checking the bank balance is completed and it worked successfully.
    case 3:
        system("cls");
        printf("Enter the account name: ");
        fgets(acc_name, sizeof(acc_name), stdin);
        acc_name[strcspn(acc_name, "\n")] = '\0';
        printf("Enter the account number: ");
        scanf("%d", &acc_no);
        getchar(); // Consume the newline character left by scanf
        printf("Enter the email: ");
        fgets(email, sizeof(email), stdin);
        email[strcspn(email, "\n")] = '\0';
        printf("Enter the contact number: ");
        fgets(phone_no, sizeof(phone_no), stdin);
        phone_no[strcspn(phone_no, "\n")] = '\0';
        checkBalance(acc_name, acc_no, email, phone_no);
        break;

    // Case 4 is for deposit the amount in the account completed and it works successfully.
    case 4:
        system("cls");
        printf("Enter the account name: ");
        fgets(acc_name, sizeof(acc_name), stdin);
        acc_name[strcspn(acc_name, "\n")] = '\0';
        printf("Enter the account number: ");
        scanf("%d", &acc_no);
        getchar(); // Consume the newline character left by scanf
        printf("Enter the email: ");
        fgets(email, sizeof(email), stdin);
        email[strcspn(email, "\n")] = '\0';
        printf("Enter the contact number: ");
        fgets(phone_no, sizeof(phone_no), stdin);
        phone_no[strcspn(phone_no, "\n")] = '\0';
        printf("Enter the amount to deposit: ");
        scanf("%f", &balance);
        deposit(acc_name, acc_no, email, phone_no, balance);
        break;

    // Case 5 is for withdraw the amount from the account is completed and it runs successfully.
    case 5:
        system("cls");
        printf("Enter the account name: ");
        fgets(acc_name, sizeof(acc_name), stdin);
        acc_name[strcspn(acc_name, "\n")] = '\0';
        printf("Enter the account number: ");
        scanf("%d", &acc_no);
        getchar();
        printf("Enter the email: ");
        fgets(email, sizeof(email), stdin);
        email[strcspn(email, "\n")] = '\0';
        printf("Enter the contact number: ");
        fgets(phone_no, sizeof(phone_no), stdin);
        phone_no[strcspn(phone_no, "\n")] = '\0';
        printf("Enter the amount to withdraw: ");
        scanf("%f", &balance);

        withdraw(acc_name, acc_no, email, phone_no, balance);
        break;


    // This is the 6th case which is transfer the amount from 1st account to 2nd account and it works successfully.
    case 6:
        system("cls");
        printf("Enter the 1st account name: ");
        fgets(acc_name, sizeof(acc_name), stdin);
        acc_name[strcspn(acc_name, "\n")] = '\0'; // Remove newline character

        printf("Enter the 1st account number: ");
        scanf("%d", &acc_no);
        getchar(); // Consume the newline left by scanf

        printf("Enter the 1st email: ");
        fgets(email, sizeof(email), stdin);
        email[strcspn(email, "\n")] = '\0'; // Remove newline character

        printf("Enter the 1st contact number: ");
        fgets(phone_no, sizeof(phone_no), stdin);
        phone_no[strcspn(phone_no, "\n")] = '\0'; // Remove newline character

        printf("Enter the amount to transfer: ");
        scanf("%f", &balance);
        getchar(); // Consume the newline left by scanf

        // Second account details
        char acc2_name[60], email2[60], phone_no2[15];
        int acc2_no;

        printf("Enter the 2nd account name: ");
        fgets(acc2_name, sizeof(acc2_name), stdin);
        acc2_name[strcspn(acc2_name, "\n")] = '\0'; // Remove newline character

        printf("Enter the 2nd account number: ");
        scanf("%d", &acc2_no);
        getchar(); // Consume the newline left by scanf

        printf("Enter the 2nd email: ");
        fgets(email2, sizeof(email2), stdin);
        email2[strcspn(email2, "\n")] = '\0'; // Remove newline character

        printf("Enter the 2nd contact number: ");
        fgets(phone_no2, sizeof(phone_no2), stdin);
        phone_no2[strcspn(phone_no2, "\n")] = '\0'; // Remove newline character

        // Call the transferAmount function with both accounts' details
        transferAmount(acc_name, acc_no, email, phone_no, balance, acc2_name, acc2_no, email2, phone_no2);
        break;


        // case 7 is show the account details if you want to see account information and It's works successfully without a small error.
        case 7:
        system("cls");
        printf("Enter the 1st account name: ");
        fgets(acc_name, sizeof(acc_name), stdin);
        acc_name[strcspn(acc_name, "\n")] = '\0';

        printf("Enter the 1st email: ");
        fgets(email, sizeof(email), stdin);
        email[strcspn(email, "\n")] = '\0'; 

        viewAccountInformation(acc_name,email);
        break;


        case 8:
            break;

        case 9:
            system("cls");
            printf("Thanks for using the bank!\n\n");
            printf("Press any key to continue...");
            getchar();
            system("cls");
            system("color 07");
            exit(1);
    }
}