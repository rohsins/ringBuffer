/*
	Author: Rohit Singh (rohsins@gmail.com)
*/

#ifndef _RingBuffer_H_
#define _RingBuffer_H_

#include <stdint.h>
#include <string.h>

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

		int read (T *out, T delimiter) {
			volatile int tempCounter = 0;
			const int tempTail = tail;
			
			while (ringVariable[tail] != delimiter) {
				if (head == tail) {
					tail = tempTail;
					return -1;
				}
				
				tempCounter++;
				tail = ((tail + 1) % RINGBUFFLENGTH);
			}
			
			{
				tempCounter++;
				tail = ((tail + 1) % RINGBUFFLENGTH);
				
				if ((tempTail + tempCounter) < RINGBUFFLENGTH) {
					memcpy((T *) (out), (T *) (ringVariable + tempTail), tempCounter);
					memset((T *) (ringVariable + tempTail), 0, tempCounter);
				} else {
					const int buffPosteriorEnd= RINGBUFFLENGTH - tempTail;
					const int buffAnteriorEnd = tempCounter - buffPosteriorEnd;
					
					memcpy((T *) (out), (T *) (ringVariable + tempTail), buffPosteriorEnd);
					memcpy((T *) (out + buffPosteriorEnd), (T *) (ringVariable), buffAnteriorEnd);
					
					memset((T *) (ringVariable + tempTail), 0, buffPosteriorEnd);
					memset((T *) (ringVariable), 0, buffAnteriorEnd);
				}
			}
			return tempCounter;
		}
		
		uint8_t drop (int length) {
			if (head == tail) {
				return 1;
			}
			for (int i = 0; i < length; i++) {
				ringVariable[tail] = 0;
				tail = ((tail + 1) % RINGBUFFLENGTH);
			}
			return 0;
		}
};

#endif
