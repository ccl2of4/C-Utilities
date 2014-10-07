#include <stdlib.h>
#include <stdio.h>
#include "fileIO.h"

char *next_line(FILE *file) {
	int buffer_size = 2*sizeof(char);
	int str_index = 0;
	char *line = malloc(buffer_size);
	int c = 0;

	line[str_index] = 0;
	while( (c = getc(file)) != EOF ) {
		if(c == '\n') return line;
		if(str_index > buffer_size - 2) {
			buffer_size *= 2;
			line = realloc(line,buffer_size);
		}
		line[str_index++] = c;
		line[str_index] = 0;
	}
	free(line);
	return NULL;
}
