#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define SPACEBAR 32

int moving, startx, starty;
GLfloat angle = 0.0;
GLfloat angle2 = 0.0;
static int fingerBase = 0, fingerUp = 0, fingerBase2 = 0, fingerUp2 = 0;
static int allbodyY = 0, allbodyZ = 0;
static int SHOULDERRIGHT = 0, SHOULDERRIGHT2 = 0, SHOULDERRIGHTZROT = 0;
static int SHOULDERLEFT = 0, SHOULDERLEFT2 = 0, SHOULDERLEFTZROT = 0, SHOULDER = 0;
static int LEFTLEGUP = 0, LEFTLEG2 = 0, LEFTLEGSIDE = 0;
static int RIGHTLEGUPALL = 0, RIGHTLEG2 = 0, RIGHTLEGSIDE = 0;
int run = 0;
int timercount = 0;


double eye[] = { 0 , 0, -1 };
double center[] = { 0, 0, 4 };
double up[] = { 0, 1, 0 };
double perpendicularAxis[] = { 0, 0, 0 };
GLfloat Znear = 100.0;
int windowWidth;
int windowHeight;

void rotatePoint(double a[], double theta, double p[]) //Camera movements 
{
	double temp[3];
	temp[0] = p[0];
	temp[1] = p[1];
	temp[2] = p[2];
	temp[0] = -a[2] * p[1] + a[1] * p[2];
	temp[1] = a[2] * p[0] - a[0] * p[2];
	temp[2] = -a[1] * p[0] + a[0] * p[1];
	temp[0] *= sin(theta);
	temp[1] *= sin(theta);
	temp[2] *= sin(theta);
	temp[0] += (1 - cos(theta)) * (a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
	temp[1] += (1 - cos(theta)) * (a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
	temp[2] += (1 - cos(theta)) * (a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);
	temp[0] += cos(theta) * p[0];
	temp[1] += cos(theta) * p[1];
	temp[2] += cos(theta) * p[2];
	p[0] = temp[0];
	p[1] = temp[1];
	p[2] = temp[2];
}
void crossProduct(double a[], double b[], double c[])
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
}
void normalize(double a[])
{
	double norm;
	norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
	norm = sqrt(norm);
	a[0] /= norm;
	a[1] /= norm;
	a[2] /= norm;
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

/*void lookUp()
{
	crossProduct(up, center, perpendicularAxis);
	normalize(perpendicularAxis);
	rotatePoint(perpendicularAxis, 0.05, center);
	rotatePoint(perpendicularAxis, 0.05, up);

	glutPostRedisplay();

}

void lookDown()
{
	crossProduct(up, center, perpendicularAxis);
	normalize(perpendicularAxis);
	rotatePoint(perpendicularAxis, -0.05, center);
	rotatePoint(perpendicularAxis, -0.05, up);

	glutPostRedisplay();
}


void lookRight()
{
	rotatePoint(up, -0.05, center);

	glutPostRedisplay();
}

void lookLeft()
{
	rotatePoint(up, 0.05, center);

	glutPostRedisplay();
}*/


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix(); // to make all get contained in the body
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);
	glRotatef(angle2, 1.0, 0.0, 0.0);// angels of moving the whole figuer X with mouse
	glRotatef(angle, 0.0, 1.0, 0.0); //angels of moving the whole figuer Y with mouse
	glScalef(1.0, 1.2, 1.0); //scale of whole body we work on

	glTranslatef(0.0, 0.0, allbodyZ);/// MOVE THE BODY FRONT OR BACK (Z)

	  //////////////////////////////////////////////////////////////////Head
	glPushMatrix();
	glTranslatef(0.0, 1.0, 0.0);  //translating it to Y up
	glutWireSphere(0.25, 25, 25);  // head is simply a sphere
	glPopMatrix();
	//////////////////////////////////////////////////////////////////Body
	glPushMatrix();
	glScalef(0.5, 0.9, 0.3);  //scale of figuer according to first scale
	glutWireCube(1.5); //cube size
	glPopMatrix();

	/////////////////////////////////////////////////////////////////Left Arm
	glPushMatrix();
	glTranslatef(-0.6, 0.55, 0.0); // arm coordinates 1
	glRotatef((GLfloat)SHOULDERLEFT, 0.0, 0.0, 1.0); // rotate in Z
	glRotatef((GLfloat)-SHOULDER, 0.0, 0.0, 1.0); // rotate in Z
	glTranslatef(0.0, -0.41, 0.0);  // arm coordinates to manage it after rotation
	glRotatef((GLfloat)SHOULDERLEFTZROT, 0.0, 1.0, 0.0); //rotation in y
	glTranslatef(0.63, -0.22, 0.0);
	glPushMatrix();
	glTranslatef(-0.55, 0.43, 0.0);
	glScalef(0.2, 0.5, 0.3);// el dra3 ba2eto el 7etta el tanya
	glutWireCube(1.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.0, 0.15, 0.0);
	glRotatef((GLfloat)SHOULDERLEFT2, 1.0, 0.0, 0.0);//x rotation
	glTranslatef(-1.55, -0.22, 0.0);
	glScalef(0.2, 0.5, 0.3);// el dra3 b2eto el 7eta el 2ola ely 3nd el swabe3
	glutWireCube(1.0);
	glRotatef(-90, 0.0, 0.0, 1.0);//to make it point down

	glPushMatrix();
	//Draw finger flang 1
	glTranslatef(0.55, 0.15, 0.25);
	glRotatef((GLfloat)fingerBase2, 0.0, 0.0, 1.0);
	glTranslatef(0.05, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	//Draw finger flang 1
	glTranslatef(0.15, 0.0, 0.0);
	glRotatef((GLfloat)fingerUp2, 0.0, 0.0, 1.0);
	glTranslatef(0.05, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	//Draw finger flang 2
	glTranslatef(0.55, -0.15, -0.35);
	glRotatef((GLfloat)-fingerBase2, 0.0, 0.0, 1.0);
	glTranslatef(0.05, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	//Draw finger flang 2
	glTranslatef(0.15, 0.0, 0.0);
	glRotatef((GLfloat)-fingerUp2, 0.0, 0.0, 1.0);
	glTranslatef(0.05, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	//Draw finger flang 3
	glTranslatef(0.55, -0.15, -0.12);
	glRotatef((GLfloat)-fingerBase2, 0.0, 0.0, 1.0);
	glTranslatef(0.05, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	//Draw finger flang 3
	glTranslatef(0.15, 0.0, 0.0);
	glRotatef((GLfloat)-fingerUp2, 0.0, 0.0, 1.0);
	glTranslatef(0.05, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	//Draw finger flang 4
	glTranslatef(0.55, -0.15, 0.09);
	glRotatef((GLfloat)-fingerBase2, 0.0, 0.0, 1.0);
	glTranslatef(0.05, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	//Draw finger flang 4
	glTranslatef(0.15, 0.0, 0.0);
	glRotatef((GLfloat)-fingerUp2, 0.0, 0.0, 1.0);
	glTranslatef(0.05, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	//Draw finger flang 5
	glTranslatef(0.55, -0.15, 0.3);
	glRotatef((GLfloat)-fingerBase2, 0.0, 0.0, 1.0);
	glTranslatef(0.05, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	//Draw finger flang 5
	glTranslatef(0.15, 0.0, 0.0);
	glRotatef((GLfloat)-fingerUp2, 0.0, 0.0, 1.0);
	glTranslatef(0.05, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	//////////////////////////////////////////////RIGHT ARM////////////////////////////////////////////////
	glPushMatrix();
	glTranslatef(0.6, 0.55, 0.0);
	glRotatef((GLfloat)SHOULDERRIGHT, 0.0, 0.0, 1.0);
	glRotatef((GLfloat)SHOULDER, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -0.41, 0.0);
	glRotatef((GLfloat)SHOULDERRIGHTZROT, 0.0, 1.0, 0.0);
	glTranslatef(-0.63, -0.22, 0.0);
	glPushMatrix();
	glTranslatef(0.55, 0.43, 0.0);
	glScalef(0.2, 0.5, 0.3);
	glutWireCube(1.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.0, 0.15, 0.0);
	glRotatef((GLfloat)SHOULDERRIGHT2, 1.0, 0.0, 0.0);
	glTranslatef(1.55, -0.22, 0.0);
	glScalef(0.2, 0.5, 0.3);
	glutWireCube(1.0);





	glRotatef(-90, 0.0, 0.0, 1.0);

	glPushMatrix();
	//Draw finger flang 1
	glTranslatef(0.55, -0.15, 0.25);
	glRotatef((GLfloat)fingerBase, 0.0, 0.0, 1.0);
	glTranslatef(0.05, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	//Draw finger flang 1
	glTranslatef(0.15, 0.0, 0.0);
	glRotatef((GLfloat)fingerUp, 0.0, 0.0, 1.0);
	glTranslatef(0.05, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	//Draw finger flang 2
	glTranslatef(0.55, 0.15, -0.35);
	glRotatef((GLfloat)-fingerBase, 0.0, 0.0, 1.0);
	glTranslatef(0.05, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	//Draw finger flang 2
	glTranslatef(0.15, 0.0, 0.0);
	glRotatef((GLfloat)-fingerUp, 0.0, 0.0, 1.0);
	glTranslatef(0.05, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	//Draw finger flang 3
	glTranslatef(0.55, 0.15, -0.12);
	glRotatef((GLfloat)-fingerBase, 0.0, 0.0, 1.0);
	glTranslatef(0.05, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	//Draw finger flang 3
	glTranslatef(0.15, 0.0, 0.0);
	glRotatef((GLfloat)-fingerUp, 0.0, 0.0, 1.0);
	glTranslatef(0.05, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	//Draw finger flang 4 
	glTranslatef(0.55, 0.15, 0.09);
	glRotatef((GLfloat)-fingerBase, 0.0, 0.0, 1.0);
	glTranslatef(0.05, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	//Draw finger flang 4
	glTranslatef(0.15, 0.0, 0.0);
	glRotatef((GLfloat)-fingerUp, 0.0, 0.0, 1.0);
	glTranslatef(0.05, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	//Draw finger flang 5
	glTranslatef(0.55, 0.15, 0.3);
	glRotatef((GLfloat)-fingerBase, 0.0, 0.0, 1.0);
	glTranslatef(0.05, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	//Draw finger flang 5
	glTranslatef(0.15, 0.0, 0.0);
	glRotatef((GLfloat)-fingerUp, 0.0, 0.0, 1.0);
	glTranslatef(0.05, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();



	//////////////////////////////////////////////RIGHT LEG///////////////////////////////////////////////////
	glPushMatrix();
	glTranslatef(-0.1, -0.8, 0.0);
	glRotatef((GLfloat)RIGHTLEGUPALL, 1.0, 0.0, 0.0);
	glRotatef((GLfloat)RIGHTLEGSIDE, 0.0, 0.0, 1.0);
	glTranslatef(0.1, 0.8, 0.0);
	glPushMatrix();
	glTranslatef(-0.25, -1.02, 0.0);
	glScalef(0.25, 0.7, 0.3);//first part of the leg
	glutWireCube(1.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.8, -1.35, 0.0);
	glRotatef((GLfloat)RIGHTLEG2, 1.0, 0.0, 0.0);
	glTranslatef(-0.8, 1.35, 0.0);
	glPushMatrix();
	glTranslatef(-0.25, -1.72, 0.0);
	glScalef(0.25, 0.7, 0.3);//second part of the leg
	glutWireCube(1.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.25, -2.0, 0.0);
	glScalef(0.26, 0.2, 0.5);// the leg it's self from down
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	//////////////////////////////////////////////LEFT LEG///////////////////////////////////////////////////
	glPushMatrix();
	glTranslatef(0.1, -0.8, 0.0);
	glRotatef((GLfloat)LEFTLEGUP, 1.0, 0.0, 0.0);
	glRotatef((GLfloat)LEFTLEGSIDE, 0.0, 0.0, 1.0);
	glTranslatef(-0.1, 0.8, 0.0);
	glPushMatrix();
	glTranslatef(0.25, -1.02, 0.0);
	glScalef(0.23, 0.7, 0.3);
	glutWireCube(1.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.8, -1.35, 0.0);
	glRotatef((GLfloat)LEFTLEG2, 1.0, 0.0, 0.0);
	glTranslatef(-0.8, 1.35, 0.0);
	glPushMatrix();
	glTranslatef(0.25, -1.72, 0.0);
	glScalef(0.25, 0.7, 0.3);
	glutWireCube(1.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.25, -2.0, 0.0);
	glScalef(0.26, 0.2, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();




	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}





void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}



void timer(int t)
{
	if (run == 1)
	{


		glutTimerFunc(50, timer, 0);

		if (SHOULDER < 180)
		{
			SHOULDER = (SHOULDER + 5) % 360;

		}
		else
		{
			if (SHOULDERLEFT < 180)
			{
				SHOULDERLEFT = (SHOULDERLEFT + 5) % 360;

			}

			if (SHOULDERRIGHT > -180)
			{
				SHOULDERRIGHT = (SHOULDERRIGHT - 5) % 360;

			}

		}
		if (SHOULDER == 180 && SHOULDERLEFT == 180 && SHOULDERRIGHT == -180)
		{
			SHOULDER = 0;
			SHOULDERLEFT = 0;
			SHOULDERRIGHT = 0;
		}

	}


	glutPostRedisplay();
}


void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		rotatePoint(up, 0.05, center);
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		rotatePoint(up, -0.05, center);
		break;
	case GLUT_KEY_UP:
		crossProduct(up, center, perpendicularAxis);
		normalize(perpendicularAxis);
		rotatePoint(perpendicularAxis, 0.05, center);
		rotatePoint(perpendicularAxis, 0.05, up);
		break;
	case GLUT_KEY_DOWN:
		crossProduct(up, center, perpendicularAxis);
		normalize(perpendicularAxis);
		rotatePoint(perpendicularAxis, -0.05, center);
		rotatePoint(perpendicularAxis, -0.05, up);
		break;
	}
	glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case SPACEBAR:

		timercount++;
		if (timercount > 1)
		{
			if (run == 1)
			{
				run = 0;
			}
			else run = 1;
		}
		else run = 1;
		timer(SHOULDER);
		glutPostRedisplay();
		break;
	case 's':
		if (SHOULDERRIGHT < 190)
		{
			SHOULDERRIGHT = (SHOULDERRIGHT + 5) % 360;
			glutPostRedisplay();
		}
		if (SHOULDERLEFT > -190)
		{
			SHOULDERLEFT = (SHOULDERLEFT - 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'S':
		if (SHOULDERRIGHT > 0)
		{
			SHOULDERRIGHT = (SHOULDERRIGHT - 5) % 360;
			glutPostRedisplay();
		}
		if (SHOULDERLEFT < 0)
		{
			SHOULDERLEFT = (SHOULDERLEFT + 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'a':
		if (SHOULDERRIGHTZROT < 90)
		{
			SHOULDERRIGHTZROT = (SHOULDERRIGHTZROT + 5) % 360;
			glutPostRedisplay();
		}
		if (SHOULDERLEFTZROT > -90)
		{
			SHOULDERLEFTZROT = (SHOULDERLEFTZROT - 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'A':
		if (SHOULDERRIGHTZROT > 0)
		{
			SHOULDERRIGHTZROT = (SHOULDERRIGHTZROT - 5) % 360;
			glutPostRedisplay();
		}
		if (SHOULDERLEFTZROT < 0)
		{
			SHOULDERLEFTZROT = (SHOULDERLEFTZROT + 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'E':
		if (SHOULDERRIGHT2 > -80)
		{
			SHOULDERRIGHT2 = (SHOULDERRIGHT2 - 5) % 360;
			glutPostRedisplay();
		}
		if (SHOULDERLEFT2 > -90)
		{
			SHOULDERLEFT2 = (SHOULDERLEFT2 - 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'e':
		if (SHOULDERRIGHT2 < 0)
		{
			SHOULDERRIGHT2 = (SHOULDERRIGHT2 + 5) % 360;
			glutPostRedisplay();
		}
		if (SHOULDERLEFT2 < 0)
		{
			SHOULDERLEFT2 = (SHOULDERLEFT2 + 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'd':
		if (RIGHTLEGUPALL > -90)
		{
			RIGHTLEGUPALL = (RIGHTLEGUPALL - 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'D':
		if (LEFTLEGUP > -90)
		{
			LEFTLEGUP = (LEFTLEGUP - 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'q':
		if (RIGHTLEGUPALL < 65)
		{
			RIGHTLEGUPALL = (RIGHTLEGUPALL + 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'Q':
		if (LEFTLEGUP < 65)
		{
			LEFTLEGUP = (LEFTLEGUP + 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'k':
		if (RIGHTLEG2 > -10)
		{
			RIGHTLEG2 = (RIGHTLEG2 - 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'n':
		if (LEFTLEG2 > -10)
		{
			LEFTLEG2 = (LEFTLEG2 - 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'K':
		if (RIGHTLEG2 < 90)
		{
			RIGHTLEG2 = (RIGHTLEG2 + 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'N':
		if (LEFTLEG2 < 90)
		{
			LEFTLEG2 = (LEFTLEG2 + 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'h':
		if (RIGHTLEGSIDE < 10)
		{
			RIGHTLEGSIDE = (RIGHTLEGSIDE + 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'H':
		if (RIGHTLEGSIDE > -85)
		{
			RIGHTLEGSIDE = (RIGHTLEGSIDE - 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'i':
		if (LEFTLEGSIDE > -10)
		{
			LEFTLEGSIDE = (LEFTLEGSIDE - 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'I':
		if (LEFTLEGSIDE < 85)
		{
			LEFTLEGSIDE = (LEFTLEGSIDE + 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'b':
		if (allbodyZ > -5)
		{
			allbodyZ = (allbodyZ - 1) % 360;
			glutPostRedisplay();
		}
		break;
	case 'f':
		if (allbodyZ < 2)
		{
			allbodyZ = (allbodyZ + 1) % 360;
			glutPostRedisplay();
		}
		break;
	case 'g':
		fingerBase = (fingerBase + 5);
		if (fingerBase > 90) {
			fingerBase = fingerBase - 5;
			break;
		}
		glutPostRedisplay();
		break;
	case 'G':
		fingerBase = (fingerBase - 5);
		if (fingerBase < -5) {
			fingerBase = fingerBase + 5;
			break;
		}
		glutPostRedisplay();
		break;
	case 'u':
		fingerUp = fingerUp + 5;
		if (fingerUp > 90) {
			fingerUp = fingerUp - 5;
			break;
		}
		glutPostRedisplay();
		break;
	case 'U':
		fingerUp = fingerUp - 5;
		if (fingerUp < -5) {
			fingerUp = fingerUp + 5;
			break;
		}
		glutPostRedisplay();
		break;
	case 'j':
		fingerBase2 = (fingerBase2 - 5);
		if (fingerBase2 < -90) {
			fingerBase2 = fingerBase2 + 5;
			break;
		}
		glutPostRedisplay();
		break;
	case 'J':
		fingerBase2 = (fingerBase2 + 5);
		if (fingerBase2 > 5) {
			fingerBase2 = fingerBase2 - 5;
			break;
		}
		glutPostRedisplay();
		break;
	case 'O':
		fingerUp2 = fingerUp2 - 5;
		if (fingerUp2 < -90) {
			fingerUp2 = fingerUp2 + 5;
			break;
		}
		glutPostRedisplay();
		break;
	case 'o':
		fingerUp2 = fingerUp2 + 5;
		if (fingerUp2 > 5) {
			fingerUp2 = fingerUp2 - 5;
			break;
		}

		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

static void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			moving = 1;
			startx = x;
			starty = y;
		}
		if (state == GLUT_UP) {
			moving = 0;
		}
	}
}


static void motion(int x, int y)
{
	if (moving) {
		angle = angle + (x - startx);
		angle2 = angle2 + (y - starty);
		startx = x;
		starty = y;
		glutPostRedisplay();
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(2000, 1000);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(argv[0]);
	init();
	glutMotionFunc(motion);
	glutMouseFunc(mouse);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboard);


	glutMainLoop();
	return 0;
}