#include "xuSniffer.h"


xuSniffer * instanceThis;
char filter_exp[] = "";

xuSniffer::xuSniffer(void)
{
	transito = NULL;
}


xuSniffer::~xuSniffer(void)
{
}



/*
 * dissect/print packet
 */
void xuSniffer::got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{
    
        static int count = 1;                   /* packet counter */
        
        /* declare pointers to packet headers */
        const struct sniff_ethernet *ethernet;  /* The ethernet header [1] */
        const struct sniff_ip *ip;              /* The IP header */
        const struct sniff_tcp *tcp;            /* The TCP header */
        const char *payload;                    /* Packet payload */
    
        int size_ip;
        int size_tcp;
        int size_payload;
        
        printf("\nPacket number %d:\n", count);
        count++;
        
        /* define ethernet header */
        ethernet = (struct sniff_ethernet*)(packet);
        
        /* define/compute ip header offset */
        ip = (struct sniff_ip*)(packet + SIZE_ETHERNET);
        size_ip = IP_HL(ip)*4;
        if (size_ip < 20) {
                printf("   * Invalid IP header length: %u bytes\n", size_ip);
               // return;
        }
    
        /* print source and destination IP addresses */
        printf("       From: %s\n", inet_ntoa(ip->ip_src));
        printf("         To: %s\n", inet_ntoa(ip->ip_dst));
        
    int tipo = 0;
        //printf("         tTIPO: %s\n", inet_ntoa(ip->ip_p));
        cout<<"       ::TIPO::: "<<ip->ip_p<<endl;
		/* determine protocol */
        switch(ip->ip_p) {
                case IPPROTO_TCP:
                        printf("   Protocol: TCP\n");
            tipo = 1;
                        break;
                case IPPROTO_UDP:
            tipo = 2;
                        printf("   Protocol: UDP\n");
                        break;
                case IPPROTO_ICMP:
            tipo = 3; 
                        printf("   Protocol: ICMP\n");
                        break;
                case IPPROTO_IP:
            tipo = 4;
                        printf("   Protocol: IP\n");
                        break;
                default:
            tipo = 5;
                        printf("   Protocol: unknown\n");
                        break;
        }
        
        /*
         *  OK, this packet is TCP.
         */
        
        /* define/compute tcp header offset */
        tcp = (struct sniff_tcp*)(packet + SIZE_ETHERNET + size_ip);
        size_tcp = TH_OFF(tcp)*4;
        if (size_tcp < 20) {
                printf("   * Invalid TCP header length: %u bytes\n", size_tcp);
                return;
        }
        
       
        
        /* compute tcp payload (segment) size */
        size_payload = ntohs(ip->ip_len) - (size_ip + size_tcp);
        
        /*
         * Print payload data; it might be binary, so don't just
         * treat it as a string.
         */
        if (size_payload > 0) {
                printf("   Payload (%d bytes):\n", size_payload);
                //print_payload(payload, size_payload);
        }
    
    
    if(transito!=NULL)
    {
        
		//cout<<"IP HOST"<<dir_ip<<endl;
		//cout<<"IP SRC"<<inet_ntoa(ip->ip_src)<<endl;
        if(strncmp(inet_ntoa(ip->ip_src),dir_ip,13)!=0)
        {
			//El paquete viende otra IP, baja
			transito->addNodo(tipo, size_payload, true);
        }else{
            //Viene de la misma IP, sube
			transito->addNodo(tipo, size_payload, false);
        }
        
    }
    
    return;
}


