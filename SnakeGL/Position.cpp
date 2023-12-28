//
//  Position.cpp
//  SnakeGL
//
//  Created by Gerardo Galvez on 24/12/23.
//

#include "Position.hpp"

Position::Position() : Position(0, 0)
{
}

Position::Position(int x, int y)
{
    this->X = x;
    this->Y = y;
}
