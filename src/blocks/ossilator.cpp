#include "blocks.hpp"
#include "../musical_utils.h"

ossilator::ossilator(frequency f) {
	freq = f;
}

workUnit ossilator::compute_workunit(timestamp start_time) {
	workUnit w;
	w.start_time = start_time;
	for (int i = 0; i < WORKUNIT; i++)
		w.samples[i] = playsin(start_time+i, freq);
	return w;
}