#include "../include/catex.h"
#include <err.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

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

    cxAddBodyPlaintext(cx, "I have added body text!");

    if (strcmp(cx->body[cx->cur_buf], "I have added body text!") != 0)
    {
        if (should_print)
            printf("Error: cxAddBody did not add body text.\nBody text: %s", 
                    cx->body[cx->cur_buf]);
        counter++;
    }

    char* lol = malloc(sizeof(char)*(MAX_CHAR_BUF_SIZE+4));
    for (int i = 0; i < MAX_CHAR_BUF_SIZE+3; i++)
    {
        lol[i] = 'a';
    }
    lol[MAX_CHAR_BUF_SIZE+3] = '\0';

    cxAddBodyPlaintext(cx, lol);

    for (int i = strlen("I have added body text!"); i < MAX_CHAR_BUF_SIZE; i++)
    {
        if (cx->body[0][i] != 'a')
        {
            if (should_print)
                printf("Error: cxAddBody did not correctly add buffer.\n");
            counter++;
        }
    }

    // TODO: Figure out why this isn't passing? It should be fine, but for some
    // reason the second buffer is just giving nonsense.
    for (int i = 0; i < cx->cur_char; i++)
    {
        if (cx->body[1][i] != 'a')
        {
            if (should_print)
            {
                printf("Error: cxAddBody did not correctly add buffer.\n");
                printf("Expected %c got %c\n", 'a', cx->body[1][i]);
            }
            counter++;
            break;
        }
    }

    free(lol);
    cxFree(cx);
    printf("Test driver completed. Errors encountered: %d\n", counter);
    return 0;
}
