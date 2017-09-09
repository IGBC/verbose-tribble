#ifndef A400_H
#define A440_H
#define A  0
#define As 1
#define B  2
#define C  3
#define Cs 4
#define D  5
#define Ds 6
#define E  7
#define F  8
#define Fs 9
#define G  10
#define Gs 11

double A440_playtriad(long t, int root);
int A440_note(int n, int octave);
int A440_tone(int n);
int A440_n(int n, int octave);
#endif