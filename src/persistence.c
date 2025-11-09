#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "../include/persistence.h"

// ============================================
// UTILITAIRES
// ============================================

// Créer le dossier data s'il n'existe pas
void ensure_data_directory() {
    struct stat st = {0};
    if (stat("data", &st) == -1) {
        mkdir("data", 0700);
    }
}

// ============================================
// SAUVEGARDE CSV - COMPTES
// ============================================

int save_accounts_to_csv(Bank *bank) {
    ensure_data_directory();
    
    FILE *file = fopen(ACCOUNTS_FILE, "w");
    if (file == NULL) {
        printf("❌ Erreur: Impossible de créer %s\n", ACCOUNTS_FILE);
        return -1;
    }
    
    // En-tête CSV
    fprintf(file, "id,account_number,holder_name,balance,created_date,is_active\n");
    
    // Écrire chaque compte
    for (int i = 0; i < bank->account_nb; i++) {
        Account *acc = &bank->accounts[i];
        fprintf(file, "%d,%s,%s,%.2f,%ld,%d\n",
                acc->id,
                acc->account_number,
                acc->holder_name,
                acc->balance,
                (long)acc->created_date,
                acc->is_active);
    }
    
    fclose(file);
    printf("✓ %d comptes sauvegardés dans %s\n", bank->account_nb, ACCOUNTS_FILE);
    return 0;
}

int load_accounts_from_csv(Bank *bank) {
    FILE *file = fopen(ACCOUNTS_FILE, "r");
    if (file == NULL) {
        printf("⚠️  Aucun fichier de comptes trouvé. Démarrage avec banque vide.\n");
        return 0;
    }
    
    char line[256];
    // Ignorer l'en-tête
    fgets(line, sizeof(line), file);
    
    bank->account_nb = 0;
    while (fgets(line, sizeof(line), file)) {
        Account *acc = &bank->accounts[bank->account_nb];
        long created_date_long;
        
        sscanf(line, "%d,%[^,],%[^,],%lf,%ld,%d",
               &acc->id,
               acc->account_number,
               acc->holder_name,
               &acc->balance,
               &created_date_long,
               &acc->is_active);
        
        acc->created_date = (time_t)created_date_long;
        bank->account_nb++;
        
        if (bank->account_nb >= MAX_ACCOUNTS) break;
    }
    
    fclose(file);
    printf("✓ %d comptes chargés depuis %s\n", bank->account_nb, ACCOUNTS_FILE);
    return 0;
}

// ============================================
// SAUVEGARDE CSV - TRANSACTIONS
// ============================================

int save_transactions_to_csv(Bank *bank) {
    ensure_data_directory();
    
    FILE *file = fopen(TRANSACTIONS_FILE, "w");
    if (file == NULL) {
        printf("❌ Erreur: Impossible de créer %s\n", TRANSACTIONS_FILE);
        return -1;
    }
    
    fprintf(file, "id,account_number,transaction_type,amount,transaction_date\n");
    
    for (int i = 0; i < bank->transaction_nb; i++) {
        Transaction *trans = &bank->transactions[i];
        fprintf(file, "%d,%s,%s,%.2f,%ld\n",
                trans->id,
                trans->account_number,
                trans->transaction_type,
                trans->amount,
                (long)trans->transaction_date);
    }
    
    fclose(file);
    printf("✓ %d transactions sauvegardées dans %s\n", bank->transaction_nb, TRANSACTIONS_FILE);
    return 0;
}

int load_transactions_from_csv(Bank *bank) {
    FILE *file = fopen(TRANSACTIONS_FILE, "r");
    if (file == NULL) {
        printf("⚠️  Aucun fichier de transactions trouvé.\n");
        return 0;
    }
    
    char line[256];
    fgets(line, sizeof(line), file); // Ignorer en-tête
    
    bank->transaction_nb = 0;
    while (fgets(line, sizeof(line), file)) {
        Transaction *trans = &bank->transactions[bank->transaction_nb];
        long trans_date_long;
        
        sscanf(line, "%d,%[^,],%[^,],%lf,%ld",
               &trans->id,
               trans->account_number,
               trans->transaction_type,
               &trans->amount,
               &trans_date_long);
        
        trans->transaction_date = (time_t)trans_date_long;
        bank->transaction_nb++;
        
        if (bank->transaction_nb >= MAX_TRANSACTIONS) break;
    }
    
    fclose(file);
    printf("✓ %d transactions chargées depuis %s\n", bank->transaction_nb, TRANSACTIONS_FILE);
    return 0;
}

// ============================================
// SAUVEGARDE CSV - ADMINS
// ============================================

int save_admins_to_csv(Bank *bank) {
    ensure_data_directory();
    
    FILE *file = fopen(ADMINS_FILE, "w");
    if (file == NULL) {
        printf("❌ Erreur: Impossible de créer %s\n", ADMINS_FILE);
        return -1;
    }
    
    fprintf(file, "username,password,is_active\n");
    
    for (int i = 0; i < bank->admin_count; i++) {
        Admin_account *admin = &bank->admins[i];
        fprintf(file, "%s,%s,%d\n",
                admin->username,
                admin->password,
                admin->is_active);
    }
    
    fclose(file);
    printf("✓ %d admins sauvegardés dans %s\n", bank->admin_count, ADMINS_FILE);
    return 0;
}

