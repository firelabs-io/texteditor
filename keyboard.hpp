#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
#include <iostream>
#ifdef _WIN32
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#endif

class Keyboard {
public:
    Keyboard();
    ~Keyboard();
    int getKey();
    bool isArrowKey(int key);

private:
    void initTerminal();
    void resetTerminal();
#ifndef _WIN32
    struct termios orig_termios;
#endif
};

Keyboard::Keyboard() {
    initTerminal();
}

Keyboard::~Keyboard() {
    resetTerminal();
}

void Keyboard::initTerminal() {
#ifndef _WIN32
    struct termios new_termios;
    tcgetattr(STDIN_FILENO, &orig_termios);
    new_termios = orig_termios;
    new_termios.c_lflag &= ~ICANON;
    new_termios.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
#endif
}

void Keyboard::resetTerminal() {
#ifndef _WIN32
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
#endif
}

int Keyboard::getKey() {
#ifdef _WIN32
    if (_kbhit()) {
        int ch = _getch();
        if (ch == 224) { 
            switch (_getch()) {
                case 72: return 0; 
                case 80: return 1; 
                case 75: return 2; 
                case 77: return 3; 
            }
        }
        return ch;
    }
#else
    int ch = getchar();
    if (ch == 27) { 
        getchar(); 
        switch (getchar()) {
            case 'A': return 0; 
            case 'B': return 1; 
            case 'D': return 2; 
            case 'C': return 3; 
        }
    }
    return ch;
#endif
    return -1; 
}

bool Keyboard::isArrowKey(int key) {
    return key >= 0 && key <= 3; 
}
void clear() {
    std::cout << "\033[2J\033[1;1H"; // ANSI escape codes to clear the screen
}

#endif 
