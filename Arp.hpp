/*!
  * \file Arp.hpp
  * \brief Class header for build ARP packet.
  * \author Jeremy ZYRA
  * \version 1.0
*/
#ifndef ARP_H
#define ARP_H

#include <iostream>
#include <cstring>
#include <stdint.h>
#include <pcap.h>
#include <netinet/if_ether.h>
#include "Ethernet.hpp"
using namespace std;

/*!
  * \class Arp
  * \brief Class header for build ARP packet.
*/
class Arp : public Ethernet {
	public:
	/*!
		* \brief Arp Constructor.
		Arp class's constructor.
		* \param Pointer to network interface.
	*/
	Arp(pcap_t *device);
	/*!
		* \brief Accessor on source mac.
		* \return Return MAC address.
	*/
	ucharMac getSrcArpMac();
	/*!
		* \brief Accessor on destination mac.
		* \return Return MAC address.
	*/
	ucharMac getDstArpMac();
	/*!
		* \brief Accessor on Arp's operation type.
		* \return Return Operation type (answer or request).
	*/
	uint16_t getOp();
	/*!
		* \brief Accessor for set source mac.
		* \param Mac address.
	*/
	void setSrcArpMac(const ucharMac &srcMac);
	/*!
		* \brief Accessor for set destination mac.
		* \param Mac address.
	*/
	void setDstArpMac(const ucharMac &dstMac);
	/*!
		* \brief Accessor for set Arp's operation type.
		* \param Operation value.
	*/
	void setOp(uint16_t op);
	/*!
		* \brief Accessor for set IP destination.
		* \param IP address.
	*/
	void setDstIp(const uint8Ip &dstIp);
	/*!
		* \brief Accessor for set IP source.
		* \param IP address.
	*/
	void setSrcIp(const uint8Ip &srcIp);
	/*!
		* \brief Function for send packet.
		* \return Status (if trame is sended or not).
	*/
	virtual int send();

	protected:
	struct ether_arp *_arp;
};

#endif
