#include "MiniBoard.h"

const std::string MiniBoard::markMap[] = {"   ", "\033[94m O \033[0m", "\033[91m X \033[0m", "DRAW"};

bool MiniBoard::placeMark(mark m)
{
    if(winner != mark::empty || active == field::no) return false;

    if(board[active] != mark::empty) return false;

    board[active] = m;

    checkCompleteness();

    return true;
}

mark MiniBoard::getField(field f) const { return board[f]; }

std::string MiniBoard::getDisplayStr(bool isActive) const
{
    std::string output = "";

    for(int y = 0; y <3; y++)
    {
        for(int x = 0; x < 3; x++)
        {
            if(x + 3 * y == active) output += "\033[42m";

            output += markMap[board[x + 3*y]];
            if(isActive) output += "\033[92m";

            if(x + 3 * y == active) output += "\033[49m";

            if(x < 2) output += '|';
        }

        ///move cursor left 5 places and down 1 place, write ----- and do it again
        if(y < 2) output += "\033[11D\033[1B-----------\033[11D\033[1B";
    }

    //return to the starting pos
    output += "\033[4A\033[11D\033[0m";

    return output + getDisplayWinnerStr();
}

std::string MiniBoard::getDisplayWinnerStr() const
{
    std::string output = "";
    if(winner == mark::o)
    {
        //blue bg color, 4 forward
        output += "\033[104m\033[3C     ";
        //just next lines of an O...
        output += "\033[7D\033[1B   \033[0m   \033[104m   ";

        output += "\033[10D\033[1B   \033[0m     \033[104m   ";

        output += "\033[10D\033[1B   \033[0m   \033[104m   ";
        
        output += "\033[7D\033[1B     ";
        //return
        output += "\033[8D\033[4A\033[0m";
    }
    else if(winner == mark::x)
    {
        //red bg color
        output += "\033[101m";

        for(int y = 0; y < 5; y++)
            //one back and one down
            output += "   \033[1D\033[1B";

        //five up and two back
        output += "\033[5A\033[2D";

        for(int y = 0; y < 5; y++)
        {
            //five back and one down
            output += "   ";
            if(y < 4) output += "\033[5D\033[1B";
        }

        //return
        output += "\033[3D\033[4A\033[0m";
    }

    return output;
}