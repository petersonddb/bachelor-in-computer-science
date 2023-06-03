#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv) {
	if(argc < 3)
		printf("Usage: %s <key> <byte> [<byte>...]\n", argv[0]);
	else {
		int idx;
		char key, cry, **hexas;

		idx   = 0;
		key   = strtol(argv[1], NULL, 16);
		hexas = argv + 2;

		while(idx < (argc - 2)) {
			cry = strtol(hexas[idx], NULL, 16) - key;
			printf("%3hhu, ", cry);
			++idx;

			if(idx % 8 == 0)
				puts("");
		}

		puts("");
	}

	return 0;
}
