#include <iostream>
#include <mpi.h>

using namespace std;

void mpiSend(int& number, int current, int destination){
    printf("Process number %d will send a number %d to process number %d \n", current, number, destination);
    MPI_Send(&number,1, MPI_INT, destination, 0, MPI_COMM_WORLD);
    printf("Process number %d sent a number %d to process number %d \n", current, number, destination);
}

void mpiRecv(int& number, int source, int current){
    printf("Process number %d will reveive a number %d from process number %d \n", current, number, source);
    MPI_Recv(&number,1, MPI_INT, source, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    printf("Process number %d received a number %d from process number %d \n", current, number, source);
}


int main(int argc, char **argv) {
    int myrank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    int sourceProc = 0;
    int destProc = 1;
    int x = 20;
    int received;

    if(myrank == 0){
        mpiSend(x,myrank, destProc);
        mpiRecv(received,destProc,myrank);
        
    } else if (myrank == 1) {
        mpiRecv(received, sourceProc, myrank);
        
        received += 20;
        printf("Added 20 and now it is %d \n", received);
        
        mpiSend(received, myrank, sourceProc);
  
    } else{
        printf("Something went wrong");
    }

    MPI_Finalize();
    return 0;
}


