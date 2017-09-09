#include "blocks.hpp"
#include "../musical_utils.h"
#include <cstdio>

ossilator::ossilator(frequency f) {
	freq = f;
}

workUnit ossilator::compute_workunit(timestamp start_time) {
	workUnit w;
	w.start_time = start_time;
	//fprintf(stderr, "\nossilator: computing workunit\n");
	for (int i = 0; i < WORKUNIT; i++) {
		w.samples[i] = playsin(start_time+i, freq);
		//fprintf(stderr, "%05lit %lf\n",start_time+i , w.samples[i]);
	}
	fprintf(stderr, "oss: %05li %01.03lf %01.03lf %01.03lf %01.03lf %01.03lf %01.03lf %01.03lf %01.03lf %01.03lf %01.03lf \n",
		w.start_time,
		w.samples[0], w.samples[1], w.samples[2], w.samples[3], w.samples[4], w.samples[5], w.samples[6], w.samples[7], w.samples[8], w.samples[9]);
	return w;
}