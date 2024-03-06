#ifndef BIBIO_H
#define BIBIO_H

typedef struct
{
  int id;
  char login[25];
  char password[20];
  char role;
} Apprenant;

typedef struct
{
  char login[25];
  char password[20];
} Admin;

void connexion(Admin *, Apprenant *);
void presenceDevWeb(Apprenant *);

void connexionApprenant(Apprenant *);
void menuApprenant();

void menuAdmin();

void connexionAdmin(Admin *);

#endif
