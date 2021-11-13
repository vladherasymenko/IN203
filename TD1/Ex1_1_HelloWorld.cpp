#include <mpi.h>
#include <cstdlib>

int main(int argc, char* argv[]) {
	int numtasks, rank;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	std::cout << "Bonjour, je suis la tâche n° " << rank + 1 << " sur " << numtasks << " tâches\n";

	MPI_Finalize();
	return 0;

}