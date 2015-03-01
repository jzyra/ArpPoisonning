/*!
  * \file Packet.hpp
  * \brief Class header for build network packet.
  * \author Jeremy ZYRA
  * \version 1.0
*/
#ifndef PACKET_H
#define PACKET_H

#include <pcap.h>
#include "Types.hpp"

/*!
  * \class Packet
  * \brief Class header for build network packet.
*/
class Packet {
	public:
	/*!
		* \brief Packet Constructor.
		Packet class's constructor.
		* \param Pointer to network interface.
	*/
	Packet(pcap_t *device);
	/*!
		* \brief Function for send packet.
		* \return Status (if trame is sended or not).
	*/
	virtual int send();

	protected:
	pcap_t *_device;
};

#endif
