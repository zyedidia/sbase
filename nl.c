/* See LICENSE file for copyright and license details. */
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "text.h"
#include "util.h"

static void nl(FILE *);

static char mode = 't';
static const char *sep = "\t";
static long incr = 1;
static regex_t preg;

static void
usage(void)
{
	eprintf("usage: %s [-b style] [-i increment] [-s sep] [FILE...]\n",
			argv0);
}

int
main(int argc, char *argv[])
{
	FILE *fp;
	char *r;

	ARGBEGIN {
	case 'b':
		r = EARGF(usage());
		mode = r[0];
		if(r[0] == 'p') {
			regcomp(&preg, &r[1], REG_NOSUB);
		} else if(!strchr("ant", mode)) {
			usage();
		}
		break;
	case 'i':
		incr = estrtol(EARGF(usage()), 0);
		break;
	case 's':
		sep = EARGF(usage());
		break;
	default:
		usage();
	} ARGEND;

	if(argc == 0) {
		nl(stdin);
	} else for(; argc > 0; argc--, argv++) {
		if(!(fp = fopen(argv[0], "r")))
			eprintf("fopen %s:", argv[0]);
		nl(fp);
		fclose(fp);
	}

	return EXIT_SUCCESS;
}

void
nl(FILE *fp)
{
	char *buf = NULL;
	long n = 0;
	size_t size = 0;

	while(afgets(&buf, &size, fp)) {
		if((mode == 'a')
				|| (mode == 'p'
					&& !regexec(&preg, buf, 0, NULL, 0))
				|| (mode == 't' && buf[0] != '\n')) {
			printf("%6ld%s%s", n += incr, sep, buf);
		} else {
			printf("       %s", buf);
		}
	}
	free(buf);
}

