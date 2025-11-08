#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/account.h"



void initialize_bank(Bank *bank){
    bank -> account_nb =0; //val
    bank -> transaction_nb =0;
    bank -> admin_count =0;

    // Créer un compte admin par défaut
    strcpy(bank->admins[0].username, "admin");
    strcpy(bank->admins[0].password, "admin");
    bank->admins[0].is_active = 1;
    bank->admin_count = 1;


    printf("✓ Banque initialisée!\n");
    printf("  Admin: username='admin', password='admin'\n");

}



int add_admin(Bank *bank, const char *username, const char *password) {
    //  Vérifier si limite atteinte
    if (bank->admin_count >= MAX_ADMINS) {
        printf("Erreur: Limite d'admins atteinte!\n");
        return -1;
    }
    
//  Vérifier si username existe 

    for (int i=0; i< bank->admin_count ;i++){
        if (strcmp(bank->admins[i].username, username) == 0){
            printf("Erreur ! nom existe déjà\n");
            return -1;
        }
    }


    //ajouter le nouveau admin 
    strcpy(bank->admins[bank->admin_count].username, username);
    strcpy(bank->admins[bank->admin_count].password, password);
    bank->admins[bank->admin_count].is_active = 1;
    bank->admin_count++;


    printf("✓ Admin '%s' ajouté!\n", username);
    return bank->admin_count - 1;
}


int authenticate_admin(Bank *bank, const char *username, const char *password) {
    // Parcourir tous les admins
    for (int i = 0; i < bank->admin_count; i++) {
        // Vérifier si actif ET username correct ET password correct
        if (bank->admins[i].is_active &&
            strcmp(bank->admins[i].username, username) == 0 &&
            strcmp(bank->admins[i].password, password) == 0) {
            
            printf("✓ Bienvenue %s!\n", username);
            return 1;  
        }
    }
    
    printf("✗ Identifiants incorrects!\n");
    return 0;  
}


void generate_account_number(char *account_number, int account_id) {
    sprintf(account_number, "ACC%06d", 1001 + account_id);
    // Exemple: ACC001001, ACC001002, etc.
}




int create_account(Bank *bank, const char *name) {
    // 1. Vérifier limite
    if (bank->account_nb >= MAX_ACCOUNTS) {
        printf("Erreur: Limite de comptes atteinte!\n");
        return -1;
    }
    
    // 2. Vérifier nom valide
    if (strlen(name) == 0) {
        printf("Erreur: Nom vide!\n");
        return -1;
    }

    //creer le compte 
    Account *new_account = &bank->accounts[bank->account_nb];
    new_account->id = bank->account_nb;
    generate_account_number(new_account->account_number, new_account->id);
    strcpy(new_account->holder_name, name);
    new_account->balance = 0.0;
    new_account->created_date = time(NULL);
    new_account->is_active = 1;
    bank->account_nb++;

     printf("\n✓ Compte créé!\n");
    printf("  N°: %s\n", new_account->account_number);
    printf("  Titulaire: %s\n", new_account->holder_name);
    
    return new_account->id;
}

Account* find_account(Bank *bank, const char *account_number) {
    for (int i = 0; i < bank->account_nb; i++) {
        if (strcmp(bank->accounts[i].account_number, account_number) == 0) {
            return &bank->accounts[i];  // Retourne l'adresse
        }
    }
    printf("Erreur: Compte introuvable!\n");
    return NULL;  // Pas trouvé
}

void display_account_info(Account *account) {
    if (account == NULL) {
        return;  // Sortir si pointeur NULL
    }
    
    printf("\n========== INFOS COMPTE ==========\n");
    printf("Numéro: %s\n", account->account_number);
    printf("Titulaire: %s\n", account->holder_name);
    printf("Solde: %.2f DT\n", account->balance);
    printf("Date création: %s", ctime(&account->created_date));
    printf("Statut: %s\n", account->is_active ? "ACTIF" : "FERMÉ");
    printf("==================================\n");
}

void close_account(Bank *bank, const char *account_number) {
    Account *account = find_account(bank, account_number);
    
    if (account == NULL) return;
    
    // Vérifier si déjà fermé
    if (!account->is_active) {
        printf("⚠ Compte déjà fermé!\n");
        return;
    }
    
    // Vérifier solde = 0
    if (account->balance != 0.0) {
        printf("Erreur: Solde doit être à 0! (Actuel: %.2f DT)\n", 
               account->balance);
        return;
    }
    
    account->is_active = 0;
    printf("✓ Compte fermé!\n");
}

