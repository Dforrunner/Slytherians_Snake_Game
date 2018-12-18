#include "Graphics.h"
#include "Game.h"

GLint width, height;
int wd;
Game g,gT;
Snake snake,snakeT;
Map map,mapT;
normFood nFood,nFoodT;
goodFood gFood,gFoodT;
extern int unitSize;
extern int wallSize;
extern screen_mode screen;
extern int score;
extern bool food;
int BUTTON_COUNTER = 1;

void init() {
    screen = start;
    width = 500;
    height = 520;
    //int textPosX1 = 140 , textPosY1 = 200, textPosX2 = 350, textPosY2 = 250;
    map.gridSize(width, height);
    map.setBpos(140,200,350,250);

    snake.setSpeed(120); //set's the speed at which the snake is moving using timer
    snake.setColor(1, 0.5, 0); //set's the snake colors

    nFood.setFill(0,0,1); //set normal food color
    gFood.setFill(0,5,2); //set good food color
    //food.setFoodPosition(100,100);
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background foodColor
    glClearColor(0.184314f, 0.309804f, 0.184314f, 1.0f); //green 0.419608, 0.556863, 0.137255
}

double red , green ,blue;
void display_start() {
    string intro = "SNAKE GAME";
    glColor3f(2, 1, 0);
    glRasterPos2i(width/3, height/3);
    for (int i = 0; i < intro.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, intro[i]);
    }
    map.drawButtons(1); //start new game and continue game buttons
};

void generateFood(){
    int bonus = 50;
    int bonus2 = 150;
    int bonus3 = 250;
    int bonus4 = 350;
    if (score == bonus ||score == bonus2 ||score == bonus3 || score == bonus4) {
        gFood.draw(); // draw food
        snake.eatFood(2); //call eat food condition
    } else {
        nFood.draw(); // draw food
        snake.eatFood(1);
    };
};

void display_game() {
    generateFood();
    snake.CollisionTest();
    snake.draw(); // draws snake
    map.setupDisplay(); //sets up the grid map, walls and the stat bar
};

void resume_game(){
    generateFood();
    snake.draw(); // draws snake
    snake.CollisionTest();
    map.setupDisplay(); //sets up the grid map, walls and the stat bar
};

void game_over(){
    string stringScore = to_string(score);
    string message = "GAME OVER";
    glColor3f(1, 1, 1);
    glRasterPos2i(width/3, height/3);
    for (int i = 0; i < message.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    };

    string lastScore =  "Score: " + stringScore;
    glRasterPos2i(width/2.5, height/2);
    for (int i = 0; i < lastScore.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, lastScore[i]);
    };

    map.drawButtons(2); //restart button
};

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height);

    // do an orthographic parallel projection with the foodPosition
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);   // Clear the foodColor buffer with current clearing foodColor


    /**
     * Draw here
     */
    switch(screen) {
        case start: display_start();
            break;
        case game: display_game();
            break;
        case resume: resume_game();
            break;
        case gameover: game_over();
            break;

    };
    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y)
{
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }
    else if (key == 32) {
        snake.save();
        snake.setDirection(STOP);
        screen = start;
    }
    else if (key == 112) {
        screen = start;
    }

    glutPostRedisplay();
};

void kbdS(int key, int x, int y) {
    // move Rectangle r1 with the arrow keys
    switch(key) {
        case GLUT_KEY_DOWN:
            if(snake.getDirection() != UP && (screen == game,resume) && BUTTON_COUNTER > 1)
                snake.setDirection(DOWN);
                BUTTON_COUNTER = 1;
            break;
        case GLUT_KEY_LEFT:
            if(snake.getDirection() != RIGHT && (screen == game,resume) && BUTTON_COUNTER > 1)
                snake.setDirection(LEFT);
                BUTTON_COUNTER = 1;
            break;
        case GLUT_KEY_RIGHT:
            if(snake.getDirection() != LEFT && (screen == game,resume) && BUTTON_COUNTER > 1)
                snake.setDirection(RIGHT);
                BUTTON_COUNTER = 1;
            break;
        case GLUT_KEY_UP:
            if(snake.getDirection() != DOWN && (screen == game,resume) && BUTTON_COUNTER > 1)
                snake.setDirection(UP);
                BUTTON_COUNTER = 1;
            break;
    };

    glutPostRedisplay();
};

void cursor(int x, int y) {
    if(screen == start || screen == gameover) {
        if (map.buttonOverlap(x, y, 1) || map.buttonOverlap(x, y, 2) || map.buttonOverlap(x, y, 3)) {
            map.setButtonFill(1, 1, 1);
        } else{
            map.setButtonFill(2, 3, 0);
        };

    };

    glutPostRedisplay();
};

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {


    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && screen == start) {
        if(map.buttonOverlap(x, y, 1)){ //Start new game button
            g.clearScreen();
            snake.newSnake();
            screen = game;
        }else if(map.buttonOverlap(x, y, 2)){ //continue game button
            g.clearScreen();
            snake.load();
            screen = resume;
        };
    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && screen == gameover){
        if(map.buttonOverlap(x, y, 3)) {// restart game button
            g.clearScreen(); // clears game progress to start a new game from beginning
            snake.newSnake();
            screen = game;
        };
    };

    glutPostRedisplay();
}

void timer(int) {

    if (screen == game,resume) { ++BUTTON_COUNTER; snake.move(); } // continuously moves snake
    glutPostRedisplay();
    glutTimerFunc((unsigned int) snake.getSpeed(), timer, 0);

}

/* Main function: GLUT runs as a console application starting at main()  */
int graphicsPlay(int argc, char** argv) {
    init();

    mapT.testMap();
    nFoodT.testnFood();
    gFoodT.testgFood();
    snakeT.testsnake();
    gT.testGame();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(400, 150); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Snake Game" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, timer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}