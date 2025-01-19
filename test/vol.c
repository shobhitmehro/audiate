#include <stdio.h>
#include <sndfile.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <input.wav> <output.wav>\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    const char *output_file = argv[2];
    
    SF_INFO sfinfo;
    SNDFILE *infile = sf_open(input_file, SFM_READ, &sfinfo);
    if (!infile) {
        printf("Error: Unable to open input file: %s\n", sf_strerror(NULL));
        return 1;
    }

    SNDFILE *outfile = sf_open(output_file, SFM_WRITE, &sfinfo);
    if (!outfile) {
        printf("Error: Unable to create output file: %s\n", sf_strerror(NULL));
        sf_close(infile);
        return 1;
    }

    const int buffer_size = 1024;
    float buffer[buffer_size];

    while (1) {
        sf_count_t read_count = sf_read_float(infile, buffer, buffer_size);
        if (read_count == 0) break;

        for (sf_count_t i = 0; i < read_count; i++) {
            buffer[i] *= 2.0f;  
        }

        sf_write_float(outfile, buffer, read_count);
    }

    // Close files
    sf_close(infile);
    sf_close(outfile);

    printf("Processed audio saved to %s\n", output_file);
    return 0;
}
