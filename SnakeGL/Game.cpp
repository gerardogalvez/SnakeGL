//
//  Game.cpp
//  SnakeGL
//
//  Created by Gerardo Galvez on 26/12/23.
//

#include "Game.hpp"

void Game::updateFoodPosition()
{
    int x;
    int y;
    do
    {
        x = rand() % _gridSize;
        y = rand() % _gridSize;
    } while (_grid[x][y] != AVAILABLE);
    
    _foodPosition = Position(x, y);
    _grid[x][y] = FOOD;
};

void Game::resetGame()
{
    _snake.clear();
    _currentDirection = UP;
    _score = 0;
    
    for (int i = 0; i < _gridSize; i++) {
        for (int j = 0; j < _gridSize; j++) {
            _grid[i][j] = AVAILABLE;
        }
    }
    
    Position initialSnakePosition = Position(_gridSize / 2, _gridSize / 2);
    _snake.push_back(initialSnakePosition);
    _grid[initialSnakePosition.X][initialSnakePosition.Y] = SNAKE;
    
    updateFoodPosition();
}

void Game::updateSnake()
{
    Position back = _snake.back();
    _grid[back.X][back.Y] = AVAILABLE;
    
    Position newPos = getNextSnakePosition();
    _snake.pop_back();
    _snake.push_front(newPos);
}

Position Game::getNextSnakePosition()
{
    Position front = _snake.front();
    Position nextPosition;
    switch (_currentDirection) {
        case UP:
            nextPosition = front.Y == 0 ?
                Position(front.X, _gridSize - 1) :
                Position(front.X, front.Y - 1);
            break;
        case DOWN:
            nextPosition = front.Y == _gridSize - 1 ?
                Position(front.X, 0) :
                Position(front.X, front.Y + 1);
            break;
        case LEFT:
            nextPosition = front.X == 0 ?
                Position(_gridSize - 1, front.Y) :
                Position(front.X - 1, front.Y);
            break;
        case RIGHT:
            nextPosition = front.X == _gridSize - 1 ?
                Position(0, front.Y) :
                Position(front.X + 1, front.Y);
            break;
        default:
            break;
    }
    
    // End game if snake hits itself
    if (_grid[nextPosition.X][nextPosition.Y] == SNAKE)
    {
        resetGame();
        return _snake.front();
    }
    
    // Add a new section to the snake
    if (_grid[nextPosition.X][nextPosition.Y] == FOOD)
    {
        addToSnakeBack();
        updateFoodPosition();
        _score++;
    }
    
    _grid[nextPosition.X][nextPosition.Y] = SNAKE;
    return nextPosition;
}

void Game::addToSnakeBack()
{
    Position newPosition = _snake.back();
    _grid[newPosition.X][newPosition.Y] = SNAKE;
    _snake.push_back(newPosition);
}

void Game::setDirection(Direction direction)
{
    _currentDirection = direction;
}

Direction Game::getDirection() const { return _currentDirection; }
std::deque<Position> Game::getSnake() const { return _snake; }
Position Game::getFoodPosition() const { return _foodPosition; }
int Game::getScore() const { return _score; }

Game::Game(int gridSize)
{
    _gridSize = gridSize;
    _grid = std::vector<std::vector<CellStatus>>(_gridSize, std::vector<CellStatus>(_gridSize, AVAILABLE));
    _snake = std::deque<Position>();
    
    resetGame();
}
