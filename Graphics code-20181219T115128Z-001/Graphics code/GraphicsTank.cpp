///TANK SHOOTER
///PREPARED BY:
///NAFISUL ISLAM NAZMI (15-29550-2)
///ESHREAT JAHAN  (14-27975-3)
///MD. GOLAM RAHAMAN (14-27496-3)
///ESMET ZERIN (15-29544-2)


#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <setjmp.h>
using namespace std;
static jmp_buf jmpbuf;
static int jmp_set = FALSE;

int screen_width, screen_height;
bool welcome = 1, game = 0, over = 0, pause = 0;
int startx, starty;
int tankx = 30, tanky, tankl = 120;
vector<pair<int, int> > fire;
int enemytankx[10], enemytanky[10];
int tankw = 200, tankh = 150;
int score = 10;


int tankSpeed = 10;
int fireSpeed = 20;
int sleep = 1;
int tanks = 5;
int modulo = 600;

void myInit (void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(20.0);
    glLineWidth(5.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, screen_width, 0.0, screen_height);

}

void welcomeScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);
    string welcome_text = "Welcome to Tank Shooter game.\nInstructions:\n";
    welcome_text += "1. Use A, S, W, D to control your tank.\nA = left\nD = right\nW = up\nS = down\n";
    welcome_text += "2. Use SpaceBar / LMB to shoot.\n";
    welcome_text += "3. To avoid collision with enemy tanks, you can either destroy enemy tanks by shooting it or simply dodging it.\n";
    welcome_text += "4. Shooting the enemy tank will give you 20 points, whereas dodging it will give 10 points.\n";
    welcome_text += "5. Press Esc to quit the game.\n";
    welcome_text += "6. Press P to pause/resume.\n";
    memset(enemytankx, -1, sizeof(enemytankx));
    memset(enemytanky, -1, sizeof(enemytanky));
    fire.clear();
    score = 0;
    tankx = 30;
    tanky = screen_height / 2 - tankh / 2;


    int x = 50, y = screen_height - 50;
    int len = welcome_text.size();
    glColor3ub(0, 0, 0);
    glRasterPos2i(x, y);
    for(int i = 0; i < len; i++)
    {
        if(welcome_text[i] == '\n')
        {
            y -= 30;
            glRasterPos2i(x, y);
        }

        else
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, welcome_text[i]);
    }


    int w = 200, h = 100;
    startx = screen_width / 2 - w / 2;
    starty = screen_height / 4;

    glBegin(GL_QUADS);
    glVertex2i(startx, starty);
    glVertex2i(startx + w, starty);
    glVertex2i(startx + w, starty + h);
    glVertex2i(startx, starty + h);
    glEnd();

    string start = "Start Game";
    len = start.size();
    glColor3ub(255, 255, 255);
    glRasterPos2i(startx + 40, starty + 40);
    for(int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, start[i]);
    }
    glFlush();

}































void drawTank(int x, int y, int type)
{
    if(type == 1)
        glColor3ub(35, 108, 23);
    else
        glColor3ub(131, 33, 36);
    //glLineWidth(5);

    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x + tankw, y);
    glVertex2i(x + tankw, y + tankh);
    glVertex2i(x, y + tankh);
    glEnd();

    int tempw = 50, temph = 40;
    if(type == 1)
        glColor3ub(0, 255, 0);
    else
        glColor3ub(255, 0, 0);
    glBegin(GL_QUADS);
    glVertex2i(x + tempw, y + temph);
    glVertex2i(x + tankw - tempw, y + temph);
    glVertex2i(x + tankw - tempw, y + tankh - temph);
    glVertex2i(x + tempw, y + tankh - temph);
    glEnd();

    //glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2i(x + tankw - tempw, y + tankh / 2);
    if(type == 1)
        glVertex2i(x + tankw - tempw + tankl, y + tankh / 2);
    else
        glVertex2i(x + tempw - tankl, y + tankh / 2);

    glEnd();
    glFlush();

}

void drawFire()
{
    glColor3ub(255, 255, 0);
    glBegin(GL_POINTS);
    for(int i = 0; i < fire.size(); i++)
        glVertex2i(fire[i].first, fire[i].second);

    glEnd();
    glFlush();
}

