#ifndef PORT_H_
#define PORT_H_
/*
 * header used for portability stuff
 * (right now just integer types)
 * 
 * needs to be extern since the extern headers need it
 */
#include <limits.h>
#ifndef  DJGPP
#	include <inttypes.h>
#else
	typedef unsigned char  uint8_t;
	typedef signed char    int8_t;
	typedef unsigned short uint16_t;
	typedef short          int16_t;

/* 32-bit */
	typedef unsigned       uint32_t;
	typedef int            int32_t;
#  endif


#endif /*PORT_H_*/
