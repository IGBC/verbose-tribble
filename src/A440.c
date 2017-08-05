#include "A440.h"
#include "musical_utils.h"

double A440_playtriad(long t, int root) {
        double sample = (playsin(t, A440_tone(root))
                   + playsin(t, A440_tone(root + 2))
                   + playsin(t, A440_tone(root + 4))
                   ) / 3;
        return sample;
}

int A440_note(int n, int octave) {
    return A440_tone(A440_n(n, octave));
}

int A440_tone(int n) {
    return note(440, 12, n);
}

int A440_n(int n, int octave) {
    int oct_offset = (octave - 4) * 12;
    return oct_offset + n;
}
