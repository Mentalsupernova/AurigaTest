//
// Created by tsvetkov viktor on 18.05.2023.
//
#include "utils.h"
#define POLYNOMINAL (0x04C11DB7)
#define CRC32_INITIAL_VALUE (0xFFFFFFFF)

uint32_t string_to_mask(char * mask_array){
    uint32_t res = 0;
    res |= (mask_array[0] << 24);
    res |= (mask_array[1] << 16);
    res |= (mask_array[2] << 8);
    res |= mask_array[3];

    return res;
}

void write_error(char * out_string,char * out_file_path){
    FILE * out_file = fopen(out_file_path,"a");
    fprintf(out_file, out_string);
    fclose(out_file);

}

void calc_crc32(unsigned char *data, size_t size, uint32_t *crc) {
    const uint32_t polynomial = POLYNOMINAL;
    *crc = CRC32_INITIAL_VALUE;

    for (size_t i = 0; i < size; i++) {
        *crc ^= data[i];

        for (size_t j = 0; j < 8; j++) {
            if (*crc & 0x80000000) {
                *crc = (*crc << 1) ^ polynomial;
            } else {
                *crc <<= 1;
            }
        }
    }

    *crc ^= CRC32_INITIAL_VALUE;
}

FILE * open_file(char * file_path){
    FILE *file;
    file = fopen(file_path, "rw");
    if (file == NULL) {
        perror("file opening failed");
    }
    return file;
}
