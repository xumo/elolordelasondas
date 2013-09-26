#ifndef _ETHERNET_H
#define _ETHERNET_H

#include<stdint.h>

#define	ETHERMTU			1500
#define ETHER_ADDR_LEN		6 
#define	ETHERMTU			1500
#define ETHER_HDRLEN		14


#define ETHERTYPE_ARP		0x0806	/* Addr. resolution protocol */
#define	ETHERTYPE_8021Q		0x8100
#define	ETHERTYPE_IP		0x0800	/* IP protocol */
#define ETHERTYPE_IPV6		0x86dd
#define	ETHERTYPE_LOOPBACK	0x9000


typedef struct	ether_header {
	uint8_t	ether_dhost[ETHER_ADDR_LEN];
	uint8_t	ether_shost[ETHER_ADDR_LEN];
	uint16_t	ether_type;
} ETHER_HEADER;

void print_ethernet_header(const ETHER_HEADER *ether_hdr)
{
		  fprintf(stdout,"\tEthernet Header Starts.......\n\tSrc MAC : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X Dst MAC : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n"
					   "\tProtocol : 0x%.4x\n\tEthernet Header Ends.......\n\n",
			ether_hdr->ether_dhost[0], ether_hdr->ether_dhost[1], ether_hdr->ether_dhost[2], ether_hdr->ether_dhost[3], ether_hdr->ether_dhost[4], ether_hdr->ether_dhost[5],
			ether_hdr->ether_shost[0], ether_hdr->ether_shost[1], ether_hdr->ether_shost[2], ether_hdr->ether_shost[3], ether_hdr->ether_shost[4], ether_hdr->ether_shost[5],
			ntohs(ether_hdr->ether_type));
}
#endif