#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#include"czytelnia.h"


/*** Implementacja procedur interfejsu ***/

int my_read_lock_lock(czytelnia_t* czytelnia_p){
	pthread_mutex_lock (& czytelnia_p->muteks);
	if(czytelnia_p->liczba_pisz > 0 ||  czytelnia_p->liczba_pisz == 0)
		pthread_cond_wait(&czytelnia_p->czytelnicy, &czytelnia_p->muteks);
	czytelnia_p -> liczba_czyt ++;
	pthread_cond_signal(&czytelnia_p ->czytelnicy);
	pthread_mutex_unlock (& czytelnia_p->muteks);
}


int my_read_lock_unlock(czytelnia_t* czytelnia_p){
	pthread_mutex_lock(&czytelnia_p->muteks);
	czytelnia_p->liczba_czyt --;
	if(czytelnia_p->liczba_czyt > 0 || czytelnia_p->liczba_czyt == 0)
		pthread_cond_signal(&czytelnia_p->pisarze);
	pthread_mutex_unlock(&czytelnia_p->muteks);
}


int my_write_lock_lock(czytelnia_t* czytelnia_p){
	pthread_mutex_lock(&czytelnia_p->muteks);
	if((czytelnia_p->liczba_czyt + czytelnia_p->liczba_pisz) > 0)
		pthread_cond_wait(&czytelnia_p->pisarze,&czytelnia_p->muteks);
	czytelnia_p->liczba_pisz++;
	pthread_mutex_unlock(&czytelnia_p->muteks);
}


int my_write_lock_unlock(czytelnia_t* czytelnia_p){
	pthread_mutex_lock(&czytelnia_p->muteks);
	czytelnia_p->liczba_pisz --;
	if(czytelnia_p->liczba_czyt == 0){
		pthread_cond_signal(&czytelnia_p->czytelnicy);
	}else{
		pthread_cond_signal(&czytelnia_p->pisarze);
	}
	pthread_mutex_unlock(&czytelnia_p->muteks);
}

void inicjuj(czytelnia_t* czytelnia_p){
	czytelnia_p->liczba_czyt = 0;
	czytelnia_p->liczba_pisz = 0;
	pthread_mutex_init(&czytelnia_p->muteks,NULL);
	pthread_cond_init(&czytelnia_p->czytelnicy, NULL);
	pthread_cond_init(&czytelnia_p->pisarze, NULL);
}

void czytam(czytelnia_t* czytelnia_p){
  printf("czytelnicy: %d \n", czytelnia_p->liczba_czyt);
    usleep(rand()%1000000);
}

void pisze(czytelnia_t* czytelnia_p){
  printf("pisarze: %d \n", czytelnia_p->liczba_pisz);
    usleep(rand()%1000000);
}


