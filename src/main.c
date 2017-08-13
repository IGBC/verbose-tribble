#include "musical_utils.h"
#include "A440.h"

#include <stdlib.h>
#include <stdio.h>

int main() {
    int notes[] = {A440_n(D,4),
                   A440_n(B,5), 
                   A440_n(G,4),
                   A440_n(D,4),
                   A440_n(E,5), 
                   A440_n(B,5), 
                   A440_n(G,4),
                   A440_n(B,5),
                   
                   A440_n(A,5), 
                   A440_n(G,5), 
                   A440_n(E,5),
                   A440_n(A,5),
                   A440_n(C,6), 
                   A440_n(G,5), 
                   A440_n(E,5),
                   A440_n(G,5),};
    
    int beats [] = {6, 5, 6, 3, 3, 1};
    
    int mod[] = {0.9, 0.7};
    
    int drone[] = {C, E, C, G};
    
    int beat = 5;
    int cycle = 0;
    
    double a=1,b=1,c=1,d=1,e=1,s=0.2;
    for(long t=0;;t++) {
        int relapos = (t*beat) % RATE; // relative clock position inside current beat length
        // clock resets to 0
        if (relapos==0) {
            // code to look up new beat length
            switch(cycle) {
              case 0: case 2: beat=6; break;
              case 1: beat=5; break;
              case 3: case 4: beat=3; break;
              case 5: beat=1; break;
            }
            cycle = (cycle+1)%6; // loops 
            
            // harmonic coeficent generation on new beat
            a = sqrt(((double)rand())/RAND_MAX);
            b = sqrt(((double)rand())/RAND_MAX);
            c = sqrt(((double)rand())/RAND_MAX);
            d = sqrt(((double)rand())/RAND_MAX);
            e = sqrt(((double)rand())/RAND_MAX);
            
            // harmonic normalisation. 
            s = 1.0/(a+b+c+d+e);
            a *=s; b *=s; c *= s; d *= s; e *= s;
        }
        
        //beat = sequencer(t, beat, beats, sizeof(beats)/sizeof(int));
        
        //if (beat == beat2)
        //    fprintf(stderr, "%li,  We dont dissagree (politely)!!!\n");
        
        
        // make noises
       	double m = a * playsaw(t, sequencer(t, 1, notes, sizeof(notes)/sizeof(int)))*0.05;
       	double n = b * playsaw(t, 3*sequencer(t, 1, notes, sizeof(notes)/sizeof(int)))*0.05;
       	double o = c * playsaw(t, 5*sequencer(t, 1, notes, sizeof(notes)/sizeof(int)))*0.05;
        double p = d * playsaw(t, 7*sequencer(t, 1, notes, sizeof(notes)/sizeof(int)))*0.05;
      	double q = e * playsaw(t, 9*sequencer(t, 1, notes, sizeof(notes)/sizeof(int)))*0.05;
       	double gain = 0.1 + ADSR(t, t - ((t*beat) % RATE), 0.01, 0.3, 0.4, 0.4, 0.2); //sequencer(t, 1, mod, sizeof(mod)/sizeof(int))
       	write32(((m+n+o+p+q)*gain));
       	//write32(A440_playtriad(t, sequencer(t, beat, notes, sizeof(notes)/sizeof(int)))/gain);
    }
    return 0;
}
