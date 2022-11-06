/*
 * Buffers.h
 *
 *  Created on: 18 окт. 2022 г.
 *      Author: shurik
 */
#include <inttypes.h>

#ifndef __BUFFERS__H__
#define __BUFFERS__H__

template<unsigned int SZ>
class AsyncTextOutBuffer {
	uint8_t buf[SZ & ~3];
	unsigned wptr, rptr, sptr;
	const unsigned sz;
	const char defch;
	void overflow(unsigned& p) {if (p == sz) p = 0;}
	bool aligned(unsigned& p) {return !(p & 3);}
	inline char string();
public:
	AsyncTextOutBuffer(char dc)
				: wptr(0), rptr(0), sptr(0), sz(SZ & ~3), defch(dc) {}
	inline void push(char);
	inline void push(const char*);
	inline char pop();
	bool empty() {return wptr == rptr && !sptr;}
};

//-----------------------------------------------------------------------
template <unsigned int SZ>
void AsyncTextOutBuffer<SZ>::push(char c) {
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

template <unsigned int SZ>
void AsyncTextOutBuffer<SZ>::push(const char* s) {
	if (!aligned(wptr)) {
		overflow(wptr = (wptr + 4) & ~3);
	}
	*(uint32_t*)(buf + wptr) = uint32_t(s);
	overflow(wptr += 4);
}

template <unsigned int SZ>
char AsyncTextOutBuffer<SZ>::pop() {
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
				return buf[rptr++];
			}
		}
	}
	return defch;
}

template <unsigned int SZ>
char AsyncTextOutBuffer<SZ>::string() {
	char c = ((char*)(sptr))[0];
	if (c) sptr++;
	else sptr = 0;
	return c;
}

#endif
