#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <math.h> // for sqrt()
static int h, w;
float angle = 0.0f;
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 0.0f, z = 5.0f;
float deltaAngle = 0.0f;
float deltaMove = 0;
double pos_x = 0, pos_y = 0;

static GLfloat fovy = 52.0f; // in degrees
static GLfloat c = 1.0 / (GLfloat)tan(fovy / 4.0), a = (GLfloat)w / (GLfloat)h, n = 1.0f, f = 1000.0f;
static GLfloat Xvalue = 0.0f;
static GLfloat Yvalue = 0.0f;
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zRot = 0.0f;
static GLfloat xScale = 1.0f;
static GLfloat yScale = 1.0f;
static GLfloat zScale = 1.0f;
static bool SHAPE = true;
void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}

void computeDir(float deltaAngle) {

	angle += deltaAngle;
	lx = sin(angle);
	lz = -cos(angle);
}
void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27)
		exit(0);
}


void processSpecialKeys(int key, int x, int y) {
	const float step = 5;

	switch (key) {
	case GLUT_KEY_LEFT: deltaAngle = -0.01f; break;
	case GLUT_KEY_RIGHT: deltaAngle = 0.01f; break;
	case GLUT_KEY_UP: deltaMove = 0.5f; break;
	case GLUT_KEY_DOWN: deltaMove = -0.5f; break;
	}
	glutPostRedisplay();
}
void releaseKey(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_LEFT:
	case GLUT_KEY_RIGHT: deltaAngle = 0.0f; break;
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN: deltaMove = 0; break;
	}
}
void init(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}
void reshape(int w, int h) {
	
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f); // fov, aspect ratio, ncp, fcp 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//gluLookAt(camera.eyeX, camera.eyeY, camera.eyeZ, // eye 
	//        camera.centerX, camera.centerY, camera.centerZ, // center
	//        camera.upX, camera.upY, camera.upZ // up 
	//
	//);


}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		SHAPE =true;
	}
	else
		SHAPE = false ;
}
void display(void) {
	if (deltaMove)
		computePos(deltaMove);
	if (deltaAngle)
		computeDir(deltaAngle);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	gluLookAt(x, 1.0f, z,
		x + lx, 1.0f, z + lz,
		0.0f, 1.0f, 0.0f);
	glTranslatef(Xvalue, Yvalue, -3.0);
	glScalef(xScale, yScale, zScale);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);

	//glTranslatef(0.0,0.0,1.0f);;

	glColor3f(1.0f, 1.0f, 1.0f);
	glutWireCube(2.0);
	if (SHAPE == true)
	{
		glutWireTeapot(0.5f);
	   
	}
	else
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		glutSolidTeapot(0.5f);
	
		
	}
	glFlush();
	glutSwapBuffers();
	


}

void keyInput(unsigned char key, int x, int y)
{ // Keyboard input processing routine.
	switch (key)
	{
	case 'A': // move left
		Xvalue -= 0.1;
		
		break;
	case 'D': // move right
		Xvalue += 0.1;
		glutPostRedisplay();
		break;
	case 'S': // move down
		Yvalue -= 0.1;
		glutPostRedisplay();
		break;
	case 'W': // move up
		Yvalue += 0.1;
		glutPostRedisplay();
		break;
	case 'e': // scale down
		zScale -= 0.1;
		xScale -= 0.1;
		yScale -= 0.1;
		glutPostRedisplay();
		break;
	case 'E': // scale up
		zScale += 0.1;
		xScale += 0.1;
		yScale += 0.1;
		glutPostRedisplay();
		break;
	case 'f': // rotate x axis CW
		xRot -= 5.0f;
		glutPostRedisplay();
		break;
	case 'F': // rotate x axis CCW
		xRot += 5.0f;
		glutPostRedisplay();
		break;
	case 'g': // rotate y axis CW
		yRot -= 10.0f;
		glutPostRedisplay();
		break;
	case 'G': // rotate y axis CCW
		yRot += 10.0f;
		glutPostRedisplay();
		break;
	case 'h': // rotate z axis CW
		zRot -= 5.0f;
		glutPostRedisplay();
		break;
	case 'H': // rotate z axis CCW
		zRot += 5.0f;
		glutPostRedisplay();
		break;
	case 'p':

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(52, 1, 5, 3);
		gluLookAt(0, 0, -7, 0, 0, 0, 0, 1, 0);
		glMatrixMode(GL_MODELVIEW);
		glutPostRedisplay();
		break;

	case 'o':
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		
		glOrtho(-2, 2, -1, 1, 1, 500);
		glMatrixMode(GL_MODELVIEW);
		glutPostRedisplay();
		break;


	}
}
int main(int argc, char *argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	//glutCreateWindow(argv[0]);
	glutInitWindowPosition(500, 200);
	glutInitWindowSize(800, 600);
	glutCreateWindow("fgh");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	
	glutMouseFunc(mouse);
	glutSpecialFunc(processSpecialKeys);
	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);
	glutKeyboardFunc(keyInput);

	

	glutMainLoop();

	return 0;

}