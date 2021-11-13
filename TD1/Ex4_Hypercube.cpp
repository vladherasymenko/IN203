#include <mpi.h>
#include <cstdlib>
#include <math.h>



int main(int argc, char* argv[]) {
	int nbp, rank;
	int tag = 123;


	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &nbp);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	
	double d_max = log2(nbp);
	if (d_max - int(d_max) != 0) {
		if(rank == 0){
			std::cout << "Il faut que le nombre d'UC soit une puissance de 2 !\n";
		}
		return 1;
	}

	if (rank == 0) {
		std::cout << "La dimension d = " << d_max << std::endl;
	}
	MPI_Status Stat;

	//etape 1
	int jeton_buf;

	int check_if_recieved[nbp] = { 0 };
	
	for(int d = 0; d<d_max; d++){
		if (rank == 0) {
			int jeton = 1;
			jeton_buf = jeton;
			//std::cout << "Je suis p." << rank << ". 'Je vais envoyer le jeton à " << pow(2, d) + rank << std::endl;
			MPI_Send(&jeton, 1, MPI_INT, pow(2,d), tag, MPI_COMM_WORLD);
		}
		else {
			if (rank <= pow(2, d)-1) {
				//std::cout << "Je suis p." << rank << ". 'Je viens de recevoir le jeton \n";
				if(check_if_recieved[rank] == 0){
					MPI_Recv(&jeton_buf, 1, MPI_INT, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &Stat);
					check_if_recieved[rank] = 1;
				}
				//std::cout << "Je suis p." << rank << ". 'Je vais envoyer le jeton à " << pow(2, d) + rank << std::endl;
				MPI_Send(&jeton_buf, 1, MPI_INT, pow(2, d) + rank, tag, MPI_COMM_WORLD);
			}
		}
	}

	for (int k = 0; k < pow(2, d_max-1); k++) {
		if (rank == pow(2,d_max-1)+k) {
			//std::cout << "Je suis p." << rank << ". 'Je viens de recevoir le jeton \n";
			MPI_Recv(&jeton_buf, 1, MPI_INT, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &Stat);
		}
	}

	std::cout << "Je suis p." << rank << ". 'J'ai le jeton : " << jeton_buf << std::endl;

	MPI_Finalize();
	return 0;

}

// mpirun - np 16 --oversubscribe . / a.out
