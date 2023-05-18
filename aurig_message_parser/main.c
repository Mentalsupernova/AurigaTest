#include "Message.h"
#define INPUT_FILE_PATH ("data_in.txt")
#define OUTPUT_FILE_PATH ("data_out.txt")

int main() {
    Message_parse_file(INPUT_FILE_PATH);
    Message_process_queue(OUTPUT_FILE_PATH);
    return 0;
}
