#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include <unistd.h>
#include "mpi.h"

int main( int argc, char** argv ){ 
  
	int rank, ranksent, size, source, dest, tag, i; 
	MPI_Status status;
	char host[256], hostrec[256];
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank ); 
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	size_t length;
	gethostname(&host, length);
  
	if(size>1){    
		if( rank != 0 ){ 
			dest=0; tag=0;       
			MPI_Send( &host, 10, MPI_CHAR, dest, tag, MPI_COMM_WORLD );      
		} else {      
			for( i=1; i<size; i++ ) { 	
			MPI_Recv( &hostrec, 10, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status );
			printf("Dane od procesu o randze (i=%d): %s (%d)\n", i,hostrec, status.MPI_SOURCE );
			}      
		}
	}
	else{
		printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
	}  
	MPI_Finalize(); 
  
	return(0);
}

