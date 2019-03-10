#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include <unistd.h>
#include "mpi.h"

int main( int argc, char** argv ){ 
	int rank, ranksent, size, source, dest, tag, i; 
	MPI_Status status;
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank ); 
	MPI_Comm_size( MPI_COMM_WORLD, &size );

	int j;
	for (j=0; j<4; j++){
		if( rank == 0 ){
			dest=rank+1;
			MPI_Send( &rank, 1, MPI_INT, dest, tag, MPI_COMM_WORLD );
			printf("Wyslano z procesu %d\n", rank);	  
			MPI_Recv( &ranksent, 1, MPI_INT, size-1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			printf("Proces %d odebral: %d\n", rank, ranksent);      
		}else if (rank==size-1){
			dest=0;
			MPI_Recv( &ranksent, 1, MPI_INT, rank-1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			printf("Proces %d odebral: %d\n", rank, ranksent);
			MPI_Send( &rank, 1, MPI_INT, dest, tag, MPI_COMM_WORLD );
			printf("Wyslano z procesu %d\n", rank);  
		}else{
			MPI_Recv( &ranksent, 1, MPI_INT, rank-1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			printf("Proces %d odebral: %d\n", rank, ranksent);
			printf("Koniec sztafety");
			break;
		}
	}
  
  MPI_Finalize(); 
  
  return(0);

}

