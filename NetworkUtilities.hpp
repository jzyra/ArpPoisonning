/*!
  * \file NetworkUtilities.hpp
  * \brief Utilities class for implement network functions.
  * \author Jeremy ZYRA
  * \version 1.0
*/
#ifndef NETWORKUTILITIES_H
#define NETWORKUTILITIES_H

#include <iostream>
#include <iomanip>
#include <pcap.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <cstdlib>
#include "Types.hpp"
using namespace std;

/*!
  * \class NetworkUtilities
  * \brief Utilities class for implement network functions.
*/
class NetworkUtilities {
	private:
	/*!
		* \brief NetworkUtilities
		NetworkUtilities class's constructor.
		* \param This class can't be instancied.
	*/
	NetworkUtilities();

	public:
	/*!
		* \brief Function for get device's MAC address
		* \param Pointer to network interface.
		* \return Return MAC address.
	*/
	static ucharMac getMacAddr(char *device);
	/*!
		* \brief Function for get device's IP address
		* \param Pointer to network interface.
		* \return Return IP address.
	*/
	static uint8Ip getIpAddr(char *device);
	/*!
		* \brief Print MAC address.
		* \param Pointer to network interface.
	*/
	static void printUcharMac(const ucharMac &mac);
	/*!
		* \brief Print IP address.
		* \param Pointer to network interface.
	*/
	static void printUint8Ip(const uint8Ip &ip);
};

#endif
