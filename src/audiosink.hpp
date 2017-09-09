#ifndef AUDIOSINK_HPP
#define AUDIOSINK_HPP
#include "streaming_interface.hpp"

class audio_sink {
public:
	audio_sink(streaming_interface *in);
	~audio_sink();
	void next_sample();

private:
	workUnit outputBuffer;
	int bufferFillLevel = 0;
	
	timestamp cache_t = 0;
    timestamp sample_t = 0;

	void write(sample);
	void refillCache();
	streaming_interface *input;
};
#endif