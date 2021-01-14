#ifndef _RingBuffer_H_
#define _RingBuffer_H_

#include <stdint.h>

template <typename T, int size>
class RingBuffer {
	private:
		static const int RINGBUFFLENGTH = size + 1; // to detect if the ring buffer is overwritten.
		T ringVariable[RINGBUFFLENGTH];
		volatile unsigned int head, tail;

	public:
		inline int dataLength (void) {
			if (head > tail) { return (head - tail); }
			else if (head < tail) { return ((RINGBUFFLENGTH - tail) + head); }
			else { return 0; }
		}

		uint8_t write (T in) {
				if (head == ((tail - 1 + RINGBUFFLENGTH) % RINGBUFFLENGTH)) {
					return 1;
				}
				ringVariable[head] = in;
				head = (head + 1) % RINGBUFFLENGTH;
				return 0;
		}

		uint8_t write (T in[], int length) {
			for (int i = 0; i < length; i++) {
				if (head == ((tail - 1 + RINGBUFFLENGTH) % RINGBUFFLENGTH)) {
					return 1;
				}
				ringVariable[head] = in[i];
				head = (head + 1) % RINGBUFFLENGTH;
			}
			return 0;
		}

		uint8_t write (T in[], T delimiter) {
			int charinc = 0;
			while (in[charinc] != delimiter) {
				if (head == ((tail - 1 + RINGBUFFLENGTH) % RINGBUFFLENGTH)) {
					return 1;
				}
				ringVariable[head] = in[charinc++];
				head = (head + 1) % RINGBUFFLENGTH;
			}
			return 0;
		}

		uint8_t read (T *out) {
				if (head == tail) {
					return 1;
				}
				*out = ringVariable[tail];
				ringVariable[tail] = 0;
				tail = ((tail + 1) % RINGBUFFLENGTH);
				return 0;
		}

		uint8_t read (T *out, int length) {
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

		uint8_t read (T *out, T delimiter) {
			int tempCounter = 0;
			while (ringVariable[tail] != delimiter) {
				if (head == tail) {
					return 1;
				}
				out[tempCounter]=ringVariable[tail];
				ringVariable[tail] = 0;
				tempCounter++;
				tail = ((tail + 1) % RINGBUFFLENGTH);
			}
			return 0;
		}
};

#endif
