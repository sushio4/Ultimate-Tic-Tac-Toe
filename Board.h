#pragma once
#include "types.h"
#include <string>
#include <iostream>

class Board
{
protected:
    mark winner = mark::empty;
    field active = field::no;

public:
    void checkCompleteness();
    mark returnWinner() const;
    void setWinner(mark w);
    virtual mark getField(field f) const = 0;
};
