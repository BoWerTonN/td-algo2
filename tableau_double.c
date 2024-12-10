#include "tableau_double.h"

tableau_double nouveau_tableau(int m) {
	tableau_double tbl = {NULL, 0, 0};
	// A ecrire
	return tbl;
}

void redim_tableau(tableau_double * tbl, int m) {
	// A ecrire
}

void inserer_tableau(tableau_double * tbl, int pos, double el) {
	// A ecrire
}

double supprimer_tableau(tableau_double * tbl, int pos) {
	// A ecrire
	return 0;
}

void liberer_tableau(tableau_double* tbl) {
	free(tbl->t);
	tbl->t = NULL;
	tbl->n = tbl->m = 0;
}