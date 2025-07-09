// mute annoying unncesessary warnings
#ifdef __APPLE__
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wincompatible-pointer-types-discards-qualifiers"
	#pragma clang diagnostic ignored "-Wstrict-prototypes"
	#pragma clang diagnostic ignored "-Wnewline-eof"
#endif

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// to get getopt, compile using GCC from MSYS2
#ifdef __WIN32
	#include <getopt.h>
#endif

// includes from ../include
#include <args.h>
#include <errors.h>

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "Usage: csv-view -i <file>.csv\n");
		fprintf(stderr, "Run `csv-view -h` for more information about this command\n\n");
		fprintf(stderr, "NOTE: *ALL* failed assertions are failed memory allocations within this program, just so you know 😉\n\n");
		return EXIT_NO_ARGS;
	}

	Args *args = malloc((sizeof(Args*)) + ((sizeof(char*)) * 2));
	assert(args != NULL);

	int c;
	while ((c = getopt(argc, argv, "i:c:")) != -1) {
		switch (c) {
			case 'i':
				args->input = strdup(optarg);
				break;
			case 'c':
				args->colors = strdup(optarg);
				break;
			default:
				free(args);
				// for more accesibility, repeat the same message throughout the program so the user knows.
				fprintf(stderr, "NOTE: *ALL* failed assertions are failed memory allocations within this program, just so you know 😉\n\n");
				return EXIT_BAD_ARGS;
		}
	}

	

	free(args);
	
	return 0;
}

#ifdef __APPLE__
	#pragma clang diagnostic pop
#endif