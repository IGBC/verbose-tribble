#include "musical_utils.h"
#include "A440.h"

int main() {
    int notes[] = {A440_note(D,4), 
                   A440_note(B,5), 
                   A440_note(G,4),
                   A440_note(D,4),
                   A440_note(E,5), 
                   A440_note(B,5), 
                   A440_note(G,4),
                   A440_note(B,5),
                   
                   A440_note(A,5), 
                   A440_note(G,5), 
                   A440_note(E,5),
                   A440_note(A,5),
                   A440_note(C,6), 
                   A440_note(G,5), 
                   A440_note(E,5),
                   A440_note(G,5),};
    
    int drone[] = {C, E, C, G};
                      
    for(long t=0;;t++) {
       	double m = playsaw(t, sequencer(t, 1, notes, sizeof(notes)/sizeof(int)))*0.05;
       	write32((m)/1.05);
       	//write32(playsaw(t, 50));
    }
    return 0;
}
