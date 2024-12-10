#include <stdio.h> /* pour affichages */
#include <stdlib.h> /* pour malloc */
#include <ctype.h> /* pour tolower() dans le choix de menu */

#include <time.h> /* pour l'initialisation du geneateur de nombres  aleatoires */

#include "util.h" /* les differents remplissages et utilitaires*/
#include "chrono.h" /* gestion du chronometrage et des interruptions en cas de depassement de temps */

#include "tableau_double.h"
#include "liste_double.h"
#include "liste_tableau.h"




time_t seed;
double* initialize_array(double* array, int n) {
    if (array) free(array);

    array = malloc(sizeof(double)*n);
    if (!array) {
        printf("Erreur de allocation\n");
        exit(-1);
    }

    srand(seed+n);
    remplirAlea(array, n);
    return array;
}





int verif_elements(double a, double b, int i) {
    if (a == b) return 0;
    printf("Element %d incorrect\n", i);
    return -1;
}

int verif_elements_leq(double a, double b, int i) {
    if (a <= b) return 0;
    printf("Ordre des elements %d et %d incorrecte\n", i,i+1);
    return -1;
}

int verif_nombre(int n, int nn) {
    if (n == nn) return 0;
    printf("Nombre d'elements incorrect\n");
    return -1;
}

int verif_capacite(int m, int mm) {
    if (m == mm) return 0;
    printf("Capacite incorrecte\n");
    return -1;
}

int verif_capacite_suf(int m, int mm) {
    if (m >= mm) return 0;
    printf("Capacite trop faible\n");
    return -1;
}

int verif_memoire(void* p) {
    if (p != NULL) return 0;
    printf("Memoire pas allouee\n");
    return -1;
}

void pass() {
    printf("Reussi\n");
}

int test_tableau_dynamique(double* array, int n) {
    int i, j;
    printf("------------- Tests du tableau dynamique ------------\n");

    if (n < 4) {
        printf("Test impossible avec moins de 4 éléments\n");
        return -2;
    }

    int m = 4;
    tableau_double tbl = nouveau_tableau(m);
    printf("Test d'initialisation... \t");
    if (verif_memoire((void*)tbl.t) || verif_nombre(tbl.n, 0) || verif_capacite(tbl.m, m))
        return -3;
    tbl.t[m-1] += 0; // Teste la memoire (peut generer un Segmentation Fault si incorrect)
    pass();

    m = 20;
    redim_tableau(&tbl, m);
    printf("Test de redimensionnement...\t");
    if (verif_memoire((void*)tbl.t) || verif_nombre(tbl.n, 0) || verif_capacite(tbl.m, m))
        return -4;
    tbl.t[m-1] += 0; // Teste la memoire (peut generer un Segmentation Fault si incorrect)
    pass();

    printf("Test de insertion a la fin...\t");
    for (j=0; j<n/2; j++)
        inserer_tableau(&tbl, j, array[j]);
    i=j;
    if (verif_nombre(tbl.n, i) || verif_capacite_suf(tbl.m, i))
        return -5;
    for (j=0; j<i; j++)
        if (verif_elements(tbl.t[j], array[j], j))
            return -5;
    pass();

    printf("Test de insertion...\t\t");
    for (j=n-1; j>=i; j--)
        inserer_tableau(&tbl, i, array[j]);
    if (verif_nombre(tbl.n, n) || verif_capacite_suf(tbl.m, n))
        return -6;
    for (j=0; j<n; j++)
        if (verif_elements(tbl.t[j], array[j], j))
            return -6;
    pass();

    int c=0, p=1, l=0;
    printf("Test de suppression...\t\t");
    for (j=1;j<n-c;j*=2) {
        supprimer_tableau(&tbl, j);
        c++;
    }
    if (verif_nombre(tbl.n, n-c) || verif_capacite_suf(tbl.m, n-c))
        return -7;
    for (j=0; j<n; j++) {
        if (j-l == p) {
            p *= 2;
            l++;
            continue;
        }
        if (verif_elements(tbl.t[j-l], array[j], j-l))
            return -7;
    }
    pass();

    liberer_tableau(&tbl);
    return 0;
}

