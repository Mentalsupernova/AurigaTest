//
// Created by tsvetkov viktor on 18.05.2023.
//
#include <stdarg.h>
#include "Message.h"

static Message  * messages_queue[MAX_QUEUE_SIZE];
void Message_parse_file(char * input_file_path){

    char line_1[MAX_LINE_SIZE];
    char line_2[MAX_LINE_SIZE];
    FILE * input_file = open_file(input_file_path);
    int counter = 0;
    while (fscanf(input_file, "%s %s", line_1, line_2) == 2) {
        Message *message = (Message *)malloc(sizeof(Message));
        // Process the parsed strings
        const char *message_start = strstr(line_1, "mess=");  // Find the "mess=" token
        const char *mask_start = strstr(line_2, "mask=");  // Find the "mask=" token
        message_start += 5;  // Move past the "mess=" keyword
        message->length = message_start[1];
        message->type = message_start[0];
        message_start +=2;
        strncpy(message->message,message_start, strlen(message_start)-3);
        message_start += strlen(message_start) -3;
        message->crc32 = string_to_mask(message_start);
        mask_start +=5;
        message->mask = string_to_mask(mask_start);
        message->processed_status = false;
        message->message_is_ok = false;

        printf("message : %s\n", message->message);
        printf("crc : %x\n", message->crc32);
        printf("type : %d\n", message->type);
        printf("length : %d\n", message->length);
        printf("mask: %d\n", message->mask);
        printf("-----\n");
        messages_queue[counter] = message;
        counter++;
        if(counter>MAX_QUEUE_SIZE){
            break;
        }
    }

    // Close the input and output files
    fclose(input_file);
}
char* Message_prepare_out_string(const char* format, ...) {
    va_list args;
    va_start(args, format);
    int stringLength = vsnprintf(NULL, 0, format, args);
    char* messageString = (char*)malloc((stringLength + 1) * sizeof(char));
    vsnprintf(messageString, stringLength + 1, format, args);
    va_end(args);
    strcat(messageString,"\n");
    return messageString;
}

/**
 * @brief flushes message into ouput file with fields
 * - message type - initial message length - initial message data bytes - initial CRC-32 - modified message length - modified message data bytes with mask - modified CRC-32
 * @param output_file_path
 * @param message
 */
void output_message(char * output_file_path,Message * message){
    char * message_type_str ="message type : ";
    FILE * file = fopen(output_file_path,"a");
    fprintf(file, Message_prepare_out_string("message type : %d",message->type));
    fprintf(file, Message_prepare_out_string("initial message length  : %d",message->length));
    fprintf(file, Message_prepare_out_string("initial message data bytes : %s",message->message));
    fprintf(file, Message_prepare_out_string("initial crc32 : %d",message->crc32));
    fprintf(file, Message_prepare_out_string("modified message length : %d", strlen(message->modified_message)));
    fprintf(file, Message_prepare_out_string("modified message data bytes : %s",message->modified_message));
    fprintf(file, Message_prepare_out_string("modified crc32 : %d",message->modified_crc32));
    fclose(file);
}
void Message_apply_mask_to_tetraids(unsigned char *array, size_t size, uint32_t mask) {
    unsigned char mask_bytes[4];
    memcpy(mask_bytes, &mask, sizeof(uint32_t));

    for (size_t i = 0; i < size; i += 4) {
        for (size_t j = 0; j < 4; j++) {
            array[i + j] ^= mask_bytes[j % 4];
        }
    }
}

void Message_process_queue(char * output_file_path){
    for(int i =0;i<sizeof(messages_queue);i++){
        if(messages_queue[i]==NULL){
            break;
        }
            if (strlen(messages_queue[i]->message)) {
                uint32_t tmp_crc = 0;
                calc_crc32(messages_queue[i]->message, strlen(messages_queue[i]->message),&tmp_crc);
                messages_queue[i]->calculated_crc = tmp_crc;
                if(!messages_queue[i]->crc32 == messages_queue[i]->calculated_crc) {

                    messages_queue[i]->message_is_ok = true;
                }else{
                    write_error("Error crc error \n", output_file_path);
                    messages_queue[i]->message_is_ok = false;
                }
                strncpy(messages_queue[i]->modified_message,messages_queue[i]->message, strlen(messages_queue[i]->message));
                Message_apply_mask_to_tetraids(messages_queue[i]->modified_message, strlen(messages_queue[i]->modified_message),messages_queue[i]->mask);
                uint32_t tmp_mod_crc  = 0;
                calc_crc32(messages_queue[i]->modified_message, strlen(messages_queue[i]->modified_message),&tmp_mod_crc);
                messages_queue[i]->modified_crc32 = tmp_mod_crc;

            } else {
                write_error("Error message is empty \n", output_file_path);
                messages_queue[i]->message_is_ok = false;
            }
        output_message(output_file_path,messages_queue[i]);
        free(messages_queue[i]);
    }
}
