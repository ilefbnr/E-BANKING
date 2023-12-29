#include <stdio.h>
#include <string.h>
#define maxt 100
#define maxc 100
#define Nbcmpt 0
#define bdclient "clients.txt"
#define bdcompte "comptes.txt"





typedef struct Date {
    int Jour;
    int Mois;
    int Annee;
}Date;

typedef struct Transaction {
    char type [6];
    int montant ;
    struct Date date;

}transaction;



typedef struct Client {
    int codecli;
    char nom[10];
    char prenom[10];
    char adrs[10];
    struct Date date_nais;
} Client;

Client clients[maxc];

typedef struct Compte {
    int code_cpt;
    int Code_cli;
    char typecmpt [10];
    int solde;
    struct Date d_compte;

} Compte;

Compte comptes[maxc];

int a, b, x;







void design(const char *message);
void menu0 (int x,FILE *file,FILE *file1);
void menu1 (int x,FILE *file,FILE *file1);
void menu2 (int x,FILE *file,FILE *file1);
void access ();
void gerer_clients(int x,FILE *file,FILE *file1);
int comparer(const void *a, const void *b);
void gerer_compte(int a,FILE *file,FILE *file1);
void gerer_operation(int a,FILE *file,FILE *file1);
int getNbccounts(Compte comptes[], int codeCli, int nbcmpt);





int getnbaccounts(Compte comptes[], int codeCli, int nbcmpt) {
    int count = 0;

    for (int i = 0; i < nbcmpt; i++) {
        if (comptes[i].Code_cli == codeCli) {
            count++;
        }
    }

    return count;
}




void ajouterclient (FILE *file) {

        struct Client cl;


        printf("Code Client : ");
        scanf("%d", &cl.codecli);

        printf("Nom : ");
        scanf("%s", cl.nom);

        printf("Prenom : ");
        scanf("%s", cl.prenom);


         printf("Adresse : ");
         scanf("%s", cl.adrs);


         printf("Date de naissance | ");
        printf("Jour : ");
        scanf("%d", &cl.date_nais.Jour);
        printf("Mois : ");
        scanf("%d", &cl.date_nais.Mois);
        printf("Annee : ");
        scanf("%d", &cl.date_nais.Annee);


        fwrite(&cl, sizeof(cl), 1, file);
         if(fwrite != 0)
            printf("client ajoute avec succes");
         else
            printf("erreur");




}


void modifclient (FILE *file) {
    int code;
    printf("Entrez le code du client a modifier : ");
    scanf("%d", &code);

    struct  Client cl;
    FILE *f1 = fopen("f1.txt", "w");
    int found = 0;

    rewind(file);
    while (fread(&cl, sizeof(Client), 1, file)) {
        if (cl.codecli == code) {
            printf("Client trouve.\n");
             printf("donner le nouveau nom : ");
           scanf("%s", cl.nom);

        printf("donner le nouveau prenom : ");
        scanf("%s", cl.prenom);

        printf("Adresse : ");
        scanf("%s", cl.adrs);


        printf("Date de naissance | ");
        printf("Jour : ");
        scanf("%d", &cl.date_nais.Jour);
        printf("Mois : ");
        scanf("%d", &cl.date_nais.Mois);
        printf("Annee : ");
        scanf("%d", &cl.date_nais.Annee);


            found = 1;
        }
        fwrite(&cl, sizeof(Client), 1, f1);
    }

    fclose(file);
    fclose(f1);

    remove(bdclient);
    rename("f1.txt", bdclient);
    file = fopen(bdclient, "a+");

    if (found) {
        printf("Client modifie avec succes.\n");
    } else {
        printf("Client non trouve.\n");
    }


}




void suprimclient(FILE *file) {
    int code;
    printf("Entrez le code du client a supprimer : ");
    scanf("%d", &code);

    struct Client cl;
    FILE *f1 = fopen("f1", "w");
    int found = 0;

    rewind(file);

    while (fread(&cl, sizeof(Client), 1, file)) {
        if (cl.codecli != code){
                fwrite(&cl, sizeof(Client), 1, f1);
        } else {
            found =1;
        }
    }


    fclose(file);
    fclose(f1);

    remove(bdclient);
    rename("f1", bdclient);
    file = fopen(bdclient, "a+");

    if (!found) {
        printf("Client non trouve.\n");
    }

}








