#ifndef __CATEX__
#define __CATEX__

/* Note that everything that adjusts the document itself has an integer return.
 * The design philosophy is that if at any time you need to see if something
 * failed or had an issue, always check the return code. Any function that does
 * have a return code in there somewhere.
 */

/* WARNING: IF YOU TRY TO ADD TOO BIG OF A BODY TO A DOCUMENT, CATEX WILL FREE
 * ITSELF AS TO SAVE YOU FROM OVEREXPENDING MEMORY.
 */

#define MAX_CHAR_BUF_SIZE 1000
#define MAX_NUM_BUFS 50

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
    char* compiler;
    int cur_buf;
    int cur_char;
} catex;

/* Generates an instance of catex and returns it's pointer.
 * 
 * *file_path: String that is the path to the file. Must not already exist.
 * *compiler: Latex compiler to be used when making the pdf document.
 *
 * Return: Pointer to catex object.
 */
catex* cxInit(char* file_path, char* compiler);

/* Changes doctype to be the one given.
 *
 * *cx: Pointer to the catex object
 * *new_doctype: Doctype to be printed.
 *
 * Return: 0 if initialized:
 */
int cxChangeDoctype(catex* cx, char* new_doctype);

/* Generates a tex file for the given catex object.
 * 
 * *cx: Pointer to the cx object to create a file for.
 *
 * Returns: 0 if successful, 1 if fail.
 *
 * Note: This will fork a process to generate the tex file, and write it to the
 * current working directory.
 */
int cxCreateTex(catex* cx);

/* Compiles the given catex object to pdf.
 * 
 * *cx: Pointer to catex object
 * 
 * Returns: 0 if successful, 1 if fail.
 *
 * Note: This will generate a tex file first, if there isn't one in the
 * directory matching the cx->name.
 */
int cxCompilePdf(catex* cx);

/* Adds body to the body of the text.
 *
 * *cx: Pointer to cx struct.
 * *text: String to be added to the body.
 *
 * Returns: 0 if successful, 1 if there are any tex symbols in the string
 * (and therefore not completed) and 2 if there is any other error.
 */
int cxAddBody(catex* cx, char* text);

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

/* Frees a created catex object.
 *
 * *cx: catex object to free.
 *
 * Returns: 0 if sucessful, 1 if not.
 */
int cxFree(catex* cx);

#endif