bool opponentCollision(int n)
{
    int x = enemytankx[n] - tankl, y = enemytanky[n], xl = enemytankx[n] + tankw, yl = enemytanky[n] + tankh;
    int tempx, tempy, tempxl, tempyl;
    for(int i = 0; i < tanks; i++)
    {
        if(i == n || enemytankx[i] == -1 || enemytanky[i] == -1)
            continue;
        tempx = enemytankx[i] - tankl;
        tempy = enemytanky[i];
        tempxl = enemytankx[i] + tankw;
        tempyl = enemytanky[i] + tankh;
        if(((x >= tempx && x <= tempxl) || (xl >= tempx && xl <= tempxl)) && ((y >= tempy && y <= tempyl) || (yl >= tempy && yl <= tempyl)))
        {
            return false;
        }

    }
    return true;
}

void generate_tank(int n)
{
    do
    {
        enemytankx[n] = screen_width + rand() % modulo;
        enemytanky[n] = rand() % (screen_height - tankh);
        //cout << n << ": " << enemytankx[n] << " " << enemytanky[n] << endl;
    } while(!opponentCollision(n));


}

void translate()
{
    for(int i = 0; i < tanks; i++)
    {
        enemytankx[i] -= tankSpeed;
        if(enemytankx[i] + tankw < 0)
        {

            enemytankx[i] = -1;
            enemytanky[i] = -1;
            score += 10;

        }

    }
    for(int i = 0; i < fire.size(); i++)
    {
        fire[i].first += fireSpeed;
        if(fire[i].first > screen_width)
        {
            fire.erase(fire.begin() + i);
            i--;
        }
    }

    glutPostRedisplay();
}

void fireCollision()
{
    bool temp;
    int fx, fy, tx, ty, txl, tyl;
    for(int i = 0; i < fire.size(); i++)
    {
        temp = 0;
        fx = fire[i].first;
        fy = fire[i].second;
        for(int j = 0; j < tanks; j++)
        {
//            tx = enemytankx[j] - tankl + 100;
            if(enemytankx[j] == -1 || enemytanky[j] == -1)
                continue;
            tx = enemytankx[j];
            txl = enemytankx[j] + tankw;
            ty = enemytanky[j];
            tyl = enemytanky[j] + tankh;
            if(fx >= tx && fx <= txl && fy >= ty && fy <= tyl)
            {


                enemytankx[j] = -1;
                enemytanky[j] = -1;
                fire.erase(fire.begin() + i);
                temp = 1;
                score += 20;

            }

        }
        if(temp)
            i--;
    }
}

void tankCollision()
{
    int tx, txl, ty, tyl;
//    int x = tankx, xl = tankx + tankw + tankl - 60;
    int x = tankx, xl = tankx + tankw;
    int y = tanky, yl = tanky + tankh;
    for(int i = 0; i < tanks; i++)
    {
//        tx = enemytankx[i] - tankl + 60;
        if(enemytankx[i] == -1 || enemytanky[i] == -1)
            continue;
        tx = enemytankx[i];
        txl = tx + tankw;
        ty = enemytanky[i];
        tyl = ty + tankh;
        if(((x >= tx && x <= txl) || (xl >= tx && xl <= txl)) && ((y >= ty && y <= tyl) || (yl >= ty && yl <= tyl)))
        {

            welcome = 0;
            game = 0;
            pause = 0;
            over = 1;
        }
    }

}

void drawRoad()
{
    glColor3ub(100, 100, 100);
    glBegin(GL_QUADS);
    glVertex2i(0, 0);
    glVertex2i(screen_width, 0);
    glVertex2i(screen_width, screen_height);
    glVertex2i(0, screen_height);
    glEnd();

    glLineWidth(20);
    glColor3ub(255, 255, 255);
    glBegin(GL_LINES);
    glVertex2i(0, screen_height / 2);
    glVertex2i(screen_width, screen_height / 2);
    glVertex2i(0, screen_height / 4);
    glVertex2i(screen_width, screen_height / 4);
    glVertex2i(0, 3 * screen_height / 4);
    glVertex2i(screen_width, 3 * screen_height / 4);
    glEnd();
    glLineWidth(5);
    glFlush();
}

void drawScore()
{
    string message = "SCORE: ";
    int x = screen_width - 300;
    int y = screen_height - 100;
    glColor3ub(255, 255, 255);
    int len = message.size();
    glRasterPos2i(x, y);
    for(int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }

    char buffer[20];
    sprintf(buffer, "%d", score);
    len = strlen(buffer);
    for(int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buffer[i]);
    }
    glFlush();
}

void gameScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawRoad();
    drawTank(tankx, tanky, 1);
    for(int i = 0; i < tanks; i++)
    {
        if(enemytankx[i] == -1 || enemytanky[i] == -1)
            generate_tank(i);

        drawTank(enemytankx[i], enemytanky[i], 2);
    }
    drawFire();
    drawScore();
    if(!pause)
    {
        fireCollision();
        tankCollision();
        Sleep(sleep);
        translate();
    }
}

void overScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);
    string message = "GAME OVER";
    int x = screen_width / 2 - 50, y = screen_height / 2 + 100;
    int len = message.size();
    glColor3ub(255, 0, 0);
    glRasterPos2i(x, y);
    for(int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }
    message = "YOUR SCORE: ";
    x -= 20;
    y -= 100;
    glColor3ub(0, 255, 0);
    len = message.size();
    glRasterPos2i(x, y);
    for(int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }

    char buffer[20];
    sprintf(buffer, "%d", score);
    len = strlen(buffer);
    for(int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buffer[i]);
    }

    int w = 200, h = 100;
    startx = screen_width / 2 - w / 2 + 20;
    starty = screen_height / 4;

    glBegin(GL_QUADS);
    glVertex2i(startx, starty);
    glVertex2i(startx + w, starty);
    glVertex2i(startx + w, starty + h);
    glVertex2i(startx, starty + h);
    glEnd();

    message = "Go Back";
    len = message.size();
    glColor3ub(255, 255, 255);
    glRasterPos2i(startx + 55, starty + 40);
    for(int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }
    glFlush();
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if(welcome)
    {
        welcomeScreen();
    }
    else if(game)
    {
        gameScreen();
    }

    else if(over)
    {
        overScreen();
    }



}

void keyboard(unsigned char key, int x, int y)
{
    if(key == 27)
        exit(0);

    if(game)
    {
        if(key == 'a' && !pause)
        {
            tankx -= tankSpeed;
            if(tankx < 0)
                tankx = 0;
        }
        else if(key == 's'  && !pause)
        {
            tanky -= tankSpeed;
            if(tanky < 0)
                tanky = 0;
        }
        else if(key == 'd'  && !pause)
        {
            tankx += tankSpeed;
            if(tankx + tankw + tankl > screen_width)
                tankx = screen_width - tankw - tankl;
        }
        else if(key == 'w'  && !pause)
        {
            tanky += tankSpeed;
            if(tanky + tankh > screen_height)
                tanky = screen_height - tankh;
        }
        else if(key == ' ' && !pause)
        {
            fire.push_back(make_pair(tankx + tankw + tankl - 40, tanky + (tankh / 2)));
        }
        else if(key == 'p')
        {
            pause = !pause;
        }
        glutPostRedisplay();
    }

}

void mouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(game && !pause)
            fire.push_back(make_pair(tankx + tankw + tankl - 40, tanky + (tankh / 2)));

        else if(x >= startx && x <= startx + 200 && y <= screen_height - starty && y >= screen_height - starty - 100)
        {
            if(welcome)
            {
                welcome = 0;
                over = 0;
                game = 1;
                pause = 0;
            }
            else if(over)
            {
                welcome = 1;
                over = 0;
                game = 0;
                pause = 0;
            }
            glutPostRedisplay();
        }
    }
}







#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <GL/glut.h>



//#pragma region



float posX = 0, posY = 0, posZ = 0;
float missileStartPosY = 0;

int x1 = 0;
int x2 = 0;
int y1 = 0;
int y2 = 100;

//plane Left collision points
int planeLeftX = 0;
int planeLeftY = 0;

int planeLeftBodyX = 0;
int planeLeftBodyY = 0;

int planeLeftWingUp1X = 0;
int planeLeftWingUp1Y = 0;

int planeLeftWingUp2X = 0;
int planeLeftWingUp2Y = 0;

int planeLeftWingDown1X = 0;
int planeLeftWingDown1Y = 0;

int planeLeftWingDown2X = 0;
int planeLeftWingDown2Y = 0;

//plane Left collision points

int planeRightX = 0;
int planeRightY = 0;

int planeRightBodyX = 0;
int planeRightBodyY = 0;

int planeRightWingUp1X = 0;
int planeRightWingUp1Y = 0;

