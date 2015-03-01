/*!
  * \file Ethernet.hpp
  * \brief Class header for build Ethernet packet.
  * \author Jeremy ZYRA
  * \version 1.0
*/
#ifndef ETHERNET_H
#define ETHERNET_H

#include <iostream>
#include <stdint.h>
#include <pcap.h>
#include <netinet/if_ether.h>
#include "Packet.hpp"
using namespace std;

/*!
	* \class Ethernet
	* \brief Class header for build Ethernet packet.
*/
class Ethernet : public Packet {
	public:
	/*!
		* \brief Ethernet Constructor.
		Ethernet class's constructor.
		* \param Pointer to network interface.
	*/
	Ethernet(pcap_t *device);
	/*!
		* \brief Accessor on source mac.
		* \return Return MAC address.
	*/
	ucharMac getSrcMac();
	/*!
		* \brief Accessor on destination mac.
		* \return Return MAC address.
	*/
	ucharMac getDstMac();
	/*!
		* \brief Accessor on type of Ethernet trame.
		* \return Return type value.
	*/
	uint16_t getEtherType();
	/*!
		* \brief Accessor for set source mac address.
		* \param MAC address.
	*/
	void setSrcMac(ucharMac &srcMac);
	/*!
		* \brief Accessor for set destination mac address.
		* \param MAC address.
	*/
	void setDstMac(ucharMac &dstMac);
	/*!
		* \brief Accessor for set Ethernet trame's type.
		* \param Ethernet trame's type value.
	*/
	void setEtherType(uint16_t type);
	/*!
		* \brief Function for send packet.
		* \return Status (if trame is sended or not).
	*/
	virtual int send();

	protected:
	struct ether_header *_ethernet;
};

#endif
