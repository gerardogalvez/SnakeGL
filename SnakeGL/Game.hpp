//
//  Game.hpp
//  SnakeGL
//
//  Created by Gerardo Galvez on 26/12/23.
//

#ifndef Game_hpp
#define Game_hpp

#include <queue>
#include <vector>
#include "Position.hpp"
#include "Direction.hpp"
#include "CellStatus.hpp"

class Game
{
private:
    unsigned int _gridSize;
    std::deque<Position> _snake;
    Position _foodPosition;
    Direction _currentDirection;
    unsigned int _score;
    std::vector<std::vector<CellStatus>> _grid;
    
    void updateFoodPosition();
    Position getNextSnakePosition();
    void addToSnakeBack();
    void resetGame();
    
public:
    Game(int gridSize);
    
    int getScore() const;
    std::deque<Position> getSnake() const;
    Position getFoodPosition() const;
    void setDirection(Direction direction);
    Direction getDirection() const;
    void updateSnake();
};

#endif /* Game_hpp */
