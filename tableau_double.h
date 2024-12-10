#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef struct {
	double* t;		// mémoire allouée pour le tableau
	int n;			// nombre d'éléments insérés
	int m;			// capacité : taille de la mémoire
} tableau_double;

tableau_double nouveau_tableau(int m);
void redim_tableau(tableau_double * tbl, int m);
void inserer_tableau(tableau_double * tbl, int pos, double el);
double supprimer_tableau(tableau_double * tbl, int pos);
void liberer_tableau(tableau_double* tbl);