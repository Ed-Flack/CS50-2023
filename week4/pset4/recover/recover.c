#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int BLOCK_SIZE = 512;
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");

    if (f == NULL)
    {
        printf("Cannot open %s", argv[1]);
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];
    int count = 0;
    FILE *image = NULL;
    char filename[8];
    while (fread(buffer, 1, BLOCK_SIZE, f) == BLOCK_SIZE)
    {
        char firstFourBitsOfFourthByte = buffer[3] >> 4;
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && firstFourBitsOfFourthByte == 0xE)
        {
            if (count != 0)
            {
                fclose(image);
            }
            sprintf(filename, "%03d.jpg", count);
            image = fopen(filename, "w");
            count++;
        }
        if (count != 0)
        {
            fwrite(buffer, BLOCK_SIZE, 1, image);
        }
    }
    fclose(image);
    fclose(f);
}
