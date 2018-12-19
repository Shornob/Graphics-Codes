#include<GL/gl.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

float _angle = 0.0;
float _cameraAngle = 0.0;
float _ang_tri = 0.0;

//Draws the 3D scene
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	glRotatef(-_cameraAngle, 0.0, 1.0, 0.0); //Rotate the camera
	glTranslatef(0.0, 0.0, -7.0); //Move forward 5 units

    glPushMatrix();

    glRotatef(_angle, 0.0, 1.0, 0.0);

    glColor3f(1.0,1.0,0.0);
	glPushMatrix(); //Save the current state of transformations
	glTranslatef(0.0, 0.0, 0.0); //Move to the center of the pentagon
	//glRotatef(_angle, 0.0, 1.0, 0.0); //Rotate about the y-axis
	glScalef(0.60, 0.90, 0.50); //Scale by 0.7 in the x, y, and z directions
    glutSolidCube(2.0);
	glPopMatrix(); //Undo the move to the center of the pentagon/*

    glColor3f(1.0,0.0,0.0);
    glPushMatrix(); //Save the current state of transformations
	glTranslatef(0.0, 1.1, 0.0); //Move to the center of the pentagon
	//glRotatef(_angle, 0.0, 1.0, 0.0); //Rotate about the y-axis
	glScalef(0.50, 0.70, 0.50); //Scale by 0.7 in the x, y, and z directions
    glutSolidCube(0.8);
	glPopMatrix(); //Undo the move to the center of the pentagon/*

///right side
    glColor3f(0.0,1.0,0.0);
    glPushMatrix(); //Save the current state of transformations
	glTranslatef(0.8, 0.4, 0.0); //Move to the center of the pentagon
	//glRotatef(_angle, 0.0, 1.0, 0.0); //Rotate about the y-axis
	glScalef(0.50, 0.70, 0.40); //Scale by 0.7 in the x, y, and z directions
    glutSolidCube(1.0);
	glPopMatrix(); //Undo the move to the center of the pentagon/*

	glColor3f(1.0,1.0,1.0);
    glPushMatrix(); //Save the current state of transformations
	glTranslatef(0.65, -0.01, 0.0); //Move to the center of the pentagon
	//glRotatef(_angle, 0.0, 1.0, 0.0); //Rotate about the y-axis
	glScalef(0.30, 0.8, 0.10); //Scale by 0.7 in the x, y, and z directions
    glutSolidCube(1.6);
	glPopMatrix(); //Undo the move to the center of the pentagon/*

///left side

glColor3f(0.0,1.0,0.0);
    glPushMatrix(); //Save the current state of transformations
	glTranslatef(-0.8, 0.4, 0.0); //Move to the center of the pentagon
	//glRotatef(_angle, 0.0, 1.0, 0.0); //Rotate about the y-axis
	glScalef(0.50, 0.70, 0.40); //Scale by 0.7 in the x, y, and z directions
    glutSolidCube(1.0);
	glPopMatrix(); //Undo the move to the center of the pentagon/*

	glColor3f(1.0,1.0,1.0);
    glPushMatrix(); //Save the current state of transformations
	glTranslatef(-0.65, -0.01, 0.0); //Move to the center of the pentagon
	//glRotatef(_angle, 0.0, 1.0, 0.0); //Rotate about the y-axis
	glScalef(0.30, 0.8, 0.10); //Scale by 0.7 in the x, y, and z directions
    glutSolidCube(1.6);
	glPopMatrix(); //Undo the move to the center of the pentagon/*





	///left side legs

    glColor3f(1.0,0.0,1.0);
    glPushMatrix(); //Save the current state of transformations
	glTranslatef(-0.3, -1.0, 0.0); //Move to the center of the pentagon
	//glRotatef(_angle, 0.0, 1.0, 0.0); //Rotate about the y-axis
	glScalef(0.40, 0.90, 0.40); //Scale by 0.7 in the x, y, and z directions
    glutSolidCube(1.0);
	glPopMatrix(); //Undo the move to the center of the pentagon/*

	glColor3f(1.0,1.0,1.0);
    glPushMatrix(); //Save the current state of transformations
	glTranslatef(-0.3, -1.5, 0.0); //Move to the center of the pentagon
	//glRotatef(_angle, 0.0, 1.0, 0.0); //Rotate about the y-axis
	glScalef(0.10, 0.8, 0.10); //Scale by 0.7 in the x, y, and z directions
    glutSolidCube(1.6);
	glPopMatrix(); //Undo the move to the center of the pentagon/*





	///left side legs

    glColor3f(1.0,0.0,1.0);
    glPushMatrix(); //Save the current state of transformations
	glTranslatef(0.3, -1.0, 0.0); //Move to the center of the pentagon
	//glRotatef(_angle, 0.0, 1.0, 0.0); //Rotate about the y-axis
	glScalef(0.40, 0.90, 0.40); //Scale by 0.7 in the x, y, and z directions
    glutSolidCube(1.0);
	glPopMatrix(); //Undo the move to the center of the pentagon/*

	glColor3f(1.0,1.0,1.0);
    glPushMatrix(); //Save the current state of transformations
	glTranslatef(0.3, -1.5, 0.0); //Move to the center of the pentagon
	//glRotatef(_angle, 0.0, 1.0, 0.0); //Rotate about the y-axis
	glScalef(0.10, 0.8, 0.10); //Scale by 0.7 in the x, y, and z directions
    glutSolidCube(1.6);
	glPopMatrix();


    glPopMatrix();
	glutSwapBuffers();
}

void update(int value) {
	_angle += 2.0f;
	if (_angle > 360) {
		_angle -= 360;
	}
	_ang_tri += 2.0f;
	if (_ang_tri > 360) {
		_ang_tri -= 360;
	}

	glutPostRedisplay(); //Tell GLUT that the display has changed

	//Tell GLUT to call update again in 25 milliseconds
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(200,100);

	//Create the window
	glutCreateWindow("Transformations");
	initRendering();

	//Set handler functions
	glutDisplayFunc(drawScene);

	glutReshapeFunc(handleResize);

	glutTimerFunc(25, update, 0); //Add a timer

	glutMainLoop();
	return 0;
}


	/*glBegin(GL_TRIANGLES);

	//Pentagon
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);

	glVertex3f(-0.5, 0.0, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.5, 0.0, 0.0);

	glVertex3f(-0.5, 0.0, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(0.0, 0.5, 0.0);

	glEnd();

*/








