#include <stdio.h>
#include "bibio.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

void connexion(Admin *ad, Apprenant *ap)
{
  FILE *fp_admin, *fp_apprenant;
  int role = 0;
  char loginR[20];
  char *passwordR;
  int trouvee = 0;

  fp_admin = fopen("table_login_admin.txt", "r");
  if (fp_admin == NULL)
  {
    printf("Impossible d'ouvrir le fichier des admins\n");
    exit(1);
  }

  printf("Username (champs obligatoire): ");
  scanf("%s", loginR);
  passwordR = getpass("Password: ");

  while (fscanf(fp_admin, "%s %s", ad->login, ad->password) == 2)
  {
    if (strcmp(ad->login, loginR) == 0 && strcmp(ad->password, passwordR) == 0)
    {
      trouvee = 1;
      role = 1;
      break;
    }
  }
  fclose(fp_admin);

  if (trouvee == 0)
  {
    fp_apprenant = fopen("table_login_apprenant.txt", "r");
    if (fp_apprenant == NULL)
    {
      printf("Impossible d'ouvrir le fichier des apprenants\n");
      exit(1);
    }

    while (fscanf(fp_apprenant, "%s %s", ap->login, ap->password) == 2)
    {
      if (strcmp(ap->login, loginR) == 0 && strcmp(ap->password, passwordR) == 0)
      {
        trouvee = 1;
        role = 2;
        break;
      }
    }
    fclose(fp_apprenant);
  }

  if (trouvee == 1)
  {
    if (role == 1)
    {
      menuAdmin(ad);
    }
    else
    {
      menuApprenant(ap);
    }
  }
  else
  {
    printf("Login et/ou mot de passe incorrect(s)\n");
  }
}
/*void connexionAdmin(Admin *ad)
{
   FILE *fp1;
   char loginR[20];
   char *passwordR;
   int trouvee = 0;
   fp1 = fopen("table_login_admin.txt", "at+");
   if (fp1 == NULL)
   {
     printf("Impossible d'ouvrir le fichier");
     exit(1);
   }
   do
   {
     printf("Username (champs obligatoire): ");
     getchar();
     fgets(loginR, sizeof(loginR), stdin);
   } while (strlen(loginR) == 1 && (loginR[0] == '\n' || loginR[0] == '\r'));

   passwordR = getpass("Password: ");

   loginR[strcspn(loginR, "\n")] = '\0';

   while (!feof(fp1))
   {
     fscanf(fp1, "%s %s", ad->login, ad->password);
     if ((strcmp(ad->login, loginR) == 0) && (strcmp(ad->password, passwordR) == 0))
     {
       trouvee = 1;
       break;
     }
   }
   fclose(fp1);
   if (trouvee == 1)
   {
     menuAdmin();
   }
   else
   {
     printf("Login et/ou mot de passe incorrect(s)\n");
   }
}*/
/*
void connexionApprenant(Apprenant *ap)
{
  FILE *fp;
  char loginR[20];
  char *passwordR;
  int trouvee = 0;
  fp = fopen("table_login_apprenant.txt", "at+");
  if (fp == NULL)
  {
    printf("Impossible d'ouvrir le fichier");
    exit(1);
  }

  do
  {
    printf("Username (champs obligatoire): ");
    getchar();
    fgets(loginR, sizeof(loginR), stdin);
  } while (strlen(loginR) == 1 && (loginR[0] == '\n' || loginR[0] == '\r'));

  passwordR = getpass("Password: ");

  loginR[strcspn(loginR, "\n")] = '\0';

  while (!feof(fp))
  {
    fscanf(fp, "%s %s", ap->login, ap->password);
    if ((strcmp(ap->login, loginR) == 0) && (strcmp(ap->password, passwordR) == 0))
    {
      trouvee = 1;
      break;
    }
  }
  fclose(fp);
  if (trouvee == 1)
  {
    printf("*********************************BONJOUR %s*********************************!\n", loginR);
    menuApprenant(ap);
  }
  else
  {
    printf("Login et/ou mot de passe incorrect(s)\n");
  }
}
*/

/*void connexion(Apprenant *ap, Admin *ad)
{
  int choixRole;
  char loginR[20];
  int trouvee = 0;
  printf("##########ROLE##########\n");
  printf("1 - ESPACE ADMINISTRATEUR\n");
  printf("2 - ESPACE UTILISATEUR\n");
  printf("########################\n");
  printf("CHOIX CONNEXION: ");
  scanf("%d", &choixRole);
  if (choixRole == 1)
  {
    connexionAdmin(ad);
  }
  else if (choixRole == 2)
  {
    connexionApprenant(ap);
  }
}*/

