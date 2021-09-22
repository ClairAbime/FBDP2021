#include<stdio.h>
#include<stdlib.h>
#include"mpi.h"
#define a 10
#define b 100
#define N 100000
int main(int argc, char** argv)
{
	int myid,numprocs,t;
	double dx,s,sum=0.0;
	MPI_Status status;
	dx=(double)(b-a)/N;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	numprocs--;
	if(myid==0)
	{
		for(int i=0;i<N;i++)
		{
			MPI_Send(&i,1,MPI_INT,i%numprocs+1,1,MPI_COMM_WORLD);
		}
		for(int source=1;source<=numprocs;source++)
		{
			MPI_Recv(&s,1,MPI_DOUBLE,source,99,MPI_COMM_WORLD,&status);
			sum+=s;
		}
		printf("The integral of y=x^3 from 10 to 100 is %lf\n",sum);
	}
	else
	{
		for(int i=myid-1;i<N;i=i+numprocs)
		{
			MPI_Recv(&t,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
			double x,y;
			x=(double)10+(t+0.5)*dx;
			y=x*x*x;
			sum+=dx*y;}
		MPI_Send(&sum,1,MPI_DOUBLE,0,99,MPI_COMM_WORLD);		
	}
	MPI_Finalize();
}
