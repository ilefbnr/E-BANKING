#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/account.h"
#include "../include/persistence.h"

// ============================================
// FONCTIONS UTILITAIRES
// ============================================

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pause_screen() {
    printf("\nAppuyez sur Entrée pour continuer...");
    getchar();
}

// ============================================
// MENUS
// ============================================

void display_main_menu() {
    printf("\n╔══════════════════════════════════════╗\n");
    printf("║     SYSTÈME E-BANKING - MENU         ║\n");
    printf("╚══════════════════════════════════════╝\n");
    printf("1. Mode Utilisateur\n");
    printf("2. Mode Administrateur\n");
    printf("3. Quitter\n");
    printf("═══════════════════════════════════════\n");
    printf("Votre choix: ");
}

void display_user_menu() {
    printf("\n========== MENU UTILISATEUR ==========\n");
    printf("1. Créer un compte\n");
    printf("2. Consulter mon compte\n");
    printf("3. Déposer de l'argent\n");
    printf("4. Retirer de l'argent\n");
    printf("5. Consulter le solde\n");
    printf("6. Voir l'historique\n");
    printf("7. 💸 Transférer de l'argent\n");
    printf("8. 📄 Générer un relevé\n");
    printf("9. Retour au menu principal\n");
    printf("======================================\n");
    printf("Votre choix: ");
}

void display_admin_menu() {
    printf("\n========== MENU ADMINISTRATEUR ==========\n");
    printf("1. Voir tous les comptes\n");
    printf("2. Consulter un compte\n");
    printf("3. Fermer un compte\n");
    printf("4. Réactiver un compte\n");
    printf("5. Ajouter un administrateur\n");
    printf("6. Historique d'un compte\n");
    printf("7. 💰 Appliquer les intérêts\n");
    printf("8. 💾 Sauvegarder/Charger données\n");
    printf("9. Retour au menu principal\n");
    printf("=========================================\n");
    printf("Votre choix: ");
}

// ============================================
// GESTION UTILISATEUR
// ============================================

void handle_create_account(Bank *bank) {
    char name[MAX_NAME_LENGTH];
    
    printf("\n--- CRÉATION DE COMPTE ---\n");
    printf("Nom du titulaire: ");
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0;
    
    if (strlen(name) == 0) {
        printf("❌ Erreur: Le nom ne peut pas être vide!\n");
        return;
    }
    
    create_account(bank, name);
}

void handle_view_my_account(Bank *bank) {
    char account_number[ACCOUNT_NUMBER_LENGTH];
    
    printf("\n--- CONSULTER MON COMPTE ---\n");
    printf("Numéro de compte: ");
    fgets(account_number, ACCOUNT_NUMBER_LENGTH, stdin);
    account_number[strcspn(account_number, "\n")] = 0;
    
    Account *account = find_account(bank, account_number);
    if (account != NULL) {
        display_account_info(account);
    }
}

