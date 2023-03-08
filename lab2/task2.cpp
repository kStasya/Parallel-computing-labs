#include "mpi.h"

#define N 3

int main(int argc, char **argv){
    MPI_Status status;
    int i = 256, j; // передаваемые целочисленные значения
    int size, rank; 
    double starttime, endtime, time; 
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // общее число параллельных процессов
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // идентификатор процесса

    starttime = MPI_Wtime();
    if (rank==0)
    {
        MPI_Send(&i, 1, MPI_INT, 1, 1,  MPI_COMM_WORLD);
        MPI_Recv(&j, 1, MPI_INT, 1, 2, MPI_COMM_WORLD, &status);
        printf("Процесс 0 получил значение: %d.\n", j);
    } else if (rank == 1)
    {
        MPI_Recv(&j, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        MPI_Send(&i, 1, MPI_INT, 0, 2,  MPI_COMM_WORLD);
        printf("Процесс 1 получил значение: %d.\n", j);
    } 
    MPI_Barrier(MPI_COMM_WORLD);
    endtime = MPI_Wtime();
    time = endtime - starttime;  // in microseconds
    printf("Затраченное время: %f мкс.\n", time);
    MPI_Finalize();
    return 0;
}
