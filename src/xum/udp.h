#ifndef _UDP_H
#define _UDP_H

#include <stdint.h>
#include "print_ascii.h"

typedef struct udphdr {
	uint16_t	sport;		/* source port */
	uint16_t	dport;		/* destination port */
	uint16_t	len;		/* udp length */
	uint16_t	chksum;		/* udp checksum */
} UDP_HEADER;


#define UDP_HDRLEN 8
//#define UDP_PAYLOAD_SIZE(t)  (ntohs((t)->len) - UDP_HDRLEN)

void print_udp_header(const UDP_HEADER *udp_hdr, const u_char *udp_payload_offset, const uint32_t  udp_payload_size)
{
	fprintf(stdout,"\n\tUDP Packet Starts....\n"
					"\tSrc Port: %d  Dst Port: %d\n"
					"\tUDP Len: %d   Chk_sum: %d\n",
					ntohs(udp_hdr->sport),
					ntohs(udp_hdr->dport),
					ntohs(udp_hdr->len),
					ntohs(udp_hdr->chksum));
		
		ascii_print(udp_payload_offset, udp_payload_size); 
}

#endif