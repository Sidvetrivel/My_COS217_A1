#include <stdio.h>
#include <ctype.h>
/* setting all possible states */
enum Statetype {START, SINGLE_QUOTE, BACKSLASH_CHAR, MAYBE_COMMENT, 
                COMMENT, MAYBE_END_COMMENT, DOUBLE_QUOTE,
                BACKSLASH_STRING};

/* initial state for the DFA and outputs the next state */
enum Statetype start(int c)
{   
    enum Statetype state;
    /* single quote */
    if (c == 39) {
        putchar(c);
        state = SINGLE_QUOTE;
    } 
     /* forware slash */
    else if (c == 47) {
        state = MAYBE_COMMENT;
    }
    /* double quote */
    else if(c == 34) {
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

/* enter single_quote state */
enum Statetype single_quote(int c)
{
    enum Statetype state;
    /* backslash char */
    if (c == 92) {
        putchar(c);
        state = BACKSLASH_CHAR;
    }
    /* end single quote */
    else if(c == 39) {
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

/* backslash in char state */
enum Statetype backslash_char(int c)
{
    enum Statetype state;
    putchar(c);
    state = SINGLE_QUOTE;
    return state;
}

/* maybe_comment state */
enum Statetype maybe_comment(int c)
{   
    enum Statetype state;
    /* single quote */
    if (c == 39) {
        putchar(47);
        putchar(39);
        state = SINGLE_QUOTE;
    } 
    /* double quote */
    else if (c == 34) {
        putchar(47);
        putchar(34);
        state = DOUBLE_QUOTE;
    }
    /* confirmed comment */
    else if(c == 42) {
        putchar(32);
        state = COMMENT;
    }
    /* maybe comment */
    else if(c == 47){
        putchar(c);
        state = MAYBE_COMMENT;
    }
    /* else case*/
    else{
        putchar(47);
        putchar(c);
        state = START;
    }
    return state;
}

/* comment state */
enum Statetype comment(int c)
{
    enum Statetype state;
    /* maybe end of comment */
    if(c == 42){
        putchar(c);
        state = MAYBE_END_COMMENT;
    }
    /* else case */
    else {
        state = COMMENT;
    }
    return state;
}

/* possible end comment state */
enum Statetype maybe_end_comment(int c)
{
    enum Statetype state;
    /* maybe end of comment */
    if(c == 42){
        putchar(c);
        state = MAYBE_END_COMMENT;
    }
    /* else case */
    else {
        putchar(c);
        state = COMMENT;
    }
    return state;
}

/* enter double quote state */
enum Statetype double_quote(int c)
{
    enum Statetype state;
    /* backslash in string t */
    if(c == 39){
        putchar(c);
        state = BACKSLASH_STRING;
    }
    /* double quote back to start */
    else if(c == 34) {
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
    }
    return 0;
}