int planeRightWingUp2X = 0;
int planeRightWingUp2Y = 0;

int planeRightWingDown1X = 0;
int planeRightWingDown1Y = 0;

int planeRightWingDown2X = 0;
int planeRightWingDown2Y = 0;


int missileLeftX = 0;
int missileLeftY = 0;


int missileRightX = 0;
int missileRightY = 0;

float move_unit = 15;

//#pragma endregion Varriables

int colCountL = 0;
int colCountR = 0;


void keyboardown(int key, int x, int y)
{
	switch (key){
		//case GLUT_KEY_RIGHT:

		//	posX += move_unit;
		//	//	missilePosX += move_unit;
		//	break;

		//case GLUT_KEY_LEFT:
		//	posX -= move_unit;
		//	break;

	case GLUT_KEY_UP:
		y1 -= move_unit;
		glutPostRedisplay();

		break;

	case GLUT_KEY_DOWN:
		y1 += move_unit;
		glutPostRedisplay();
		break;

	default:
		break;


	}

}

void myMouse(int b, int s, int x, int y) {      // mouse click callback
	if (s == GLUT_DOWN) {


		if (b == GLUT_LEFT_BUTTON) {


			y2 += move_unit;
			glutPostRedisplay();
		}

		else if (b == GLUT_RIGHT_BUTTON){

			y2 -= move_unit;

		}
	}
}

float mouseChange = 3.5;

int  tempY = 0;

int planePos = 500;

void myMouseMove(int x, int y)
{


	if (tempY > y && tempY >= 0 && tempY <= 700)
	{
		//printf("%d \n", planePos);
		y2 -= mouseChange;
		planePos = planePos - mouseChange;
	}

	else if (tempY < y && tempY >= 0 && tempY <= 700)
	{
		y2 += mouseChange;
		//printf("\t \t %d \n", planePos);
		planePos = planePos + mouseChange;
	}

	tempY = y;

	glutPostRedisplay();
}


void drawHealthBarLeft(int x, float r ,float g ,float b)
{

	if (colCountL == 0)
	{


		glBegin(GL_QUADS);
		glColor3f(0 + r, .5 + g, 0 + b);
		glVertex2f(20, 25);
		glVertex2f(330 - x, 25);
		glVertex2f(330 - x, 45);
		glVertex2f(20, 45);
		glEnd();


	}



	else if (colCountL == 1)
	{
		//yellow
		glBegin(GL_QUADS);
		glColor3f(1, 1, 0);
		glVertex2f(20, 25);
		glVertex2f(225, 25);
		glVertex2f(225, 45);
		glVertex2f(20, 45);
		glEnd();
	}
		else if (colCountL == 2)
		{
			glBegin(GL_QUADS);
			glColor3f(1, 0, 0);
			glVertex2f(20, 25);
			glVertex2f(95, 25);
			glVertex2f(95, 45);
			glVertex2f(20, 45);
			glEnd();
		}






}


void drawHealthBarRight()
{
	if (colCountR == 0)
	{	//green
		glBegin(GL_QUADS);
		glColor3f(0, .5, 0);
		glVertex2f(550, 25);
		glVertex2f(860, 25);
		glVertex2f(860, 45);
		glVertex2f(550, 45);
		glEnd();
	}

	else if (colCountR == 1)
	{
		//yellow
		glBegin(GL_QUADS);
		glColor3f(1, 1, 0);
		glVertex2f(660, 25);
		glVertex2f(860, 25);
		glVertex2f(860, 45);
		glVertex2f(660, 45);
		glEnd();
	}


	else if (colCountR ==2)
	{
	//red
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex2f( 790,  25);
	glVertex2f( 860,  25);
	glVertex2f( 860,  45);
	glVertex2f( 790,  45);
	glEnd();
	}

}



