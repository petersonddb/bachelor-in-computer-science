#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv) {
	if(argc < 2)
		printf("Usage: %s <byte> [<byte>...]\n", argv[0]);
	else {
		int  i   = 1;
		char sum = 0;

		while(i < argc) {
			sum += atoi(argv[i]);
			++i;
		}

		printf("Result: %hhu\n", sum);
	}

	return 0;
}
