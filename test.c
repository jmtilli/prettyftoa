#include "prettyftoa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static inline double myintpow10(int exponent)
{
	double a = 1.0;
	double b = 10.0;
	if (exponent < 0)
	{
		//abort();
		return 1.0 / myintpow10(-exponent);
	}
	// invariant: a * b^exponent stays the same
	while (exponent > 0)
	{
		if ((exponent % 2) == 0)
		{
			exponent /= 2;
			b *= b;
		}
		else
		{
			exponent -= 1;
			a *= b;
		}
	}
	return a;
}

static inline void test_fix_exponent(const char *str, const char *tgt)
{
	char buf[128];
	if (snprintf(buf, sizeof(buf), "%s", str) >= (int)sizeof(buf))
	{
		abort();
	}
	pretty_ftoa_fix_exponent(buf);
	if (strcmp(buf, tgt) != 0)
	{
		printf("fix exponent fail: %s / %s\n", str, tgt);
		abort();
	}
}


static void test_number(double d)
{
	char buf[25];
	if (!isfinite(d))
	{
		return;
	}
	//printf("### testing number %.17g\n", d);
	pretty_ftoa(buf, sizeof(buf), d);
	if (strchr(buf, 'e') == NULL &&
	    strchr(buf, 'E') == NULL &&
	    strchr(buf, '.') == NULL)
	{
		printf("not a floating point: %.17g / %s\n", d, buf);
		abort();
	}
	if (atof(buf) != d)
	{
		printf("number %.17g did not convert: %s\n", d, buf);
		abort();
	}
}

int main(int argc, char **argv)
{
	double d;
	size_t iter;
	int exponent;

	test_fix_exponent("5e0", "5e0");
	test_fix_exponent("5e+0", "5e0");
	test_fix_exponent("5e+00", "5e0");
	test_fix_exponent("5e-0", "5e0");
	test_fix_exponent("5e-00", "5e0");
	test_fix_exponent("5e-1", "5e-1");
	test_fix_exponent("5e+1", "5e1");
	test_fix_exponent("5e+01", "5e1");
	test_fix_exponent("5e-01", "5e-1");
	test_fix_exponent("5e01", "5e1");

	for (iter = 0; iter < 100*1000*1000; iter++)
	{
		d = drand48();
		exponent = rand() % 661;
		exponent -= 330;
		d *= myintpow10(exponent);
		if (drand48() < 0.5)
		{
			d = -d;
		}
		if (iter % 100000 == 0)
		{
			printf("%zu\n", iter);
		}
		test_number(d);
	}
	return 0;
}
