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
 
    cxFree(cx);
    printf("Test driver completed. Errors encountered: %d\n", counter);
    return 0;
}
