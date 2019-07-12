#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int max(int i1, int i2) {
    return i1 > i2 ? i1 : i2;
}

void drive(int controlFront, int controlSide, int controlTurn) {
    double phi = atan2(controlSide, controlFront);

    int vd = max(controlFront + controlSide, 1023);
    vd -= controlTurn / 2;
    int vphi = controlTurn / 2;

    vd /= 2;

    double s = vd * sin(phi + 3.141592 / 4);
    double c = vd * cos(phi + 3.141592 / 4);

    int speedVL = s + vphi;
    int speedVR = c - vphi;
    int speedHL = c + vphi;
    int speedHR = s - vphi;

    speedVL = speedVL / 1023.0 * 300 + 1023 - 300;

    printf("#######\n");
    printf("%i %i\n", speedVL, speedVR);
    printf("%i %i\n", speedHL, speedHR);
}

int main() {
    drive(1023, 0, 0);
    drive(1023, 1023, 0);
    drive(1023, 500, 0);

    printf("dir: %f\n", atan2(0, 0) * 57.2957795);
    printf("dir: %f\n", atan2(0, 1023) * 57.2957795);
    printf("dir: %f\n", atan2(1023, 1023) * 57.2957795);
    printf("dir: %f\n", atan2(1023, 0) * 57.2957795);
    printf("dir: %f\n", atan2(-1023, -1023) * 57.2957795 + 360);
    printf("dir: %f\n", atan2(0, -1023) * 57.2957795);
    printf("dir: %f\n", atan2(-1023, 0) * 57.2957795);
}