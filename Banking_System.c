/* Purpose:Banking Management System
Author: Pranav Vashisth*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int c; // to keep count of num of customers
typedef struct Customer
{
    char name[100];
    int ac_no, age;
    int pswd;
    float balance;
} Cust;
Cust arr[100];

void addcust();     // to add new customer to bank
void custdetails(); // including balance check
void deposit();
void withdrawl();
void invest(); // investment schemes
void loan();
void bank_management();
void loadCustomerCount(); // Load 'c' from the file
void saveCustomerCount(); // Save 'c' to the file
void load_data();         // to get data from csv
void dump_data();         // to put data to csv
int main()
{
    system("cls");       // clear screen code!!!
    load_data();
    loadCustomerCount(); // Load the customer count at the start
    printf("Welcome to our banking service!!!\n\n");
    printf("Menu: \n");
    printf("1. To add new Customer\n2. To display customer details and balance\n3. To Deposit\n4. To Withdrawl\n5. For Investment Schemes\n6. For Loan\n7. For Bank's Manager\nTo reprint menu enter 8\n");
    int ch, n = 1;
    do
    {
        printf("Enter your choice: ");
        scanf("%d", &ch);
        getchar(); // to consume any \n
        switch (ch)
        {
        case 1:
            addcust();
            dump_data();
            saveCustomerCount(); // Save the updated customer count whenever a customer is added
            break;
        case 2:
            custdetails();
            break;
        case 3:
            deposit();
            break;
        case 4:
            withdrawl();
            break;
        case 5:
            invest();
            break;
        case 6:
            loan();
            break;
        case 7:
            bank_management();
            break;
        case 8:
            printf("1. To add new Customer\n2. To display customer details and balance\n3. To Deposit\n4. To Withdrawl\n5. For Investment Schemes\n6. For Loan\n7. For Bank's Manager\n");
            break;
        default:
            printf("Invalid choice!");
            break;
        }
        printf("\nTo return enter 1 else any other num ");
        scanf("%d", &n);
        getchar(); // to consume any \n
    } while (n == 1);
    return 0;
}

void addcust()
{
    printf("Enter customer's name: ");
    fgets(arr[c].name, 100, stdin);
    printf("Enter customer's age: ");
    scanf("%d", &arr[c].age);
    printf("Enter customer's account no.: ");
    scanf("%d", &arr[c].ac_no);
    printf("Dear Customer generate a password: ");
    scanf("%d", &arr[c].pswd);
    printf("To start your account add some money: ");
    scanf("%f", &arr[c].balance);
    printf("\nCongrats! Your Account has been created!!!\nEnjoy Banking with us!!");
    printf("Your serial no. is %d. Kindly remember it for future banking options!", c);
    c++; // creating slot for next customer
}
void custdetails()
{
    int temp, pass;
    printf("Enter your serial no. ");
    scanf("%d", &temp);
    if (temp <= c)
    {
        printf("Enter password :");
        scanf("%d", &pass);
        if (pass == arr[temp].pswd)
        {
            printf("Your details are:\n\n");
            printf("Name: %s\n", arr[temp].name);
            printf("Your age: %d\n", arr[temp].age);
            printf("Your acc no. %d\n", arr[temp].ac_no);
            printf("Your balance: %f\n", arr[temp].balance);
        }
        else
            printf("Invalid Password!");
    }
    else
        printf("Customer does not exist!");
}
void deposit()
{
    int temp;
    float depo;
    printf("Enter your serial no. ");
    scanf("%d", &temp);
    if (temp <= c)
    {
        printf("Enter the amount to be deposit: ");
        scanf("%f", &depo);
        arr[temp].balance += depo;
        printf("Your acc no. %d\n", arr[temp].ac_no);
        printf("Your updated balance: %f\n", arr[temp].balance);
    }
    else
        printf("Customer does not exist!");
}
void withdrawl()
{
    int temp, pass;
    float wdl;
    printf("Enter your serial no. ");
    scanf("%d", &temp);
    if (temp <= c)
    {
        printf("Enter password :");
        scanf("%d", &pass);
        if (pass == arr[temp].pswd)
        {
            printf("Enter withdrawl amount: ");
            scanf("%f", &wdl);
            if (wdl <= arr[temp].balance)
            {
                arr[temp].balance -= wdl;
                printf("Your acc no. %d\n", arr[temp].ac_no);
                printf("Your updated balance: %f\n", arr[temp].balance);
            }
            else
                printf("Withdrawl amount exceeds the balance, either deposit money or seek a loan");
        }
        else
            printf("Invalid Password!");
    }
    else
        printf("Customer does not exist!");
}
void loan()
{
    printf("Service unavailable for now!!!");
}
void invest()
{
    printf("Service unavailable for now!!!");
}
void bank_management()
{
    int pass; // password is 123456
    printf("Enter password to access: ");
    scanf("%d", &pass);
    if (pass == 123456)
    {
        printf("Total no. of customers:  %d\n", c);
        for (int i = 0; i < c; i++)
        {
            printf("Acc no. %d      Name %s\n", arr[i].ac_no, arr[i].name);
        }
    }
    else
        printf("Access denied!!!");
}
// Function to load customer count from the file
void loadCustomerCount()
{
    FILE *countFile = fopen("CustomerCount.txt", "r");
    if (countFile != NULL)
    {
        fscanf(countFile, "%d", &c);
        fclose(countFile);
    }
    else
    {
        c = 0; // If file doesn't exist, initialize c to 0
    }
}
// Function to save customer count to the file
void saveCustomerCount()
{
    FILE *countFile = fopen("CustomerCount.txt", "w");
    if (countFile != NULL)
    {
        fprintf(countFile, "%d", c);
        fclose(countFile);
    }
}
void dump_data() {
    FILE *file;
    file = fopen("BANK.csv", "a");  // Open the file in append mode
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    for (int i = 0; i < c; i++) {
        // Ensure that you are passing all the necessary fields of the struct
        fprintf(file, "%s,%d,%d,%f,%d\n", arr[i].name, arr[i].age, arr[i].ac_no, arr[i].balance, arr[i].pswd);
    }

    fclose(file);  
}
void load_data() {
    FILE *file;
    file = fopen("BANK.csv", "r"); 
    if (file == NULL) {
        printf("No existing data file found. Starting fresh.\n");
        return; 
    }

    c = 0;

    
    while (fscanf(file, "%99[^,],%d,%d,%f,%d\n", 
                  arr[c].name, &arr[c].age, &arr[c].ac_no, &arr[c].balance, &arr[c].pswd) != EOF) {
        c++; // Increment the customer count
    }

    fclose(file);  
    printf("Loaded %d customers from BANK.csv\n", c);
}
