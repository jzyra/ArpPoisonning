/*!
  * \file NetworkUtilities.cpp
  * \brief Utilities class for implement network functions.
  * \author Jeremy ZYRA
  * \version 1.0
*/
#include "NetworkUtilities.hpp"

NetworkUtilities::NetworkUtilities() {
}

ucharMac NetworkUtilities::getMacAddr(char *device) {
	ucharMac mac;
	struct ifreq ifr;
	int fd;
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0) {
		cerr << "[-] Socket error " << endl;
		exit(1);
	}
	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, device, sizeof(ifr.ifr_name) - 1);
	ifr.ifr_name[sizeof(ifr.ifr_name) - 1] = '\0';
	if (ioctl(fd, SIOCGIFHWADDR, (int8_t *)&ifr) < 0) {
		close(fd);
		cerr << "[-] Socket error " << endl;
		exit(1);
	}
	close(fd);
	memcpy(mac.datas, &ifr.ifr_hwaddr.sa_data, 0x06);
	return mac;
}

uint8Ip NetworkUtilities::getIpAddr(char *device) {
	uint8Ip ip;
	struct ifreq ifr;
	register struct sockaddr_in *sin;
	int fd;
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0) {
		cerr << "[-] Socket error " << endl;
		exit(1);
	}
	sin = (struct sockaddr_in *)&ifr.ifr_addr;
	if (device == NULL) {
		cerr << "[-] Device error " << endl;
		exit(1);
	}
	strncpy(ifr.ifr_name, device, sizeof(ifr.ifr_name) -1);
	ifr.ifr_name[sizeof(ifr.ifr_name) - 1] = '\0';
	ifr.ifr_addr.sa_family = AF_INET;
	if (ioctl(fd, SIOCGIFADDR, (int8_t*) &ifr) < 0) {
		cerr << "[-] Socket error " << endl;
		exit(1);
	}
	close(fd);
	for (int i = 0; i<4; ++i) {
		ip.datas[i] = ((sin->sin_addr.s_addr >> (i*8)) & 0xFF);
	}
	return ip;
}

void NetworkUtilities::printUcharMac(const ucharMac &mac) {
	cout << setw(2) << setfill('0') << hex;
	for (int i = 0; i < 6; ++i) {
		cout << static_cast<int>(mac.datas[i]);
		if (i < 5) {
			cout << ":";
		}
	}
	cout << dec;
}

void NetworkUtilities::printUint8Ip(const uint8Ip &ip) {
	for (int i = 0; i < 4; ++i) {
		cout << static_cast<int>(ip.datas[i]);
		if (i < 3) {
			 cout << ".";
		}
	}
}