void drawPlaneLeft(int planeX, int planeY)
{
	//collision
	planeLeftX = planeX + 120;
	planeLeftY = planeY + 450;

	planeLeftBodyX = planeX + 90;
	planeLeftBodyY = planeY + 450;

	planeLeftWingUp1X = planeX + 72;
	planeLeftWingUp1Y = planeY + 437;

	planeLeftWingUp2X = planeX + 57;
	planeLeftWingUp2Y = planeY + 422;

	planeLeftWingDown1X = planeX + 72;
	planeLeftWingDown1Y = planeY + 462;

	planeLeftWingDown2X = planeX + 57;
	planeLeftWingDown2Y = planeY + 477;



	//printf("%d %d\n", planeLeftX, planeLeftY);
	//drawing plane
	//plane head
	glBegin(GL_TRIANGLES);
	glColor3f(.8, .4, .1);
	glVertex2f(planeX + 700 - 580, planeY + 450);
	glVertex2f(planeX + 700 - 595, planeY + 445);
	glVertex2f(planeX + 700 - 595, planeY + 455);
	glEnd();
	//body
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex2f(planeX + 700 - 595, planeY + 445);
	glVertex2f(planeX + 700 - 595, planeY + 455);
	glVertex2f(planeX + 700 - 673, planeY + 455);
	glVertex2f(planeX + 700 - 673, planeY + 445);
	glEnd();
	//up wing
	glColor3f(.5, 0, 1);
	glBegin(GL_POLYGON);
	glVertex2f(planeX + 700 - 625, planeY + 445);
	glVertex2f(planeX + 700 - 625, planeY + 440);
	glVertex2f(planeX + 700 - 655, planeY + 410);
	glVertex2f(planeX + 700 - 665, planeY + 410);
	glVertex2f(planeX + 700 - 650, planeY + 440);
	glVertex2f(planeX + 700 - 650, planeY + 445);
	glEnd();
	//down wing
	glColor3f(.5, 0, 1);
	glBegin(GL_POLYGON);
	glVertex2f(planeX + 700 - 625, planeY + 900 - 445);
	glVertex2f(planeX + 700 - 625, planeY + 900 - 440);
	glVertex2f(planeX + 700 - 655, planeY + 900 - 410);
	glVertex2f(planeX + 700 - 665, planeY + 900 - 410);
	glVertex2f(planeX + 700 - 650, planeY + 900 - 440);
	glVertex2f(planeX + 700 - 650, planeY + 900 - 445);
	glEnd();
	//tail
	glColor3f(0, 1, .2);
	glBegin(GL_POLYGON);
	glVertex2f(planeX + 700 - 673, planeY + 455);
	glVertex2f(planeX + 700 - 673, planeY + 445);
	glVertex2f(planeX + 700 - 690, planeY + 430);
	glVertex2f(planeX + 700 - 680, planeY + 450);
	glVertex2f(planeX + 700 - 690, planeY + 470);
	glEnd();

}
void drawPlaneRight(int planeX, int planeY)
{
	//check plane collision
	planeRightX = planeX + 120;
	planeRightY = planeY + 450;

	planeRightBodyX = planeX + 90;
	planeRightBodyY = planeY + 450;

	planeRightWingUp1X = planeX + 72;
	planeRightWingUp1Y = planeY + 437;

	planeRightWingUp2X = planeX + 57;
	planeRightWingUp2Y = planeY + 422;

	planeRightWingDown1X = planeX + 72;
	planeRightWingDown1Y = planeY + 462;

	planeRightWingDown2X = planeX + 57;
	planeRightWingDown2Y = planeY + 477;


	// draw plane

	//plane head
	glBegin(GL_TRIANGLES);
	glColor3f(.9, .1, .8);
	glVertex2f(planeX + 200 + 580, planeY + 900 - 450);
	glVertex2f(planeX + 200 + 595, planeY + 900 - 445);
	glVertex2f(planeX + 200 + 595, planeY + 900 - 455);
	glEnd();
	//body
	glBegin(GL_QUADS);
	glColor3f(.2, .8, .9);
	glVertex2f(planeX + 200 + 595, planeY + 900 - 445);
	glVertex2f(planeX + 200 + 595, planeY + 900 - 455);
	glVertex2f(planeX + 200 + 673, planeY + 900 - 455);
	glVertex2f(planeX + 200 + 673, planeY + 900 - 445);
	glEnd();
	//down wing
	glBegin(GL_POLYGON);
	glColor3f(.5, .1, .5);
	glVertex2f(planeX + 200 + 625, planeY + 900 - 445);
	glVertex2f(planeX + 200 + 625, planeY + 900 - 440);
	glVertex2f(planeX + 200 + 655, planeY + 900 - 410);
	glVertex2f(planeX + 200 + 665, planeY + 900 - 410);
	glVertex2f(planeX + 200 + 650, planeY + 900 - 440);
	glVertex2f(planeX + 200 + 650, planeY + 900 - 445);
	glEnd();
	//up wing
	glBegin(GL_POLYGON);
	glColor3f(.5, .1, .5);
	glVertex2f(planeX + 200 + 625, planeY + 445);
	glVertex2f(planeX + 200 + 625, planeY + 440);
	glVertex2f(planeX + 200 + 655, planeY + 410);
	glVertex2f(planeX + 200 + 665, planeY + 410);
	glVertex2f(planeX + 200 + 650, planeY + 440);
	glVertex2f(planeX + 200 + 650, planeY + 445);
	glEnd();
	//tail
	glBegin(GL_POLYGON);
	glColor3f(.9, .1, .8);
	glVertex2f(planeX + 200 + 673, planeY + 900 - 455);
	glVertex2f(planeX + 200 + 673, planeY + 900 - 445);
	glVertex2f(planeX + 200 + 690, planeY + 900 - 430);
	glVertex2f(planeX + 200 + 680, planeY + 900 - 450);
	glVertex2f(planeX + 200 + 690, planeY + 900 - 470);
	glEnd();

}