int load_admins_from_csv(Bank *bank) {
    FILE *file = fopen(ADMINS_FILE, "r");
    if (file == NULL) {
        printf("⚠️  Aucun fichier d'admins trouvé.\n");
        return 0;
    }
    
    char line[256];
    fgets(line, sizeof(line), file); // Ignorer en-tête
    
    bank->admin_count = 0;
    while (fgets(line, sizeof(line), file)) {
        Admin_account *admin = &bank->admins[bank->admin_count];
        
        sscanf(line, "%[^,],%[^,],%d",
               admin->username,
               admin->password,
               &admin->is_active);
        
        bank->admin_count++;
        
        if (bank->admin_count >= MAX_ADMINS) break;
    }
    
    fclose(file);
    printf("✓ %d admins chargés depuis %s\n", bank->admin_count, ADMINS_FILE);
    return 0;
}

// ============================================
// SAUVEGARDE/CHARGEMENT GLOBAL
// ============================================

int save_all_data(Bank *bank) {
    printf("\n💾 Sauvegarde des données...\n");
    save_accounts_to_csv(bank);
    save_transactions_to_csv(bank);
    save_admins_to_csv(bank);
    printf("✅ Toutes les données ont été sauvegardées!\n");
    return 0;
}

int load_all_data(Bank *bank) {
    printf("\n📂 Chargement des données...\n");
    load_accounts_from_csv(bank);
    load_transactions_from_csv(bank);
    load_admins_from_csv(bank);
    printf("✅ Toutes les données ont été chargées!\n");
    return 0;
}

// ============================================
// TRANSFERT D'ARGENT
// ============================================

int transfer_money(Bank *bank, const char *from_account, const char *to_account, double amount) {
    // Trouver les comptes
    Account *from = NULL;
    Account *to = NULL;
    
    for (int i = 0; i < bank->account_nb; i++) {
        if (strcmp(bank->accounts[i].account_number, from_account) == 0) {
            from = &bank->accounts[i];
        }
        if (strcmp(bank->accounts[i].account_number, to_account) == 0) {
            to = &bank->accounts[i];
        }
    }
    
    // Vérifications
    if (from == NULL) {
        printf("❌ Compte source introuvable: %s\n", from_account);
        return -1;
    }
    
    if (to == NULL) {
        printf("❌ Compte destinataire introuvable: %s\n", to_account);
        return -1;
    }
    
    if (!from->is_active) {
        printf("❌ Compte source fermé!\n");
        return -1;
    }
    
    if (!to->is_active) {
        printf("❌ Compte destinataire fermé!\n");
        return -1;
    }
    
    if (amount <= 0) {
        printf("❌ Montant invalide!\n");
        return -1;
    }
    
    if (from->balance < amount) {
        printf("❌ Solde insuffisant! (Solde: %.2f DT)\n", from->balance);
        return -1;
    }
    
    // Effectuer le transfert
    from->balance -= amount;
    to->balance += amount;
    
    // Enregistrer les transactions
    if (bank->transaction_nb < MAX_TRANSACTIONS) {
        Transaction *trans1 = &bank->transactions[bank->transaction_nb++];
        trans1->id = bank->transaction_nb - 1;
        strcpy(trans1->account_number, from_account);
        strcpy(trans1->transaction_type, "TRANSFER_OUT");
        trans1->amount = amount;
        trans1->transaction_date = time(NULL);
    }
    
    if (bank->transaction_nb < MAX_TRANSACTIONS) {
        Transaction *trans2 = &bank->transactions[bank->transaction_nb++];
        trans2->id = bank->transaction_nb - 1;
        strcpy(trans2->account_number, to_account);
        strcpy(trans2->transaction_type, "TRANSFER_IN");
        trans2->amount = amount;
        trans2->transaction_date = time(NULL);
    }
    
    printf("\n✅ Transfert réussi!\n");
    printf("   De: %s (Nouveau solde: %.2f DT)\n", from_account, from->balance);
    printf("   Vers: %s (Nouveau solde: %.2f DT)\n", to_account, to->balance);
    printf("   Montant: %.2f DT\n", amount);
    
    return 0;
}

// ============================================
// RELEVÉ DE COMPTE
// ============================================

