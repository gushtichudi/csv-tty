// mute annoying unncesessary warnings
#ifdef __APPLE__
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wincompatible-pointer-types-discards-qualifiers"
	#pragma clang diagnostic ignored "-Wstrict-prototypes"
	#pragma clang diagnostic ignored "-Wnewline-eof"
#endif

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// includes from ../include
#include <errors.h>

char *return_csv_contents(const char *filepath) {
	FILE *tmp = fopen(".miscount_tmp", "r");
	if (tmp == NULL) {
		fprintf(stderr, "Cannot open %s: %s\n", filepath, strerror(errno));
		return 1;
	}

	char *buffer = 0;
	long buflen;

	fseek(tmp, 0, SEEK_END);
	buflen = ftell(tmp);
	fseek(tmp, 0, SEEK_SET);

	buffer = malloc(buflen);
	assert(buffer != NULL);

	fread(tmpbuf, 1, buflen, tmp);
	fclose(tmp);

	return buffer;
}

#ifdef __APPLE__
	#pragma clang diagnostic pop
#endif