void drawMissileLeft(int missileX, int missileY)

{
	missileLeftX = missileX + 700 - 550;
	missileLeftY = missileY + 450;

	//printf("%d %d \n",missileLeftX,missileLeftY);
	//missile head
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2f(missileX + 700 - 550, missileY + 450);
	glVertex2f(missileX + 700 - 565, missileY + 447);
	glVertex2f(missileX + 700 - 565, missileY + 452);
	glEnd();

	//body
	glBegin(GL_QUADS);
	glColor3f(.8, .4, .1);
	glVertex2f(missileX + 700 - 565, missileY + 447);
	glVertex2f(missileX + 700 - 565, missileY + 452);
	glVertex2f(missileX + 700 - 560, missileY + 452);
	glVertex2f(missileX + 700 - 560, missileY + 447);
	glEnd();

	//tail
	glBegin(GL_POLYGON);
	glColor3f(0, .3, 0);
	glVertex2f(missileX + 700 - 560, missileY + 452);
	glVertex2f(missileX + 700 - 560, missileY + 447);
	glVertex2f(missileX + 700 - 580, missileY + 442);
	glVertex2f(missileX + 700 - 573, missileY + 450);
	glVertex2f(missileX + 700 - 580, missileY + 457);
	glEnd();


	//glFlush();


}

void drawMissileRight(int missileX, int missileY)
{

	missileRightX = missileX + 150;
	missileRightY = missileY + 450;

	//printf("%d %d \n", missileRightX, missileRightY);
	// missileX + 550, missileY + 450
	//missile head
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex2f(missileX + 200 + 550, missileY + 450);
	glVertex2f(missileX + 200 + 565, missileY + 447);
	glVertex2f(missileX + 200 + 565, missileY + 452);
	glEnd();

	//body
	glBegin(GL_QUADS);
	glColor3f(.4, .6, .7);
	glVertex2f(missileX + 200 + 565, missileY + 447);
	glVertex2f(missileX + 200 + 565, missileY + 452);
	glVertex2f(missileX + 200 + 560, missileY + 452);
	glVertex2f(missileX + 200 + 560, missileY + 447);
	glEnd();

	//tail
	glBegin(GL_POLYGON);
	glColor3f(1, 0.5, 0);

	glVertex2f(missileX + 200 + 560, missileY + 452);
	glVertex2f(missileX + 200 + 560, missileY + 447);
	glVertex2f(missileX + 200 + 580, missileY + 442);
	glVertex2f(missileX + 200 + 573, missileY + 450);
	glVertex2f(missileX + 200 + 580, missileY + 457);
	glEnd();
}


void drawMissile(int x, int y)
{
	drawMissileLeft(posX, posY);
	drawMissileRight(0, 0);
}

int right2left = 0;
void fireMissileRight()
{
	right2left = right2left - 4;

	if (right2left <= -750)
	{
		right2left = 0;
		drawMissileRight(right2left, y2);
	}
	else
	{
		drawMissileRight(right2left, y2);
	}




}


int left2Right = 0;
void fireMissileLeft()
{
	left2Right = left2Right + 3;


	if (left2Right >= 750)
	{
		left2Right = 0;
		drawMissileLeft(left2Right, y1);
	}
	else
	{
		drawMissileLeft(left2Right, y1);
	}

}