// presence dev web
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void presenceRefDig(Apprenant *ap)
{
  char prenom[25];
  char nom[20];
  FILE *fp3;
  fp3 = fopen("table_presence_ref_dig.txt", "at+");
  if (fp3 == NULL)
  {
    printf("Impossible d'ouvrir le fichier.\n");
    exit(1);
  }
  printf("Prenom: ");
  getchar();
  fgets(prenom, sizeof(prenom), stdin);
  prenom[strcspn(prenom, "\n")] = '\0';
  printf("Nom: ");
  fgets(nom, sizeof(nom), stdin);

  nom[strcspn(nom, "\n")] = '\0';

  time_t timestamp = time(NULL);
  struct tm *local_time = localtime(&timestamp);
  char formatted_time[100];
  strftime(formatted_time, sizeof(formatted_time), "%Y-%m-%d %H:%M:%S", local_time);

  fprintf(fp3, "%s %s %s\n", nom, prenom, formatted_time);
  fclose(fp3);
}

void presenceData(Apprenant *ap)
{
  char prenom[25];
  char nom[20];
  FILE *fp4;
  fp4 = fopen("table_presence_data.txt", "at+");
  if (fp4 == NULL)
  {
    printf("Impossible d'ouvrir le fichier.\n");
    exit(1);
  }
  printf("Prenom: ");
  getchar();
  fgets(prenom, sizeof(prenom), stdin);
  prenom[strcspn(prenom, "\n")] = '\0';
  printf("Nom: ");
  fgets(nom, sizeof(nom), stdin);

  nom[strcspn(nom, "\n")] = '\0';

  time_t timestamp = time(NULL);
  struct tm *local_time = localtime(&timestamp);
  char formatted_time[100];
  strftime(formatted_time, sizeof(formatted_time), "%Y-%m-%d %H:%M:%S", local_time);

  fprintf(fp4, "%s %s %s\n", nom, prenom, formatted_time);
  fclose(fp4);
}

void presenceDevWeb(Apprenant *ap)
{
  char prenom[25];
  char nom[20];
  FILE *fp2;
  fp2 = fopen("table_presence_dev_web.txt", "at+");
  if (fp2 == NULL)
  {
    printf("Impossible d'ouvrir le fichier.\n");
    exit(1);
  }
  printf("Prenom: ");
  getchar();
  fgets(prenom, sizeof(prenom), stdin);
  prenom[strcspn(prenom, "\n")] = '\0';
  printf("Nom: ");
  fgets(nom, sizeof(nom), stdin);

  nom[strcspn(nom, "\n")] = '\0';

  time_t timestamp = time(NULL);
  struct tm *local_time = localtime(&timestamp);
  char formatted_time[100];
  strftime(formatted_time, sizeof(formatted_time), "%Y-%m-%d %H:%M:%S", local_time);

  fprintf(fp2, "%s %s %s\n", nom, prenom, formatted_time);
  fclose(fp2);
}

void menuApprenant(Apprenant *ap)
{
  int ok = 0;
  int choix;
  int choix1;

  do
  {
    printf("####################MENU APPRENANT####################\n");
    printf("\t1-MARQUER MA PRÉSENCE\n");
    printf("\t2-NOMBRE DE MINUTES D’ABSENCE\n");
    printf("\t3-MES MESSAGES (0)\n");
    printf("\t4-QUITTER\n");
    printf("######################################################\n");
    printf("CHOIX => ");
    scanf("%d", &choix);
    /* if (choix == 1)
     {
       printf("#######################################\n");
       printf(" 1 - REF DEV WEB/MOBILE\n");
       printf(" 2 - REF REFERENCE DIGITAL\n");
       printf("3 - REF DATA\n");
       printf("CHOIX => ");
       scanf("%d", &choix1);
       switch (choix1)
       {
       case 1:
         presenceDevWeb(ap);
         break;

       case 2:
         presenceRefDig(ap);
         break;

       case 3:
         presenceData(ap);
         break;

       default:
         printf("Choix invalide.\n");
         break;
       }
     }*/

  } while (1);
}

void menuAdmin()
{
  int choix;
  do
  {
    printf("####################MENU ADMIN####################\n");
    printf("\t1-GESTION DES ÉTUDIANTS\n");
    printf("\t2-GÉNÉRATION DE FICHIERS\n");
    printf("\t3-MARQUER LES PRÉSENCES\n");
    printf("\t4-ENVOYER UN MESSAGE\n");
    printf("\t5-QUITTER\n");
    printf("######################################################\n");
    printf("CHOIX => ");
    scanf("%d", &choix);
  } while (1);
}
