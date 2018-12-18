#include "Game.h"
#include "Graphics.h"
using namespace std;
screen_mode screen;

//-------------------------------------------------Map Class--------------------------------------//
    Map::Map() = default;
    int gridX, gridY;
    int score;
    int unitSize = 20; //size of each square unit
    int wallSize = 20; //size of the walls

    void Map::gridSize(int w,int h) {
        gridX = w, gridY = h;
    };
    void Map::squareUnit(int x,int y){
        if(x == wallSize || x == gridX-wallSize || y== wallSize+20 || y==gridY-wallSize)
        {
            glColor3f(1,0,0);
            glLineWidth(1.0);
        }
        else
        {
            glColor3f(1.0,1.0,1.0);
            glLineWidth(1.0);
        }
        glBegin(GL_LINES);
        glColor3f(0,0,0);
        glVertex2d(x,y);
        glVertex2d(x+unitSize,y);
        glVertex2d(x+unitSize,y);
        glVertex2d(x+unitSize,y+unitSize);
        glVertex2d(x+unitSize,y+unitSize);
        glVertex2d(x,y+unitSize);
        glVertex2d(x,y+unitSize);
        glVertex2d(x,y);
        glEnd();
    };
    void Map::setupDisplay(){
        for(int x = 0; x < gridX; x++) {
            for(int y = 0; y < gridY; y++) {
                squareUnit(x,y);
                y += unitSize-1;
            }
            x += unitSize-1;
        }

        //Top wall also used as the stat bar on the display
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glColor3f(0.419608, 0.556863, 0.137255);
        glBegin(GL_QUADS);
        glVertex2i(0, 0);
        glVertex2i(0, wallSize+20);
        glVertex2i(gridX, wallSize+20);
        glVertex2i(gridX, 0);
        glEnd();

        //left wall
        glBegin(GL_QUADS);
        glVertex2i(0, 0);
        glVertex2i(0, gridY);
        glVertex2i(wallSize, gridY);
        glVertex2i(wallSize, 0);
        glEnd();

        //right wall
        glBegin(GL_QUADS);
        glVertex2i(gridX-wallSize, 0);
        glVertex2i(gridX, 0);
        glVertex2i(gridX, gridY);
        glVertex2i(gridX-wallSize, gridY);
        glEnd();

        //bottom wall
        glBegin(GL_QUADS);
        glVertex2i(0, gridY);
        glVertex2i(0, gridY-wallSize);
        glVertex2i(gridX, gridY-wallSize);
        glVertex2i(gridX, gridY);
        glEnd();

        // draw a string on to the stat bar
        string stringScore = to_string(score);
        string message = "Score: " + stringScore;
        glColor3f(0.752941, 0.752941, 0.752941);
        glRasterPos2i(wallSize, wallSize + 10);
        for (int i = 0; i < message.length(); ++i) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
        }
        glFlush();  // Render now
    };

    Color Map::getButtonFill() const{
        return buttonFill;
    };
    Button Map::getBpos() const{
        return bpos;
    };
    void Map::setBpos(int x1, int y1, int x2, int y2){
        bpos = {x1, y1, x2, y2};
    };

    void Map::setButtonFill(double r, double g, double b){
        buttonFill = {r,g,b};
    };


    void Map::drawButtons(int buttonNum){
        if(buttonNum == 1) {
            glColor3f(buttonFill.r, buttonFill.g, buttonFill.b);
            string message = "Start New Game";
            glRectd(bpos.x1, bpos.y1, bpos.x2, bpos.y2);
            glColor3f(0, 0, 0);
            glRasterPos2i(gridX / 3, gridY / 2.2);
            for (int i = 0; i < message.length(); ++i) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
            };

            glColor3f(buttonFill.r, buttonFill.g, buttonFill.b);
            glRectd(bpos.x1, bpos.y1 + 60, bpos.x2, bpos.y2 + 60);
            glColor3f(0, 0, 0);
            string restart = "   Reload Game";
            glRasterPos2i(gridX / 3, gridY / 1.8);
            for (int i = 0; i < restart.length(); ++i) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, restart[i]);
            };
        } else if (buttonNum == 2){
            glColor3f(buttonFill.r, buttonFill.g, buttonFill.b);
            glRectd(bpos.x1, bpos.y1 + 100, bpos.x2, bpos.y2 + 100);
            glColor3f(0,0,0);
            string restart =  "Restart";
            glRasterPos2i(207, 330);
            for (int i = 0; i < restart.length(); ++i) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, restart[i]);
            };
        };
    };

    bool Map::buttonOverlap(int x, int y, int buttonNum) const{
        if(buttonNum == 1) { //start new game button
            return(x > bpos.x1 && y > bpos.y1 && x < bpos.x2 && y < bpos.y2);
        } else if(buttonNum == 2) { //resume game button
            return (x > bpos.x1 && y > bpos.y1+60 && x < bpos.x2 && y < bpos.y2+60);
        } else if(buttonNum == 3) { // restart game button
            return (x > bpos.x1 && y > bpos.y1+100 && x < bpos.x2 && y < bpos.y2+100);
        };
    };

    void Map::testMap(){
        setButtonFill(1,2,3);
        setBpos(1,2,3,4);

        if(getButtonFill().r==1 && getButtonFill().g==2 && getButtonFill().b==3){
            if(getBpos().x1==1&&getBpos().y1==2&&getBpos().x2==3&&getBpos().y2==4){

                cout<<"Map class functions online.(1/5)"<<endl;
            }
        }
        else{
            cout<<"Some Map class functions are not working."<<endl;
        }
    }


