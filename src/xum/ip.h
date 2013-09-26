#ifndef _IP_H_
#define _IP_H_

#include <stdint.h>


typedef struct ip_address {
	uint8_t byte_1;
	uint8_t byte_2;
	uint8_t byte_3;
	uint8_t byte_4;
} IP_ADDR;

typedef struct ip_header {
	uint8_t	ip_vhl;		/* header length, version */
	uint8_t	ip_tos;		/* type of service */
	uint16_t ip_len;	/* Total Length is the length of the datagram, measured in octets, including internet header and data.  
						    This field allows the length of a datagram to be up to 65,535 octets.*/
	uint16_t ip_id;		/* Identification:  16 bits :  An identifying value assigned by the sender to aid in assembling the	
							fragments of a datagram. */
	uint16_t ip_off;		/* fragment offset field */
	uint8_t	ip_ttl;		 /* time to live */
	uint8_t	ip_p;		  /* protocol */
	uint16_t	ip_sum;		/* checksum*/
	IP_ADDR ip_src;		   /* source address */
	IP_ADDR ip_dst;	       /* destination address */
} IP_HEADER;

#define	IPVERSION	4
#define V_IP(ip)    (((ip)->ip_vhl & 0xf0) >> 4)
#define HL_IP(ip)	((ip)->ip_vhl & 0x0f)
#define TOS_IP(ip)     ((ip)->ip_tos)
#define LEN_IP(ip)  ((ip)->ip_len)
#define ID_IP(ip)	((ip)->ip_id)
#define OFF_IP(ip)  ((ip)->ip_off)
#define TTL_IP(ip)  ((ip)->ip_ttl)
#define POROTO_IP(ip) ((ip)->ip_p)
#define CHKSUM_IP(ip) ((ip)->ip_sum)

	   
void print_ip_header(const IP_HEADER *ip_hdr)
{

fprintf(stdout,"\n\tIP Packet Starts .....\n"
		       "\tVer: %u  Hdr Len: %u TOS: %u  Total Len: %u ID: %u TTL: %u Protocol: %u\n"
			   "\tSrc IP : %d.%d.%d.%d Dst IP : %d.%d.%d.%d\n\tIP Packet Ends.......\n\n",
			   V_IP(ip_hdr), HL_IP(ip_hdr),	TOS_IP(ip_hdr), LEN_IP(ip_hdr), ID_IP(ip_hdr),	TTL_IP(ip_hdr), POROTO_IP(ip_hdr), 
			   ip_hdr->ip_src.byte_1,ip_hdr->ip_src.byte_2,ip_hdr->ip_src.byte_3,ip_hdr->ip_src.byte_4,
			   ip_hdr->ip_dst.byte_1,ip_hdr->ip_dst.byte_2,ip_hdr->ip_dst.byte_3,ip_hdr->ip_dst.byte_4);
										
}

#endif