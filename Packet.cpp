/*!
  * \file Packet.cpp
  * \brief Class for build network packet.
  * \author Jeremy ZYRA
  * \version 1.0
*/
#include "Packet.hpp"

Packet::Packet(pcap_t *device) {
	_device = device;
}

int Packet::send() {
	return 0;
}
