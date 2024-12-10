/* chrono.h (IGI-3005)

  JCG 15/09/2008
  maj 07/12/2017
  DV  2024-11-22

  fonctions de chronometrage 
*/

#include <setjmp.h> /* pour l'interruption en cas de depassement de temps */

#ifndef __CHRONO_H__
#define __CHRONO_H__

void lanceChrono(double limite);
void arretChrono();
double lectureChrono();

typedef int (* type_fonction)(double *, int); 

#define  HORS_DELAI (-1.0)

double chronometre(type_fonction func, double w[], int n, double limite);

#endif
