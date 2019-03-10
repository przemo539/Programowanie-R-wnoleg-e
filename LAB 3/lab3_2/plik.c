#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
void * zadanie_watku (void * arg_wsk)
{

	printf("identyfikator: %d \n wskaznik: %d \n\n",pthread_self(), *((int *)arg_wsk));
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_testcancel();
	sleep(2);
	return(NULL);
}
main(){
	pthread_t tid[10];
	void *wynik;
	int i=0;
	int id[10];
	for(i=0;i<10;i++){
		id[i]=i;
		pthread_create(&tid[i], NULL, zadanie_watku, &id[i]);
	}
	
	for(i=0;i<10;i++){
		pthread_cancel(tid[i]);
		
		pthread_join(tid[i], &wynik);
		
		if (wynik == PTHREAD_CANCELED)
			printf("\twatek glowny: watek potomny zostal zabity\n");
		else
			printf("\twatek glowny: watek potomny NIE zostal zabity - blad\n");
	}
	pthread_exit(NULL); 
}