void handle_deposit(Bank *bank) {
    char account_number[ACCOUNT_NUMBER_LENGTH];
    double amount;
    
    printf("\n--- DÉPÔT D'ARGENT ---\n");
    printf("Numéro de compte: ");
    fgets(account_number, ACCOUNT_NUMBER_LENGTH, stdin);
    account_number[strcspn(account_number, "\n")] = 0;
    
    printf("Montant à déposer (DT): ");
    if (scanf("%lf", &amount) != 1) {
        printf("❌ Montant invalide!\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
    
    deposit(bank, account_number, amount);
}

void handle_withdraw(Bank *bank) {
    char account_number[ACCOUNT_NUMBER_LENGTH];
    double amount;
    
    printf("\n--- RETRAIT D'ARGENT ---\n");
    printf("Numéro de compte: ");
    fgets(account_number, ACCOUNT_NUMBER_LENGTH, stdin);
    account_number[strcspn(account_number, "\n")] = 0;
    
    printf("Montant à retirer (DT): ");
    if (scanf("%lf", &amount) != 1) {
        printf("❌ Montant invalide!\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
    
    withdraw(bank, account_number, amount);
}

void handle_check_balance(Bank *bank) {
    char account_number[ACCOUNT_NUMBER_LENGTH];
    
    printf("\n--- CONSULTER LE SOLDE ---\n");
    printf("Numéro de compte: ");
    fgets(account_number, ACCOUNT_NUMBER_LENGTH, stdin);
    account_number[strcspn(account_number, "\n")] = 0;
    
    display_balance(bank, account_number);
}

void handle_view_transactions(Bank *bank) {
    char account_number[ACCOUNT_NUMBER_LENGTH];
    
    printf("\n--- HISTORIQUE DES TRANSACTIONS ---\n");
    printf("Numéro de compte: ");
    fgets(account_number, ACCOUNT_NUMBER_LENGTH, stdin);
    account_number[strcspn(account_number, "\n")] = 0;
    
    display_transactions(bank, account_number);
}

// ============================================
// GESTION ADMINISTRATEUR
// ============================================

int admin_login(Bank *bank) {
    char username[50];
    char password[50];
    
    printf("\n╔══════════════════════════════════════╗\n");
    printf("║     AUTHENTIFICATION ADMIN           ║\n");
    printf("╚══════════════════════════════════════╝\n");
    
    printf("Username: ");
    fgets(username, 50, stdin);
    username[strcspn(username, "\n")] = 0;
    
    printf("Password: ");
    fgets(password, 50, stdin);
    password[strcspn(password, "\n")] = 0;
    
    return authenticate_admin(bank, username, password);
}

void handle_view_all_accounts(Bank *bank) {
    printf("\n--- TOUS LES COMPTES ---\n");
    display_all_accounts(bank);
}

void handle_admin_view_account(Bank *bank) {
    char account_number[ACCOUNT_NUMBER_LENGTH];
    
    printf("\n--- CONSULTER UN COMPTE ---\n");
    printf("Numéro de compte: ");
    fgets(account_number, ACCOUNT_NUMBER_LENGTH, stdin);
    account_number[strcspn(account_number, "\n")] = 0;
    
    Account *account = find_account(bank, account_number);
    if (account != NULL) {
        display_account_info(account);
    }
}

void handle_close_account(Bank *bank) {
    char account_number[ACCOUNT_NUMBER_LENGTH];
    char confirm;
    
    printf("\n--- FERMER UN COMPTE ---\n");
    printf("Numéro de compte: ");
    fgets(account_number, ACCOUNT_NUMBER_LENGTH, stdin);
    account_number[strcspn(account_number, "\n")] = 0;
    
    Account *account = find_account(bank, account_number);
    if (account == NULL) return;
    
    display_account_info(account);
    
    printf("\n⚠️  ATTENTION: Voulez-vous vraiment fermer ce compte? (o/n): ");
    scanf("%c", &confirm);
    clear_input_buffer();
    
    if (confirm == 'o' || confirm == 'O') {
        close_account(bank, account_number);
    } else {
        printf("❌ Opération annulée.\n");
    }
}

void handle_reopen_account(Bank *bank) {
    char account_number[ACCOUNT_NUMBER_LENGTH];
    
    printf("\n--- RÉACTIVER UN COMPTE ---\n");
    printf("Numéro de compte: ");
    fgets(account_number, ACCOUNT_NUMBER_LENGTH, stdin);
    account_number[strcspn(account_number, "\n")] = 0;
    
    reopen_account(bank, account_number);
}

void handle_add_admin(Bank *bank) {
    char username[50];
    char password[50];
    
    printf("\n--- AJOUTER UN ADMINISTRATEUR ---\n");
    printf("Username: ");
    fgets(username, 50, stdin);
    username[strcspn(username, "\n")] = 0;
    
    printf("Password: ");
    fgets(password, 50, stdin);
    password[strcspn(password, "\n")] = 0;
    
    add_admin(bank, username, password);
}

// ============================================
// MODES D'UTILISATION
// ============================================

void user_mode(Bank *bank) {
    int choice;
    
    while (1) {
        display_user_menu();
        
        if (scanf("%d", &choice) != 1) {
            printf("❌ Choix invalide!\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        
        switch (choice) {
            case 1:
                handle_create_account(bank);
                break;
            case 2:
                handle_view_my_account(bank);
                break;
            case 3:
                handle_deposit(bank);
                break;
            case 4:
                handle_withdraw(bank);
                break;
            case 5:
                handle_check_balance(bank);
                break;
            case 6:
                handle_view_transactions(bank);
                break;
            case 7:
                menu_transfer(bank);
                break;
            case 8:
                menu_statement(bank);
                break;
            case 9:
                printf("\n↩️  Retour au menu principal...\n");
                return;
            default:
                printf("❌ Choix invalide!\n");
        }
        
        pause_screen();
    }
}

void admin_mode(Bank *bank) {
    int choice;
    
    if (!admin_login(bank)) {
        printf("\n❌ Accès refusé!\n");
        pause_screen();
        return;
    }
    
    while (1) {
        display_admin_menu();
        
        if (scanf("%d", &choice) != 1) {
            printf("❌ Choix invalide!\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        
        switch (choice) {
            case 1:
                handle_view_all_accounts(bank);
                break;
            case 2:
                handle_admin_view_account(bank);
                break;
            case 3:
                handle_close_account(bank);
                break;
            case 4:
                handle_reopen_account(bank);
                break;
            case 5:
                handle_add_admin(bank);
                break;
            case 6:
                handle_view_transactions(bank);
                break;
            case 7:
                menu_interest(bank);
                break;
            case 8:
                menu_persistence(bank);
                break;
            case 9:
                printf("\n↩️  Déconnexion...\n");
                return;
            default:
                printf("❌ Choix invalide!\n");
        }
        
        pause_screen();
    }
}

// ============================================
// MAIN
// ============================================

int main() {
    Bank bank;
    int choice;
    
    initialize_bank(&bank);
    
    // Charger les données sauvegardées
    load_all_data(&bank);
    
    printf("\n");
    printf("╔════════════════════════════════════════════╗\n");
    printf("║                                            ║\n");
    printf("║      🏦  SYSTÈME E-BANKING  🏦             ║\n");
    printf("║                                            ║\n");
    printf("║      Gestion de Comptes Bancaires         ║\n");
    printf("║                                            ║\n");
    printf("╚════════════════════════════════════════════╝\n");
    
    while (1) {
        display_main_menu();
        
        if (scanf("%d", &choice) != 1) {
            printf("❌ Choix invalide!\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        
        switch (choice) {
            case 1:
                user_mode(&bank);
                break;
            case 2:
                admin_mode(&bank);
                break;
            case 3:
                // Sauvegarder avant de quitter
                save_all_data(&bank);
                printf("\n");
                printf("╔════════════════════════════════════════════╗\n");
                printf("║   Merci d'avoir utilisé E-Banking! 👋     ║\n");
                printf("║   À bientôt!                               ║\n");
                printf("╚════════════════════════════════════════════╝\n\n");
                exit(0);
            default:
                printf("❌ Choix invalide!\n");
        }
    }
    
    return 0;
}