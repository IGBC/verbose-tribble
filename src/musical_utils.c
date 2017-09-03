#include "musical_utils.h"

#include <math.h>
#include <limits.h>
#include <stdio.h>

#define lenof(x) sizeof(x)/sizeof(((x)[0]))

double lerp(double t, double y0, double y1, double t0, double t1) {
    double u = t  - t0;
    double l = t1 - t0;
    return (y0 * (1-(u/l))) + (y1 * (u/l));
}

/* Generate frequencies of a musical scale.
 * scale is defined by nth root 2 constant where n = 12 in european music 
 * notes sit at integer powers of the constant, multiplied by a base freqency.
 */
double note(int base, int scale, int i) {
    double factor = pow(2.0,1.0/scale);
    return base * pow(factor, i);
}

// A chord is a combination of notes from the same scale

/* Timing functions */

/* converts timestep to seconds (flooring the fractional result) */
int seconds(int t) {
    return t/RATE;
}

/* cycles through the provided list of integer items at the rate of 
 * the given beat (bps) */ 
double sequencer(long t, double beat, double *item_array, int len) {
    int val =  (int)((t*beat) / RATE) % len;
    return item_array[val];
}

/* cycles through the provided list of integer items at the rate of 
 * the given beat (bps) */ 
double sequencer_b(long t, double beat, double *item_array, int *counts) {
    int val = (int)((t*beat) / RATE) % lenof(item_array);
    return item_array[val];
}

double ADSR(long t, long trig_t, double A, double D, double H, double S, double R) {
    if (t - trig_t < A*RATE)
        return lerp(t, 0, 1, trig_t, trig_t + (A*RATE));
    if (t - trig_t < (A+D)*RATE)
        return lerp(t, 1, S, trig_t + (A*RATE), trig_t + ((A+D)*RATE));
    if (t - trig_t < (A+D+H)*RATE)
        return S;
    if (t - trig_t < (A+D+H+R)*RATE)
        return lerp(t, S, 0, trig_t + ((A+D+H)*RATE), trig_t + ((A+D+H+R)*RATE));
    return 0;
}

/* Sample Writing (Output) functions */

/* Both of these write the output to std out in formats designed for alsa */

/* Output sample in unsigned 8 bit format (U8) */
void writeU8(double sample) {
    putchar((1+sample) * 127);
}

/* Output sample in S32LE format */
#define BUFSIZE 100000
void write32_(double val) {
    static int buf[BUFSIZE];
    static int pos = 0;
    int sample = val * INT_MAX;
    buf[pos++] = sample;
    if (pos>BUFSIZE-1) {
        fwrite(buf, sizeof(int), BUFSIZE, stdout);
        pos = 0;
    }
    //for (int i = 0; i < 4; i++, sample >>= 8)
        //putchar(sample & 0xff);
}

void write32( double val ) {
    /* Do a windowing mean (reduces popping)*/
    /*
    static double v0 = 0, v1 = 0;
    double mean = (v0+v1+val)/3.0;
    v0 = v1; v1 = val;
    */
    write32_( val );
}

/* Tone Generator Functions */

/* All of these do the same thing, 
 * They take the current timestep (in samples) and
 * the desired frequency in Hz. With these they produce
 * a sample as a float between -1 and 1.
 */

// Square Wave
double playsqr(long t, int freq) {
    int val = ((t*freq)/RATE) % 2;
    return (val ? 1.0 : -1.0);
}

// Sawtooth Wave
double playsaw(long t, int freq) { // modding by sample counts requires integer math here
    long T = (1.0/(double)freq)*RATE; // period in samples
    return (double)(2*((t % T) - T/2))/(double)T; //y = 2t/T { -1 < t < 1 }
}

// Sine Wave
double playsin(long t, int freq) {
    return sin(t*TAU/RATE*freq);
}
