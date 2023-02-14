#include <stdio.h>
#include <ctype.h>
/* setting all possible states */
enum Statetype {START, SINGLE_QUOTE, BACKSLASH_CHAR, MAYBE_COMMENT, 
                COMMENT, MAYBE_END_COMMENT, DOUBLE_QUOTE,
                BACKSLASH_STRING};

/* start state */
enum Statetype start(int c)
{   
    enum Statetype state;
    /* single quote */
    if (c == 39) {
        putchar(c);
        state = single_quote;
    } 
     /* forware slash */
    else if (c == 47) {
        putchar(c);
        state = maybe_comment;
    }
    /* double quote */
    else if(c == 34) {
        putchar(c);
        state = double_quote;
    }
    /* else case */
    else{
        putchar(c);
        state = start;
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
        state = backslash_char;
    }
    /* end single quote */
    else if(c == 39) {
        putchar(c);
        state = start;
    }
    /* else case */
    else{
        putchar(c);
        state = single_quote;
    }
    return state;
}

/* backslash in char state */
enum Statetype backslash_char(int c)
{
    enum Statetype state;
    putchar(c);
    state = single_quote;
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
        state = single_quote;
    } 
     /* double quote */
    else if (c == 34) {
        putchar(47);
        putchar(34);
        state = double_quote;
    }
    /* confirmed comment */
    else if(c == 42) {
        putchar(32);
        state = comment;
    }
    /* maybe comment */
    else if(c == 47){
        putchar(c);
        state = maybe_comment;
    }
    /* else case*/
    else{
        putchar(47);
        putchar(c);
        state = start;
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
        state = maybe_end_comment;
    }
    /* else case */
    else {
        putchar('\n');
        state = comment;
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
        state = maybe_end_comment;
    }
    /* else case */
    else {
        putchar('\n');
        state = comment;
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
        state = backslash_string;
    }
    /* double quote back to start */
    else if(c == 34) {
        putchar(c);
        state = start;
    }
    /* else case */
    else {
        putchar(c);
        state = double_quote;
    }
    return state;
}

/* backslash in string state */
enum Statetype backslash_string(int c)
{
    enum Statetype state;
    putchar(c);
    state = double_quote;
    return state;
}


int main(void)
{
    int c;
    enum Statetype state = start;
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

