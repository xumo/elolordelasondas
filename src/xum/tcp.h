#ifndef _TCP_H
#define _TCP_H_

#include <stdint.h>
#include "print_ascii.h"

typedef struct tcphdr {
	uint16_t	sport;		/* source port */
	uint16_t	dport;		/* destination port */
	uint32_t	seq;			/* sequence number */
	uint32_t	ack;			/* acknowledgement number */
	uint8_t	    off_set;		/* data offset 4 bits*/
	uint8_t	    flags;			/* TCP Flags */
	u_int16_t	win;			/* window */
	u_int16_t	chksum;			/* checksum */
	u_int16_t	urp;			/* urgent pointer */
} TCP_HEADER;

#define TCP_OFF(t)	(((t)->off_set & 0xf0) >> 4)  

// flags
#define	TCP_FIN		0x01
#define	TCP_SYN		0x02
#define	TCP_RST		0x04
#define	TCP_PUSH	0x08
#define	TCP_ACK		0x10
#define	TCP_URG		0x20
#define TCP_ECNECHO	0x40	/* ECN Echo */
#define TCP_CWR		0x80	/* ECN Cwnd Reduced */
#define TCP_FLAGS (TCP_FIN|TCP_SYN|TCP_RST|TCP_PUSH|TCP_ACK|TCP_URG|TCP_ECNECHO|TCP_CWR)
					
void print_tcp_flags(uint16_t f)
{

	fprintf(stdout,"\tflags: 0x%x : ",f);
	if((f) & (TCP_FLAGS)) {			// If flag is present in TCP header
		 if(f & TCP_FIN) putchar('F');
		 if(f & TCP_SYN) putchar('S');
		 if(f & TCP_RST) putchar('R');
		 if(f & TCP_PUSH) putchar('P');
		 if(f & TCP_ACK) putchar('A');
		 if(f & TCP_URG) putchar('U');
		 if(f & TCP_ECNECHO) putchar('E');
		 if(f & TCP_CWR) putchar('C');
	}
	else fprintf(stdout,"\tno flags");
    fprintf(stdout,"\n");
}

void print_tcp_header(const TCP_HEADER *tcp_hdr, const u_char *tcp_payload_offset, const uint32_t  tcp_payload_size)
{
		
	
	fprintf(stdout,"\n\tTCP Packet Starts....\n"
					 "\tSrc Port: %5u Dst Port: %5u\n"
					 "\tSeq No: %10lu    Ack No: %10lu\n"
					 "\tWindow: %5u    Chk_sum: %5u\n",
					ntohs(tcp_hdr->sport),ntohs(tcp_hdr->dport),
					ntohl(tcp_hdr->seq),ntohl(tcp_hdr->ack),
					ntohs(tcp_hdr->win),ntohs(tcp_hdr->chksum));
	print_tcp_flags(tcp_hdr->flags);	
	ascii_print(tcp_payload_offset, tcp_payload_size);
		
}

#endif