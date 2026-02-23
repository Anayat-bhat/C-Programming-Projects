#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_FILE "accounts.dat"
#define NAME_LENGTH 50

typedef struct {
    int accNumber;
    char name[NAME_LENGTH];
    float balance;
} Account;

/* ===================== FUNCTION DECLARATIONS ===================== */

void createAccount();
void deposit();
void withdraw();
void balanceInquiry();
void deleteAccount();
void listAccount();
int accountExists(int accNumber);

/* ===================== MAIN ===================== */

int main() {
    int choice;

    do {
        printf("\n===== BANK MANAGEMENT SYSTEM =====\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Balance Inquiry\n");
        printf("5. Delete Account\n");
        printf("6. List All Accounts\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: balanceInquiry(); break;
            case 5: deleteAccount(); break;
            case 6: listAccount(); break;
            case 7: printf("Exiting...\n"); break;
            default: printf("Invalid choice.\n");
        }

    } while (choice != 7);

    return 0;
}



/* ===================== CHECK ACCOUNT ===================== */

int accountExists(int accNumber) {
    FILE *fp = fopen(DATA_FILE, "rb");
    if (!fp) return 0;

    Account acc;

    while (fread(&acc, sizeof(Account), 1, fp)) {
        if (acc.accNumber == accNumber) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

/* ===================== CREATE ACCOUNT ===================== */

void createAccount() {
    FILE *fp = fopen(DATA_FILE, "ab");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    Account acc;

    printf("Enter Account Number: ");
    scanf("%d", &acc.accNumber);

    if (accountExists(acc.accNumber)) {
        printf("Account already exists.\n");
        fclose(fp);
        return;
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", acc.name);

    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);

    if (acc.balance < 0) {
        printf("Balance cannot be negative.\n");
        fclose(fp);
        return;
    }

    fwrite(&acc, sizeof(Account), 1, fp);
    fclose(fp);

    printf("Account created successfully.\n");
}

/* ===================== DEPOSIT ===================== */

void deposit() {
    FILE *fp = fopen(DATA_FILE, "rb+");
    if (!fp) {
        printf("No account found.\n");
        return;
    }

    int accNo;
    float amount;
    Account acc;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(Account), 1, fp)) {
        if (acc.accNumber == accNo) {

            printf("Enter amount to deposit: ");
            scanf("%f", &amount);

            if (amount <= 0) {
                printf("Invalid amount.\n");
                fclose(fp);
                return;
            }

            acc.balance += amount;

            fseek(fp, -sizeof(Account), SEEK_CUR);
            fwrite(&acc, sizeof(Account), 1, fp);

            fclose(fp);
            printf("Deposit successful.\n");
            return;
        }
    }

    fclose(fp);
    printf("Account not found.\n");
}

/* ===================== WITHDRAW ===================== */

void withdraw() {
    FILE *fp = fopen(DATA_FILE, "rb+");
    if (!fp) {
        printf("No account found.\n");
        return;
    }

    int accNo;
    float amount;
    Account acc;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(Account), 1, fp)) {
        if (acc.accNumber == accNo) {

            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);

            if (amount <= 0) {
                printf("Invalid amount.\n");
                fclose(fp);
                return;
            }

            if (acc.balance < amount) {
                printf("Insufficient balance.\n");
                fclose(fp);
                return;
            }

            acc.balance -= amount;

            fseek(fp, -sizeof(Account), SEEK_CUR);
            fwrite(&acc, sizeof(Account), 1, fp);

            fclose(fp);
            printf("Withdrawal successful.\n");
            return;
        }
    }

    fclose(fp);
    printf("Account not found.\n");
}

/* ===================== BALANCE INQUIRY ===================== */

void balanceInquiry() {
    FILE *fp = fopen(DATA_FILE, "rb");
    if (!fp) {
        printf("No account found.\n");
        return;
    }

    int accNo;
    Account acc;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(Account), 1, fp)) {
        if (acc.accNumber == accNo) {
            printf("\nAccount Number: %d\n", acc.accNumber);
            printf("Name: %s\n", acc.name);
            printf("Balance: %.2f\n", acc.balance);
            fclose(fp);
            return;
        }
    }

    fclose(fp);
    printf("Account not found.\n");
}

/* ===================== DELETE ACCOUNT ===================== */

void deleteAccount() {
    FILE *fp = fopen(DATA_FILE, "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (!fp || !temp) {
        printf("Error opening file.\n");
        return;
    }

    int accNo, found = 0;
    Account acc;

    printf("Enter Account Number to delete: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(Account), 1, fp)) {
        if (acc.accNumber != accNo) {
            fwrite(&acc, sizeof(Account), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove(DATA_FILE);
    rename("temp.dat", DATA_FILE);

    if (found)
        printf("Account deleted successfully.\n");
    else
        printf("Account not found.\n");
}

/* ===================== LIST ALL ACCOUNTS ===================== */

void listAccount() {
    FILE *fp = fopen(DATA_FILE, "rb");
    if (!fp) {
        printf("No accounts found.\n");
        return;
    }

    Account acc;
    printf("\n----- All Accounts -----\n");

    while (fread(&acc, sizeof(Account), 1, fp)) {
        printf("Acc No: %d | Name: %s | Balance: %.2f\n",
               acc.accNumber, acc.name, acc.balance);
    }

    fclose(fp);
}