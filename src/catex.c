#include "../include/catex.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

catex* cxInit(char* file_path)
{
    if (strlen(file_path) > (MAX_CHAR_BUF_SIZE / 4))
    {
        // This would be insanity. But make sure it doesn't happen
        return NULL;
    }

    catex* return_val = malloc(sizeof(catex));
    if (return_val == NULL)
    {
        return NULL;
    }

    // TODO: Make this not look horrible?
    // It technically is memory safe but my god it is really bad.
    
    // Allocate internals.
    
    return_val->preamble = (char*) malloc(sizeof(char)*MAX_CHAR_BUF_SIZE);
    if (return_val->preamble == NULL)
    {
        free(return_val); // Give back the few bytes we have.
        return NULL;
    }

    return_val->doctype = (char*) malloc(sizeof(char)*MAX_CHAR_BUF_SIZE);
    if (return_val->doctype == NULL)
    {
        free(return_val->preamble);
        free(return_val);
        return NULL;
    }

    return_val->body = (char**) malloc(sizeof(char*)*MAX_NUM_BUFS);
    if (return_val->body == NULL)
    {
        free(return_val->preamble);
        free(return_val->doctype);
        free(return_val);
        return NULL;
    }

    return_val->body[0] = (char*) malloc(sizeof(char)*MAX_CHAR_BUF_SIZE);
    if (return_val->body[0] == NULL)
    {
        free(return_val->preamble);
        free(return_val->doctype);
        free(return_val->body);
        free(return_val);
        return NULL;
    }

    return_val->name =  (char*) malloc(sizeof(char)*(MAX_CHAR_BUF_SIZE / 4));
    // dividing by 2 in this case because name is just the filepath. If there
    // is a filepath longer than 200 chars we have a bigger issue than this.
  
    strcpy(return_val->name, file_path); // copy the file path over

    if (return_val->name == NULL)
    {
        free(return_val->preamble);
        free(return_val->doctype);
        free(return_val->body);
        free(return_val->body[0]);
        free(return_val);
        return NULL;
    }


    return_val.cur_buf = 0;
    return_val.cur_char = 0;
    
    return return_val;
}

int cxFree(catex* cx)
{
    // Free all those mems!
    free(cx->preamble);
    free(cx->doctype);
    for (int x = 0; x <= cx->cur_buf; x++)
    {
        free(cx->body[x]);
    }
    free(cx->body);
    free(cx->name);
    free(cx);
    return 0; 
    // Cant really return 1 or anything but it's important to keep the 
    // philosophy going.
}
