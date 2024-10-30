#include "../include/catex.h"
#include <err.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int counter = 0;
    int should_print = 0;
    if (argc >= 2)
    {
        if (strcmp(argv[1], "--verbose") == 0)
        {
            should_print = 1;
        }
    }
    
    printf("Beginning test driver.\n");
    catex* cx = cxInit("hello", "pdflatex");

    if (cx == NULL)
    {
        if (should_print)
            perror("Error: cxInit returned NULL.\n");
        counter++;
    }

    if (strcmp(cx->doctype, "article") != 0)
    {
        if (should_print)
            perror("Error: cxInit did not generate the correct doctype.\n");
        counter++;
    }
    
    if (strcmp(cx->name, "hello") != 0)
    {
        if (should_print)
            perror("Error: cxInit did not generate the correct name.\n");
        counter++;
    }
    
    if (strcmp(cx->compiler, "pdflatex") != 0)
    {
        if (should_print)
            perror("Error: cxInit did not generate the correct compiler.\n");
        counter++;
    }

    /* TESTING cxAddBody */

    cxAddBody(cx, "I have added body text!");

    if (strcmp(cx->body[cx->cur_buf], "I have added body text!") != 0)
    {
        if (should_print)
            printf("Error: cxAddBody did not add body text.\nBody text: %s", 
                    cx->body[cx->cur_buf]);
        counter++;
    }

    /* This is a bad edge case. TODO: Fix cxAddBody for a case where the input
     * string is larger than the MAX_CHAR_BUF_SIZE
    char* lol = malloc(sizeof(char)*MAX_CHAR_BUF_SIZE+1);
    for (int i = 0; i < MAX_CHAR_BUF_SIZE; i++)
    {
        lol[i] = 'a';
    }
    lol[MAX_CHAR_BUF_SIZE]
    */
    cxFree(cx);
    printf("Test driver completed. Errors encountered: %d\n", counter);
    return 0;
}
