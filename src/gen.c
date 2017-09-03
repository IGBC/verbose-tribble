#include <sys/random.h>
#include <stdio.h>

#include "musical_utils.h"
#include "A440.h"

int randomr(int min, int max);

// music context
int barlen=16;
int baseoctave=5;
int nNotes=6;
int bps=8;

//assume A440 for a second
int main(void) {
    // Generate a note pool
    fprintf(stderr, "Notepool: ");
    int notepool[24]; //bigger than needed
    for (int i = 0; i < nNotes; i++) {
        notepool[i] = randomr(-11, 11);
        fprintf(stderr, "%3i, ", notepool[i]);
    }

    fprintf(stderr, "\nBar:\n");
    
    // Generate and print a bar
    double bar[1024]; //bigger than needed
    for(int i = 0; i < barlen; i++)
        fprintf(stderr, "%3i, ", i);
    fprintf(stderr, "\n");
    for (int i = 0; i < barlen; i++) {
        int val = randomr(0, nNotes-1);
        fprintf(stderr, "%3i, ", notepool[val]);
        bar[i] = A440_note(notepool[val], baseoctave);
    }
    fprintf(stderr, "\n");
    for(int i = 0; i < barlen; i++)
        fprintf(stderr, "%3i, ", (int)bar[i]);
    fprintf(stderr, "\n");
    
    float V0;
    for(long t=0;;t++) {
        int freq = sequencer(t, bps, bar, barlen);
        float sample = playsqr(t, freq);
        write32(sample);
        V0 = sample;
    }
    
    return 0;
}

int randomr(int min, int max) {
    unsigned int buffer;
    int ret = getrandom(&buffer, sizeof(int), 0);
    if (ret != sizeof(int))
        printf("syscall getrandom() error:");
    int out = buffer % (max + 1 - min) + min;
    return out;
}

