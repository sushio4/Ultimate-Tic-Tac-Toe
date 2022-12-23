#include "MasterBoard.h"

MasterBoard::MasterBoard()
{
    active = field::lt;
    requiredOuter = field::no;
    boards[active].active = field::lt;
}

mark MasterBoard::getField(field f) const
{
    return boards[f].returnWinner();
}

bool MasterBoard::placeMark()
{
    field fOuter = active;

    if (boards[fOuter].returnWinner() != mark::empty)
        return false;

    if (active != fOuter && boards[active].returnWinner() == mark::empty)
        return false;

    bool validMove = boards[fOuter].placeMark(current);

    if (!validMove)
        return false;

    checkCompleteness();

    if(current == mark::o) current = mark::x;
    else current = mark::o;

    requiredOuter = boards[fOuter].active;
    if(boards[requiredOuter].returnWinner()) requiredOuter = field::no;
    else
    {
        boards[active].active = field::no;
        active = requiredOuter;
        boards[active].active = field::lt;
    }

    return true;
}

std::string MasterBoard::getDisplayStr() const
{
    std::string output = "\033[2;3f";
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            output += boards[x + 3 * y].getDisplayStr((x + 3 * y == active || requiredOuter == field::no) && !boards[x+3*y].winner);
            // draw vertical line
            if (x < 2)
                output += "\033[107m\033[12C  \033[1B\033[2D  \033[1B\033[2D  \033[1B\033[2D  \033[1B\033[2D  \033[4A\033[0m ";
        }
        // horizontal line
        if (y < 2)
            output += "\033[30D\033[6B\033[107m                                         \033[41D\033[2B\033[0m";
    }

    return output + "\033[7B\033[30D";
}

void MasterBoard::moveUp()
{
    field subField = boards[active].active;

    if(subField == field::no) boards[active].active = lt;

    //if its not in the top 3
    if (subField >= 3)
    {
        boards[active].active = (field)(subField - 3);
        return;
    }

    //if you can't move the outer
    if (requiredOuter != field::no || active < 3)
        return; 

    // go one outer up
    boards[active].active = field::no;
    active = (field)(active - 3);

    // place active there
    boards[active].active = (field)(subField + 6);  
}

void MasterBoard::moveDown()
{
    field subField = boards[active].active;

    if(subField == field::no) boards[active].active = lt;

    //if its not in the bottom 3
    if(subField < 6)
    {
        boards[active].active = (field)(subField + 3);
        return;
    }

    //if it can't move the outer
    if(requiredOuter != field::no || active >= 6)
        return;

    
    boards[active].active = field::no;
    active = (field)(active + 3);

    boards[active].active = (field)(subField - 6);
}

void MasterBoard::moveLeft()
{
    field subField = boards[active].active;

    if(subField == field::no) boards[active].active = lt;

    // if not the left 3
    if(subField % 3)
    {
        boards[active].active = (field)(subField - 1);
        return;
    }

    if(requiredOuter != field::no || active % 3 == 0)
        return;

    boards[active].active = field::no;
    active = (field)(active - 1);

    boards[active].active = (field)(subField + 2);
}

void MasterBoard::moveRight()
{
    field subField = boards[active].active;

    if(subField == field::no) boards[active].active = lt;

    // if not the rightmost 3
    if(subField % 3 < 2)
    {
        boards[active].active = (field)(subField + 1);
        return;
    }

    if(requiredOuter != field::no || active % 3 == 2)
        return;

    boards[active].active = field::no;
    active = (field)(active + 1);

    boards[active].active = (field)(subField - 2);
}

std::string MasterBoard::returnCurrent() const
{
    return MiniBoard::markMap[current];
}