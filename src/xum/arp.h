#ifndef _ARP_H_
#define _ARP_H
#include <stdint.h>

typedef struct arp_header {

	uint16_t	arp_hrd;		/*  hardware address */
	uint16_t	arp_pro;		/* protocol address */
	uint8_t	    arp_hln;		/* length of hardware address */
	uint8_t  	arp_pln;		/* length of protocol address */
	uint16_t	arp_op;			/* request or reply */
	uint8_t     arp_sha[6];		/* sender hardware address */
	uint8_t     arp_spa[4];		/* sender protocol address */
	uint8_t     arp_tha[6];		/* target hardware address */
	uint8_t     arp_tpa[4];		/* target protocol address */


} ARP_HEADER;

#define ARP_HDRLEN	8
#define ARPHRD_ETHER 	1	/* ethernet hardware format */
#define	ARP_REQUEST	1	/* request to resolve address */
#define	ARP_REPLY	2	/* response to previous request */



void print_arp_header(const ARP_HEADER *arp_hdr)
{
	 fprintf(stdout,"\n\tARP Packet Starts....\n"
					"\tHardware Type: 0x%.4x Protocol Type: 0x%.4x\n"
					"\tHardware Length: 0x%.1x Protocol Length: 0x%.1x\n"
					"\tOperation (Request 1 or Reply 2 ) : %x\n"
					"\tSender Hardware Address: %2x:%2x:%2x:%2x:%2x:%2x Sender Protocol Address: %d.%d.%d.%d\n"
					"\tTarget Hardware Address: %2x:%2x:%2x:%2x:%2x:%2x Target Protocol Address: %d.%d.%d.%d\n"
					"\n\n",
					ntohs(arp_hdr->arp_hrd),ntohs(arp_hdr->arp_pro),
					ntohs(arp_hdr->arp_hln),ntohs(arp_hdr->arp_pln),
					ntohs(arp_hdr->arp_op),
					arp_hdr->arp_sha[0],arp_hdr->arp_sha[1],arp_hdr->arp_sha[2],arp_hdr->arp_sha[2],arp_hdr->arp_sha[4],arp_hdr->arp_sha[6],
					arp_hdr->arp_spa[0],arp_hdr->arp_spa[1],arp_hdr->arp_spa[2],arp_hdr->arp_spa[3],
					arp_hdr->arp_tha[0],arp_hdr->arp_tha[1],arp_hdr->arp_tha[2],arp_hdr->arp_tha[2],arp_hdr->arp_tha[4],arp_hdr->arp_tha[6],
					arp_hdr->arp_tpa[0],arp_hdr->arp_tpa[1],arp_hdr->arp_tpa[2],arp_hdr->arp_tpa[3]
					);


}
#endif