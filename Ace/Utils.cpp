#include "Utils.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <sys/select.h> 

namespace Utils {

    void setNonBlocking(bool enable) {
        static struct termios oldt, newt;
        if (enable) {
            tcgetattr(STDIN_FILENO, &oldt);
            newt = oldt;
            newt.c_lflag &= ~(ICANON | ECHO); 
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        } else {
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        }
    }

    int kbhit() {
        struct timeval tv;
        fd_set fds;
        
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds); 
        
        select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
        
        return FD_ISSET(STDIN_FILENO, &fds);
    }

    char getch() {
        char c;
        if (read(STDIN_FILENO, &c, 1) > 0) {
            return c;
        }
        return 0;
    }

    void clearScreen() {
        std::cout << "\033[2J\033[1;1H";
    }
    
    void hideCursor() {
        std::cout << "\033[?25l";
    }

    void showCursor() {
        std::cout << "\033[?25h";
    }
}