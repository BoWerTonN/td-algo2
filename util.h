/* util.h (IGI-3005)

  JCG 15/09/2008
  maj 07/12/2017
  DV  2024-12-09

  fonctions utilitaires :
    - vérification de tri
    - remplissage de tableau
    - affichage de tableau
*/


#ifndef __UTIL_H__
#define __UTIL_H__

char *saisie_rep() ;
int saisie_int();
double saisie_double() ;

int verif_trie(double *v, int n) ;

int remplirAlea(double v[], int n);

void affiche(double t[], int n) ;

#endif
