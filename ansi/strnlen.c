/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Header: /cvsup/minix/src/lib/ansi/strlen.c,v 1.1.1.1 2005/04/21 14:56:06 beng Exp $ */

#include	<string.h>

size_t
strnlen(const char *org, size_t maxlen)
{
	register const char *s = org;

        if (maxlen == 0)
          return 0;

	while (*s++ && maxlen--)
		/* EMPTY */ ;

	return --s - org;
}
