#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include <freeglut.h>

using namespace std;
void DrawScene(void);
void InitOpenGL(void);
void ReshapeWindow(int width, int height);
int mainWindow;

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
    	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    	glutInitWindowSize(800, 800);
	glutInitWindowPosition(150,150);
    	mainWindow = glutCreateWindow("Sierpinski carpet");

	if(mainWindow == 0)
	{
		puts("unable to create window!!!\n");
		exit(-1);
	}

	glutSetWindow(mainWindow);
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(ReshapeWindow);
	InitOpenGL();
	glutMainLoop();
	return(0);
}

void printColor(GLdouble c_x, GLdouble c_y,GLdouble side)
{
	glBegin(GL_POLYGON);
	glColor3f(1.0f,0.0f,0.0f);
	glVertex2f(c_x,c_y);
	glVertex2f(c_x , c_y-side);
	glVertex2f(c_x-side, c_y- side);
	glVertex2f(c_x-side,c_y);
	glEnd();
}

void printSierpinskiCarpet(GLdouble c_x, GLdouble c_y,GLdouble side, int iteration)
{
	if(iteration>0)
	{
		printSierpinskiCarpet(c_x-side/3,c_y+side/3, side/3, iteration-1);  	//right, top
		printSierpinskiCarpet(c_x,c_y+side/3,side/3,iteration-1);		//center, top
		printSierpinskiCarpet(c_x+side/3, c_y+side/3,side/3,iteration-1);	//left, top
		printSierpinskiCarpet(c_x-side/3,c_y,side/3,iteration-1);		//left, center
		printSierpinskiCarpet(c_x+side/3,c_y,side/3,iteration-1);		//right, center
		printSierpinskiCarpet(c_x-side/3,c_y-side/3,side/3,iteration-1);	//left, down
		printSierpinskiCarpet(c_x,c_y-side/3,side/3,iteration-1);		//center, down
		printSierpinskiCarpet(c_x + side/3,c_y-side/3,side/3,iteration-1);	//right, down																	
	}
	else //print square
	{
		printColor(c_x,c_y,side);
	}
}

void DrawScene(void)
{
	int iterationNumber;
	cout<<"how many iteration?"<<endl;
	cin>>iterationNumber;
 	glClear(GL_COLOR_BUFFER_BIT);
	printSierpinskiCarpet(0.0f,0.0f,70.0f, iterationNumber);
	glFlush();
}

void InitOpenGL(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void ReshapeWindow(int width, int height)
{
	int aspectRatio;
	if(height == 0) height = 1;
	aspectRatio = width / height;
	glViewport(0, 0, width, height);
    	glMatrixMode(GL_PROJECTION); 
    	glLoadIdentity();
    
    	if(width <= height)
		glOrtho(-100.0, 100.0, -100.0/aspectRatio, 100.0/aspectRatio, 1.0, -1.0);  
    	else
		glOrtho(-100.0*aspectRatio, 100.0*aspectRatio, -100.0, 100.0, 1.0, -1.0);
 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	
}
