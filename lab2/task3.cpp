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
    int process_number;
    int numProc;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_Size(MPI_COMM_WORLD, &numProc);
    int sourceProc = 0;
    int endProc = numProc-1;
    int x = 20;
    int y = 1;
    int received;

    if(myrank == 0){
        mpiSend(x,myrank,myrank+1);
        mpiRecv(x,endProc, myrank);
        
    } else {
        mpiRecv(received, myrank-1,myrank);
        received += y;
        printf("Added 1 and now it is %d \n", received);
        mpiSend(received, myrank, ((myrank+1+numProc)%numProc)));
    } 

    MPI_Finalize();
    return 0;
}