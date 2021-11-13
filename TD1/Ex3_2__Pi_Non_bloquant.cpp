# include <chrono>
# include <random>
#include <mpi.h>
#include <cstdlib>

// Attention , ne marche qu'en C++ 11 ou supérieur :
double approximate_pi(unsigned long nbSamples) {
	typedef std::chrono::high_resolution_clock myclock;
	myclock::time_point beginning = myclock::now();
	myclock::duration d = myclock::now() - beginning;
	unsigned seed = d.count();
	std::default_random_engine generator(seed);
	std::uniform_real_distribution <double > distribution(-1.0, 1.0);
	unsigned long nbDarts = 0;
	// Throw nbSamples darts in the unit square [ -1:1] x [ -1:1]
	for (unsigned sample = 0; sample < nbSamples; ++sample) {
		double x = distribution(generator);
		double y = distribution(generator);
		// Test if the dart is in the unit disk
		if (x * x + y * y <= 1) nbDarts++;
	}
	// Number of nbDarts throwed in the unit disk
	double ratio = double(nbDarts) / double(nbSamples);
	return ratio;
}


int main(int argc, char* argv[]) {
	int nbp, rank;
	int tag = 123;

	MPI_Request reqs_send[nbp-1];
	MPI_Request reqs_recieve[nbp - 1];
	MPI_Status stats_send[nbp - 1];
	MPI_Status stats_recieve[nbp - 1];

	int samples_total = 10000000;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &nbp);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int samples_par_uc = (int)samples_total / nbp + 1;

	double r;
	double buf_r[nbp];

	if (rank == 0) {

		r = approximate_pi(samples_par_uc);
		buf_r[0] = r;
		std::cout << "Je suis p." << rank << ". La valeur calculee est : " << 4 * r << std::endl;
		for (int k = 1; k <= nbp - 1; k++) {
			MPI_Irecv(&buf_r[k], 1, MPI_DOUBLE, k, tag, MPI_COMM_WORLD, &reqs_recieve[k-1]);
		}
		std::cout << "Waiting...\n";
		MPI_Waitall(nbp - 1, reqs_send, stats_send);
		std::cout << "Done\n";
		double res = 0;
		for (int i = 0; i < nbp; i++) {
			res += buf_r[i];
		}
		res = 4 * res / nbp;
		std::cout << "Je suis p." << rank << ". La valeur de pi finale moyenne est : " << res << std::endl;
	}
	else {
		r = approximate_pi(samples_par_uc);
		std::cout << "Je suis p." << rank << ". La valeur calculee est : " << 4*r << std::endl;
		MPI_Isend(&r, 1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &reqs_send[rank]);
		std::cout << "sent\n";
		std::cout << reqs_send[rank];
	}
	MPI_Waitall(nbp - 1, reqs_send, stats_send);
	MPI_Waitall(nbp - 1, reqs_recieve, stats_recieve);
	MPI_Finalize();
	return 0;

}
