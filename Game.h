
#ifndef SNAKE_H
#define SNAKE_H

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

#define STOP 0
#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2
/**
 * enum set game status
 */
enum screen_mode {start, game, gameover, resume};
/**
 * position struct class
 */
struct Position {
    int x;
    int y;
    int d;
};
/**
 * Button struct class
 */
struct Button {
    int x1;
    int y1;
    int x2;
    int y2;
};
/**
 * color struct class
 */
struct Color {
    double r;
    double g;
    double b;
};

//-------------------------------------------------Map Class--------------------------------------//
class Map {
private:
    Color buttonFill;
    Button bpos;
public:
    Map();

    /**
     * Requires: button fill and button position
     * Modifies: nothing
     * Effects: getters for button position and fill
     */
    Color getButtonFill() const;
    Button getBpos() const;

    /**
     * Requires: button position and color numbers
     * Modifies: nothing
     * Effects: setter's for the button position and the button fill
     */
    void setBpos(int x1, int y1, int x2, int y2);
    void setButtonFill(double r, double g, double b);

    /**
     * Requires: the button number to be drawn
     * Modifies: nothing
     * Effects: draws the buttons
     */
    void drawButtons(int buttonNum);

    /**
     * Requires: mouse x and y coordinates as well as the button number tested
     * Modifies: nothing
     * Effects: mouse over lap
     */
    bool buttonOverlap(int x, int y, int buttonNum) const;
    /**
     * Requires: squareUnit
     * Modifies: nothing
     * Effects: set's up the default game display (adds walls, grid, score count)
     */
    virtual void setupDisplay();
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: creates one square unit which is used in setupDisplay to create a grid
     */
    virtual void squareUnit(int x,int y);

    /**
     * Requires: width and height
     * Modifies: nothing
     * Effects:  pretty much a getter for the grid width and height specified in Graphics.cpp
     */
    virtual void gridSize(int w,int h);

    void testMap();

};
//-------------------------------------------Food Class (Parent)---------------------------------//

class Food {
protected:
    Color fill;
public:
    //default constructors
    Food();
    Food(Color fill);

    /**
    * Requires: nothing
    * Modifies: nothing
    * Effects:  gets the food fill
    */
    virtual Color getFill() const;

    /**
    * Requires: the paramaters
    * Modifies: fill
    * Effects: pure virtual method for the food fill
    */
    virtual void setFill(double r, double g, double b) = 0;
    /**
    * Requires: integer reference
    * Modifies: xy coordinates
    * Effects: generates random coordinates for the food. Generates coordinates that are only within the grid
    */
    virtual void newCoordinates(int &x, int &y, int n);

    /**
    * Requires: food rect
    * Modifies: nothing
    * Effects: draws the food
    */
    virtual void draw() = 0;
};

//-------------------------------------------normFood Class (Child)---------------------------------//
class normFood : public Food {
public:
    //default constructor
    normFood();

    /**
    * Requires: nothing
    * Modifies: overrides the fill of the food ofject
    * Effects:  color
    */
    void setFill(double r, double g, double b) override;

    /**
    * Requires: food rect
    * Modifies: nothing
    * Effects: draws the food
    */
    void draw() override;
    void testnFood();
};

//-------------------------------------------goodFood Class (Child)---------------------------------//
class goodFood : public Food {
public:
    //default constructor
    goodFood();

    /**
     * Requires: nothing
     * Modifies: overrides the fill of the food ofject
     * Effects:  color
     */
    void setFill(double r, double g, double b) override;


    /**
    * Requires: nothing
    * Modifies: nothing
    * Effects: draws the food
    */
    void draw() override;
    void testgFood();
};

//-------------------------------------------Snake Class---------------------------------//
class Snake {
private:
    Color fill;
    Position xy;
    int direction;
    int speed;
    vector<Position> body;
public:
    //default constructors
    Snake();

    void newSnake();

    /**
    * Requires: nothing.
    * Modifies: nothing
    * Effects: getters for fill, xy coordinates, speed, direction and body position
    */
    Color getFill() const;
    Position getXY() const;
    int getSpeed() const;
    int getDirection() const;
    vector<Position> getBody() const;

    /**
    * Requires: The parameters for each setter respectively
    * Modifies: fill, coordinates, speed and direction
    * Effects: setters for the fill, xy coordiantes, speed and direction of the snake
    */
    void setColor(double r, double g, double b);
    void setXY(int x, int y);
    void setSpeed(int s);
    void setDirection(int d);

    /**
    * Requires: nothing
    * Modifies: nothing
    * Effects:  save the game
    */
    void save() const;

    /**
    * Requires: nothing
    * Modifies: nothing
    * Effects: load game from save
    */
    void load();

    /**
     * Requires: coordinates
     * Modifies: directions
     * Effects: changes the direction the snake is going to move
     */
     void move();

    /**
     * Requires: body
     * Modifies: nothing
     * Effects: draws the snake body
     */
     void draw();

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects:  checks to see if the food and snake head overlap if they do ads to score and increases snake size
     */
     void eatFood(int n);

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: checks to see is the snake had hit any wall and if it has game over
     */
     void CollisionTest();

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: increases the snake body size everytime the snake eats food
     */
     void grow();
     void testsnake();
};

//-------------------------------------------Game Class---------------------------------//
class Game {
public:
    //default constructor
    Game();

    /**
    * Requires: nothing
    * Modifies: nothing
    * Effects:  clears game progress to start a new game from beginning
    */
    virtual void clearScreen();
    void testGame();
};

#endif //SNAKE_H
