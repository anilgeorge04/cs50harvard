#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Check command Line correct namefile usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // Check memory card opens successfully
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        fprintf(stderr, "File %s could not be opened\n", argv[1]);
        return 1;
    }

    // Size of data type BYTE is 1 byte
    typedef uint8_t BYTE;
    int count = 0;
    char filename[8];
    // bf declared to points to a 512 BYTE array, i.e. 1 block
    BYTE *bf = malloc(512);
    // Buffer file pointer to write to jpeg file
    FILE *img;

    // Loop through memory card till end of file
    while (fread(bf, sizeof(BYTE), 512, card) == 512)
    {
        // Check start of new JPEG
        if (bf[0] == 0xff && bf[1] == 0xd8 && bf[2] == 0xff && (bf[3] & 0xf0) == 0xe0)
        {
            if (count > 0)
            {
                fclose(img);
            }
            // create new jpeg file
            sprintf(filename, "%03i.jpg", count);
            img = fopen(filename, "w");
            if (img == NULL)
            {
                fprintf(stderr, "Could not create JPEG output file(s)\n");
                fclose(card);
                free(bf);
                return 1;
            }
            count++;
        }
        // write to jpeg file
        if (count > 0)
        {
            fwrite(bf, sizeof(BYTE), 512, img);
        }
    }
    fclose(img);
    fclose(card);
    free(bf);
}