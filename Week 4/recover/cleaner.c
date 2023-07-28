#include <stdio.h>
#include <stdlib.h>

int main() {
    int i;
    char filename[8];

    for (i = 0; i <= 50; i++) {
        sprintf(filename, "%03d.jpg", i);
        remove(filename);
    }

    return 0;
}