#include "Board.h"

class MiniBoard : public Board
{
    friend class MasterBoard;

public:
    bool placeMark(mark m);
    mark getField(field f) const;
    std::string getDisplayStr(bool isActive) const;
    std::string getDisplayWinnerStr() const;

    const static std::string markMap[4];

private:
    mark board[9] = {(mark)0};
};
