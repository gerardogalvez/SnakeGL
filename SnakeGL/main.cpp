//
//  main.cpp
//  SnakeGL
//
//  Created by Gerardo Galvez on 23/12/23.
//

#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <queue>
#include <string.h>

#include <GLUT/glut.h>

#include "Position.hpp"
#include "Direction.hpp"
#include "Game.hpp"

const float WINDOW_SIZE = 600;
const int GRID_DIMENSIONS = 30;
const float GAP = 0.01;
const float MARGIN = 0.9;
const float SQUARE_SIZE = MARGIN * 2 / GRID_DIMENSIONS;
const unsigned int TICKS_PER_SECOND = 6;
const unsigned int UPDATE_RATE = 1000 / TICKS_PER_SECOND;

Game game(GRID_DIMENSIONS);

float snakeColors[][3] = {
    {1, 0, 0},
    {1, 0.5, 0},
    {1, 1, 0},
    {0, 1, 0},
    {0, 1, 0.75},
    {0, 0.5, 1},
    {0.5, 0, 1},
    {1, 0, 1},
};

void drawSquare(int i, int j, float r, float g, float b)
{
    glColor3f(r, g, b);
    
    glVertex3f(-MARGIN + SQUARE_SIZE * i + GAP, MARGIN - SQUARE_SIZE * j - GAP, 0); // top left
    glVertex3f(-MARGIN + SQUARE_SIZE * i + GAP, MARGIN - SQUARE_SIZE * (j + 1) + GAP, 0); // bottom left
    glVertex3f(-MARGIN + SQUARE_SIZE * (i + 1) - GAP, MARGIN - SQUARE_SIZE * j - GAP, 0); // top right
    
    glVertex3f(-MARGIN + SQUARE_SIZE * (i + 1) - GAP, MARGIN - SQUARE_SIZE * (j + 1) + GAP, 0); // bottom right
    glVertex3f(-MARGIN + SQUARE_SIZE * i + GAP, MARGIN - SQUARE_SIZE * (j + 1) + GAP, 0); // bottom left
    glVertex3f(-MARGIN + SQUARE_SIZE * (i + 1) - GAP, MARGIN - SQUARE_SIZE * j - GAP, 0); // top right
}


void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Draw text
    glColor3f(1.0, 1.0, 1.0);
    std::string title = "SnakeGL";
    std::string scoreText = "Score: " + std::to_string(game.getScore());
    
    glRasterPos2f(-0.9, -0.97);
    for (int i = 0; i < title.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, title[i]);
    }
    
    glRasterPos2f(0, -0.97);
    for (int i = 0; i < scoreText.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scoreText[i]);
    }
    
    
    
    glBegin(GL_TRIANGLES);
    // Draw snake
    std::deque<Position> snake = game.getSnake();
    std::deque<Position>::iterator iterator;
    int colorIndex = 0;
    for (iterator = snake.begin(); iterator != snake.end(); iterator++) {
        float* color = snakeColors[colorIndex++ % std::size(snakeColors)];
        drawSquare((*iterator).X, (*iterator).Y, color[0], color[1], color[2]);
    }
    
    // Draw food
    Position foodPosition = game.getFoodPosition();
    drawSquare(foodPosition.X, foodPosition.Y, 1, 1, 1);
    glEnd();
    
    // Draw borders
    glBegin(GL_LINES);
    
        glColor3f(1, 1, 1);
        
        glVertex2f(-MARGIN, MARGIN); // top left
        glVertex2f(-MARGIN, -MARGIN); // bottom left
        
        glVertex2f(MARGIN, MARGIN); // top right
        glVertex2f(MARGIN, -MARGIN); // bottom right
        
        glVertex2f(MARGIN, MARGIN); // top right
        glVertex2f(-MARGIN, MARGIN); // top left
        
        glVertex2f(MARGIN, -MARGIN); // bottom right
        glVertex2f(-MARGIN, -MARGIN); // bottom left
    
    glEnd();
    
    glutSwapBuffers();
}

void processSpecialKeys(int key, int x, int y)
{
    Direction direction = game.getDirection();
    switch (key) {
        case GLUT_KEY_UP:
        {
            if (direction != DOWN)
                game.setDirection(UP);
            break;
        }
        case GLUT_KEY_DOWN:
        {
            if (direction != UP)
                game.setDirection(DOWN);
            break;
        }
        case GLUT_KEY_LEFT:
        {
            if (direction != RIGHT)
                game.setDirection(LEFT);
            break;
        }
        case GLUT_KEY_RIGHT:
        {
            if (direction != LEFT)
                game.setDirection(RIGHT);
            break;
        }
        default:
        {
            // NOOP
            break;
        }
    }
}

void updateSnake(int value)
{
    game.updateSnake();
    glutPostRedisplay();
    glutTimerFunc(UPDATE_RATE, updateSnake, value);
}

int main(int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
    glutCreateWindow("SnakeGL");
    
    glutSpecialFunc(processSpecialKeys);
    glutDisplayFunc(renderScene);
    glutTimerFunc(UPDATE_RATE, updateSnake, 1);
    
    glutMainLoop();

    return 1;
}
