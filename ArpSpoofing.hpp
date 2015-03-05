/*!
  * \file ArpSpoofing.hpp
  * \brief Class header for run MITM attack.
  * \author Jeremy ZYRA
  * \version 1.0
*/
#ifndef ARPSPOOFING_H
#define ARPSPOOFING_H

#include <iostream>
#include <cstdlib>
#include <pcap.h>
#include <stdint.h>
#include <arpa/inet.h>
#include "Arp.hpp"
#include "NetworkUtilities.hpp"

#define PACKET_SIZE 65536
#define TIMEOUT_MS 3000
#define PROMISC_MODE 0
#define TIME_SLEEP 2
using namespace std;

/*!
  * \class ArpSpoofing
  * \brief Class header for run MITM attack.
*/
class ArpSpoofing {
	public:
	/*!
		* \brief ArpSpoofing Constructor.
		ArpSpoofing class's constructor.
		* \param iface : Pointer to network interface.
		* \param target : Target's IP.
		* \param destination : IP who is hijacked in target's ARP cache.
	*/
	ArpSpoofing(char *iface, char *target, char *destination);
	/*!
		* \brief Run MITM attack.
	*/
	void run();

	private:
	ucharMac *getTargetMac();

	pcap_t *_iface;
	uint8Ip _targetIp;
	uint8Ip _destIp;
	uint8Ip _deviceIp;
	ucharMac _deviceMac;
};

#endif
