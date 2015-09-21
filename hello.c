/*
 * This is a non-traditional hello demo for Propeller-GCC.
 * The demo repeats printing every 100ms with the iteration.
 * It uses waitcnt instead of sleep so it will fit in a COG.
 */
#include <stdio.h>
#include <propeller.h>
#include <badgetools.h>

int xAccel = 0;
int yAccel = 0;
int zAccel = 0;

void init() {
    printf("Badge setup...\n");
    pause(1000);
    badge_setup();
    printf("Badge setup\n");
    clear();
    accels(&xAccel, &yAccel, &zAccel);
    screen_auto(1);
    
}

int main(void)
{
    init();
    int yvals[128];
    for(int i = 0; i < 128; i++) {
        yvals[i] = 0;
    }
    int xvals[128];
    for(int i = 0; i < 128; i++) {
        xvals[i] = 0;
    }
    int zvals[128];
    for(int i = 0; i < 128; i++) {
        zvals[i] = 0;
    }
    int n = 0;
    while(1) {
 //       waitcnt(CLKFREQ/1000+CNT);
        accels(&xAccel, &yAccel, &zAccel);
        printf("Accel z %d\n", zAccel);

        double xNorm = ( (xAccel + 100.0) / 200.0 ); 
        double yNorm = ( (yAccel + 100.0) / 200.0 ); 
        double zNorm = ( (zAccel + 100.0) / 200.0 ); 

        double amplitude = ( xAccel * xAccel) + (yAccel * yAccel) + (zAccel * zAccel);
        int x = xNorm * 63;
        if (x > 63)
            x = 63;
        if (x < 0)
            x = 0;
       int y = yNorm * 63;
        if (y > 63)
            y = 63;
        if (y < 0)
            y = 0;
       int z = zNorm * 63;
        if (z > 63)
            z = 63;
        if (z < 0)
            z = 0;

        point(n, xvals[n], 0);
        point(n, yvals[n], 0);
        point(n, zvals[n], 0);
        xvals[n] = x;
        yvals[n] = y;
        zvals[n] = z;
        point(n, xvals[n], 1);
        point(n, yvals[n], 1);
        point(n, zvals[n], 1);
        n = (n + 1) % 127;
    }
    return 0;
}
