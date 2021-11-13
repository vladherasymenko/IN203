#include <mpi.h>
#include <cstdlib>

int main(int argc, char* argv[]) {
	int nbp, rank;
	int tag = 123;
	MPI_Status Stat;

	int message_buf = rand() % 10 + 1;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &nbp);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		std::cout << "Je suis p." << rank << ". La valeur actuelle du message est : " << message_buf << std::endl;
		message_buf += 1;
		MPI_Send(&message_buf, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
		MPI_Recv(&message_buf, 1, MPI_INT, nbp-1, tag, MPI_COMM_WORLD, &Stat);
		std::cout << "Je suis p." << rank << ". C'est le dernier message. La valeur finale est : " << message_buf << std::endl;

	}
	else {
		MPI_Recv(&message_buf, 1, MPI_INT, rank - 1, tag, MPI_COMM_WORLD, &Stat);
		std::cout << "Je suis p." << rank << ". La valeur actuelle du message est : " << message_buf << std::endl;
		message_buf += 1;
		MPI_Send(&message_buf, 1, MPI_INT, (rank+1)%nbp, tag, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;

}