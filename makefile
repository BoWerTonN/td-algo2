main : main.o liste_double.o tableau_double.o liste_tableau.o util.o chrono.o
	gcc -Wall -pedantic -o main main.o liste_double.o tableau_double.o liste_tableau.o util.o chrono.o
main.o: main.c util.h chrono.h tableau_double.h liste_double.h liste_tableau.h 
	gcc -Wall -pedantic -c $<
liste_double.o: liste_double.c liste_double.h
	gcc -Wall -pedantic -c $<
tableau_double.o: tableau_double.c tableau_double.h
	gcc -Wall -pedantic -c $<
liste_tableau.o: liste_tableau.c liste_tableau.h
	gcc -Wall -pedantic -c $<
util.o: util.c util.h
	gcc -Wall -pedantic -c $<
chrono.o: chrono.c chrono.h
	gcc -Wall -pedantic -c $<

.PHONY : clean solution
clean :
	-rm *.o main
solution: liste_double_sol.c tableau_double_sol.c main.o util.o chrono.o
	gcc -Wall -pedantic -c liste_double_sol.c -o liste_double.o
	gcc -Wall -pedantic -c tableau_double_sol.c -o tableau_double.o
	gcc -Wall -pedantic -o main main.o liste_double.o tableau_double.o liste_tableau.o util.o chrono.o
