#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include "account.h"

// Fichiers de données
#define ACCOUNTS_FILE "data/accounts.csv"
#define TRANSACTIONS_FILE "data/transactions.csv"
#define ADMINS_FILE "data/admins.csv"

// Taux d'intérêt annuel pour compte épargne
#define INTEREST_RATE 0.03  // 3%

// Fonctions de persistence (CSV)
int save_accounts_to_csv(Bank *bank);
int load_accounts_from_csv(Bank *bank);
int save_transactions_to_csv(Bank *bank);
int load_transactions_from_csv(Bank *bank);
int save_admins_to_csv(Bank *bank);
int load_admins_from_csv(Bank *bank);

// Sauvegarder/charger tout
int save_all_data(Bank *bank);
int load_all_data(Bank *bank);

// Transfert d'argent
int transfer_money(Bank *bank, const char *from_account, const char *to_account, double amount);

// Relevé de compte
int generate_statement(Bank *bank, const char *account_number, const char *filename);

// Calcul d'intérêts
double calculate_interest(double balance, int days);
void apply_interest_to_account(Bank *bank, const char *account_number);
void apply_interest_to_all_accounts(Bank *bank);

#endif
