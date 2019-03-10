#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include<pthread.h>


void * watek_klient (void * arg);
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
int l_kf;
main(){

  pthread_t *tab_klient;
  int *tab_klient_id;

  int l_kl, l_kr, i;

  printf("\nLiczba klientow: "); scanf("%d", &l_kl);

  printf("\nLiczba kufli: "); scanf("%d", &l_kf);

  //printf("\nLiczba kranow: "); scanf("%d", &l_kr);
  l_kr = 1;

  tab_klient = (pthread_t *) malloc(l_kl*sizeof(pthread_t));
  tab_klient_id = (int *) malloc(l_kl*sizeof(int));
  for(i=0;i<l_kl;i++) tab_klient_id[i]=i;


  printf("\nOtwieramy pub (simple)!\n");
  printf("\nLiczba wolnych kufli %d\n", l_kf); 

  for(i=0;i<l_kl;i++){
    pthread_create(&tab_klient[i], NULL, watek_klient, &tab_klient_id[i]); 
  }
  for(i=0;i<l_kl;i++){
    pthread_join( tab_klient[i], NULL);
  }
  printf("\nZamykamy pub!\n");


}


void * watek_klient (void * arg_wsk){

  int moj_id = * ((int *)arg_wsk);

  int i, j=0;
  int ile_musze_wypic = 2;

  printf("\nKlient %d, wchodzę do pubu\n", moj_id); 
    
  for(i=0; i<ile_musze_wypic; i++){
		int sucess = 0;
		do{
			pthread_mutex_lock(&mutex);
			if(l_kf > 0){
				sucess = 1;
				l_kf--;
				printf("\nKlient %d, wybieram kufel %d\n", moj_id); 
				
				j;
				printf("\nKlient %d, nalewam z kranu %d\n", moj_id, j); 
				usleep(300);	
				pthread_mutex_unlock(&mutex);	
						
			}else{		
				printf("Klient %d, brak wolnych kufli\n", moj_id);
				pthread_mutex_unlock(&mutex);	
				usleep(200);
			}		
			
		}while(!sucess);
		
		printf("\nKlient %d, pije\n", moj_id); 
		nanosleep((struct timespec[]){{0, 5000000L}}, NULL);
		pthread_mutex_lock(&mutex);
		printf("\nKlient %d, odkladam kufel\n", moj_id); 
		l_kf++;
    	pthread_mutex_unlock(&mutex);			
		printf("\nAktualnie kufli:%d\n", l_kf); 
  }

  printf("\nKlient %d, wychodzę z pubu\n", moj_id); 
    
  return(NULL);
} 