int generate_statement(Bank *bank, const char *account_number, const char *filename) {
    // Trouver le compte
    Account *account = NULL;
    for (int i = 0; i < bank->account_nb; i++) {
        if (strcmp(bank->accounts[i].account_number, account_number) == 0) {
            account = &bank->accounts[i];
            break;
        }
    }
    
    if (account == NULL) {
        printf("❌ Compte introuvable!\n");
        return -1;
    }
    
    // Créer le fichier
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("❌ Erreur: Impossible de créer le relevé\n");
        return -1;
    }
    
    // En-tête du relevé
    fprintf(file, "═══════════════════════════════════════════════════════\n");
    fprintf(file, "              RELEVÉ DE COMPTE BANCAIRE                \n");
    fprintf(file, "═══════════════════════════════════════════════════════\n\n");
    
    // Informations du compte
    fprintf(file, "Numéro de compte: %s\n", account->account_number);
    fprintf(file, "Titulaire: %s\n", account->holder_name);
    fprintf(file, "Date de création: %s", ctime(&account->created_date));
    fprintf(file, "Statut: %s\n", account->is_active ? "ACTIF" : "FERMÉ");
    fprintf(file, "Solde actuel: %.2f DT\n\n", account->balance);
    
    fprintf(file, "═══════════════════════════════════════════════════════\n");
    fprintf(file, "                  HISTORIQUE DES TRANSACTIONS          \n");
    fprintf(file, "═══════════════════════════════════════════════════════\n\n");
    
    // Transactions
    int count = 0;
    double total_in = 0.0;
    double total_out = 0.0;
    
    for (int i = 0; i < bank->transaction_nb; i++) {
        if (strcmp(bank->transactions[i].account_number, account_number) == 0) {
            count++;
            Transaction *trans = &bank->transactions[i];
            
            fprintf(file, "%d. Type: %-15s | Montant: %10.2f DT\n",
                    count, trans->transaction_type, trans->amount);
            fprintf(file, "   Date: %s\n", ctime(&trans->transaction_date));
            
            if (strcmp(trans->transaction_type, "DEPOSIT") == 0 ||
                strcmp(trans->transaction_type, "TRANSFER_IN") == 0) {
                total_in += trans->amount;
            } else {
                total_out += trans->amount;
            }
        }
    }
    
    if (count == 0) {
        fprintf(file, "Aucune transaction trouvée.\n");
    }
    
    // Résumé
    fprintf(file, "\n═══════════════════════════════════════════════════════\n");
    fprintf(file, "                      RÉSUMÉ                           \n");
    fprintf(file, "═══════════════════════════════════════════════════════\n");
    fprintf(file, "Total des crédits: %.2f DT\n", total_in);
    fprintf(file, "Total des débits: %.2f DT\n", total_out);
    fprintf(file, "Nombre de transactions: %d\n", count);
    fprintf(file, "═══════════════════════════════════════════════════════\n");
    
    time_t now = time(NULL);
    fprintf(file, "\nRélevé généré le: %s", ctime(&now));
    
    fclose(file);
    
    printf("✅ Relevé généré: %s\n", filename);
    return 0;
}

// ============================================
// CALCUL D'INTÉRÊTS
// ============================================

double calculate_interest(double balance, int days) {
    // Intérêt = Capital × Taux × (Jours / 365)
    return balance * INTEREST_RATE * (days / 365.0);
}

void apply_interest_to_account(Bank *bank, const char *account_number) {
    Account *account = NULL;
    for (int i = 0; i < bank->account_nb; i++) {
        if (strcmp(bank->accounts[i].account_number, account_number) == 0) {
            account = &bank->accounts[i];
            break;
        }
    }
    
    if (account == NULL) {
        printf("❌ Compte introuvable!\n");
        return;
    }
    
    if (!account->is_active) {
        printf("❌ Compte fermé!\n");
        return;
    }
    
    // Calculer les jours depuis la création
    time_t now = time(NULL);
    int days = (int)difftime(now, account->created_date) / 86400; // 86400 sec = 1 jour
    
    if (days < 1) {
        printf("⚠️  Compte trop récent pour appliquer des intérêts.\n");
        return;
    }
    
    double interest = calculate_interest(account->balance, days);
    account->balance += interest;
    
    // Enregistrer la transaction
    if (bank->transaction_nb < MAX_TRANSACTIONS) {
        Transaction *trans = &bank->transactions[bank->transaction_nb++];
        trans->id = bank->transaction_nb - 1;
        strcpy(trans->account_number, account_number);
        strcpy(trans->transaction_type, "INTEREST");
        trans->amount = interest;
        trans->transaction_date = now;
    }
    
    printf("✅ Intérêts appliqués!\n");
    printf("   Compte: %s\n", account_number);
    printf("   Période: %d jours\n", days);
    printf("   Intérêts: %.2f DT\n", interest);
    printf("   Nouveau solde: %.2f DT\n", account->balance);
}

void apply_interest_to_all_accounts(Bank *bank) {
    printf("\n💰 Application des intérêts à tous les comptes...\n\n");
    
    int count = 0;
    for (int i = 0; i < bank->account_nb; i++) {
        if (bank->accounts[i].is_active && bank->accounts[i].balance > 0) {
            apply_interest_to_account(bank, bank->accounts[i].account_number);
            count++;
        }
    }
    
    printf("\n✅ Intérêts appliqués à %d compte(s)\n", count);
}
