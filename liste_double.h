#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef struct _maillon_double {
	double val;
	struct _maillon_double* suiv;
} maillon_double, *liste_double;


maillon_double* nouveau_maillon(double val);
maillon_double* inserer_apres_liste(maillon_double* m, double val);

maillon_double* avancer_liste(maillon_double* p, int i);
int longueur_liste(liste_double lst);

maillon_double* inserer_position_liste(liste_double* lst, int i, double val);
void supprimer_position_liste(liste_double* lst, int i);
void supprimer_apres_liste(maillon_double* m);

void afficher_liste(liste_double lst);
void liberer_liste(liste_double lst);

// Tri fusion

liste_double fusionner_1(liste_double l1, int n, liste_double l2, int m);
int tri_fusion_1(liste_double* lst, int n);

void separer_liste(liste_double lst, liste_double* l1, liste_double* l2);
liste_double fusionner_2(liste_double l1, liste_double l2);
int tri_fusion_2(liste_double* lst);