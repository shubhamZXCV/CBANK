#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

enum AccountType
{
    savings,
    current
};
char *AccountTypestr[] = {"savings", "current"};

typedef struct AccountInfo
{
    int accountNumber;
    enum AccountType accountType;
    char name[50];
    float accountBalance;
} AccountInfo;

typedef struct Node
{
    AccountInfo data;
    struct Node *next;
} Node;

typedef Node *LinkedList;

int size(LinkedList l)
{
    int s = 0;
    while (l != NULL)
    {
        s++;
        l = l->next;
    }
    return s;
}

Node *findNode(LinkedList l, int pos)
{
    while (pos--)
    {
        l = l->next;
    }
    return l;
}
bool doesAccountExistByNameAccountType(LinkedList l, enum AccountType type, char name[])
{
    while (l != NULL)
    {
        if (strcmp(l->data.name, name) == 0 && l->data.accountType == type)
        {
            return true;
        }
        l = l->next;
    }
    return false;
}

bool doesAccountExistByAccountNumber(LinkedList l, int accountNumber)
{
    int start = 0;
    int end = size(l) - 1;
    while (start <= end)
    {
        int mid = start + (end - start) / 2;
        Node *current = findNode(l, mid);
        if (current->data.accountNumber == accountNumber)
        {
            return true;
        }
        if (current->data.accountNumber > accountNumber)
        {
            end = mid - 1;
        }
        else
        {
            start = mid + 1;
        }
    }
    return false;
}

Node *NodeAtAccountNumber(LinkedList l, int accountNumber)
{
    int start = 0;
    int end = size(l) - 1;
    while (start <= end)
    {
        int mid = start + (end - start) / 2;
        Node *current = findNode(l, mid);
        if (current->data.accountNumber == accountNumber)
        {
            return current;
        }
        if (current->data.accountNumber > accountNumber)
        {
            end = mid - 1;
        }
        else
        {
            start = mid + 1;
        }
    }
    return NULL;
}

LinkedList createAccount(LinkedList l)
{
    Node *head = l;
    AccountInfo person;
    char type[10];
    scanf("%s", type);
    if (strcmp(type, "savings") == 0)
    {
        person.accountType = savings;
    }
    else if (strcmp(type, "current") == 0)
    {
        person.accountType = current;
    }
    scanf("%s", person.name);
    scanf("%f", &person.accountBalance);
    // person.accountNumber = size(l) + 101;

    Node *newAccount = (Node *)malloc(sizeof(Node));
    newAccount->data = person;

    if (doesAccountExistByNameAccountType(l, person.accountType, person.name) == true)
    {
        printf("Invalid: User already exists!\n");
        return head;
    }
    else
    {
        

        if (l == NULL)
        {
            newAccount->data.accountNumber = 100;
            newAccount->next = NULL;
            printf("Account Number:%d\n", newAccount->data.accountNumber);
            printf("Account Holder: %s\n", newAccount->data.name);
            printf("Account Type: %s\n", AccountTypestr[newAccount->data.accountType]);
            printf("Balance: Rs %.2f\n", newAccount->data.accountBalance);
            return newAccount;
        }

        if (l->data.accountNumber != 100)
        {
            newAccount->data.accountNumber = 100;
            newAccount->next = l;
            printf("Account Number:%d\n", newAccount->data.accountNumber);
            printf("Account Holder: %s\n", newAccount->data.name);
            printf("Account Type: %s\n", AccountTypestr[newAccount->data.accountType]);
            printf("Balance: Rs %.2f\n", newAccount->data.accountBalance);
            return newAccount;
        }

        while (l->next != NULL)
        {
            if ((l->next->data.accountNumber) - (l->data.accountNumber) != 1)
            {

                break;
            }
            l = l->next;
        }
        if (l->next == NULL)
        {
            newAccount->data.accountNumber = l->data.accountNumber + 1;
            newAccount->next = NULL;
            l->next = newAccount;
            printf("Account Number:%d\n", newAccount->data.accountNumber);
            printf("Account Holder: %s\n", newAccount->data.name);
            printf("Account Type: %s\n", AccountTypestr[newAccount->data.accountType]);
            printf("Balance: Rs %.2f\n", newAccount->data.accountBalance);
            return head;
        }
        else
        {

            newAccount->data.accountNumber = l->data.accountNumber + 1;
            newAccount->next = l->next;
            l->next = newAccount;
            printf("Account Number:%d\n", newAccount->data.accountNumber);
            printf("Account Holder: %s\n", newAccount->data.name);
            printf("Account Type: %s\n", AccountTypestr[newAccount->data.accountType]);
            printf("Balance: Rs %.2f\n", newAccount->data.accountBalance);
            return head;
        }
    }
}

