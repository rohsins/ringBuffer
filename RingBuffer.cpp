#include "RingBuffer.h"

uint32_t RingBuffer::write(char in) {
		if (head == ((tail - 1 + RINGBUFFLENGTH) % RINGBUFFLENGTH)) {
			return 1;
		}
		ringVariable[head] = in;
		head = (head + 1) % RINGBUFFLENGTH;
		return 0;
}

uint32_t RingBuffer::writeBytes(char in[], int length) {
	for (int i = 0; i < length; i++) {
		if (head == ((tail - 1 + RINGBUFFLENGTH) % RINGBUFFLENGTH)) {
			return 1;
		}
		ringVariable[head] = in[i];
		head = (head + 1) % RINGBUFFLENGTH;
	}
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

uint32_t RingBuffer::readBytes(char *out, int length) {
	if (head == tail) {
		return 1;
	}
	for (int i = 0; i < length; i++) {
		out[i]=ringVariable[tail];
		ringVariable[tail] = 0;
		tail = ((tail + 1) % RINGBUFFLENGTH);
	}
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
