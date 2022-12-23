#include "Board.h"

void Board::checkCompleteness()
{
    using f = field;

    //check for draw
    if( getField(lt) * getField(t) * getField(rt) *
        getField(l)  * getField(c) *  getField(r) *
        getField(lb) * getField(b) * getField(rb) )
    {
        winner = mark::draw;
        return;
    }

    //all with center
    {
        mark c = getField(f::c);

        if((c == getField(f::l) && c == getField(f::r)
        ||  c == getField(f::t) && c == getField(f::b)
        ||  c == getField(f::lt) && c == getField(f::rb)
        ||  c == getField(f::rt) && c == getField(f::lb))
            && c != mark::empty)
            winner = c;
    }
    //the rest with lt
    {
        mark lt = getField(f::lt);

        if((lt == getField(f::t) && lt == getField(f::rt)
        ||  lt == getField(f::l) && lt == getField(f::lb))
            && lt != mark::empty)
            winner = lt;
    }
    //the rest with rb
    {
        mark rb = getField(f::rb);

        if((rb == getField(f::r) && rb == getField(f::rt) 
        ||  rb == getField(f::b) && rb == getField(f::lb))
            && rb != mark::empty)
            winner = rb;
    }
}

mark Board::returnWinner() const { return winner; }

void Board::setWinner(mark w) { winner = w; }