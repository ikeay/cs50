#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        fprintf(stderr, "Your image cannot be opened.\n");
        return 1;
    }

    uint8_t input_buffer[BLOCK_SIZE];
    FILE *image = NULL;
    int count = 0;
    while (true)
    {
        int size = fread(input_buffer, sizeof(uint8_t), BLOCK_SIZE, file);
        if (size == 0)
        {
            break;
        }

        if (input_buffer[0] == 0xff &&
            input_buffer[1] == 0xd8 &&
            input_buffer[2] == 0xff &&
            (input_buffer[3] & 0xf0) == 0xe0
           )
        {
            if (image != NULL)
            {
                fclose(image);
                count++;
            }

            char file_name[7];
            sprintf(file_name, "%03i.jpg", count);
            image = fopen(file_name, "w");
        }

        if (image != NULL)
        {
            fwrite(input_buffer, sizeof(uint8_t), size, image);
        }
    }

    fclose(image);
    fclose(file);
    return 0;
}
