#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

struct rotation {
	
	float xAngle;
	float yAngle;
	float zAngle;
	int cylinderAxis[3];
};

// Postavke prozora
int windowWidth = 800;
int windowHeight = 600;
char title[] = "Klatna";

// Postavke
int sphereSlices = 30;
int sphereStacks = 30;
int cylinderSlices = 30;
int cylinderStacks = 30;
float sphereRadius = 0.2f;
float cylinderHeight = 2.0f;

bool animationOn = false;
rotation upperCylinder;
rotation lowerCylinder;
float rotationSpeed = 1.0f;

GLUquadric *quad = gluNewQuadric();


void InitGL() {
  
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float pos[] = {1.5f, 1.5f, -5.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

// tu se namjestaju rotacije svih 
void DoCalculations() {
  
	if(animationOn) {
		if(upperCylinder.cylinderAxis[0]) {
			if(upperCylinder.xAngle >= 360) upperCylinder.xAngle -= 360;
				upperCylinder.xAngle += rotationSpeed;
		}
		if(upperCylinder.cylinderAxis[1]) {
			if(upperCylinder.yAngle >= 360) upperCylinder.yAngle -= 360;
				upperCylinder.yAngle += rotationSpeed;
		}
		if(upperCylinder.cylinderAxis[2]) {
			if(upperCylinder.zAngle >= 360) upperCylinder.zAngle -= 360;
				upperCylinder.zAngle += rotationSpeed;
		}
		if(lowerCylinder.cylinderAxis[0]) {
			if(lowerCylinder.xAngle >= 360) lowerCylinder.xAngle -= 360;
				lowerCylinder.xAngle += rotationSpeed;
		}
		if(lowerCylinder.cylinderAxis[1]) {
			if(lowerCylinder.yAngle >= 360) lowerCylinder.yAngle -= 360;
				lowerCylinder.yAngle += rotationSpeed;
		}
		if(lowerCylinder.cylinderAxis[2]) {
			if(lowerCylinder.zAngle >= 360) lowerCylinder.zAngle -= 360;
				lowerCylinder.zAngle += rotationSpeed;
		}
	}
}

int ToggleAxis(int axis) {
  
	return (axis == 0)? 1: 0;
}

void Display() {
 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	DoCalculations();

	glTranslatef(0.0f, 0.0f, -8.0f);
	glRotatef(upperCylinder.xAngle, 1, 0, 0);
	glRotatef(upperCylinder.yAngle, 0, 1, 0);
	glRotatef(upperCylinder.zAngle, 0, 0, 1);
	glPushMatrix();
		glPushMatrix();											// Gornja kuglica Start
			glColor3f(0.0f, 1.0f, 0.0f);
			glutSolidSphere(sphereRadius, sphereSlices, sphereStacks);
			glTranslatef(0.0f, -sphereRadius, 0.0f);
			glRotatef(90.0f, 1, 0, 0);
			glPushMatrix();											// Gornji cilindar Start
				glColor3f(0.0f, 0.0f, 1.0f);
				gluCylinder(quad, sphereRadius, sphereRadius, cylinderHeight, cylinderSlices, cylinderStacks);
				glRotatef(-90.0f, 1, 0, 0);									// Vracamo rotaciju na normalu
				glTranslatef(0.0f, -(cylinderHeight + sphereRadius), 0.0f);
				glRotatef(lowerCylinder.xAngle, 1, 0, 0);
				glRotatef(lowerCylinder.yAngle, 0, 1, 0);
				glRotatef(lowerCylinder.zAngle, 0, 0, 1);
				glPushMatrix();											// Srednja kuglica Start
					glColor3f(0.0f, 0.7f, 0.0f);
					glutSolidSphere(sphereRadius, sphereSlices, sphereStacks);
					glTranslatef(sphereRadius, 0.0f, 0.0f);
					glRotatef(90.0f, 0, 1, 0);
					glPushMatrix();											// Donji cilindar start
						glColor3f(1.0f, 0.0f, 0.0f);
						gluCylinder(quad, sphereRadius, sphereRadius, cylinderHeight, cylinderSlices, cylinderStacks);
					glPopMatrix();											// Donji cilindar stop
				glPopMatrix();											// Srednja kuglica Stop
			glPopMatrix();											// Gornji cilindar Stop
		glPopMatrix();											// Gornja kuglica End
	glPopMatrix();

	glutSwapBuffers();
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y) {
 
	switch (key) {
		case 27: //	Escape
		exit(0);
	case 115: // s
		animationOn = true;
		break;
	case 120: // x
		animationOn = false;
		break;
	case 113: // q
		upperCylinder.cylinderAxis[0] = ToggleAxis(upperCylinder.cylinderAxis[0]);
		break;
	case 119: // w
		upperCylinder.cylinderAxis[1] = ToggleAxis(upperCylinder.cylinderAxis[1]);
		break;
	case 101: // e
		upperCylinder.cylinderAxis[2] = ToggleAxis(upperCylinder.cylinderAxis[2]);
		break;
	case 98: // b
		lowerCylinder.cylinderAxis[0] = ToggleAxis(lowerCylinder.cylinderAxis[0]);
		break;
	case 110: // n
		lowerCylinder.cylinderAxis[1] = ToggleAxis(lowerCylinder.cylinderAxis[1]);
		break;
	case 109: // m
		lowerCylinder.cylinderAxis[2] = ToggleAxis(lowerCylinder.cylinderAxis[2]);
		break;
	}
}

void Resize(int w, int h) {
  
	if (h == 0) h = 1;
	GLfloat aspect = (GLfloat)w / (GLfloat)h;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// view angle u y, aspect, near, far
	gluPerspective(45.0f, aspect, 1.0f, 100.0f);
}

int main(int argc, char** argv) {
  
	glutInit(&argc, argv);										// Pokreni glut
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);	// Enablaj double buffer, depth i rgb mode (zbog toga da se ne preklapaju povrsine)
	glutInitWindowSize(windowWidth, windowHeight);				// Visina i sirina prozora
	glutInitWindowPosition(50, 50);								// Pozicija prozora
	glutCreateWindow(title);									// Prozor i naslov

	// Namjesti funkcije za handlanje.
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(Resize);

	InitGL();

	glutMainLoop();
	return 0;
}