int test_liste(double* array, int n) {
    int i, j;
    liste_double lst, p;
    printf("------------- Tests de la liste chainee -------------\n");

    if (n < 4) {
        printf("Test impossible avec moins de 4 éléments\n");
        return -2;
    }

    printf("Test de nouveau maillon... \t");
    lst = nouveau_maillon(array[0]);
    if (verif_elements((*lst).val, array[0], 0))
        return -3;
    pass();

    printf("Test de insertion apres... \t");
    i = 1+n/2;
    for (j=i-1; j>=1; j--)
        inserer_apres_liste(lst, array[j]);
    p = lst;
    for (j=0; j<i; j++) {
        if ((p==NULL && verif_nombre(j,i)) || verif_elements(p->val, array[j],j))
            return -4;
        p = p->suiv;
    }
    pass();

    printf("Test de avancer... \t\t");
    p = avancer_liste(lst, i/2);
    if ((p==NULL && verif_nombre(0,1)) || verif_elements(p->val, array[i/2],i/2))
        return -5;
    pass();

    printf("Test de longueur... \t\t");
    if (verif_nombre(longueur_liste(lst), i))
        return -6;
    pass();

    printf("Test de insertion position...\t");
    for (j=n-1; j>=i; j--)
        inserer_position_liste(&lst, i, array[j]);
    if (verif_nombre(longueur_liste(lst), n))
        return -6;
    p = lst;
    for (j=0; j<n; j++) {
        if ((p==NULL && verif_nombre(j,n)) || verif_elements(p->val, array[j],j))
            return -6;
        p = p->suiv;
    }
    pass();

    printf("Test de suppression apres...\t");
    supprimer_apres_liste(lst);
    supprimer_apres_liste(lst->suiv);
    p = lst;
    for (j=0; j<3; j++) {
        if ((p==NULL && verif_nombre(j,n)) || verif_elements(p->val, array[2*j],j))
            return -7;
        p = p->suiv;
    }
    pass();

    int c=2, k=1, l=0;
    printf("Test de suppression position...\t");
    for (j=4;j<n-c;j*=2) {
        supprimer_position_liste(&lst, j);
        c++;
    }
    if (verif_nombre(longueur_liste(lst), n-c))
        return -8;
    p = lst;
    for (j=0; j<n; j++) {
        if (j-l == k) {
            k *= 2;
            l++;
            continue;
        }
        if ((p==NULL && verif_nombre(j,n)) || verif_elements(p->val, array[j], j-l))
            return -8;
        p = p->suiv;
    }
    pass();

    printf("Test de liberation...\t\t");
    liberer_liste(lst);
    pass();

    return 0;
}

int test_tri_fusion_1(double* array, int n) {
    liste_double lst = NULL, p;
    int j;

    printf("--------------- Tests du tri fusion 1 ---------------\n");

    printf("Insertion...\t\t");
    for (j=n-1; j>=0; j--)
        inserer_position_liste(&lst, 0, array[j]);
    p = lst;
    for (j=0; j<n; j++) {
        if ((p==NULL && verif_nombre(j,n)) || verif_elements(p->val, array[j],j))
            return -2;
        p = p->suiv;
    }
    pass();

    printf("Tri Fusion 1...\t\t");
    tri_fusion_1(&lst, n);
    p = lst;
    if (p == NULL && verif_nombre(0,1))
        return -3;
    for (j=0; j<n-1; j++) {
        if ((p->suiv==NULL && verif_nombre(j,n)) || verif_elements_leq(p->val, p->suiv->val, j))
            return -3;
        p = p->suiv;
    }
    return 0;
}