//-------------------------------------------Food Class (Parent)---------------------------------//

Food::Food() = default;
Food::Food(Color fill){};
bool food = true;
int foodX, foodY;

    Color Food::getFill() const{
        return fill;
    };

    void Food::newCoordinates(int &x, int &y, int n) {
        if(n ==1) {
            int _maxX = (gridX - wallSize) / unitSize;
            int _maxY = (gridY - wallSize) / unitSize;
            int _minX = (wallSize) / unitSize;
            int _minY = (wallSize + 20) / unitSize;
            x = (rand() % (_maxX - _minX) + _minX) * unitSize;
            y = (rand() % (_maxY - _minY) + _minY) * unitSize;

        }else{
            int _maxX = (gridX - wallSize*2) / unitSize;
            int _maxY = (gridY - wallSize*2) / unitSize;
            int _minX = wallSize / unitSize;
            int _minY = (wallSize + 20) / unitSize;
            x = (rand() % (_maxX - _minX) + _minX) * unitSize;
            y = (rand() % (_maxY - _minY) + _minY) * unitSize;
        };

    };


//-------------------------------------------normFood Class (Child)---------------------------------//

    normFood::normFood() = default;

    void normFood::setFill(double r, double g, double b) {
        fill = {r,g,b};
    };

    void normFood::draw() {
        if(food)
            newCoordinates(foodX, foodY, 1);
        food = false;
        glColor3f(fill.r, fill.g, fill.b);
        glRectd(foodX , foodY, foodX + unitSize, foodY + unitSize);

    };

    void normFood::testnFood(){
        setFill(1,2,3);
        if(getFill().r==1 && getFill().g==2&& getFill().b==3){
            cout<<"normFood class functions online.(2/5)"<<endl;
        }
        else{
            cout<<"Some normFood class functions are not working."<<endl;
        }
    }

//-------------------------------------------goodFood Class (Child)---------------------------------//

    goodFood::goodFood() = default;

    void goodFood::setFill(double r, double g, double b) {
        fill = {r,g,b};
    };
    void goodFood::draw() {
        if(food)
            newCoordinates(foodX, foodY, 2);
        food = false;
        glColor3f(fill.r, fill.g, fill.b);
        glRectf(foodX, foodY, foodX + (unitSize*2), foodY + (unitSize*2));

    };
    void goodFood::testgFood(){
        setFill(1,2,3);
        if(getFill().r==1 && getFill().g==2&& getFill().b==3){
         cout<<"goodFood class functions online.(3/5)"<<endl;
      }
      else{
            cout<<"Some goodFood class functions are not working."<<endl;
     }
    }

