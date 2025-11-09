#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <time.h>

// Constantes 
#define MAX_ACCOUNTS 150
#define MAX_TRANSACTIONS 2000
#define MAX_NAME_LENGTH 100
#define ACCOUNT_NUMBER_LENGTH 12
#define MAX_ADMINS 5

// Type d'utilisateur
typedef enum {
    ADMIN,
    USER
} UserType;

// Compte administrateur
typedef struct {
    char username[50];
    char password[50];
    int is_active;  // 1 = actif, 0 = inactif
} Admin_account;

// Structure Account 
typedef struct {
    int id;
    char account_number[ACCOUNT_NUMBER_LENGTH];
    char holder_name[MAX_NAME_LENGTH];
    double balance;
    time_t created_date;
    int is_active;  // 1 = actif, 0 = fermé
} Account;

// Structure Transaction
typedef struct {
    int id;
    char account_number[ACCOUNT_NUMBER_LENGTH];
    char transaction_type[20];  // "DEPOSIT", "WITHDRAWAL"
    double amount;
    time_t transaction_date;
} Transaction;

// Structure Bank 
typedef struct {
    Account accounts[MAX_ACCOUNTS];
    int account_nb;
    Transaction transactions[MAX_TRANSACTIONS];
    int transaction_nb;
    Admin_account admins[MAX_ADMINS]; 
    int admin_count;                    
} Bank;

//  Fonctions générales
void initialize_bank(Bank *bank);
int create_account(Bank *bank, const char *name);
Account* find_account(Bank *bank, const char *account_number);
void display_account_info(Account *account);

// Fonctions de transaction
void deposit(Bank *bank, const char *account_number, double amount);
void withdraw(Bank *bank, const char *account_number, double amount);
void display_balance(Bank *bank, const char *account_number);
void display_transactions(Bank *bank, const char *account_number);

// Fonctions ADMIN seulement
void add_transaction(Bank *bank, const char *account_number, const char *type, double amount);
void close_account(Bank *bank, const char *account_number);
void reopen_account(Bank *bank, const char *account_number);
void display_all_accounts(Bank *bank);

//  Fonctions d'authentification
int add_admin(Bank *bank, const char *username, const char *password);
int authenticate_admin(Bank *bank, const char *username, const char *password);

// Nouvelles fonctionnalités
void menu_persistence(Bank *bank);
void menu_transfer(Bank *bank);
void menu_statement(Bank *bank);
void menu_interest(Bank *bank);

#endif

