//
// Created by tsvetkov viktor on 18.05.2023.
//

#ifndef AURIG_MESSAGE_PARSER_UTILS_H
#define AURIG_MESSAGE_PARSER_UTILS_H
#include "stdio.h"
#include "stdint.h"

void write_error(char * out_string,char * out_file_path);
void calc_crc32(unsigned char *data, size_t size, uint32_t *crc);
FILE * open_file(char * file_path);
uint32_t string_to_mask(char * mask_array);
#endif //AURIG_MESSAGE_PARSER_UTILS_H