//------------------------------------------------Snake Class---------------------------------------//

    Snake::Snake() { newSnake(); }

    void Snake::newSnake() {
        direction = RIGHT;
        body.clear();
        body.push_back({200, 200});
        body.push_back({220, 200});
        body.push_back({240, 200});
        body.push_back({260, 200});
        body.push_back({280, 200});
    }

    Color Snake::getFill() const{
        return fill;
    };
    Position Snake::getXY() const {
        return Position();
    }
    int Snake::getSpeed() const{
        return speed;
    };
    int Snake::getDirection() const {
       return direction;
    }
    vector<Position> Snake::getBody() const {
        return body;
    }

    void Snake::setColor(double r, double g, double b){
        fill = {r, g, b};
    };
    void Snake::setXY(int x, int y) {
        body[0].x = x;
        body[0].y = y;
    }
    void Snake::setSpeed(int s){
        speed = s;
    };
    void Snake::setDirection(int d) {
        direction = d;
    }


    void Snake::draw() {

        for (int i = 1; i < body.size(); ++i) {
            if (i == 1) {
                glColor3f(fill.r, fill.g, fill.b);
            } else {
                glColor3f(fill.r, fill.g + 1, fill.b);
            }
            glRectf(body[i].x, body[i].y, body[i].x + unitSize, body[i].y + unitSize);
        }

    }

    void Snake::move() {
            // lead with "head" of snake
            if (direction == UP) { body[0].y -= unitSize; }
            else if (direction == DOWN) { body[0].y += unitSize; }
            else if (direction == LEFT) { body[0].x -= unitSize; }
            else if (direction == RIGHT) { body[0].x += unitSize; }
            else {}

            // align body
            body[0].d = direction;
            for (int i = 1; i < body.size(); ++i) {
                if (body[i-1].x > body[i].x) { body[i].d = RIGHT; }
                else if (body[i-1].x < body[i].x) { body[i].d = LEFT; }
                else if (body[i-1].y > body[i].y) { body[i].d = DOWN; }
                else { body[i].d = UP; }
            }

            // move body
            for (int i = 1; i < body.size(); ++i) {
                if (body[i].d == UP) { body[i].y -= unitSize; }
                else if (body[i].d == DOWN) { body[i].y += unitSize; }
                else if (body[i].d == LEFT) { body[i].x -= unitSize; }
                else if (body[i].d == RIGHT) { body[i].x += unitSize; }
                else {}
            }

    }

    void Snake::eatFood(int n){
        if(n == 1) {
            if (body[1].x == foodX && body[1].y == foodY) {
                score += 10;
                food = true;
                grow();
            };
        }else{
            if (body[1].x == foodX && body[1].y == foodY || body[1].x == foodX+unitSize && body[1].y == foodY+unitSize
                || body[1].x == foodX+unitSize && body[1].y == foodY || body[1].x == foodX && body[1].y == foodY+unitSize) {
                score += 40;
                food = true;
                grow();
            };
        }
    };

    void Snake::CollisionTest(){

        // Wall collision
        if (body[0].x < wallSize || body[0].x > gridX - wallSize-10 || body[0].y < wallSize+30 || body[0].y > gridY-wallSize-10){
          screen = gameover;
        };

        //Snake collision
        for (int i = 2; i < body.size(); ++i) {
            if (body[1].x==body[i].x && body[1].y==body[i].y) {
                screen = gameover;
            }
        }

    };
    void Snake::save() const {

        // let each line (row) in the text file represent a variable
        ofstream f_out("save.txt"); // overwriting file save.txt every save
        if (f_out) {
            f_out << direction << endl;
            f_out << score << endl;
            f_out << foodX << endl;
            f_out << foodY << endl;
            f_out << body.size() << endl;
            for (int i = 0; i < body.size() ; ++i) {
                f_out << body[i].x << endl;
                f_out << body[i].y << endl;
            }
        }
        f_out.close();
    }

    void Snake::load() {
        ifstream f_in;
        f_in.open("save.txt");
        if (f_in) {
            int length = 0;
            int stat;
            int stat2;
            // skip first 5 values
            if (f_in >> stat) { direction = stat; } // direction
            if (f_in >> stat) { score = stat; } // score
            if (f_in >> stat) { foodX = stat; } // food x
            if (f_in >> stat) { foodY = stat; } // food y
            if (f_in >> stat) { length = stat; } // length of body
            body.clear();
            for (int i = 0; i < length ; ++i) {
                //body.push_back(temp);
                if (f_in >> stat) {
                    f_in >> stat2; // if there is an X there must be a Y val
                    body.push_back({stat,stat2});
                }
            }
        }
        f_in.close();
    }

    void Snake::grow() {
        int x = body[body.size()-1].x;
        int y = body[body.size()-1].y;
        if (body[body.size()-1].d == UP) { body.push_back({x, y+unitSize, UP}); }
        else if (body[body.size()-1].d == DOWN) { body.push_back({x, y-unitSize, DOWN}); }
        else if (body[body.size()-1].d == LEFT) { body.push_back({x+unitSize, y, LEFT}); }
        else if (body[body.size()-1].d == RIGHT) { body.push_back({x-unitSize, y, RIGHT}); }
        else {} // impossible
    }

    void Snake::testsnake(){
        setColor(1,2,3);
        setXY(1,2);
        setSpeed(1);
        setDirection(1);
        if(getFill().r==1 && getFill().g==2 && getFill().b==3){

            if(getXY().x==getBody()[0].x && getXY().y==getBody()[0].y){
                cout<<"Snake class functions online.(4/5)"<<endl;

                if(getSpeed()==1){
                    cout<<"Snake class functions online.(4/5)"<<endl;

                    if(getDirection()==1){
                        cout<<"Snake class functions online.(4/5)"<<endl;
                    }
                }
            }
        }
        else{
            cout<<"Some Snake class functions are not working."<<endl;

        }
    }
//-----------------------------------------------Game Class--------------------------------------//

Game::Game() = default;

void Game::clearScreen() {
    score = 0;
}

void Game::testGame(){
    if(score==0){
        cout<<"Game class functions online.(5/5)"<<endl;
    }
}