#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse INPUT OUTPUT\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open input file.\n");
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER header;
    fread(&header, HEADER_SIZE, 1, input);

    // Use check_format to ensure WAV format
    // TODO #4
    if (!check_format(header))
    {
        printf("Input is not a WAV file.\n");
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open output file.\n");
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&header, HEADER_SIZE, 1, output);

    // Use get_block_size to calculate size of block
    // TODO #7
    int blockSize = get_block_size(header);

    // Write reversed audio to file
    // TODO #8
    if (fseek(input, blockSize, SEEK_END)) { // Setting pointer to end of file, if it returns true something messed up
        return 1;
    }

    BYTE buffer[blockSize];
    while(ftell(input) - blockSize > HEADER_SIZE) // We are working backwards, when we reach the header, we know we have read all the data
    {
        if (fseek(input, -2 * blockSize, SEEK_CUR)) { // Need to move the pointer back to places after each fread(), if it returns true something messed up
            return 1;
        }
        fread(buffer, blockSize, 1, input);
        fwrite(buffer, blockSize, 1, output);
    }

    fclose(input);
    fclose(output);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    return header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E';
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return header.numChannels * header.bitsPerSample / 8;
}
