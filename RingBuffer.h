#ifndef _RingBuffer_H_
#define _RingBuffer_H_

#include <stdint.h>

#define RINGBUFFSIZE 128
#define RINGBUFFLENGTH (RINGBUFFSIZE + 1)

class RingBuffer {

	public:
		char ringVariable[RINGBUFFLENGTH];
		
		unsigned int head, tail;
		
		uint32_t write(char in);
		uint32_t writeBytes(char in[], int length);
		uint32_t writeString(char in[]);
		uint32_t read(char *out);
		uint32_t readBytes(char *out, int length);
		uint32_t readString(char *out);
};

#endif
