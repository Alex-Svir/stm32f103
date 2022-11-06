/*
 * Buffers.cpp
 *
 *  Created on: 18 окт. 2022 г.
 *      Author: shurik
 */
#include "Buffers.h"
/*
template <unsigned int SZ, char DC>
void AsyncTextOutBuffer<SZ,DC>::init() {
	wptr = rptr = sptr = 0;
	sz = SZ & ~3;
}

template <unsigned int SZ, char DC>
void AsyncTextOutBuffer<SZ,DC>::push(char c) {
	switch (wptr & 3) {
	case 3:
		overflow(++wptr);
	case 0:
		buf[wptr + 1] = 0xFF;
		buf[wptr + 2] = 0xFF;
		buf[wptr + 3] = 0xFF;
	default:
		buf[wptr++] = c;
	}
}

template <unsigned int SZ, char DC>
void AsyncTextOutBuffer<SZ,DC>::push(char* s) {
	if (!aligned(wptr)) {
		overflow(wptr = (wptr + 4) & ~3);
	}
	*(uint32_t*)(buf + wptr) = uint32_t(s);
	overflow(wptr += 4);
}

template <unsigned int SZ, char DC>
char AsyncTextOutBuffer<SZ,DC>::pop() {
	if (sptr) {
		char c = string();
		if (c != '\0') return c;
	}
	while (wptr != rptr) {
		if (aligned(rptr) && buf[rptr + 3] != 0xFF) {
			sptr = *(uint32_t*)(buf + rptr);
			overflow(rptr += 4);
			if (!sptr) continue;
			char c = string();
			if (c != '\0') return c;
		} else {
			if (buf[rptr] == 0xFF)
				overflow(rptr = ((rptr + 4) & ~3));
			else {
				//tdr(rptr, buf[rptr]);
				return buf[rptr++];
			}
		}
	}
	return DC;
}

template <unsigned int SZ, char DC>
char AsyncTextOutBuffer<SZ,DC>::string() {
	char c = ((char*)(sptr))[0];
	if (c) sptr++;
	else sptr = 0;
	return c;
}
*/
