#include "mpi.h"
#include <stdio.h>
#include <iostream>

using namespace std;


int main(int argc, char *argv[])  {

	printf("Entered Code\n");

	cout << argc << endl;

	int numtasks, rank, dest, source, rc, count, tag=0;  
	char inmsg, outmsg='x';
	MPI_Status Stat;   // required variable for receive routines

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	printf("Setup Done\n");
	cout << "procs = " << numtasks << endl;
	cout << "rank = " << rank << endl;

	// task 0 sends to task 1 and waits to receive a return message
	if (rank == 0) {
		dest = 1;
                source = 1;
		cout << "Entered 'if' 1 with rank = " << rank << endl;
		MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
		cout << "Sent MPI Message 1" << endl;
                MPI_Recv(&inmsg, 1, MPI_CHAR, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &Stat);
       		cout << "Recieved MPI Message 1" << endl;
	 } 

        // task 1 waits for task 0 message then returns a message
        else if (rank == 1) {
		dest = 0;
                source = 0;
		cout << "Entered 'if' 2 with rank = " << rank << endl;
                MPI_Recv(&inmsg, 1, MPI_CHAR, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &Stat);
                cout << "Reieved MPI Message 2" << endl;
		MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
        	cout << "Sent MPI Message 2" << endl;
	}

	printf("Ran Parallel Code\n");
   
        // query receive Stat variable and print message details
//        MPI_Get_count(&Stat, MPI_CHAR, &count);
//        printf("Task %d: Received %d char(s) from task %d with tag %d \n", rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG);
   
        MPI_Finalize();
	printf("Fin\n");
	return 0;
}
