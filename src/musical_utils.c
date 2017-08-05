#include "musical_utils.h"

#include <math.h>
#include <limits.h>
#include <stdio.h>

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
int sequencer(long t, double beat, int *item_array, int len) {
    int val =  (int)((t*beat) / RATE) % len;
    return item_array[val];
}

/* Sample Writing (Output) functions */

/* Both of these write the output to std out in formats designed for alsa */

/* Output sample in unsigned 8 bit format (U8) */
void writeU8(double sample) {
    putchar((1+sample) * 127);
}

/* Output sample in S32LE format */
void write32(double val) {
    int sample = val * INT_MAX;
    for (int i = 0; i < 4; i++, sample >>= 8)
        putchar(sample & 0xff);
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