int test_tri_fusion_2(double* array, int n) {
    liste_double lst = NULL, p;
    int j;

    printf("--------------- Tests du tri fusion 2 ---------------\n");

    printf("Insertion...\t\t");
    for (j=n-1; j>=0; j--)
        inserer_position_liste(&lst, 0, array[j]);
    p = lst;
    for (j=0; j<n; j++) {
        if ((p==NULL && verif_nombre(j,n)) || verif_elements(p->val, array[j],j))
            return -2;
        p = p->suiv;
    }
    pass();

    printf("Tri Fusion 2...\t\t");
    tri_fusion_2(&lst);
    p = lst;
    if (p == NULL && verif_nombre(0,1))
        return -3;
    for (j=0; j<n-1; j++) {
        if ((p->suiv==NULL && verif_nombre(j,n)) || verif_elements_leq(p->val, p->suiv->val, j))
            return -3;
        p = p->suiv;
    }
    return 0;
}




char affiche_menu_opt(int nbelts, double tps_max) {
    /* etat actuel */
    printf("\n--------------- Configuration actuelle --------------\n\n");
    printf("%-20s : %d\n%-20s : %.3f s\n",
             "Taille", nbelts,
             "Limite de temps", tps_max); 

    /********************* MENU *****************************/
    printf("\n\t\t--- Menu ---\n");
    printf("\t1. Lancer les tests du tableau dynamique\n");
    printf("\t2. Lancer les tests de la liste chainee\n");
    printf("\t3. Lancer les tests de tri\n");
    // printf("\t4. Lancer les tests de la liste chainee sur un tableau\n");
    printf("\n");

    printf("\t5. Changer le (n)ombre d'elements\n");
    printf("\t6. Changer la (l)imite de temps\n");
    printf("\n");
    printf("\t0. (Q)uitter le programme\n");

    /**************************** reponse  ***********************/
    char  *rep = saisie_rep();
    return tolower(rep[0]);
}


int main() { 
    double tps_max = 2.0;  // temps limite
    double x;              // double pour la saisie
    double t;              // temps de tri

    char op;               // reponse utilisateur
    int n;                 //nombre saisi

    int nbelts = 10000;    // nombre d'elements du tableau
    int fin = 0;           // pour terminer

    seed = time(NULL);

    double * array = initialize_array(NULL, nbelts);

    do {
        op = affiche_menu_opt(nbelts, tps_max);

        printf("\n-----------------------------------------------------\n");
        if (op == 'n' || op == '5') {
            printf("\nEntrez le nombre d'elements a utiliser (0 pour quitter) : ");
            n = saisie_int();
            if (n < 0 )
                printf("%d : nb elements impossible \n\n", n);
            else if (n > 0) {
                nbelts = n;
                array = initialize_array(NULL, nbelts);
            }
        }
        else if (op == 'l' || op == '6') {
            printf("\nEntrez le temps maximum autorise (0 pour quitter) : ");
            x = saisie_double();
            if (x < 0) 
                printf("%.3f : temps maxi autorise impossible \n\n", x);
            if (x > 0) 
                tps_max = x;
        }
        else if (op == 'q' || op == '0') {
            fin = -1;
        }
        else if (op == '1') {
            t = chronometre(test_tableau_dynamique, array, nbelts, tps_max);

            if (t >= 0) 
                printf("Tests reussis en %.3f s\n", t);
            else if (t == HORS_DELAI) 
                printf("Tests non termine en %.3f s\n", tps_max);
            else
                printf("Erreur dans les tests!\n");
        }
        else if (op == '2') {
            t = chronometre(test_liste, array, nbelts, tps_max);

            if (t >= 0) 
                printf("Tests reussis en %.3f s\n", t);
            else if (t == HORS_DELAI) 
                printf("Tests non termine en %.3f s\n", tps_max);
            else
                printf("Erreur dans les tests!\n");
        }
        else if (op == '3') {
            t = chronometre(test_tri_fusion_1, array, nbelts, tps_max);

            if (t >= 0) 
                printf("Test reussis en %.3f s\n", t);
            else if (t == HORS_DELAI) 
                printf("Test non termine en %.3f s\n", tps_max);
            else
                printf("Erreur dans les test!\n");

            t = chronometre(test_tri_fusion_2, array, nbelts, tps_max);

            if (t >= 0) 
                printf("Test reussis en %.3f s\n", t);
            else if (t == HORS_DELAI) 
                printf("Test non termine en %.3f s\n", tps_max);
            else
                printf("Erreur dans les test!\n");
        }
    } while (! fin);

    return 0;
}

