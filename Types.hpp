/*!
  * \file Types.hpp
  * \brief Contains definitions of IP and MAC address.
  * \author Jeremy ZYRA
  * \version 1.0
*/
#ifndef TYPES_H
#define TYPES_H

#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include <arpa/inet.h>

typedef struct ucharMac { u_char datas[6]; } ucharMac;
typedef struct uint8Ip { uint8_t datas[4]; } uint8Ip;

#endif
