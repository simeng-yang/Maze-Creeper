#include "Cell.h"

//Constructor: initialize char and "stat" variables
Cell::Cell(int r, int c, char symbol):r(r), c(c), symbol(symbol), counter(1)
{

}

//Returns the row of the cell in the maze
int Cell::GetRow()
{
    return r;
}

//Returns the column of the cell in the maze
int Cell::GetColumn()
{
    return c;
}

//Returns the associated symbol of the cell in the maze
char Cell::GetChar()
{
    return symbol;
}

//Increment the counter
void Cell::IncrementCounter()
{
    counter++;
}

//Return the counter of the cell for number of visits
char Cell::GetCounter()
{
    return (char)counter + '0';
}

//Set or change the char of the cell
void Cell::SetChar(char toReplace)
{
    symbol = toReplace;
}

Cell::~Cell()
{

}