void drawPlane()
{

	drawPlaneLeft(x1, y1);
	drawPlaneRight(x2, y2);
}


void fireMissile()
{
	fireMissileLeft();
	fireMissileRight();
}
void timer_func(int n)           // NEW FUNCTION
{
	// Update the object positions, etc.
	fireMissile();  // spin the square

	glutTimerFunc(n, timer_func, n); // recursively call timer_func
}

void myInit2(void)
{
	glClearColor(0, .6, 1, 1);


	glColor3f(1, 1, 1);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 900, 750, 0.0);
}

void update(int value)
{
	fireMissile();
	drawMissile(0,0);
	glutPostRedisplay();
	glutTimerFunc(50, update, 0);
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 1.0, 3200);
	glMatrixMode(GL_MODELVIEW);
}


GLfloat UpwardsScrollVelocity = -10.0;
float view = 10.0;

char quote[6][80];
int numberOfQuotes = 0, i;


void timeTick(void)
{
	if (UpwardsScrollVelocity< -600)
		view -= 0.000011;
	if (view < 0) { view = 20; UpwardsScrollVelocity = -10.0; }
	//  exit(0);
	UpwardsScrollVelocity -= 0.1;
	glutPostRedisplay();

}

void RenderToDisplay()
{
	int l, lenghOfQuote, i;

	glTranslatef(0.0, -100, UpwardsScrollVelocity);
	glRotatef(-20, 1.0, 0.0, 0.0);
	glScalef(0.1, 0.1, 0.1);



	for (l = 0; l<numberOfQuotes; l++)
	{
		lenghOfQuote = (int)strlen(quote[l]);
		glPushMatrix();
		glTranslatef(-(lenghOfQuote * 37), -(l * 200), 0.0);
		for (i = 0; i < lenghOfQuote; i++)
		{
			glColor3f((UpwardsScrollVelocity / 10) + 300 + (l * 10), (UpwardsScrollVelocity / 10) + 300 + (l * 10), 0.0);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[l][i]);


		}
		glPopMatrix();
	}

}

void myDisplayFunction2(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 30.0, 100.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	RenderToDisplay();
	glutSwapBuffers();
}


int winner(char a)
{
	strcpy(quote[0], "Game Over");

	strcpy(quote[1], "Winner Is ");
	//	strcpy_s(quote[2], );
	strcpy(quote[2], "Player ");
	strcpy(quote[3], &a);
	numberOfQuotes = 5;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	//glutInitWindowSize(1360, 750);
	glutCreateWindow("Game Result");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glLineWidth(3);

	glutDisplayFunc(myDisplayFunction2);
	glutReshapeFunc(reshape);
	glutIdleFunc(timeTick);
	glutMainLoop();

	return 0;
}

bool collisionLeft()
{


	//printf("pX= %d pY=%d mX= %d mY = %d \n",planeLeftX,planeLeftY,missileRightX,missileRightY);
	//printf("pX= %d pY=%d mX= %d mY = %d \n", planeRightX, planeRightY, missileLeftX, missileLeftY);

	if (planeLeftX - 5 < 600 + missileRightX && 600 + missileRightX < planeLeftX + 5 && planeLeftY - 10 < missileRightY && missileRightY <= planeLeftY + 10
		||
		planeLeftBodyX - 5 < 600 + missileRightX && 600 + missileRightX < planeLeftBodyX + 5 && planeLeftBodyY - 13 < missileRightY && missileRightY <= planeLeftBodyY + 13
		||
		planeLeftWingUp1X - 5 < 600 + missileRightX && 600 + missileRightX < planeLeftWingUp1X + 5 && planeLeftWingUp1Y - 10 < missileRightY && missileRightY <= planeLeftWingUp1Y + 10
		||
		planeLeftWingUp2X - 5 < 600 + missileRightX && 600 + missileRightX < planeLeftWingUp2X + 5 && planeLeftWingUp2Y - 10 < missileRightY && missileRightY <= planeLeftWingUp2Y + 10
		||
		planeLeftWingDown1X - 5 < 600 + missileRightX && 600 + missileRightX < planeLeftWingDown1X + 5 && planeLeftWingDown1Y - 10 < missileRightY && missileRightY <= planeLeftWingDown1Y + 10
		||
		planeLeftWingDown2X - 5 < 600 + missileRightX && 600 + missileRightX < planeLeftWingDown2X + 5 && planeLeftWingDown2Y - 10 < missileRightY && missileRightY <= planeLeftWingDown2Y + 10
		)

	{
		colCountL++;
		//printf("a");

		right2left = -750;
		fireMissileRight();
		//glFlush();
		/*printf("Collision 1");*/
		//scanf_s("%d", &a);
		return true;

	}

	else
		return false;
}

