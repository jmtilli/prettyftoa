#ifndef _PRETTY_FTOA_H_
#define _PRETTY_FTOA_H_

#include <stddef.h>

void pretty_ftoa_fix_exponent(char *buf);

void pretty_ftoa(char *buf, size_t bufsiz, double d);

#endif
