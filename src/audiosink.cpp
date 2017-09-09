#include "audiosink.hpp"
#include "musical_utils.h"

audio_sink::audio_sink(streaming_interface in) {
	input = in;
}

audio_sink::~audio_sink() {

}

void audio_sink::next_sample() {
	if (bufferFillLevel == 0) {
		refillCache();
	}
	write(outputBuffer.samples[WORKUNIT-bufferFillLevel]);
	bufferFillLevel--;
	sample_t++;
}

void audio_sink::refillCache(){
	outputBuffer = input.getWorkUnit(cache_t);
	cache_t += WORKUNIT;
	bufferFillLevel = WORKUNIT;
}

void audio_sink::write(sample s) {
	write32(s);
}