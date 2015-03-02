/*!
  * \file Ethernet.cpp
  * \brief Class for build Ethernet packet.
  * \author Jeremy ZYRA
  * \version 1.0
*/
#include "Ethernet.hpp"

Ethernet::Ethernet(pcap_t *device) : Packet(device) {
	_ethernet = new ether_header;
	//Init destination/source MAC adress at 0.
	for (int i = 0; i<6; ++i) {
		_ethernet->ether_shost[i] = _ethernet->ether_dhost[i] = 0x00;
	}
	_ethernet->ether_type = 0x00;
}

Ethernet::~Ethernet() {
	delete _ethernet;
}

ucharMac Ethernet::getSrcMac() {
	ucharMac mac;	
	for (int i = 0; i<6; ++i) {
		mac.datas[i] = _ethernet->ether_shost[i];
	}
	return mac;
}

ucharMac Ethernet::getDstMac() {
	ucharMac mac;	
	for (int i = 0; i<6; ++i) {
		mac.datas[i] = _ethernet->ether_dhost[i];
	}
	return mac;
}

void Ethernet::setSrcMac(ucharMac &srcMac) {
	for(int i = 0; i<6; ++i){
		_ethernet->ether_shost[i] = srcMac.datas[i];
	}
}

void Ethernet::setDstMac(ucharMac &dstMac) {
	for(int i = 0; i<6; ++i){
		_ethernet->ether_dhost[i] = dstMac.datas[i];
	}
}

void Ethernet::setEtherType(uint16_t type) {
	_ethernet->ether_type = type;
}

uint16_t Ethernet::getEtherType() {
	return _ethernet->ether_type;
}

int Ethernet::send() {
	return pcap_sendpacket(_device, (u_char *)_ethernet, sizeof(ether_header));
}
