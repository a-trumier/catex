#ifndef __CATEX__
#define __CATEX__

/* Note that everything that adjusts the document itself has an integer return.
 * The design philosophy is that if at any time you need to see if something
 * failed or had an issue, always check the return code. Any function that does
 * have a return code in there somewhere.
 */

#define MAX_CHAR_BUF_SIZE 1000
#define MAX_NUM_BUFS 10

/* The main Catex structure. Has pointers to the preamble and the body.
 * Also has a reference to the filename, all of which have been malloc'd by
 * calling init.
 */
typedef struct ctex 
{
    char* preamble;
    char* doctype;
    char** body; // This a pointer to an array of buffers which point to strings.
    char* name;
    int cur_buf;
    int cur_char;
} catex;

/* Generates an instance of catex and returns it's pointer.
 * 
 * *file_path: String that is the path to the file. Must not already exist.
 *
 * Return: Pointer to catex object.
 */
catex* cxInit(char* file_path);

/* Changes doctype to be the one given.
 *
 * *cx: Pointer to the catex object
 * *new_doctype: Doctype to be printed.
 *
 * Return: 0 if initialized:
 */
int cxChangeDoctype(catex* cx, char* new_doctype);

// NOTE: The following functions are for experts with Latex to use. They do not
// error check syntax for tex, nor do they care about what you put in them.
// Please use them if you are handy with latex.

/* Add plaintext to the body of the tex file.
 * 
 * *cx: Pointer to catex object
 * *text: String to add to catex object
 *
 * Return: 0 if adding the text worked, 1 if not.
 */
int cxAddBodyPlaintext(catex* cx, char* text);

int cxFree(catex* cx);

#endif
