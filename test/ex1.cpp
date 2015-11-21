#include "iif.h"

static int nondet() {
	return rand() % 4;
	return rand() % 20;
}

int ex1(int* a) {
	int x;
	int y;
	int xa = a[0];
	int ya = a[1];

	iif_assume(xa + 2 * ya >= 0);
	while (nondet()) {
		recordi(xa, ya);
		x = xa + 2 * ya;
		y = -2 * xa + ya;

		x++;
		if (nondet()) y = y + x;
		else y = y - x;

		xa = x - 2 * y;
		ya = 2 * x + y;
	}
	recordi(xa, ya);
	iif_assert(xa + 2 * ya >= 0);
	return 0;
}

int main(int argc, char** argv)
{
	if (argc >= 3) {
		minv = atoi(argv[1]);
		maxv = atoi(argv[2]);
	}

	States global_states_sets[4];
	States* gsets = &global_states_sets[1];

	if (register_program(conj, "conj") == false) {
		return -1;
	}

	IIF_svm_learn isl(gsets, target_program);
	if (isl.learn() == 0) {
		std::cout << "END.\n";
		return 0;
	}

	std::cout << "TRY SVM-I method again...\n";
	IIF_svm_i_learn isil(gsets, target_program);
	if (isil.learn() == 0) {
		std::cout << "END.\n";
		return 0;
	}

	std::cout << "TRY other method again...\n";
	return 0;
}