bool collisionRight()
{

	if (planeRightX - 5 <   900 - missileLeftX && 900 - missileLeftX< planeRightX + 5 && planeRightY - 10 < missileLeftY && missileLeftY <= planeRightY + 10
		||
		planeRightBodyX - 5 <   900 - missileLeftX && 900 - missileLeftX< planeRightBodyX + 5 && planeRightBodyY - 13 < missileLeftY && missileLeftY <= planeRightBodyY + 13
		||
		planeRightWingUp1X - 5 <   900 - missileLeftX && 900 - missileLeftX< planeRightWingUp1X + 5 && planeRightWingUp1Y - 10 < missileLeftY && missileLeftY <= planeRightWingUp1Y + 10
		||
		planeRightWingUp2X - 5 <   900 - missileLeftX && 900 - missileLeftX< planeRightWingUp2X + 5 && planeRightWingUp2Y - 10 < missileLeftY && missileLeftY <= planeRightWingUp2Y + 10
		||
		planeRightWingDown1X - 5 <   900 - missileLeftX && 900 - missileLeftX< planeRightWingDown1X + 5 && planeRightWingDown1Y - 10 < missileLeftY && missileLeftY <= planeRightWingDown1Y + 10
		||
		planeRightWingDown2X - 5 <   900 - missileLeftX && 900 - missileLeftX< planeRightWingDown2X + 5 && planeRightWingDown2Y - 10 < missileLeftY && missileLeftY <= planeRightWingDown2Y + 10
		)
	{
		/*printf("pX= %d pY=%d bx = %d by = %d uw1x =%d uw1y=%d  uw2x = %d uw2y=%d  \n wd1x= %d wd1y=%d  wd2x = %d wd2y =%d  mX= %d mY = %d \n",
		planeRightX, planeRightY, planeRightBodyX, planeRightBodyY, planeRightWingUp1X, planeRightWingUp1Y, planeRightWingUp2X, planeRightWingUp2Y, planeRightWingDown1X, planeRightWingDown1Y
		, planeRightWingDown2X, planeRightWingDown2Y,missileLeftX, missileLeftY);

		printf("Collision 1");*/
		colCountR++;
		left2Right = 750;
		fireMissileRight();
		return true;
	}
	else

		return false;

}

void myDisplay2(void)


{
	char a = '1';
	char b = '2';

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glPushMatrix();
	//glTranslatef(posX, posY, posZ);
	drawPlane();
	//glPopMatrix();
	/*drawHealthBarLeft(0, 0);
	drawHealthBarRight(0, 0);*/

	//glPushMatrix();
	//glTranslatef(missilePosX, 0, 0);
	fireMissileLeft();
	fireMissileRight();
	//glPopMatrix();

	drawHealthBarLeft(0, 0, 0, 0); //draw green
	drawHealthBarRight();

	collisionLeft();
	collisionRight();

	 if (colCountL == 3)
	{
		winner(a);

	}

		else if (colCountR == 3)
		{
			winner(b);
		}


	glFlush();



}





//glutCreateWindow("Plane");




void enter_main_loop () {
    if (!setjmp(jmpbuf)) {
        jmp_set = TRUE;
        glutMainLoop();
    }
    jmp_set = FALSE;
}


void cleanup();


int main(int argc, char** argv)
{



    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    screen_width = glutGet(GLUT_SCREEN_WIDTH);
    screen_height = glutGet(GLUT_SCREEN_HEIGHT);
    glutInitWindowSize (screen_width, screen_height);
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("Tank Shooter");

    atexit(cleanup);

    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutFullScreen();
    myInit();
    glutTimerFunc(60, update, 0); // timer
	timer_func(100);
	glutMainLoop();






 exit(0);



}

void cleanup()
{
     glutDisplayFunc(myDisplay2);
	myInit2();
	glutTimerFunc(60, update, 0); // timer
	timer_func(50);
	glutMouseFunc(myMouse);
	glutSpecialFunc(keyboardown);
	glutPassiveMotionFunc(myMouseMove);
     glutMainLoop();
}
