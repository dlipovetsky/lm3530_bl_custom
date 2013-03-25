#include <stdio.h>
#include <stdlib.h>

#define MIN_FULLSCALE_CURRENT   (0)
#define MAX_FULLSCALE_CURRENT   (5)
#define FULLSCALE_CURRENT_SHIFT (2)

#define MAX_CURRENT             (0x17)
#define PWM_BRIGHTNESS          (0x20)

static void lm3530_set_fullscale_current(int level) {
    // Validate current level
    if (level < MIN_FULLSCALE_CURRENT)
        level = MIN_FULLSCALE_CURRENT;
    else if (level > MAX_FULLSCALE_CURRENT)
        level = MAX_FULLSCALE_CURRENT;

    // Retrieve values defined by kernel config 
    int max_current = MAX_CURRENT | PWM_BRIGHTNESS;

    // Construct register value to be written to controller
    int gcreg = max_current; // since max_current really holds bits 0-8 of gen config register
    gcreg &= 0xE3;
    gcreg |= (level << 2);
    
    // Output (for testing) 
    printf("gcreg = %X\nmax_current = %X\n", gcreg, max_current);
    for (int i = 7; i >= 0; --i) {
        printf("%i", ((gcreg & (1 << i)) > 0)); 
    }
    printf("\n");

    // Store new max_current
    max_current = gcreg;
}

int main (int argc, char **argv) {
    if (argc < 2) return 1;
    
    lm3530_set_fullscale_current(atoi(argv[1]));

    return 0;
}
 
        
