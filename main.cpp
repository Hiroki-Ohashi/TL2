#include <cstdio>
#include <cstdlib>

int main(int argc, char* argv[]) {
	//printf("Hello,World!\n");

	for (int i = 0; i < argc; i++) {
		printf(argv[i]);
		printf("\n");
	}

	system("pause");
	return 0;
}