#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include <time.h>
struct watek{
	int ID;
	int dzien; 
	int miesiac;
};
void * zadanie_watku (void * arg_wsk)
{
	struct watek bufor = *((struct watek*)arg_wsk);
	int id =bufor.ID;
	int dzien = bufor.dzien;
	int miesiac = bufor.miesiac;
	id = rand();
	dzien=rand();
	miesiac=rand();
	
	printf("structura: identyfikator: %d \n dzien: %d \n miesiac: %d\n\n", bufor.ID,  bufor.dzien,  bufor.miesiac);
	printf("lokal: identyfikator: %d \n dzien: %d \n miesiac: %d\n\n",id, dzien, miesiac);
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_testcancel();
	sleep(2);
	return(NULL);
}

main(){
srand(time(0));
	pthread_t tid[10];
	void *wynik;
	int i=0;
	struct watek id;
	for(i=0;i<2;i++){
		id.ID = 10;
		id.dzien = 50;
		id.miesiac = 70;
		pthread_create(&tid[i], NULL, zadanie_watku, &id);
	}
		printf("MAIN: identyfikator: %d \n dzien: %d \n miesiac: %d\n\n", id.ID,  id.dzien, id.miesiac);
	for(i=0;i<2;i++){
		
		pthread_join(tid[i], &wynik);
		
		if (wynik == PTHREAD_CANCELED)
			printf("\twatek glowny: watek potomny zostal zabity\n");
		else
			printf("\twatek glowny: watek potomny NIE zostal zabity - blad\n");
	}
		printf("MAIN: identyfikator: %d \n dzien: %d \n miesiac: %d\n\n", id.ID,  id.dzien, id.miesiac);
	pthread_exit(NULL); 
}