void gerer_clients (int a,FILE *clientfile,FILE *comptefile)
{

    if (a == 1)
    {ajouterclient (clientfile);
    printf("\n 1- retour au menu precedent");
            printf("\n 2-quitter le programme");
            int z;
            scanf("%d", &z);
            if (z==1) {menu1(1,clientfile,comptefile);}
            else if (z=2){return;}
            else return;
    }
    else if (a == 2)
    {
       modifclient (clientfile);
       printf("\n 1- retour au menu precedent");
            printf("\n 2-quitter le programme");
            int z;
            scanf("%d", &z);
            if (z==1) {menu1(1,clientfile,comptefile);}
            else if (a=z){return;}
            else return;
         }

    else if (a == 3)
    {
       suprimclient(clientfile);
       printf("\n 1- retour au menu precedent");
            printf("\n 2-quitter le programme");
            int z;
            scanf("%d", &z);
            if (z==1) {menu1(1,clientfile,comptefile);}
            else if (a=z){return;}
            else return;


    }
    else if (a == 4)
    {




    struct Client cl;
    rewind(clientfile);

    while (fread(&cl, sizeof(Client), 1, clientfile)) {
   printf("\nCode client : %d", cl.codecli);
    printf("\nNom : %s | Prenom : %s", cl.nom, cl.prenom);
    printf("\nNom : %s | Prenom : %s", cl.adrs);
     printf("\nDate de naissance : %d / %d / %d", cl.date_nais.Jour, cl.date_nais.Mois, cl.date_nais.Annee);


    }


        printf("\n 1- retour au menu precedent");
            printf("\n 2-quitter le programme");
            int z;
            scanf("%d", &z);
            if (z==1) {menu1(1,clientfile,comptefile);}
            else if (a=z){return;}
            else return;
    }
    else if (a == 5)
        menu0(1,clientfile,comptefile);



}




void ajoutcompte(FILE *file) {
    struct Compte cmpt;
        int code;
        printf("Code Compte : ");
        scanf("%d", &code);

        int found = 0;
        while (fread(&cmpt, sizeof(struct Compte), 1, file) && found == 0)
        {
            if (cmpt.code_cpt == code)
                found = 1;
        }

        if (found == 1)
        {
            printf("code existant\n");
            return;
        }

        cmpt.Code_cli=code;
        printf("type compte 'CE4' si compte d'epargne et 'CC' si compte courant | ");
        scanf("%s", &cmpt.typecmpt);
        printf("Jour : ");
        scanf("%d", &cmpt.d_compte.Jour);
        printf("Date de creation du compte | ");
        printf("Jour : ");
        scanf("%d", &cmpt.d_compte.Jour);
        printf("Mois : ");
        scanf("%d", &cmpt.d_compte.Mois);
        printf("Annee : ");
        scanf("%d", &cmpt.d_compte.Annee);
        printf("Somme : ");
        scanf("%d", &cmpt.solde);


    fwrite(&cmpt, sizeof(Compte), 1, file);


    if (fwrite != 0)
           {

            printf("compte ajoute avec succes");
            }
        else
            printf("erreur");



    }



