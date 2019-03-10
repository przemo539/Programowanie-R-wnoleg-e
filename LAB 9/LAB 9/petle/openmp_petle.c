#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 13

main ()
{
  double a[WYMIAR][WYMIAR];
  int number_of_threads = 3;
  int n,i,j;

  for(i=0;i<WYMIAR;i++) for(j=0;j<WYMIAR;j++) a[i][j]=1.02*i+1.01*j;

  n=WYMIAR;

  double suma=0.0;
  for(i=0;i<WYMIAR;i++) {
    for(j=0;j<WYMIAR;j++) {
      suma += a[i][j];
    }
  }
  
  printf("Suma wyrazów tablicy: %lf\n", suma);

  omp_set_nested(1);

	//wierszowego – zrównoleglenie pętli zewnętrznej – klauzula  reduction
	double suma_parallel=0.0;
	//#pragma omp parallel for private(j) reduction(+:suma_parallel)
	//#pragma omp parallel for ordered schedule(static, 3) private(j) reduction(+ : suma_parallel)
	#pragma omp parallel for ordered schedule(static) private(j) reduction(+ : suma_parallel)
	for(i=0;i<WYMIAR;i++) {
		int id_w = omp_get_thread_num();
		for(j=0;j<WYMIAR;j++) {
			suma_parallel += a[i][j];
			#pragma omp ordered
			printf("(%2d,%2d)-W(%1d,%1d) ",i,j,id_w,omp_get_thread_num()); 
		}
		printf("\n");
	}
	printf("Suma wyrazów tablicy równolegle: %lf\n", suma_parallel);
  
  
  
  
	//wierszowego – zrównoleglenie pętli wewnętrznej – tablica wartości dla wątków
	suma_parallel=0.0;
	double *tab_sum = malloc(sizeof *tab_sum * number_of_threads);
	for ( i = 0; i < number_of_threads; i++ )//tablica do sumowania
		tab_sum[i] = 0.0;		

	for(i=0;i<WYMIAR;i++) {
		int id_w = omp_get_thread_num();
		//#pragma omp parallel for firstprivate(i) num_threads(3)
		//#pragma omp parallel for ordered schedule(static, 3) firstprivate(i) num_threads(3)
		#pragma omp parallel for ordered schedule(static) firstprivate(i) num_threads(3)
		for(j=0;j<WYMIAR;j++) {		
			tab_sum[omp_get_thread_num()] += a[i][j];
			#pragma omp ordered
			printf("(%2d,%2d)-W(%1d,%1d) ",i,j,id_w,omp_get_thread_num()); 
		}
		printf("\n");
	}
  
	int k;
  	for ( k = 0; k < number_of_threads; k++ )
			suma_parallel += tab_sum[k];
  
	printf("Suma wyrazów tablicy równolegle: %lf\n", suma_parallel);
  
  
  	//kolumnowo – zrównoleglenie pętli zewnętrznej – klauzula  reduction
  suma_parallel=0.0;
 
	for(i=0;i<WYMIAR;i++) {
		int id_w = omp_get_thread_num();		
		//#pragma omp parallel for firstprivate(i) reduction(+:suma_parallel)
		//#pragma omp parallel for ordered schedule(static, 3) firstprivate(j) reduction(+ : suma_parallel)
		#pragma omp parallel for ordered schedule(static) firstprivate(j) reduction(+ : suma_parallel)
		for(j=0;j<WYMIAR;j++) {
		suma_parallel += a[i][j];
		#pragma omp ordered
		printf("(%2d,%2d)-W(%1d,%1d) ",i,j,id_w,omp_get_thread_num()); 
		}
		printf("\n");
	}
	printf("Suma wyrazów tablicy równolegle: %lf\n", suma_parallel);
  
  
  
	//kolumna – zrównoleglenie pętli zewnętrznej 
  suma_parallel=0.0;
  
	double suma_czesciowa = 0.0;
	//#pragma omp parallel for  private(i,j, suma_czesciowa) num_threads(3)
	//#pragma omp parallel for ordered schedule(static, 3) private(i, suma_czesciowa)
	#pragma omp parallel for ordered schedule(static) private(i, suma_czesciowa)
	for(i=0;i<WYMIAR;i++) {
		suma_czesciowa=0.0;
		int id_w = omp_get_thread_num();
		for(j=0;j<WYMIAR;j++) {
			suma_czesciowa += a[i][j];
			#pragma omp ordered
			printf("(%2d,%2d)-W(%1d,%1d) ",i,j,id_w,omp_get_thread_num()); 
		}
		#pragma omp critical
		{
			suma_parallel += suma_czesciowa;
		}
		printf("\n");    
	}
	printf("Suma wyrazów tablicy równolegle: %lf\n", suma_parallel);
  
  
  

}
