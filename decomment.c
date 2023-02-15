#include <stdio.h>
#include <ctype.h>
/* setting all possible states in the DFA */
enum Statetype {START, SINGLE_QUOTE, BACKSLASH_CHAR, MAYBE_COMMENT, 
                COMMENT, MAYBE_END_COMMENT, DOUBLE_QUOTE,
                BACKSLASH_STRING};

/* global int variable that keeps track of # of lines */
int i_linecount = 0;
int i_commentcount = 0;

/* takes parameter int c, returns the next state transition in the 
dfa, and prints to stdout. global line variable is updated within this 
function when '\n' is detected. */
enum Statetype start(int c)
{   
    enum Statetype state;
    /* single quote */
    if (c == '\'') {
        putchar(c);
        state = SINGLE_QUOTE;
    } 
     /* forware slash */
    else if (c == '/') {
        state = MAYBE_COMMENT;
    }
    /* double quote */
    else if(c == '"') {
        putchar(c);
        state = DOUBLE_QUOTE;
    }
    /* else case */
    else{
        putchar(c);
        state = START;
    }
    return state;
}

/* takes int c, outputs stdout, returns next state from single_quote */
enum Statetype single_quote(int c)
{
    enum Statetype state;
    /* backslash char */
    if (c == '\\') {
        putchar(c);
        state = BACKSLASH_CHAR;
    }
    /* end single quote */
    else if(c == '\'') {
        putchar(c);
        state = START;
    }
    /* else case */
    else{
        putchar(c);
        state = SINGLE_QUOTE;
    }
    return state;
}

/* takes int c, outputs stdout, transitions back to single_quote */
enum Statetype backslash_char(int c)
{
    enum Statetype state;
    putchar(c);
    state = SINGLE_QUOTE;
    return state;
}

/* takes int c, outputs stdout, returns 1 of 5 possible next states */
enum Statetype maybe_comment(int c)
{   
    enum Statetype state;
    /* single quote */
    if (c == '\'') {
        putchar('/');
        putchar(c);
        state = SINGLE_QUOTE;
    } 
    /* double quote */
    else if (c == '"') {
        putchar('/');
        putchar(c);
        state = DOUBLE_QUOTE;
    }
    /* confirmed comment */
    else if(c == '*') {
        putchar(' ');
        state = COMMENT;
    }
    /* maybe comment */
    else if(c == '/'){
        putchar(c);
        state = MAYBE_COMMENT;
    }
    /* else case*/
    else{
        putchar('/');
        putchar(c);
        state = START;
    }
    return state;
}

/* takes int c comment state */
enum Statetype comment(int c)
{
    enum Statetype state;
    i_commentcount = i_linecount;
    /* maybe end of comment */
    if(c == '*'){
        state = MAYBE_END_COMMENT;
    }
    /* else case */
    else {
        if(c == '\n'){
            putchar(c);
        }
        state = COMMENT;
    }
    return state;
}

/* possible end comment state */
enum Statetype maybe_end_comment(int c)
{
    enum Statetype state;
    /* maybe end of comment */
    if(c == '*'){
        state = MAYBE_END_COMMENT;
    }
    /* back to start case */
    else if(c == '/'){
        state = START;
    }
    /* stay in maybe_end_comment case */
    else {
        if(c == '\n'){
            putchar(c);
        }
        state = COMMENT;
    }
    return state;
}

/* enter double quote state */
enum Statetype double_quote(int c)
{
    enum Statetype state;
    /* backslash in string t */
    if(c == '\\'){
        putchar(c);
        state = BACKSLASH_STRING;
    }
    /* double quote back to start */
    else if(c == '"') {
        putchar(c);
        state = START;
    }
    /* else case */
    else {
        putchar(c);
        state = DOUBLE_QUOTE;
    }
    return state;
}

/* backslash in string state */
enum Statetype backslash_string(int c)
{
    enum Statetype state;
    putchar(c);
    state = DOUBLE_QUOTE;
    return state;
}

int main(void)
{
    int c;
    enum Statetype state = START;
    /* loop handles the state transitions */
    while ((c = getchar()) != EOF) {
        /* determines which function to call depending on state */
        switch (state) {
            case START:
            state = start(c);
            break;
            case SINGLE_QUOTE:
            state = single_quote(c);
            break;
            case BACKSLASH_CHAR:
            state = backslash_char(c);
            break;
            case MAYBE_COMMENT:
            state = maybe_comment(c);
            break;
            case COMMENT:
            state = comment(c);
            break;
            case MAYBE_END_COMMENT:
            state = maybe_end_comment(c);
            break;
            case DOUBLE_QUOTE:
            state = double_quote(c);
            break;
            case BACKSLASH_STRING:
            state = backslash_string(c);
            break;
        }
        if(c == '\n'){
            i_linecount++;
        }
    }
    if((state == MAYBE_END_COMMENT) | (state == COMMENT)){
         fprintf(stderr, "Error: line %d: unterminated comment\n", i_linecount);
         fprintf(stderr, "%d", i_commentcount);
         return 1;
    }
    return 0;
}