void recherchecompte(FILE *file) {
    struct Compte cmpt;
    rewind(file);
        int code;
        printf("Code compte : ");
        scanf("%d", &code);

        int found = 0;
        while (fread(&cmpt, sizeof(struct Compte), 1, file) && found == 0)
        {
            if (cmpt.code_cpt == code)
            {
                printf("\n Code compte : %d", cmpt.code_cpt);
                printf("\n Code client : %d", cmpt.Code_cli);
                printf("\n Code client : %s", cmpt.typecmpt);
                printf("\n Date creation %d / %d / %d", cmpt.d_compte.Jour, cmpt.d_compte.Mois, cmpt.d_compte.Annee);
                printf("\n Somme %d", cmpt.solde);
                found = 1;
            }
        }
        if (found == 0)
            printf("code non existant\n");
        fclose(file);

    }



 void supprimcompte(FILE *file) {
    int code;
    printf("Entrez le code du compte a supprimer : ");
    scanf("%d", &code);

    struct Compte cmpt;
    FILE *f1 = fopen("f1.txt", "w");
    int found = 0;

    rewind(file);

    while (fread(&cmpt, sizeof(Compte), 1, file)) {
        if (cmpt.code_cpt == code) {
            found = 1;
            printf("Compte supprime avec succes.\n");
        } else {
            fwrite(&cmpt, sizeof(Compte), 1, f1);
        }
    }

    fclose(file);
    fclose(f1);

    remove(bdcompte);
    rename("f1.txt", bdcompte);
    file = fopen(bdcompte, "a+");

    if (!found) {
        printf("Compte non existant.\n");
    }
     printf("\n 1- retour au menu precedent");
            printf("\n 2-quitter le programme");
            int z;
            scanf("%d", &z);
            if (z==1) {menu1(2,file,file);}
           else if (z=2){return;}
            else return;
}






void gerer_compte(int a,FILE *clientfile,FILE *comptefile) {
    if (a == 1)
    {
        ajoutcompte(comptefile);
         printf("\n 1- retour au menu precedent");
        printf("\n 2-quitter le programme");
        int z;
        scanf("%d", &z);
        if (z==1) {menu1(2,clientfile,comptefile);}
        else if (z=2){return;}
        else return;
    }
    else if (a == 2)
    {
        recherchecompte(comptefile);
        printf("\n 1- retour au menu precedent");
            printf("\n 2-quitter le programme");
            int z;
            scanf("%d", &z);
            if (z==1) {menu1(2,clientfile,comptefile);}
          else if (z=2){return;}
           else return;
    }
    else if (a == 3)
    {

    struct Compte cmpt;
    rewind(comptefile);

    while (fread(&cmpt, sizeof(Compte), 1, comptefile)) {
        printf("\n Code compte : %d", cmpt.code_cpt);
                printf("\n Code client : %d", cmpt.Code_cli);
                printf("\n Code client : %s", cmpt.typecmpt);
                printf("\n Date creation %d / %d / %d", cmpt.d_compte.Jour, cmpt.d_compte.Mois, cmpt.d_compte.Annee);
                printf("\n Somme %d", cmpt.solde);
        printf("\n-----------------------------------------\n");
    }

    }
    else if (a == 4)
    {
       supprimcompte(comptefile);
          printf("\n 1- retour au menu precedent");
            printf("\n 2-quitter le programme");
            int z;
            scanf("%d", &z);
            if (z==1) {menu1(2,clientfile,comptefile);}
           else if (z=2){return;}
            else return;
    }
    else if (a == 5)
        menu0(1,clientfile,comptefile);
}









void menu3(int a,FILE *clientfile,FILE *comptefile)
{
    if (a == 1)
    {
        struct Compte cmpt;
        int code;

        printf("Code compte : ");
        scanf("%d", &code);

        int found = 0;
        while (fread(&cmpt, sizeof(struct Compte), 1, comptefile) && found == 0)
        {
            if (cmpt.code_cpt == code)
            {
                printf("\n Code compte : %d", cmpt.code_cpt);
                printf("\n Code client : %d", cmpt.Code_cli);
                printf("\n Code typecmpt : %d", cmpt.typecmpt);
                printf("\n Date creation %d / %d / %d", cmpt.d_compte.Jour, cmpt.d_compte.Mois, cmpt.d_compte.Annee);
                printf("\n Somme %d", cmpt.solde);
                found = 1;
            }
        }
        if (found == 0)
            printf("code non existant\n");
            fclose(comptefile);
            printf("\n 1- retour au menu precedent");
            printf("\n 2-quitter le programme");
            int z;
            scanf("%d", &z);
            if (z==1) {menu2(2,clientfile,comptefile);}
            else if (z=2){return;}
            else return;
                    }

    else if (a == 2)
    {   gerer_operation(1,clientfile,comptefile);}
    else if (a == 3)
    {
        gerer_operation(1,clientfile,comptefile);
    }
     else if (a == 4)
    {
        gerer_operation(3,clientfile,comptefile);
    }
     else if (a == 3)
    {
        gerer_operation(2,clientfile,comptefile);
    }
}