void reopen_account(Bank *bank, const char *account_number) {
    Account *account = find_account(bank, account_number);
    
    if (account == NULL) {
        return;
    }
    
    if (account->is_active) {
        printf("⚠ Ce compte est déjà actif!\n");
        return;
    }
    
    account->is_active = 1;
    printf("✓ Compte %s réactivé avec succès!\n", account_number);
}

void display_all_accounts(Bank *bank) {
    if (bank->account_nb == 0) {
        printf("\nAucun compte.\n");
        return;
    }
    
    printf("\n========== TOUS LES COMPTES ==========\n");
    printf("Total: %d compte(s)\n\n", bank->account_nb);
    
    for (int i = 0; i < bank->account_nb; i++) {
        printf("%d. N°: %s | ", i+1, bank->accounts[i].account_number);
        printf("Nom: %s | ", bank->accounts[i].holder_name);
        printf("Solde: %.2f DT | ", bank->accounts[i].balance);
        printf("Statut: %s\n", bank->accounts[i].is_active ? "✓" : "✗");
    }
    printf("======================================\n");
}

void add_transaction(Bank *bank, const char *account_number, 
                     const char *type, double amount) {
    if (bank->transaction_nb >= MAX_TRANSACTIONS) {
        printf("Erreur: Limite transactions atteinte!\n");
        return;
    }
    
    Transaction *trans = &bank->transactions[bank->transaction_nb];
    trans->id = bank->transaction_nb;
    strcpy(trans->account_number, account_number);
    strcpy(trans->transaction_type, type);
    trans->amount = amount;
    trans->transaction_date = time(NULL);
    
    bank->transaction_nb++;
}

void deposit(Bank *bank, const char *account_number, double amount) {
    Account *account = find_account(bank, account_number);
    if (account == NULL) return;
    
    // Vérifier compte actif
    if (!account->is_active) {
        printf("Erreur: Compte fermé!\n");
        return;
    }
    
    // Vérifier montant positif
    if (amount <= 0) {
        printf("Erreur: Montant doit être > 0!\n");
        return;
    }
    
    // Effectuer le dépôt
    account->balance += amount;
    add_transaction(bank, account_number, "DEPOSIT", amount);
    
    printf("\n✓ Dépôt réussi!\n");
    printf("  Montant: %.2f DT\n", amount);
    printf("  Nouveau solde: %.2f DT\n", account->balance);
}

void withdraw(Bank *bank, const char *account_number, double amount) {
    Account *account = find_account(bank, account_number);
    if (account == NULL) return;
    
    // Vérifier compte actif
    if (!account->is_active) {
        printf("Erreur: Compte fermé!\n");
        return;
    }
    
    // Vérifier montant positif
    if (amount <= 0) {
        printf("Erreur: Montant doit être > 0!\n");
        return;
    }
    
    // Vérifier solde suffisant
    if (account->balance < amount) {
        printf("Erreur: Solde insuffisant!\n");
        printf("  Solde: %.2f DT\n", account->balance);
        printf("  Demandé: %.2f DT\n", amount);
        return;
    }
    
    // Effectuer le retrait
    account->balance -= amount;
    add_transaction(bank, account_number, "WITHDRAWAL", amount);
    
    printf("\n✓ Retrait réussi!\n");
    printf("  Montant: %.2f DT\n", amount);
    printf("  Nouveau solde: %.2f DT\n", account->balance);
}

void display_transactions(Bank *bank, const char *account_number) {
    printf("\n========== HISTORIQUE ==========\n");
    printf("Compte: %s\n", account_number);
    printf("================================\n");
    
    int count = 0;
    for (int i = 0; i < bank->transaction_nb; i++) {
        if (strcmp(bank->transactions[i].account_number, account_number) == 0) {
            count++;
            printf("\n#%d - %s\n", count, 
                   bank->transactions[i].transaction_type);
            printf("  Montant: %.2f DT\n", bank->transactions[i].amount);
            printf("  Date: %s", ctime(&bank->transactions[i].transaction_date));
        }
    }
    
    if (count == 0) {
        printf("\nAucune transaction.\n");
    }
    printf("================================\n");
}

void display_balance(Bank *bank, const char *account_number) {
    Account *account = find_account(bank, account_number);
    if (account == NULL) return;
    
    printf("\n========== SOLDE ==========\n");
    printf("Compte: %s\n", account->account_number);
    printf("Titulaire: %s\n", account->holder_name);
    printf("Solde: %.2f DT\n", account->balance);
    printf("===========================\n");
}




