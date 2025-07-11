#pragma once

#include <args.h>

typedef struct Csv {
	char *row;
	char *column;
} Csv;

int csv_init(Args *args);