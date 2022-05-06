#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

#define DEBUG_PRINT

#define BUFF_SIZE 8

/*
 *  Attention: this program is for Unix(Linux) only.
 *             Line feed code is LF('\n').
 */
int main(int argc, char* argv[]) {
    while(true) {
        puts("\nEnter a IPv4 header TOS field value (two char hexadecimal).  example) 0x0f");
        
        /*
         *  Get User input TOS field value to buffer.
         */
        char input_tos_buffer[BUFF_SIZE] = {0};
        if(fgets(input_tos_buffer, sizeof(input_tos_buffer), stdin) == NULL) {
            puts("Error: Unable to read the input text.");
            return -1;
        }
#ifdef DEBUG_PRINT
        for(int i = 0; i < BUFF_SIZE; i++) {
            printf("Debug buffer[%d]: char=%c hex=0x%02x \n",
                i, input_tos_buffer[i], input_tos_buffer[i]);
        }
#endif
        /*
         *  Program end keyword check.
         */
        if(strncmp(input_tos_buffer, "exit", 4) == 0 ||
           strncmp(input_tos_buffer, "quit", 4) == 0) {
            puts("Bye.");
            break;
        }
        
        /*
         *  Flush stdin.
         */
        if(strlen(input_tos_buffer) == (BUFF_SIZE - 1) && input_tos_buffer[6] != '\n') {
            while(getchar() != '\n');
        }
        
        /*
         *  Trim Line feed code.
         */
        if(strlen(input_tos_buffer) == 5 && input_tos_buffer[4] == '\n') {
            input_tos_buffer[4] = '\0';
        }

        /*
         *  Convert string to integer(unsigned long type).
         */
        char* endptr = NULL;
        unsigned long tos_field_val = strtoul(input_tos_buffer, &endptr, 16);
        if(errno != 0 || *endptr != '\0') {
            printf("Error: stdtoul() is Failure...\n");
            continue;
        }

        /*
         *  Print DSCP decimal and bit.
         */
        unsigned char dscp = (unsigned char)tos_field_val >> 2;
        printf("DSCP (decimal) : %d\n", dscp);
        printf("Priority       : %d\n", dscp & 0x07); // DSCP 0-2bit
        printf("Drop precedence: %d\n", dscp & 0x28); // DSCP 3-5bit
    }

    return 0;
}
