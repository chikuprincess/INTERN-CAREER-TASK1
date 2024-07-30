#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define MAX_TRANSACTIONS 100
#define MAX_ACCOUNTS 50

// Structure to store transaction details
typedef struct {
    char type[10]; // Deposit or Withdraw
    double amount;
} Transaction;

// Structure to store bank account details
typedef struct {
    int accountNumber;
    char accountHolderName[100];
    double balance;
    int transactionCount;
    Transaction transactionHistory[MAX_TRANSACTIONS];
} BankAccount;
// Array to store bank accounts
BankAccount accounts[MAX_ACCOUNTS];
int accountCount = 0;

// Function to create a new bank account
void createAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Cannot create more accounts. Limit reached.\n");
        return;
    }
    
    BankAccount newAccount;
    newAccount.accountNumber = accountCount + 1; // Simple incrementing account number
    printf("Enter account holder name: ");
    scanf("%s", newAccount.accountHolderName);
    newAccount.balance = 0.0;
    newAccount.transactionCount = 0;
    
    accounts[accountCount++] = newAccount;
    printf("Account created successfully. Account Number: %d\n", newAccount.accountNumber);
}

// Function to deposit funds into an account
void deposit(int accountNumber, double amount) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            accounts[i].balance += amount;
            Transaction transaction = {"Deposit", amount};
            accounts[i].transactionHistory[accounts[i].transactionCount++] = transaction;
            printf("Deposit successful. New balance: %.2f\n", accounts[i].balance);
            return;
        }
    }
    printf("Invalid account number.\n");
}

// Function to withdraw funds from an account
void withdraw(int accountNumber, double amount) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            if (accounts[i].balance < amount) {
                printf("Insufficient funds.\n");
                return;
            }
            accounts[i].balance -= amount;
            Transaction transaction = {"Withdraw", amount};
            accounts[i].transactionHistory[accounts[i].transactionCount++] = transaction;
            printf("Withdrawal successful. New balance: %.2f\n", accounts[i].balance);
            return;
        }
    }
    printf("Invalid account number.\n");
}

// Function to check account balance
void checkBalance(int accountNumber) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            printf("Account Balance: %.2f\n", accounts[i].balance);
            return;
        }
    }
    printf("Invalid account number.\n");
}

// Function to view transaction history for an account
void viewTransactionHistory(int accountNumber) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            printf("Transaction History for Account Number %d:\n", accountNumber);
            for (int j = 0; j < accounts[i].transactionCount; j++) {
                printf("%s: %.2f\n", accounts[i].transactionHistory[j].type, accounts[i].transactionHistory[j].amount);
            }
            return;
        }
    }
    printf("Invalid account number.\n");
}
void displayMenu() {
    printf("\nBanking System Menu:\n");
    printf("1. Create a new bank account\n");
    printf("2. Deposit funds into an account\n");
    printf("3. Withdraw funds from an account\n");
    printf("4. Check account balance\n");
    printf("5. View transaction history for an account\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice, accountNumber;
    double amount;

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                printf("Enter amount to deposit: ");
                scanf("%lf", &amount);
                deposit(accountNumber, amount);
                break;
            case 3:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                printf("Enter amount to withdraw: ");
                scanf("%lf", &amount);
                withdraw(accountNumber, amount);
                break;
            case 4:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                checkBalance(accountNumber);
                break;
            case 5:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                viewTransactionHistory(accountNumber);
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
