/*	$NetBSD: print-ascii.c,v 1.1 1999/09/30 14:49:12 sjg Exp $ 	*/

/*-
 * Copyright (c) 1997, 1998 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Alan Barrett and Simon J. Gerraty.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *        This product includes software developed by the NetBSD
 *        Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _PRINT_ASCII_H
#define _PRINT_ASCII_H

#define HEXDUMP_BYTES_PER_LINE 16
#define HEXDUMP_SHORTS_PER_LINE (HEXDUMP_BYTES_PER_LINE / 2)
#define HEXDUMP_HEXSTUFF_PER_SHORT 5 /* 4 hex digits and a space */
#define HEXDUMP_HEXSTUFF_PER_LINE \
		(HEXDUMP_HEXSTUFF_PER_SHORT * HEXDUMP_SHORTS_PER_LINE)

void hex_and_ascii_print_with_offset(register const u_char *cp, register uint32_t length, register uint32_t oset)
{
	register uint16_t i;
	register int s1, s2;
	register int nshorts;
	char hexstuff[HEXDUMP_SHORTS_PER_LINE*HEXDUMP_HEXSTUFF_PER_SHORT+1], *hsp;
	char asciistuff[HEXDUMP_BYTES_PER_LINE+1], *asp;

	nshorts = length / sizeof(uint16_t);
	i = 0;
	hsp = hexstuff; asp = asciistuff;
	while (--nshorts >= 0) {
		s1 = *cp++;
		s2 = *cp++;
		(void)_snprintf(hsp, sizeof(hexstuff) - (hsp - hexstuff)," %02x%02x", s1, s2);
		hsp += HEXDUMP_HEXSTUFF_PER_SHORT;
		*(asp++) = (isgraph(s1) ? s1 : '.');
		*(asp++) = (isgraph(s2) ? s2 : '.');
		if (++i >= HEXDUMP_SHORTS_PER_LINE) {
		    *hsp = *asp = '\0';
		    (void)fprintf(stdout,"\n0x%04x\t%-*s\t%s", oset, HEXDUMP_HEXSTUFF_PER_LINE, hexstuff, asciistuff);
		    i = 0; hsp = hexstuff; asp = asciistuff;
		    oset += HEXDUMP_BYTES_PER_LINE;
		}
	}
	if (length & 1) {
		s1 = *cp++;
		(void)_snprintf(hsp, sizeof(hexstuff) - (hsp - hexstuff), " %02x", s1);
		hsp += 3;
		*(asp++) = (isgraph(s1) ? s1 : '.');
		++i;
	}
	if (i > 0) {
		*hsp = *asp = '\0';
		(void)fprintf(stdout,"\n0x%04x\t%-*s\t%s",oset, HEXDUMP_HEXSTUFF_PER_LINE,hexstuff, asciistuff);
	}
}

void ascii_print(register const u_char *cp, register uint32_t length)
{
	hex_and_ascii_print_with_offset(cp, length, 0);
}


#endif