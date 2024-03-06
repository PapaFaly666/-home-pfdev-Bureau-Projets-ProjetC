#include <stdio.h>
#include "bibio.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define ID_FILE "last_id.txt"

int has_presence_today(char *filename)
{
  FILE *fp = fopen(filename, "r");
  if (fp == NULL)
  {
    return 0;
  }

  time_t timestamp = time(NULL);
  struct tm *local_time = localtime(&timestamp);
  char formatted_date[11];
  strftime(formatted_date, sizeof(formatted_date), "%Y-%m-%d", local_time);

  char line[100];
  while (fgets(line, sizeof(line), fp) != NULL)
  {
    char dummy_id[10], dummy_nom[20], dummy_prenom[25], dummy_date[11];
    if (sscanf(line, "%s %s %s %s", dummy_id, dummy_nom, dummy_prenom, dummy_date) == 4 &&
        strcmp(dummy_date, formatted_date) == 0)
    {
      fclose(fp);
      return 1;
    }
  }

  fclose(fp);
  return 0;
}

void presenceDevWeb(Apprenant *ap)
{
  char prenom[25];
  int id;
  char nom[20];
  FILE *fp2;

  fp2 = fopen("table_presence_dev_web.txt", "at");
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

  if (has_presence_today("table_presence_dev_web.txt"))
  {
    printf("Vous avez déjà marqué votre présence Dev Web aujourd'hui.\n");
    fclose(fp2);
    return;
  }

  id++;

  fprintf(fp2, "%d %s %s %s\n", id, nom, prenom, formatted_time);

  fclose(fp2);

  printf("\n");
  printf("Presence enregistrée avec succès (ID: %d)\n", id);
}

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

  if (has_presence_today("table_presence_ref_dig.txt"))
  {
    printf("Vous avez déjà marqué votre présence Ref Dig aujourd'hui.\n");
    return;
  }
  fp3 = fopen("table_presence_ref_dig.txt", "at+");
  if (fp3 == NULL)
  {
    printf("Impossible d'ouvrir le fichier de présence (Ref Dig).\n");
    return;
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

  printf("\n");
  printf("Votre présence Ref Dig a été enregistrée avec succès.\n");
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

#define ID_FILE "last_id.txt"

int read_last_id()
{
  FILE *fp = fopen(ID_FILE, "r");
  int last_id = 0;

  if (fp != NULL)
  {
    fscanf(fp, "%d", &last_id);
    fclose(fp);
  }

  return last_id;
}

void write_last_id(int id)
{
  FILE *fp = fopen(ID_FILE, "w");
  if (fp != NULL)
  {
    fprintf(fp, "%d", id);
    fclose(fp);
  }
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
    if (choix == 1)
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
    }

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
