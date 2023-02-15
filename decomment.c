#include <stdio.h>
#include <ctype.h>
/* setting all possible states in the DFA */
enum Statetype {START, SINGLE_QUOTE, BACKSLASH_CHAR, MAYBE_COMMENT, 
                COMMENT, MAYBE_END_COMMENT, DOUBLE_QUOTE,
                BACKSLASH_STRING};

/* takes parameter int c, decides output and next state at start state,
returns the next state transition in the dfa, prints int c to stdout */
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

/* takes parameter int c, decides output and next state at single_quote
state, returns the next state transition in the dfa, prints int c to 
stdout */
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

/* takes parameter int c, output next state (SINGLE_QUOTE),
returns the next state transition in the dfa, prints int c to stdout */
enum Statetype backslash_char(int c)
{
    enum Statetype state;
    putchar(c);
    state = SINGLE_QUOTE;
    return state;
}

/* takes parameter int c, decides output and next state at 
maybe_comment state, returns the next state transition in the dfa, 
prints int c to stdout and depending on the case, the previous char */
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

/* takes parameter int c, decides output and next state at 
comment state, returns the next state transition in the dfa, 
prints int c to stdout if newline character, otherwise no stdout */
enum Statetype comment(int c)
{
    enum Statetype state;
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

/* takes parameter int c, decides output and next state at 
maybe_end_comment state, returns the next state transition in the dfa, 
prints int c to stdout if c is newline character  */
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

/* takes parameter int c, decides output and next state at 
double_quote state, returns the next state transition in the dfa, 
prints int c to stdout*/
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

/* takes parameter int c, output next state (DOUBLE_QUOTE),
returns the next state transition in the dfa, prints int c to stdout */
enum Statetype backslash_string(int c)
{
    enum Statetype state;
    putchar(c);
    state = DOUBLE_QUOTE;
    return state;
}

/* main has no parameters. Handles the state transitions and when to 
break out of the while loop. If there is an error, main calculates
the line at which the error occurs and outputs it to stderr. main also 
handles a special case regarding the maybe_comment state */
int main(void)
{
    int c;
    int i_linetracker;
    int i_linecount = 1;
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
            if(state == COMMENT){
                i_linetracker = i_linecount;
            }
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
    if(state == MAYBE_COMMENT){
        putchar('/');
    }
    if((state == MAYBE_END_COMMENT) | (state == COMMENT)){
         fprintf(stderr, "Error: line %d: unterminated comment\n", 
         i_linetracker);
         return 1;
    }
    return 0;
}