LinkedList deleteAccount(LinkedList l)
{
    Node *head = l;
    int accountNumber;
    char accountType[10];
    char name[10];
    scanf("%d", &accountNumber);
    scanf("%s", accountType);
    scanf("%s", name);

    int start = 0;
    int end = size(l) - 1;

    while (start <= end)
    {
        int mid = start + (end - start) / 2;

        if (findNode(l, mid)->data.accountNumber == accountNumber)
        {
            if ((strcmp(findNode(l, mid)->data.name, name) != 0) || strcmp(AccountTypestr[findNode(l, mid)->data.accountType], accountType) != 0)
            {
                printf("Invalid: User does not exist");
                return head;
            }

            else
            {

                if (mid == 0)
                {
                    printf("Account deleted successfully");
                    return head->next;
                }
                if (mid == size(l) - 1)
                {
                    printf("Account deleted successfully");
                    findNode(l, size(l) - 2)->next = NULL;
                    return head;
                }

                findNode(l, mid - 1)->next = findNode(l, mid + 1);
                printf("Account deleted successfully");
                return head;
            }
            if (findNode(l, mid)->data.accountNumber > accountNumber)
            {
                end = mid - 1;
            }
            else
            {
                start = mid + 1;
            }
        }
    }
    printf("Invalid: User does not exist");
    return head;
}

void lowBalanceAccounts(LinkedList l)
{

    while (l != NULL)
    {
        if (l->data.accountBalance < 100)
        {
            printf("Account Number:%d,AccountHolder:%s,balance:%.2f\n", l->data.accountNumber, l->data.name, l->data.accountBalance);
            l = l->next;
        }
    }
}

void transaction(LinkedList l)
{
    int accountNumber;
    scanf("%d", &accountNumber);
    float amount;
    scanf("%f", &amount);
    int code;
    scanf("%d", &code);

    Node *current = NodeAtAccountNumber(l, accountNumber);

    if (doesAccountExistByAccountNumber(l, accountNumber) == false)
    {
        printf("Invalid: User does not exist\n");
        return;
    }
    else
    {
        if (code == 1)
        {
            current->data.accountBalance += amount;
            printf("Updated balance is Rs %0.2f\n", current->data.accountBalance);
        }
        if (code == 0)
        {
            if (current->data.accountBalance - amount >= 100)
            {
                current->data.accountBalance -= amount;
                printf("Updated balance is Rs %0.2f\n", current->data.accountBalance);
            }
            else
            {
                printf("The balance is insufficient for the specified withdrawal.\n");
            }
        }
    }
}
void display(LinkedList l)
{
    if (l == NULL)
    {
        printf("No Accounts to display\n");
        return;
    }
    printf("Account Number\tAccount Holder\tAccount Type\tBalance\n");
    while (l != NULL)
    {
        printf("%d\t\t%s\t\t%s\t\t%.2f\n", l->data.accountNumber, l->data.name, AccountTypestr[l->data.accountType], l->data.accountBalance);
        l = l->next;
    }
}

int main()
{
    printf("\t\t\t\t\t\t\t\t\tWelcome to IIIT BANK\n");
    printf("\n");
    printf("\n");
    printf("\t\t\t\tUSER MENU\n");
    printf("\n");
    printf("To create account:\n");
    printf("Type CREATE ACCOUNT TYPE NAME AMOUNT\n");
    printf("To delete your account :\n");
    printf("Type DELETE ACCOUNT NUMBER ACCOUNT TYPE ACCOUNT HOLDER\n");
    printf("TO ADD or WITHDRAW money\n");
    printf("Type TRANSACTION ACCOUNT NUMBER AMOUNT CODE(1->deposit,0->withdrawal)\n");
    printf("To access the database of our bank:\n");
    printf("Type DISPLAY\n");
    printf("To get list of people with lowbalance\n");
    printf("Type LOWBALANCE ");

    LinkedList L = NULL;

    while (1)
    {

        char operation[10];
        scanf("%s", operation);

        if (strcmp(operation, "CREATE") == 0)
        {
            L = createAccount(L);
        }
        else if (strcmp(operation, "DISPLAY") == 0)
        {
            display(L);
        }
        else if (strcmp(operation, "DELETE") == 0)
        {
            L = deleteAccount(L);
        }

        else if (strcmp(operation, "LOWBALANCE") == 0)
        {
            lowBalanceAccounts(L);
        }
        else if (strcmp(operation, "TRANSACTION") == 0)
        {
            transaction(L);
        }
        else if (strcmp(operation, "EXIT") == 0)
        {
            break;
        }
    }

    return 0;
}