#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<math.h>

#include"pomiar_czasu.h"

#define ROZMIAR 100000000 
#define LICZBA_W 3

pthread_mutex_t muteks; 
pthread_t watki[LICZBA_W];
double global_array_of_local_sums[LICZBA_W];

double f(double x);

double calkowanie(int N);
void *suma_w( void *arg_wsk);
void *suma_w_no_mutex( void *arg_wsk);

double *tab;
double suma=0; 

int main( int argc, char *argv[] ){

  int i; 

  double t1,t2,t3;

  int indeksy[LICZBA_W]; 
  for(i=0;i<LICZBA_W;i++) indeksy[i]=i;

  tab = (double *) malloc(ROZMIAR*sizeof(double));
  for(i=0; i<ROZMIAR; i++ ) tab[i] = ((double) i+1) / ROZMIAR; 


  pthread_mutex_init( &muteks, NULL);

  printf("Poczatek tworzenia watkow\n");
  t1 = czas_zegara();

  for(i=0; i<LICZBA_W; i++ ) 
    pthread_create( &watki[i], NULL, suma_w, (void *) &indeksy[i] );
  // synchronization error !!!
    // pthread_create( &watki[i], NULL, suma_w, (void *) &i ); 

  for(i=0; i<LICZBA_W; i++ ) pthread_join( watki[i], NULL );

  t1 = czas_zegara() - t1;
  printf("suma = %lf\n", suma);
  printf("Czas obliczen = %lf\n", t1);

  // version with array of local sums (to eliminate the mutex) 
  suma =0;
  printf("Poczatek tworzenia watkow\n");
  t1 = czas_zegara();

  for(i=0; i<LICZBA_W; i++ ) {
    global_array_of_local_sums[i]=0.0;
    pthread_create( &watki[i], NULL, suma_w_no_mutex, (void *) &indeksy[i] );
  // synchronization error !!!
    //pthread_create( &watki[i], NULL, suma_w, (void *) &i );
  }

  for(i=0; i<LICZBA_W; i++ ) {
    pthread_join( watki[i], NULL );
    suma += global_array_of_local_sums[i];
  }

  t1 = czas_zegara() - t1;
  printf("suma = %lf\n", suma);
  printf("Czas obliczen (no mutex) = %lf\n", t1);

/*   suma =0; */

/*   printf("Poczatek tworzenia watkow OpenMP\n"); */
/*   t1 = czas_zegara(); */

/* #pragma omp parallel for num_threads(LICZBA_W) default(none) shared (tab) reduction(+:suma)  */
/*   for(i=0;i<ROZMIAR;i++){ */
/*     suma += tab[i]; */
/*   } */



/*   t1 = czas_zegara() - t1; */
/*   printf("suma = %lf\n", suma); */
/*   printf("Czas obliczen OpenMP = %lf\n", t1); */
double calka = calkowanie(10);
printf("\ncalka(10) z sin(x): %f\n",calka);
  calka = calkowanie(100);
printf("\ncalka(100) z sin(x): %f\n",calka);
  calka = calkowanie(1000);
printf("\ncalka(100) z sin(x): %f\n",calka);
  calka = calkowanie(1000);
printf("\ncalka(1000) z sin(x): %f\n",calka);
  calka = calkowanie(10000);
printf("\ncalka(10000) z sin(x): %f\n",calka);
 
}

double f(double x){
	return sin(x);
}
double calkowanie(int N){
	double x1 = 0; 
	double c=0.0; 
	double dx = (3.14159265359-0)/N;
	double x2=0;
	int i=0;
	for(i=0;i<N;i++){
		x2=x1+dx;  
		c+=0.5*(f(x1)+f(x2))*dx; 
		x1=x2;
	}
	return c;
}

void *suma_w( void *arg_wsk){

  int i, j, moj_id;

  double moja_suma=0;

  moj_id = *( (int *) arg_wsk ); 

  j=ROZMIAR/LICZBA_W;
  for( i=j*moj_id+1; i<=j*(moj_id+1); i++){ 
    moja_suma += tab[i]; 
  }

  pthread_mutex_lock( &muteks );
  suma += moja_suma;
  pthread_mutex_unlock( &muteks );

  pthread_exit( (void *)0);

}

void *suma_w_no_mutex( void *arg_wsk){

  int i, j, moj_id;

  moj_id = *( (int *) arg_wsk ); 

  j=ROZMIAR/LICZBA_W;
  for( i=j*moj_id+1; i<=j*(moj_id+1); i++){ 
    global_array_of_local_sums[moj_id] += tab[i]; 
  }

  pthread_exit( (void *)0);

}



