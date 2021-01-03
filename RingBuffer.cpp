#include "RingBuffer.h"

uint32_t RingBuffer::write(char in) {
		if (head == ((tail - 1 + RINGBUFFLENGTH) % RINGBUFFLENGTH)) {
			return 1;
		}
		ringVariable[head] = in;
		head = (head + 1) % RINGBUFFLENGTH;
		return 0;
}

uint32_t RingBuffer::writeString(char in[]) {
	int charinc = 0;
	while (in[charinc])	{
		if (head == ((tail - 1 + RINGBUFFLENGTH) % RINGBUFFLENGTH)) {
			return 1;
		}
		ringVariable[head] = in[charinc++];
		head = (head + 1) % RINGBUFFLENGTH;
	}
	return 0;
}

uint32_t RingBuffer::read(char *out) {
		if (head == tail) {
			return 1;
		}
		*out = ringVariable[tail];
		ringVariable[tail] = 0;
		tail = ((tail + 1) % RINGBUFFLENGTH);
		return 0;
}

uint32_t RingBuffer::readString(char *out) {
	int tempCounter = 0;
	if (head == tail) {
		return 1;
	}
	while ( head != tail ) {
//		out[tempCounter]=ringVariable[tail];
		if ( ringVariable[tail] == '\n' ) {
			tempCounter--;
			out[tempCounter]='\0';
			tempCounter = 0;
//			tail = ((tail + 1) % RINGBUFFLENGTH);
		} else {
			out[tempCounter]=ringVariable[tail];
		}
		ringVariable[tail] = 0;
		tempCounter++;
		tail = ((tail + 1) % RINGBUFFLENGTH);
	}
	return 0;
}
