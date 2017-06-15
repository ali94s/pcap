#include<pcap.h>
#include<stdio.h>

int main()
{
	char errBuf[PCAP_ERRBUF_SIZE], * devStr;  
	
	devStr=pcap_lookupdev(errBuf);   //auto get network device name
	devStr="eth2";
	if(devStr) 
	{
		printf("%s\n",devStr);
		printf("success\n");
	}
	else
	{
		printf("faild\n");
		exit(1);
	}

	struct pcap_t* device;
	device=pcap_open_live(devStr,65535,1,0,errBuf);
	if(device)
	{
		printf("open success\n");
	}
	else
	{
		printf("open faild\n");
		exit(1);
	}

	struct pcap_pkthdr packet;

	while(1)
	{
		const u_char * pktStr=pcap_next(device,&packet);

		if(!pktStr)
		{
			printf("did not capture a packet!\n");  
			exit(1); 
		}
		printf("Packet length: %d\n", packet.len);  
		printf("Number of bytes: %d\n", packet.caplen);  
		printf("Recieved time: %s\n", ctime((const time_t *)&packet.ts.tv_sec));   
		int i=0;
		for(i=0;i<packet.len;++i)
		{
			printf("%02x ",pktStr[i]);
		}
		printf("\n");


	}
	pcap_close(device);  //close dev
		      


	return 0;
}
