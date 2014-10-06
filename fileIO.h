/*
  returns next line of input in file similar to Java's nextLine() method on Scanner
  returns NULL if there is no more input
  caller of function is responsible for freeing memory allocated to the char * that is returned
*/

char *next_line(FILE *file);
