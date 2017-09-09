#include "audiosink.hpp"
#include "blocks/blocks.hpp"

void main() {
	ossilator oss = ossilator(440);
	audio_sink snk = audio_sink((streaming_interface)oss);
	for(long t=0;;t++) {
       	snk.next_sample();
    }
    return 0;
}