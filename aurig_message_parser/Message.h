//
// Created by tsvetkov viktor on 18.05.2023.
//

#ifndef AURIG_MESSAGE_PARSER_MESSAGE_H
#define AURIG_MESSAGE_PARSER_MESSAGE_H
#define MAX_PAYLOAD_SIZE (252U)
#define MAX_LINE_SIZE (258U)
#define MAX_MASK_SIZE (4U)
#define MAX_QUEUE_SIZE (10U)


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "utils.h"

typedef struct{
    uint8_t type;
    uint8_t length;
    unsigned char message[MAX_PAYLOAD_SIZE];
    unsigned char modified_message[MAX_PAYLOAD_SIZE];
    uint32_t modified_crc32:24;
    uint32_t crc32:24;
    uint32_t calculated_crc:24;
    uint32_t mask;
    bool processed_status;
    bool message_is_ok;
}Message;



extern void Message_parse_file(char * input_file_path);
extern void Message_process_queue(char * output_file_path);
#endif //AURIG_MESSAGE_PARSER_MESSAGE_H
