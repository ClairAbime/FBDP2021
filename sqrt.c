#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"mpi.h"
#define N 10000
int main(int argc, char** argv)
{
	int myid,numprocs,i;
	double sqrt_sum, sqrt_single=0.0;
	//scanf("%d",&N);
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	for(i=myid;i<N;i=i+numprocs)
	{
		sqrt_single+=sqrt(i*(i+1));
	}
	MPI_Reduce(&sqrt_single,&sqrt_sum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	if(myid==0)
	{
		printf("The sum of sqrt from 0 to 10000 is %f\n",sqrt_sum);
	}
	MPI_Finalize();
}
