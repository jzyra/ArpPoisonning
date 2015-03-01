/*!
  * \file main.cpp
  * \brief Program's entry point.
  * \author Jeremy ZYRA
*/
#include <iostream>
#include <pcap.h>
#include <unistd.h>
#include "ArpSpoofing.hpp"
using namespace std;

/*!
	* \brief Function for print usage.
*/
void printUsage(char *name) {
	cout << "NAME" << endl;	
	cout << "\tArpPoisonning" << endl << endl;	
	cout << "SYNOPSIS" << endl;	
	cout << "\t" << name << " [-h] -i INTERFACE -t TARGET -d HOST" << endl << endl;	
	cout << "DESCRIPTION" << endl;	
	cout << "\tLaunch MITM attack with ARP cache poisonning method." << endl << endl;	
	cout << "OPTIONS" << endl;	
	cout << "\t-h" << endl;	
	cout << "\t\tPrint command's usage." << endl << endl;	
	cout << "\t-i INTERFACE" << endl;	
	cout << "\t\tSpecifie network interface." << endl << endl;	
	cout << "\t-t TARGET" << endl;	
	cout << "\t\tSpecifie IP to target." << endl << endl;	
	cout << "\t-d HOST" << endl;	
	cout << "\t\tSpecifie IP host who is hijacked in target's ARP cache." << endl << endl;	
	cout << "AUTHOR" << endl;	
	cout << "\tJeremy ZYRA" << endl;	
}

/*!
	* \brief Program's entry point.
*/
int main(int argc, char *argv[]) {
	int opt = 0;
	char *iface, *target, *destination;
	bool help = false;
	iface = target = destination = NULL;
	//Get parameters
	while ((opt = getopt(argc, argv,"i:t:d:h?")) != -1) {
		switch(opt) {
			//Network interface
			case 'i':
				iface = optarg;
				break;
			//Target IP
			case 't':
				target = optarg;;
				break;
			//IP hijacked
			case 'd':
				destination = optarg;
				break;
			//Flag for display usage.
			case 'h':
				help = true;
				break;
			case '?':
				help = true;
				break;
		}
	}
	if(help) printUsage(argv[0]);
	else {
		//Check mandatory parameters
		if (iface != NULL && target != NULL && destination != NULL) {
			ArpSpoofing *launch = new ArpSpoofing(iface, target, destination);
			//Run MITM attack
			launch->run();
		} else {
			printUsage(argv[0]);
		}
	}
	return 0;
}
