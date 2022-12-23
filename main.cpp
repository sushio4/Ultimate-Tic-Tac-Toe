#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "MasterBoard.h"

void turnOffBuffering()
{
    termios t;
    tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
    t.c_lflag &= ~ICANON; //Manipulate the flag bits to do what you want it to do
    tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
}

void turnOnBuffering()
{
    termios t;
    tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
    t.c_lflag |= ICANON; //Manipulate the flag bits to do what you want it to do
    tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
}

int main(int argc, char**argv)
{
    MasterBoard b;  
    turnOffBuffering();
    
    std::cout << "\033[2J";
    std::cout << b.getDisplayStr() << "Now Placing " << b.returnCurrent() << '\n';

    while(true)
    {
        wint_t ch = std::getwchar();
        if(ch == 27)
        {
            std::getwchar();
            ch = std::getwchar();
        }

        std::cout << "\033[2J";
        std::string displayStr = "";
        
        switch(ch)
        {
        case 10:
            b.placeMark();
            break;
        case 'q':
            turnOnBuffering();
            std::cout << "\033[2J" << b.getDisplayStr();
            exit(0);
            break;
        case 65:
            b.moveUp();
            break;
        case 66:
            b.moveDown();
            break;
        case 67:
            b.moveRight();
            break;
        case 68:
            b.moveLeft();
            break;
        default:
            std::cout << ch;
        }

        displayStr += b.getDisplayStr();

        if(b.returnWinner())
        {
            displayStr += "\n   GAME OVER!\n   The winner is: " + MiniBoard::markMap[b.returnWinner()];
            std::cout << displayStr << std::endl;
            exit(0);
        }

        std::cout << displayStr << "Now Placing " << b.returnCurrent() << '\n';
    }

    turnOnBuffering();
    return 0;
}