#include "MiniBoard.h"

class MasterBoard : public Board
{
public:
    MasterBoard();

    bool placeMark();
    mark getField(field f) const;
    std::string getDisplayStr() const;

    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();

    std::string returnCurrent() const;

private:
    MiniBoard boards[9];
    field requiredOuter = field::no;
    mark current = mark::o;
};