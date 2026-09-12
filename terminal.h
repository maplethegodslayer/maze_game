#ifndef TERMINAL_H
#define TERMINAL_H

#define BLINK_ENABLE "\e[5m"
#define BLINK_DISABLE "\e[25m"

#define FOREGROUND_BLACK "\e[0;30m"
#define FOREGROUND_WHITE "\e[0;37m"
#define FOREGROUND_RED "\e[0;31m"
#define FOREGROUND_GREEN "\e[0;32m"
#define FOREGROUND_BLUE "\e[0;34m"
#define FOREGROUND_YELLOW "\e[0;33m"
#define FOREGROUND_CYAN "\e[0;36m"
#define FOREGROUND_PURPLE "\e[46m"


#define BACKGROUND_BLACK "\e[40m"
#define BACKGROUND_WHITE "\e[47m"
#define BACKGROUND_RED "\e[41m"
#define BACKGROUND_GREEN "\e[42m"
#define BACKGROUND_BLUE "\e[44m"
#define BACKGROUND_YELLOW "\e[43m"
#define BACKGROUND_CYAN "\e[46m"
#define BACKGROUND_PURPLE "\e[45m"

#define COLOR_RESET "\e[0m"
#define CLEAR_SCREEN "\033[2J"
#define CURSOR_RESET "\033[H"

void clearScreen();
void cursorReset();
void clearAndResetScreen();

#endif
