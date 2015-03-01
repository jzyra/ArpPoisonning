/*!
  * \file Arp.cpp
  * \brief Class for build ARP packet.
  * \author Jeremy ZYRA
  * \version 1.0
*/
#include "Arp.hpp"

Arp::Arp(pcap_t *device) : Ethernet(device) {
	_arp = new ether_arp;
	//Init destination/source MAC adress at 0.
	for (int i = 0; i<6; ++i) {
		_arp->arp_sha[i] = _arp->arp_tha[i] = 0x00;
	}
	//Init destination/source IP adress at 0.
	for (int i = 0; i<4; ++i) {
		_arp->arp_spa[i] = _arp->arp_tpa[i] = 0x00;
	}
	_arp->ea_hdr.ar_hrd = 0x0100;
	_arp->ea_hdr.ar_pro = 0x8;
	_arp->ea_hdr.ar_hln = 0x06;
	_arp->ea_hdr.ar_pln = 0x04;
	_arp->ea_hdr.ar_op = 0x01;
	//Init ethernet at ARP flag.
	_ethernet->ether_type = 0x608;
}

ucharMac Arp::getSrcArpMac() {
	ucharMac mac;	
	for (int i = 0; i<6; ++i) {
		mac.datas[i] = _arp->arp_sha[i];
	}
	return mac;
}

ucharMac Arp::getDstArpMac() {
	ucharMac mac;	
	for (int i = 0; i<6; ++i) {
		mac.datas[i] = _arp->arp_tha[i];
	}
	return mac;
}

uint16_t Arp::getOp() {
	return _arp->ea_hdr.ar_op;
}

void Arp::setSrcArpMac(const ucharMac &srcMac) {
	for(int i = 0; i<6; ++i){
		_arp->arp_sha[i] = srcMac.datas[i];
	}
}

void Arp::setDstArpMac(const ucharMac &dstMac) {
	for(int i = 0; i<6; ++i){
		_arp->arp_tha[i] = dstMac.datas[i];
	}
}

void Arp::setOp(uint16_t op) {
	_arp->ea_hdr.ar_op = op;	
}

void Arp::setDstIp(const uint8Ip &dstIp) {
	for(int i = 0; i<4; ++i){
		_arp->arp_tpa[i] = dstIp.datas[i];
	}
}

void Arp::setSrcIp(const uint8Ip &srcIp) {
	for(int i = 0; i<4; ++i){
		_arp->arp_spa[i] = srcIp.datas[i];
	}
}

int Arp::send() {
	u_char trame[sizeof(ether_header) + sizeof(ether_arp)];
	//Copy ethernet and ARP header in trame to send.
	memcpy(trame, _ethernet, sizeof(ether_header));
	memcpy(trame + sizeof(ether_header), _arp, sizeof(ether_arp));
	//Send packet.
	return pcap_sendpacket(_device, (u_char *)trame, sizeof(ether_header) + sizeof(ether_arp));
}
