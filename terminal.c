#include "terminal.h"
#include <stdio.h>

void clearScreen(){
    printf(CLEAR_SCREEN);
}

void cursorReset(){
    printf(CURSOR_RESET);
}

void clearAndResetScreen(){
    printf(CLEAR_SCREEN CURSOR_RESET);
    fflush(stdout);
}
