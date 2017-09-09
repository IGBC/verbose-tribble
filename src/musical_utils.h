#ifndef MUSICAL_UTILS_H
#define MUSICAL_UTILS_H
#ifdef __cplusplus
extern "C" {
#endif
#define TAU (double)(8*atan(1)) // Definition of 2PI used in sin functions
#define RATE 44100 // sample rate of output 

/* Generate frequencies of a musical scale.
 * scale is defined by nth root 2 constant where n = 12 in european music 
 * notes sit at integer powers of the constant, multiplied by a base freqency.
 */
double note(int base, int scale, int i);

// A chord is a combination of notes from the same scale

/* Timing functions */

/* converts timestep to seconds (flooring the fractional result) */
int seconds(int t);

/* cycles through the provided list of integer items at the rate of 
 * the given beat (bps) */ 
double sequencer(long t, double beat, double *item_array, int len);

/* Standard Envelope Generator (ADSR)
 * takes the current time and a trigger time in samples as well as
 * A,D,H,R parameters in seconds and S parameter as a normalised
 * float. Returns a normalised float for using as a gain or 
 * whatever */
//double ADSR(long t, long trig_t, double A, double D, double H, double S, double R)
double ADSR(long t, long trig_t, double, double, double, double, double); 

/* Sample Writing (Output) functions */

/* Both of these write the output to std out in formats designed for alsa */
void writeU8(double sample); /* Output sample in unsigned 8 bit format (U8) */
void write32(double val); /* Output sample in S32LE format */

/* Tone Generator Functions */

/* All of these do the same thing, 
 * They take the current timestep (in samples) and
 * the desired frequency in Hz. With these they produce
 * a sample as a float between -1 and 1.
 */
double playsqr(long t, int freq); // Square Wave
double playsaw(long t, int freq); // Sawtooth Wave
double playsin(long t, int freq); // Sine Wave
#ifdef __cplusplus
}
#endif
#endif