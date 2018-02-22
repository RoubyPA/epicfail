#ifndef ERROR_H
#define ERROR_H

#include <errno.h>

#define ef_error(msg) _ef_error((const char *)msg,	\
				       (const char *)__FILE__,	\
				       (const char *)__func__,	\
				       __LINE__)

#define MALLOC_TEST_ERROR(ptr) \
  if (ptr == NULL) \
    { \
      ef_error("malloc"); \
    }

void _ef_error(const char *msg, const char *file, const char *func,
	       int line);

#endif /*ERROR_H*/
