#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <linux/sched.h>

int zmienna_globalna=0;

#define ROZMIAR_STOSU 1024*64

int funkcja_watku( void* argument )
{
   for( int i=0;i<100;i++){
  	zmienna_globalna++;
	argument++;
	}
   printf("zmienna globalna: %d, zmienna lokalna: %d \n", zmienna_globalna, argument);
   /*int wynik; 
   wynik=execv("./program/program",NULL); 
   if(wynik==-1) 
     printf("Proces potomny nie wykonal programu\n"); 
*/
  return 0;

}

main()
{

  void *stos;
  void *stos2;
  int zmienna=0;
  pid_t pid;
  pid_t pid2;
  int i; 
  
  stos = malloc( ROZMIAR_STOSU );
  stos2 = malloc( ROZMIAR_STOSU );
  if (stos == 0) {
    printf("Proces nadrzędny - blad alokacji stosu\n");
    exit( 1 );
  }
  if (stos2 == 0) {
    printf("Proces nadrzędny - blad alokacji stosu\n");
    exit( 1 );
  }
  inicjuj_czas();
  /*for(i=0;i<1000;i++){*/

    pid = clone( &funkcja_watku, (void * ) stos+ROZMIAR_STOSU, 
		 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &zmienna);
    pid2 = clone( &funkcja_watku, (void *) stos2+ROZMIAR_STOSU, 
		 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &zmienna );

    waitpid(pid, NULL, __WCLONE);

    waitpid(pid2, NULL, __WCLONE);


 /* }*/
  printf("koniec watku1 i zmienna glob: %d, lok:%d \n",zmienna_globalna, zmienna);
  printf("koniec watku2 i zmienna glob: %d, lok: %d\n",zmienna_globalna, zmienna);
  drukuj_czas();

  free( stos );
  free( stos2 );
}
