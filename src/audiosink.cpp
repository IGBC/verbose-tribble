#include "audiosink.hpp"
#include "musical_utils.h"
#include <cstdio>

audio_sink::audio_sink(streaming_interface *in) {
	input = in;
}

audio_sink::~audio_sink() {

}

void audio_sink::next_sample() {
	if (bufferFillLevel == 0) {
		refillCache();
	}
	//fprintf(stderr,"%04lf", outputBuffer.samples[WORKUNIT-bufferFillLevel]);
	write(outputBuffer.samples[WORKUNIT-bufferFillLevel]);
	bufferFillLevel--;
	sample_t++;
}

void audio_sink::refillCache(){
	outputBuffer = input->getWorkUnit(cache_t);
	fprintf(stderr, "snk: %05li %01.03lf %01.03lf %01.03lf %01.03lf %01.03lf %01.03lf %01.03lf %01.03lf %01.03lf %01.03lf \n",
	outputBuffer.start_time,
	outputBuffer.samples[0], outputBuffer.samples[1], outputBuffer.samples[2], outputBuffer.samples[3], outputBuffer.samples[4], outputBuffer.samples[5], outputBuffer.samples[6], outputBuffer.samples[7], outputBuffer.samples[8], outputBuffer.samples[9]);
	cache_t += WORKUNIT;
	bufferFillLevel = WORKUNIT;
	//fprintf(stderr,"\naudiosink got new workunit for t=%li:\n", outputBuffer.start_time);

}

void audio_sink::write(sample s) {
	write32(s);
}