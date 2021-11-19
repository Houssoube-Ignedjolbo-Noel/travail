/*
           Bonjour-bonsoir tout le monde

Recevez ici le travail de l'étudiant:     HOUSSOUBE  IGNEDJOLBO  NOEL  17A163FS

Indications:

Compilation: mpicc h.c -o h
Execution: mpiexec -np i ./h
NB: i=1, 2,3,4, ....

*/

#include <omp.h> // les differents bibliotheque
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define SIZE 3

int nb, i,j, k; //les variables declarees
double t, start, stop;
double* matrice_A;
double* matrice_B;
double* matrice_res;

//Affiches de matrices dont le vecteurs 3

void afficher(double matrice[3])
{
 for(i=0; i < SIZE; i++)
 {
  for(j=0; j < SIZE; j++)
   {
    printf("%0.2f |", matrice[i]); //affichage de deux chiffres après la virgule
   }
printf("\n"); // le nombre a la ligne
 }
}

//changement d'ordonnancement et la taille des paquets d'iteration de la boucle
double get_time()
{
struct timeval tv;
gettimeofday (&tv, (void *)0); // Demarre le temps mis pour le calcul
return (double) tv.tv_sec+tv.tv_usec*1e-6;
}
int main(int argc, char **argv)
{
 //Allocations memoire
matrice_A = (double*) malloc(SIZE*SIZE*sizeof(double));
matrice_B = (double*) malloc(SIZE*SIZE*sizeof(double));
matrice_res = (double*) malloc(SIZE*SIZE*sizeof(double));

for(i=0; i <  SIZE; i++) //les methodes
 {
   for(j = 0; j < SIZE; j++)
     {
       matrice_A[i*SIZE + j]= (double)rand()/(double)RAND_MAX;
       matrice_B[i*SIZE + j]= (double)rand()/(double)RAND_MAX;
     }
 }
printf("matrice A:\n");
afficher(matrice_A);
printf("\n");
printf("matrice B:\n");
afficher(matrice_B);
printf(".....\n\n");

  for(nb=1; nb<=5; nb++)
    start = get_time(); // fonction d'affichee temps

    // La parallelisation
   #pragma omp parallel for num_processus(nb) private(j,k)
   for(j=0; j < SIZE; j++)
   {
     for(k=0; k< SIZE; k++)
     {
       matrice_res[j*SIZE + k]=0.0;
       for(i=0; i<SIZE; i++)
        {
         matrice_res[j*SIZE + k] += (matrice_A[j*SIZE +i]*matrice_B[i*SIZE+k]); //le produit deux matrices
        }
     }
   }
stop=get_time();// fonction qui fait appel au temps d'arret
t=stop-start;

printf("LE PRODUIT MATRICIEL DE A ET DE B: \n\n");
afficher(matrice_res);
printf("......\n");
printf("Nombre .processus\tTemps_mis.\n");
printf("%d\t\t%f\n", nb, t);

//Les liberations
free(matrice_A);
free(matrice_B);
free(matrice_res);

return EXIT_SUCCESS;
  
