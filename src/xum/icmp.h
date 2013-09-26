#ifndef _ICMP_H_
#define _ICMP_H_

#include <stdint.h>

typedef struct icmp {

	uint8_t  type;		// ICMP type msg
	uint8_t  code;		// ICMP code msg
	uint16_t chksum;	// checksum

}ICMP_HEADER;

void print_icmp_header(const ICMP_HEADER *icmp_hdr)
{
	   fprintf(stdout,"\n\tICMP Packet Starts .......\n\tICMP type: %u ICMP code: %u\n\tICMP Packet Ends......\n\n",icmp_hdr->type, icmp_hdr->code);
}

#endif