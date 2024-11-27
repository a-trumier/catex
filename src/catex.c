#include "../include/catex.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int _cxRequireBuffer(catex* cx); // make the compiler happy

catex* cxInit(char* file_path, char* compiler)
{
    int path_len = strlen(file_path);
    if (path_len > (MAX_CHAR_BUF_SIZE / 4))
    {
        // This would be insanity. But make sure it doesn't happen
        return NULL;
    }

    catex* return_val = malloc(sizeof(catex));
    
    // This null check isn't below because this is required for the next calls
    // and must not be null for the next steps to occur.
    if (return_val == NULL)
    {
        return NULL;
    }

    // Allocate internals.
    return_val->preamble = (char*) malloc(sizeof(char)*MAX_CHAR_BUF_SIZE);
    return_val->doctype = (char*) malloc(sizeof(char)*MAX_CHAR_BUF_SIZE);
    return_val->body = (char**) malloc(sizeof(char*)*MAX_NUM_BUFS);
    return_val->body[0] = (char*) malloc(sizeof(char)*MAX_CHAR_BUF_SIZE);
    return_val->name =  (char*) malloc(sizeof(char)*(MAX_CHAR_BUF_SIZE / 4));
    // dividing by 4 in this case because name is just the filepath. If there
    // is a filepath longer than that we have a bigger issue than this.
    
    return_val->compiler = (char*) malloc(sizeof(char)*(MAX_CHAR_BUF_SIZE/40));

    // Since above is the last malloc call, we can check if ANY of the mallocs
    // have failed. If so, free everything then return null
    if (return_val->preamble == NULL || return_val->doctype == NULL || 
            return_val->body == NULL || return_val->compiler == NULL ||
            return_val->body[0] == NULL || return_val->name == NULL || 
            return_val->compiler == NULL)
    {
        free(return_val->compiler);
        free(return_val->preamble);
        free(return_val->doctype);
        free(return_val->body);
        free(return_val->body[0]);
        free(return_val->name);
        free(return_val);
        return NULL;
    }

    strcpy(return_val->name, file_path);
    strcpy(return_val->doctype, "article"); 
    strcpy(return_val->compiler, compiler);

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

int cxAddBodyPlaintext(catex* cx, char* text)
{
    int textlen = strlen(text);
    
    int i = cx->cur_char;
    int j = 0;
    char cur_char = text[0];
    while (cur_char != '\0')
    {
        printf("cur_buf: %d\n", cx->cur_buf);
        cx->body[cx->cur_buf][i] = text[j];
        cur_char = text[j];
        printf("cur_char: %c\n", cur_char);

        if (i + 1 >= MAX_CHAR_BUF_SIZE)
        {
            _cxRequireBuffer(cx);
            i = 0;
        }
        j++;
        i++;
    }
    
    cx->cur_char += textlen;
    
    return 0;
}


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
