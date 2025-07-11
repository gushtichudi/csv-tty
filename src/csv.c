// mute annoying unncesessary warnings
#ifdef __APPLE__
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wincompatible-pointer-types-discards-qualifiers"
	#pragma clang diagnostic ignored "-Wstrict-prototypes"
	#pragma clang diagnostic ignored "-Wnewline-eof"
	#pragma clang diagnostic ignored "-Wsometimes-uninitialized"
#endif

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// includes from ../include
#include <args.h>
#include <csv.h>
#include <errors.h>

// differnent os'es have different newlines ('\n' on linux, '\r\n' on macOS etc)
// if we don't handle them properly, we might get a segfault

#define NEWLINE "\r\n"
#if defined(__APPLE__)
	#define NEWLINE "\r\n"
#elif defined(__linux__)
	#define NEWLINE "\n"
#endif

static char *return_csv_contents(const char *filepath) {
	FILE *tmp = fopen(filepath, "r");
	if (tmp == NULL) {
		fprintf(stderr, "Cannot open %s: %s\n", filepath, strerror(errno));
		exit(EXIT_FILEIO_FAIL);
	}

	// obviously taken from stack overflow
	char *buffer = 0;
	long buflen;

	fseek(tmp, 0, SEEK_END);
	buflen = ftell(tmp);
	fseek(tmp, 0, SEEK_SET);

	buffer = malloc(buflen);
	assert(buffer != NULL);

	fread(buffer, 1, buflen, tmp);
	fclose(tmp);

	return buffer;
}

// --! WARNING! Vibe Coded!!! (using duck.ai) !--
static char *get_csv_topmost_row(const char *csvData) {
    size_t len = strcspn(csvData, "\n");
    char *retval = (char *)malloc((len + 1) * sizeof(char));
    assert(retval != NULL);

    strncpy(retval, csvData, len);
    retval[len] = '\0'; // Ensure null termination

    return retval;
}

static char *get_csv_values(const char *csvData) {
    const char *newline_pos = strchr(csvData, '\n');

    if (newline_pos == NULL) {
        char *empty_string = strdup("");
        assert(empty_string != NULL);
        return empty_string;
    }

    char *retval = strdup(newline_pos + 1);
    assert(retval != NULL);

    return retval;
}

// --! End of Vibe Coding !--

static int count_char_in_str(char ch, const char *str) {
	int len = strlen(str);
	int count = 0;

	for (int i = 0; i < len; ++i) {
		if (str[i] == ch) count++;
	}

	return count;
}

static Csv *make_csv(const char *csvData) {
	Csv *csv = malloc((sizeof(Csv*)) + ((sizeof(char*)) * 2));
	assert(csv != NULL);

	// topmost row
	char *key = get_csv_topmost_row(csvData);
	char *keybuf = malloc(sizeof(char*) * count_char_in_str(',', key));
	assert(keybuf != NULL);

	char *keys = strtok(key, ",");
	while (keys != NULL) {
		sprintf(keybuf, "%s\n", keys);
		keys = strtok(NULL, ",");
	}

	// this one isn't really a malloc check but still
	assert(keybuf != NULL);

	char *value = get_csv_values(csvData);
	char *valuebuf = malloc(sizeof(char*) * count_char_in_str(',', key));
	assert(valuebuf != NULL);

	char *values = strtok(value, ",");
	while (values != NULL) {
		sprintf(valuebuf, "%s\n", value);
		values = strtok(NULL, ",");
	}

	assert(valuebuf != NULL);

	csv->row = strdup(keybuf);
	csv->column = strdup(valuebuf);

	free(keybuf);
	free(valuebuf);

	return csv;
}

// ---- End of static functions ----


// possible return values:
// 	- '1'	: 	user has invalid csv data
// 	- '0':	:	success	
// 	- '-1'	:	system has failed the program
int csv_init(Args *args) {
	char *csv = return_csv_contents(args->input);
	
	Csv *fmtdCsv = make_csv(csv);

	printf("Keys:		%s\n", fmtdCsv->row);
	printf("Values:		%s\n", fmtdCsv->column);

	free(csv);
	free(fmtdCsv);

	return 0;
}

#ifdef __APPLE__
	#pragma clang diagnostic pop
#endif