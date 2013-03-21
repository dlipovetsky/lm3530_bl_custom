#include <stdio.h>
#include <stdlib.h>

#define MIN_FULLSCALE_CURRENT   (0)
#define MAX_FULLSCALE_CURRENT   (5)
#define FULLSCALE_CURRENT_SHIFT (2)

int main (int argc, char **argv) {
        if (argc < 2) return;
        
        int fs_current = atoi (argv[1]);

        int max_current = 0x17 | 0x20;

        int gcreg = max_current; // since max_current really holds bits 0-8 of gen config register
        gcreg = gcreg & 0xE3;
        gcreg = gcreg | (fs_current << 2);
        printf("gcreg = %X\nmax_current = %X\n", gcreg, max_current);
        for (int i = 7; i >= 0; --i) {
               printf("%i", ((gcreg & (1 << i)) > 0)); 
        }
        printf("\n");

        return 0;
}
 
        