void retrait(FILE *file){
    struct Compte cmpt;
        int code,soldefinal, m;

        printf("Code Compte : ");
        scanf("%d", &code);

        int nb = 0;

        rewind(file);


        FILE *nf;
        nf = fopen("nv.txt", "w");
        while (fread(&cmpt, sizeof(struct Compte), 1, file))
        {
            if (cmpt.code_cpt == code)
            {
                 do
                {
                    printf("\n montant : ");
                    scanf("%d", &m);
                    if (m > 1000)
                        printf("\n le montant ne doit pas depasser 1000 DT");
                    soldefinal = cmpt.solde - m;
                    if (soldefinal < 50)
                        printf("\n le solde ne doit pas etre inferieur a 50 DT");
                }while (m > 1000 || soldefinal < 50);

                cmpt.solde = cmpt.solde- m;

            }else {"code de compte inexistant";}
            fwrite(&cmpt, sizeof(Compte), 1, nf);
        }
        fclose(file);
        fclose(nf);

        remove(bdcompte);
        rename("nv.txt", bdcompte);
        file = fopen(bdcompte, "a+");
}


void virement(FILE *file){ struct Compte cmpt;
        struct Compte cmpt1;

        int code1, code2, soldefinal,m;

        printf("Code Compte d'envoi : ");
        scanf("%d", &code1);

        printf("Code compte destinataire : ");
        scanf("%d", &code2);

        int nb = 0;

        int code,soldefinl, m1;

        printf("Code Compte : ");
        scanf("%d", &code);



        rewind(file);


        FILE *nf;
        nf = fopen("nv.txt", "w");
        while (fread(&cmpt, sizeof(struct Compte), 1, file))
        {
            if (cmpt.code_cpt == code1)
            {
                 do
                {
                    printf("\n montant : ");
                    scanf("%d", &m1);
                    if (m1 > 1000)
                        printf("\n le montant ne doit pas depasser 1000 DT");
                    soldefinl = cmpt.solde - m1;
                    if (soldefinl < 50)
                        printf("\n le solde ne doit pas etre inferieur a 50 DT");
                }while (m1 > 1000 || soldefinl < 50);

                cmpt.solde = cmpt.solde- m1;

            }else if(cmpt.code_cpt == code2){ {
                 do
                {
                    printf("\n montant : ");
                    scanf("%d", &m1);
                    if (m1 > 1000)
                        printf("\n le montant ne doit pas depasser 1000 DT");
                    soldefinl = cmpt.solde + m1;
                    if (soldefinl < 50)
                        printf("\n le solde ne doit pas etre inferieur a 50 DT");
                }while (m1> 1000 || soldefinl < 50);

                cmpt.solde = cmpt.solde+ m1;

            }}
            fwrite(&cmpt, sizeof(Compte), 1, nf);

        }
        fclose(file);
        fclose(nf);

        remove(bdcompte);
        rename("nv.txt", bdcompte);
        file = fopen(bdcompte, "a+");}





void versement(FILE *file){
     struct Compte cmpt;
        int code,soldefinal, m;

        printf("Code Compte : ");
        scanf("%d", &code);

        int nb = 0;

        rewind(file);


        FILE *nf;
        nf = fopen("nv.txt", "w");
        while (fread(&cmpt, sizeof(struct Compte), 1, file))
        {
            if (cmpt.code_cpt == code)
            {
                 do
                {
                    printf("\n montant : ");
                    scanf("%d", &m);
                    if (m > 1000)
                        printf("\n le montant ne doit pas depasser 1000 DT");
                    soldefinal = cmpt.solde + m;
                    if (soldefinal < 50)
                        printf("\n le solde ne doit pas etre inferieur a 50 DT");
                }while (m > 1000 || soldefinal < 50);

                cmpt.solde = cmpt.solde+ m;

            }else {"code de compte inexistant";}

            fwrite(&cmpt, sizeof(Compte), 1, nf);
        }
        fclose(file);
        fclose(nf);

        remove(bdcompte);
        rename("nv.txt", bdcompte);
        file = fopen(bdcompte, "a+");
}