void xuSniffer::wrap_got_packet( u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{
    //printf("Wrapping got message");
    instanceThis->got_packet(args, header, packet);
}


void  xuSniffer::startSniffThread()
{
    //ci::ThreadSetup threadSetup;
    
    pcap_loop(handle, 0, wrap_got_packet, NULL);
    
    pcap_freecode(&fp);
    pcap_close(handle);
};


void xuSniffer::close()
{
    
    //delete mThread;
    pcap_breakloop(handle);
        stopThread();
    
   // mThread->join();
}

void xuSniffer::init()
{
        //test();
    ::instanceThis = this;
    
    char *dev = NULL;                                           /* capture device name */
        char errbuf[PCAP_ERRBUF_SIZE];          /* error buffer */
        //pcap_t *handle;                                               /* packet capture handle */
    
        /* filter expression [3] */
        
        bpf_u_int32 mask;                   /* subnet mask */
                          /* ip */
        num_packets = 10;
    
        pcap_if_t *alldevs;
        pcap_if_t *d;

        pcap_if_t *pcap_ifs = NULL;
    char pcap_error_buf[PCAP_ERRBUF_SIZE];
        //cout<<pcap_findalldevs(&pcap_ifs, pcap_error_buf)<<endl;
    if(pcap_findalldevs(&alldevs, errbuf)<0)
          fprintf(stderr,"Error:pcap_findalldevs failed.\n");
    else if (!pcap_ifs)
          fprintf(stderr,"Error:failed to fetch network interfaces list.\n");
        
        int  i = 0;

        for(d=alldevs; d; d=d->next)
        {
                printf("%d. %s", ++i, d->name);
                if (d->description)
                        printf(" (%s)\n", d->description);
                else
                        printf(" (No description available)\n");
        }
        
        if(i==0)
        {
                printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
                return ;
        }

        int inum = 1;

        for(d=alldevs, i=0; i< inum-1 ;d=d->next, i++);
        //return;
		//dev = pcap_lookupdev(errbuf);
		 dev = d->name;
        if (dev == NULL) 
        {
        fprintf(stderr, "Couldn't find default device: %s\n",
                            errbuf);
        return;
    }
		pcap_addr_t *a;
  char ip6str[128];
		for(a=d->addresses;a;a=a->next)
		{
			printf("\tAddress Family: #%d\n",a->addr->sa_family);
  
			switch(a->addr->sa_family)
			{
			  case AF_INET:
				printf("\tAddress Family Name: AF_INET\n");
				if (a->addr)
				{
					dir_ip = iptos(((struct sockaddr_in *)a->addr)->sin_addr.s_addr);
					printf("\tAddress: %s\n",iptos(((struct sockaddr_in *)a->addr)->sin_addr.s_addr));
				}
				if (a->netmask)
				  printf("\tNetmask: %s\n",iptos(((struct sockaddr_in *)a->netmask)->sin_addr.s_addr));
				if (a->broadaddr)
				  printf("\tBroadcast Address: %s\n",iptos(((struct sockaddr_in *)a->broadaddr)->sin_addr.s_addr));
				if (a->dstaddr)
				  printf("\tDestination Address: %s\n",iptos(((struct sockaddr_in *)a->dstaddr)->sin_addr.s_addr));
				break;

			  case AF_INET6:
				printf("\tAddress Family Name: AF_INET6\n");
				if (a->addr)
				  printf("\tAddress: %s\n", ip6tos(a->addr, ip6str, sizeof(ip6str)));
			   break;

			  default:
				printf("\tAddress Family Name: Unknown\n");
				break;
			}
		}
    /* get network number and mask associated with capture device */
        if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1) 
        {
                fprintf(stderr, "Couldn't get netmask for device %s: %s\n",
                dev, errbuf);
                net = 0;
                mask = 0;
        }
    
        /* print capture info */ 
        printf("Device: %s\n", dev);
        printf("Number of packets: %d\n", num_packets);
        printf("Filter expression: %s\n", filter_exp);
		cout<<"IP HOST: "<< &net<<" :::"<<endl;
  
        /* open capture device */

        handle = pcap_open_live(dev, SNAP_LEN, 1, 1000, errbuf);
        if (handle == NULL) 
        {
                fprintf(stderr, "Couldn't open device %s: %s\n", dev, errbuf);
        return;
                //exit(EXIT_FAILURE);
        }
    
       
    
        /* compile the filter expression */
        if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1) 
        {
                fprintf(stderr, "Couldn't parse filter %s: %s\n",
                filter_exp, pcap_geterr(handle));
                return;
        }
    
        /* apply the compiled filter */
        if (pcap_setfilter(handle, &fp) == -1) 
        {
                fprintf(stderr, "Couldn't install filter %s: %s\n",
                filter_exp, pcap_geterr(handle));
                return;
        }
    startThread(true, false);
    //mThread = shared_ptr<thread>( new thread( bind( &Sniffer::startSniffThread, this ) ) );   
}



void xuSniffer::threadedFunction()
{
        //startSniffThread();
        std::cout<<" Empezando función hilo"<<std::endl;
        pcap_loop(handle, 0, wrap_got_packet, NULL);
    
    pcap_freecode(&fp);
    pcap_close(handle);
        while( isThreadRunning() != 0 )
        {
                                if( lock() ){
                                        printf( "en loop");
                                        unlock();
                                        ofSleepMillis(1 * 1000);
                                }
        }
}

#define IPTOSBUFFERS    12
char *xuSniffer::iptos(u_long in)
{
    static char output[IPTOSBUFFERS][3*4+3+1];
    static short which;
    u_char *p;

    p = (u_char *)&in;
    which = (which + 1 == IPTOSBUFFERS ? 0 : which + 1);
    _snprintf_s(output[which], sizeof(output[which]), sizeof(output[which]),"%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
    return output[which];
}

char* xuSniffer::ip6tos(struct sockaddr *sockaddr, char *address, int addrlen)
{
    socklen_t sockaddrlen;

    #ifdef WIN32
    sockaddrlen = sizeof(struct sockaddr_in6);
    #else
    sockaddrlen = sizeof(struct sockaddr_storage);
    #endif


    if(getnameinfo(sockaddr, 
        sockaddrlen, 
        address, 
        addrlen, 
        NULL, 
        0, 
        NI_NUMERICHOST) != 0) address = NULL;

    return address;
}