#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

//#define DEBUG_PRINT

#define BUFF_SIZE 8

/*
 *  Attention: this program is for Unix(Linux) only.
 *             Line feed code is LF('\n').
 */
int main(int argc, char* argv[]) {
    while(true) {
        puts("\nEnter a IPv4 header TOS field value (two char hexadecimal).");
        puts("example) 0x0f");
        printf("input: ");
        
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
            puts("Info: Flush strings that over the buffer size.");
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
            puts("Error: stdtoul() is Failure. Input text invalid.");
            continue;
        }

        /*
         *  Print DSCP decimal and bit.
         *
         *  Reference: RFC2474 Section.3  IPv4 Header TOS field(octet)
         *    0   1   2   3   4   5   6   7
         *  +---+---+---+---+---+---+---+---+
         *  |         DSCP          |  CU   |
         *  +---+---+---+---+---+---+---+---+
         *  DSCP: differentiated services codepoint
         *  CU:   currently unused
         */
        puts("output:");
        
        // ================ Edit and testing section ================ //
        unsigned char dscp = (unsigned char)tos_field_val;
        printf("                 decimal  hex\n");
        printf("DSCP           : %2d       0x%02x\n", dscp, dscp);
        
        unsigned char priority = ;        // DSCP 0-2bit
        unsigned char drop_precedence = ; // DSCP 3-5bit
        printf("                 decimal  bit\n");
        printf("Priority       : %d        %d%d%d\n", priority,
            (priority) , (priority) , priority);
        printf("Drop precedence: %d        %d%d%d\n",drop_precedence,
            (drop_precedence), (drop_precedence), drop_precedence);
        // ================ Edit and testing section END ================ //
    }

    return 0;
}
