#include <stdlib.h>
#include <stdio.h>
#include <time.h>
typedef struct Matrice
{
     int x;
     struct Matrice *colone;
     struct Matrice *ligne;
} Matrice;

int getValeur(Matrice *G, int ligne, int colone)
{
     Matrice *L;
     L = G;
     for (int i = 0; i < ligne; i++)
     {
          L = L->ligne;
          if (L->ligne == NULL)
          {
               break;
          }
     }
     for (int i = 0; i < colone; i++)
     {
          L = L->colone;
          if (L->colone == NULL)
          {
               break;
          }
     }
     return L->x;
}
int setValeur(Matrice *G, int ligne, int colone, int y)
{
     Matrice *L;
     L = G;
     for (int i = 0; i < ligne; i++)
     {
          L = L->ligne;
          if (L->ligne == NULL)
          {
               break;
          }
     }
     for (int i = 0; i < colone; i++)
     {
          L = L->colone;
          if (L->colone == NULL)
          {
               break;
          }
     }
     L->x = y;
}

Matrice *construireMatrice(int nbLigne, int nbColonne, int option_deremplir)
{
     Matrice *head = malloc(sizeof(*head));
     head->colone = NULL;
     head->ligne = NULL;
     Matrice *Ligne;
     Matrice *Colone;
     Matrice *LigneNew;
     Matrice *ColoneNew;
     int indexx = 6;
     Colone = head;
     Ligne = Colone;
     int val;
     Colone->x = 21;
     for (int i = 0; i < nbLigne; i++)
     {
          for (int j = 1; j < nbColonne; j++)
          {
               ColoneNew = malloc(sizeof(*ColoneNew));
               ColoneNew->colone = NULL;
               ColoneNew->ligne = NULL;
               ColoneNew->x = rand() % 11;
               Colone->colone = ColoneNew;
               Colone = ColoneNew;
          }
          if (i == nbLigne - 1)
          {
          }
          else
          {
               LigneNew = malloc(sizeof(*LigneNew));
               LigneNew->ligne = NULL;
               LigneNew->colone = NULL;
               Ligne->ligne = LigneNew;
               LigneNew->x = rand() % 11;
               Colone = LigneNew;
               Ligne = LigneNew;
          }
     }

     if (option_deremplir == 1)
     {
          printf("\nLa matrice est vide !Voulez vous la remplir? tapez 1 pour oui autre valeur pour non : ");
          int choice = 0;
          scanf("%d", &choice);
          if (choice == 1)
          {
               for (int i = 0; i < nbLigne; i++)
               {
                    for (int j = 0; j < nbColonne; j++)
                    {
                         printf("\nDonnez la valeur de M(%d,%d) : ", i, j);
                         scanf("\n%d", &val);
                         setValeur(head, i, j, val);
                    }
               }
          }
     }
     return head;
}

int taille(Matrice *tete)
{
     int index;
     Matrice *L;
     L = tete;
     while (L != NULL)
     {
          index++;
          L = L->ligne;
     }
     return index;
}

void afficherMatrice(Matrice *tete, int nbLigne, int nbColonne)
{
     for (int i = 0; i < nbLigne; i++)
     {
          for (int j = 0; j < nbColonne; j++)
          {
               printf("|%d", getValeur(tete, i, j));
          }
          printf("\n");
     }
}

int puissance(int j)
{
     if (j % 2 == 0)
     {
          return 1;
     }
     else
     {
          return -1;
     }
}

int determinant(Matrice *choix, int taille)
{
     Matrice *New;
     int k = 0;
     int valeur;
     int a, b;
     int deter = 0;
     if (taille == 3)
     {

          return getValeur(choix, 0, 0) * (getValeur(choix, 1, 1) * getValeur(choix, 2, 2) - getValeur(choix, 1, 2) * getValeur(choix, 2, 1)) - getValeur(choix, 0, 1) * (getValeur(choix, 1, 0) * getValeur(choix, 2, 2) - getValeur(choix, 1, 2) * getValeur(choix, 3, 0)) + getValeur(choix, 0, 2) * (getValeur(choix, 1, 0) * getValeur(choix, 2, 1) - getValeur(choix, 1, 1) * getValeur(choix, 2, 0));
     }
     else if (taille == 2)
     {

          deter = getValeur(choix, 0, 0) * getValeur(choix, 1, 1) - getValeur(choix, 0, 1) * getValeur(choix, 1, 0);
          return deter;
     }
     else
     {

          for (int j = 0; j < taille; j++)
          {
               valeur = getValeur(choix, 0, j);
               if (valeur == 0)
               {
               }
               else
               {
                    New = construireMatrice(taille - 1, taille - 1, 0);
                    a = 0;
                    b = 0;
                    for (int c = 1; c < taille; c++)
                    {
                         b = 0;
                         for (int d = 0; d < taille; d++)
                         {
                              if (d == j)
                              {
                              }
                              else
                              {

                                   setValeur(New, a, b, getValeur(choix, c, d));
                                   b++;
                              }
                         }
                         a++;
                    }
                    k = k + (valeur * puissance(j) * (determinant(New, taille - 1)));
               }
          }
          return k;
     }
}

void main(int *argv, char **arfc)
{

     int ligne, colone;
     printf("Donnez Nombre de lignes de la matrice :");
     scanf("\n%d", &ligne);
     printf("Donnez Nombre de colones de la matrice :");
     scanf("\n%d", &colone);
     Matrice *tete;
     tete = construireMatrice(ligne, colone, 1);
     Matrice *D, *L;
     D = tete;
     L = D;
     afficherMatrice(tete, ligne, colone);
     if (colone == ligne)
     {
          int t1 = clock();
          printf("\n%d", determinant(tete, ligne));
          int t2 = clock();
          printf("\nTemps d'execution est : %d", t2 - t1);
     }else{
          printf("\nil faut une matrice carre pour calculer le determinant");
     }
}