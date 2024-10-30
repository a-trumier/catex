#include "../include/catex.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int _cxRequireBuffer(catex* cx); // make the compiler happy

catex* cxInit(char* file_path, char* compiler)
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
    strcpy(return_val->doctype, "article"); 

    if (return_val->name == NULL)
    {
        free(return_val->preamble);
        free(return_val->doctype);
        free(return_val->body);
        free(return_val->body[0]);
        free(return_val);
        return NULL;
    }

    return_val->compiler = (char*) malloc(sizeof(char)*(MAX_CHAR_BUF_SIZE/40));
    if (return_val->compiler == NULL)
    {
        free(return_val->preamble);
        free(return_val->doctype);
        free(return_val->body);
        free(return_val->body[0]);
        free(return_val->name);
        free(return_val);
        return NULL;
    }

    strcpy(return_val->compiler, compiler);

    // These tell us what buffer we are looking at and what character buffer
    // we are doing.
    return_val->cur_buf = 0;
    return_val->cur_char = 0;
    
    return return_val;
}

int cxChangeDoctype(catex* cx, char* new_doctype)
{
    // fairly simple here.

    strcpy(cx->doctype, new_doctype);
    return 0;
}

// TODO: Implement
int cxAddBody(catex* cx, char* text)
{
    int textlen = strlen(text);
    
    if (textlen + cx->cur_char >= MAX_CHAR_BUF_SIZE) // equal to for null char
    {
        _cxRequireBuffer(cx); // increment buffer then move on
    }
    strcpy(cx->body[cx->cur_buf] + (cx->cur_char), text);
    
    cx->cur_char += textlen;
    
    return 0;
}

// TODO: Implement
int cxAddBodyPlaintext(catex* cx, char* text);

// TODO: Implement
int cxCreateTex(catex* cx);

// TODO: Implement
int cxCompilePdf(catex* cx);

/* Function that creates another buffer to add body text to.
 *
 * *cx: Struct to add another buffer to.
 *
 * Returns: 0 if successful, 1 if we are out of buffers to add, 2 if other
 * error.
 */
int _cxRequireBuffer(catex* cx)
{
    // The idea of this function is that it is called when someone tries to add
    // to the current buffer but would go over the limit. So we step in, make a
    // new buffer, and simply return. Graceful addition of memory.
    //
    // In reality, this doesn't have a huge memory impact. However, I want to be
    // super careful with memory allocation. I don't want to just ask the OS
    // for a gig for no reason.
    
    printf("cur_buf: %d\n", cx->cur_buf);
    cx->cur_buf++;
    if (cx->cur_buf >= MAX_NUM_BUFS)
    {
        // Fie on you all! Hit the ejection switch!
        return 1;
    }
    cx->cur_char = 0;

    cx->body[cx->cur_buf] = (char*) malloc(sizeof(char)*MAX_CHAR_BUF_SIZE);
    if (cx->body[cx->cur_buf] == NULL)
    {
        return 2;
    }
    return 0;
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