void gerer_operation(int a,FILE *clientfile,FILE *comptefile)
{
    if (a == 1)
    {
         retrait(comptefile);
         printf("\n 1- retour au menu precedent");
            printf("\n 2-quitter le programme");
            int z;
            scanf("%d", &z);
            if (z==1) {menu1(2,clientfile,comptefile);}
            else if (z=2){return;}
            else return;
    }
    else if (a == 3)
    {

         printf("\n 1- retour au menu precedent");
            printf("\n 2-quitter le programme");
            int z;
            scanf("%d", &z);
            if (z==1) {menu1(2,clientfile,comptefile);}
            else if (z=2){return;}
            else return;
    }
    else if (a == 2){

         versement(comptefile);
         printf("\n 1- retour au menu precedent");
            printf("\n 2-quitter le programme");
            int z;
            scanf("%d", &z);
            if (z==1) {menu1(2,clientfile,comptefile);}
            else if (z=2){return;}
            else return;


}


}






int comparer(const void *a, const void *b)
{
    const struct Client *c1 = a;
    const struct Client *c2 = b;
    return strcmp(c1->nom, c2->nom);
}



void menu1(int a,FILE *clientfile,FILE *comptefile) {
    design("Bienvenue dans notre banque BNRS");
    int b, x;

    if (a == 1) {
        printf("\n\n\n                                        -------------------------------------------\n");
        printf("\n\t                                   1- Ajouter un client\n");
        printf("\t                                   2- Modifier les informations d'un client\n");
        printf("\t                                   3- Supprimer un client\n");
        printf("\t                                   4- Afficher les informations d'un client\n");
        printf("\t                                   5- Retour\n");
        printf("                                        -------------------------------------------\n\t                               TA REPONSE : ");
        scanf("%d", &b);
        gerer_clients(b,clientfile,comptefile);
    } else if (a == 2) {
        printf("\n\n\n                                        -------------------------------------------\n");
        printf("\n\t                                   1- Créer un nouveau compte\n");
        printf("\t                                   2- Rechercher un compte\n");
        printf("\t                                   3- Afficher la liste des comptes\n");
        printf("\t                                   4- Suppression du compte\n");
        printf("\t                                   5- Retour\n");
        printf("                                        -------------------------------------------\n\t                               TA REPONSE : ");
        scanf("%d", &b);
        gerer_compte(b,comptefile,comptefile);
    } else if (a == 3) {
        printf("\n\n\n                                        -------------------------------------------\n");
        printf("\n\t                                   1- Retrait d'argent\n");
        printf("\t                                   2- Versement d'argent\n");
        printf("\t                                   3- Virementt d'argent\n");
        printf("                                        -------------------------------------------\n\t                               TA REPONSE : ");
        scanf("%d", &x);
        gerer_operation(x,comptefile,comptefile);
    } else if (a == 4) {

        access();

    }
      else if (a == 5) {
        return;


    }
    else {
        printf("                                        -------------------------------------------\n\t                              Choix erroné. Entrer la réponse une autre fois : ");
        scanf("%d", &a);
        menu1(a,comptefile,comptefile);

}}


