#ifndef _RingBuffer_H_
#define _RingBuffer_H_

#include <stdint.h>

#define RINGBUFFSIZE 128
#define RINGBUFFLENGTH (RINGBUFFSIZE + 1)

class RingBuffer {

	public:
		char ringVariable[RINGBUFFLENGTH];
		char temporaryVariable[RINGBUFFSIZE];
		char *readout;
		
		volatile unsigned int head, tail;
		
		RingBuffer(void) {
			readout = temporaryVariable;
			head = tail = 0;
		}
		
		uint32_t write(char in);
		uint32_t writeString(char in[]);
		uint32_t read(char *out);
		uint32_t readString(char *out);
};

#endif
