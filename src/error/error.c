#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"

/* message    69: Strerror (file.c: function: line 42)*/
#define ERROR_FORMAT "Error: %s\t%d: %s (%s: %s: %d)\n" 

void
_ef_error (const char *msg, const char *file, const char *func,
	   int line)
{
  fprintf (stderr, ERROR_FORMAT,
	   msg, errno, strerror(errno),
	   file, func, line);
  exit (EXIT_FAILURE);
}
