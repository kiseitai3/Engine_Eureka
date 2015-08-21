#include <stdio.h>
#include "crc.h"

int main()
{
    char x = 5;
    unsigned char y = 5;
    uint64_t crc = 0;
    char z;
    char w[10] = "Histology\0";

    printf("%s", "test\n\r");
    fprintf(stdout, "%i \n", x - 10);
    fprintf(stdout, "%i \n", y - 10);
    fprintf(stdout, "%i \n", (char)(y - 10));

    y += 256;

    z = y - 127;
    fprintf(stdout, "%i \n", z);

    crc = crc64(w, 10);
    fprintf(stdout, "%i \n", crc);

    crc = crc64_on_file_fast("pyMod.py");
    fprintf(stdout, "0x%X \n", crc);

    scanf("%c \n", &x);
    return 0;
}