void menu2(int a,FILE *clientfile,FILE *comptefile) {
    int x,y;

    if (a == 1) {
         printf("\n\n\n                                        -------------------------------------------\n");
        printf("\n\t                                   1- access au compte courant\n");
        printf("\t                                   2- access au compte d'epargne\n");

        printf("\n\n\n                                        -------------------------------------------\n");
        scanf("%d", &x);
        printf("\n\n\n");
        if (x==1){
        printf("\n\t                                   1- Afficher toutes les informations du compte\n");
        printf("\t                                   2- payer facture\n");
        printf("\t                                   3- Retrait\n");
        printf("\t                                   4- transferer de l'argent\n");
        printf("\t                                   5- encaissement mandat\n");
        printf("                                        -------------------------------------------\n\t                               TA REPONSE : ");
        scanf("%d", &y);
        menu3(y,comptefile,comptefile);
       }
       else if (x==2){
        printf("\n\t                                   1- Afficher toutes les informations d'un compte\n");
        printf("\t                                   2- transferer de l'argent\n");
        printf("\t                                   3- encaissement mandat\n");
        printf("                                        -------------------------------------------\n\t                               TA REPONSE : ");
        scanf("%d", &y);
        if (y==2 || y==3){y+=2;}
        menu3(y,clientfile,comptefile);

       }
    }  else if (a == 2) {
        menu1(3,clientfile,comptefile);
    }

    else if (a ==3) {
            int y;
            printf("\t                                   1- payer facture\n");

            printf(" \t                                   Ou bien pour savoir plus sur nos  services veuillez nous contacter directement");
            printf("                                        -------------------------------------------\n\t                               TA REPONSE : ");
        scanf("%d", &y);
        if(y==1 ){
             menu3(2,comptefile,comptefile);
        }
    }

    else if (a == 4) {
        menu0(2,clientfile,comptefile);
    } else if (a == 5) {
        return;
    } else {
        printf("Mauvais choix\n");
        menu0(2,clientfile,comptefile);
    }
}






void menu0(int x,FILE *clientfile,FILE *comptefile) {
    int a;

    printf("\n\n\n\n");
    design("Bienvenue dans notre banque BNRS");
    printf("\n\n\n\n");
    if (x == 1) {


        printf("\n\n\n                                        -------------------------------------------\n");
        printf("\n\t                                   1- Gerer les clients\n");
        printf("\t                                   2- Gerer les comptes\n");
        printf("\t                                   3- Gerer les operations\n");
        printf("\t                                   4- Retour\n");
        printf("\t                                   5- Quitter le programme\n");
        printf("                                        -------------------------------------------\n\t                               TA REPONSE : ");



        scanf("%d", &a);
        menu1(a,clientfile,comptefile);
    } else if (x == 2) {



        printf("\n\n\n                                        -------------------------------------------\n");
        printf("\n\t                                   1- Gerer vos comptes existants\n");
        printf("\t                                   2- transferer/encaisser de l'argent \n");
        printf("\t                                   3- nos services \n");
        printf("\t                                   4- Retour t\n");
        printf("\t                                   5- Quitter le programme\n");
        printf("                                        -------------------------------------------\n\t                               TA REPONSE : ");




        scanf("%d", &a);
        menu2(a,clientfile,comptefile);
    } else {
        printf("Choix erroné\n");
        access();
    }
}

void design(const char *message) {
    int message_length = strlen(message);
    int num_dashes = message_length + 4;

    printf("                                          ");

    for (int i = 0; i < num_dashes; i++) {
        printf("-");
    }
    printf("\n");


    printf("                                          - %s -\n", message);


    printf("                                          ");
    for (int j = 0; j < num_dashes; j++) {
        printf("-");
    }
    printf("\n");
}


void access(FILE *clientfile,FILE *comptefile) {
    int a;
    design("Bienvenue dans notre banque BNRS");
    printf("\n\n\n\n");
    printf("1- ESPACE EMPLOYE\n");
    printf("2- ESPACE CLIENT\n");
    printf("-------------------------------------------\n\tVotre reponse : ");
    scanf("%d", &a);
    menu0(a,clientfile,comptefile);

}


int main(){

    FILE *clientfile = fopen(bdclient, "a+");
    FILE *comptefile = fopen(bdcompte, "a+");

    access(clientfile,comptefile);

    fclose(clientfile);
    fclose(comptefile);



   return;}

