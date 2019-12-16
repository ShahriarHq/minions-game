#include<stdio.h>
#include <bits/stdc++.h>
#include<stdlib.h>
#include<math.h>
#include <string.h>
#include <windows.h>
#include<MMSystem.h>
#include <glut.h>
#include <time.h>
#define pi (2*acos(0.0))
#define PI 3.1416

using namespace std;

float load = -45.0;
int startgame = 0;
int stop = 0;
int score = 0;

bool gameOver=true;
static float tx = 0.0;  ///minion position x
static float ty = 0.0;  ///minion position y
static float ly = 0, lx=-7;  ///bullet scale y
//static float sy = 0.6;  // scale y
float ball_x=-200, ball_y=0.0, ball_z= 0.00;
static int flag=0, ball_r=5, ball_r1=5, flag1=0;
static int g_counter = 0;
static int j=0;
static float speed = 0.03;

static float tx1 = 0.0;
static float ty1 = 0.0;





double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;
double incx=50, incy;
int state, state1;
double limit=0.0;



struct point
{
	double x,y,z;
};

void push_pop(void)
{
   // glPushMatrix();
       glRotatef(45, 0, 0, 1);
        glPushMatrix(); // Furthest Triangle, Draw first


            //glRotatef(45, 0, 0, 1);
            glTranslatef(-20, 0, 0);
            glScaled(2, 1, 0);              //x,y,z borabor kototuku lomba hobe sheta dekhabe and sheta 2gun kore barbe.
            glColor3f(0.0, 0.0, 1.0);        //push ppop matrix r moddhe rakhsi jate karo upore effect nna kore
            glBegin(GL_POLYGON);
                glVertex2f(10, 10);
                glVertex2f(10, 0);
                glVertex2f(-10, 0);
            glEnd();
        glPopMatrix();

        glPushMatrix(); // Middle Triangle, Draw 2nd
            glColor3f(0.0, 1.0, 0.0);
            glBegin(GL_POLYGON);
                glVertex2f(10, 10);
                glVertex2f(10, 0);
                glVertex2f(-10, 0);
            glEnd();
        glPopMatrix();

        glPushMatrix(); // Nearest Triangle, Draw last
            glTranslatef(20, 0, 0);
            glColor3f(1.0, 0.0, 0.0);
            glBegin(GL_POLYGON);
                glVertex2f(10, 10);
                glVertex2f(10, 0);
                glVertex2f(-10, 0);
            glEnd();
        glPopMatrix();



    //glPopMatrix();

}

void showTextLarge(char text[], int r, int g, int b, int x, int y, int z)
{
    glColor3f(r, g, b);
    glRasterPos3f( x, y, z);
    for(int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
}

void circle(float radius_x, float radius_y)
{
	int i = 0;
	float angle = 0.0;

	glBegin(GL_POLYGON);

		for(i = 0; i < 100; i++)
		{
			angle = 2 * PI * i / 100;
			glVertex3f (cos(angle) * radius_x, sin(angle) * radius_y, 0);
		}

	glEnd();
}

void drawSquare(double a,double b)
{
    //glColor3f(1.0,0.0,0.0);

	glBegin(GL_QUADS);{
		glVertex3f( a, 0,2);
		glVertex3f( a,-b,2);
		glVertex3f(-a,-b,2);
		glVertex3f(-a, 0,2);
	}glEnd();
}

void drawSphere(double radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        glColor3f((double)i/(double)stacks,1,(double)i/(double)stacks);
		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
			}glEnd();
		}
	}
}
void drawSphere1(double radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        //glColor3f((double)i/(double)stacks,1,(double)i/(double)stacks);
		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
			}glEnd();
		}
	}
}



void timer(int value) {
    if(stop == 1)
        return;
    if(load <= 45.0)
        g_counter = -1;
    if(stop == 0) {
        g_counter += 1;
        glutPostRedisplay();
        glutTimerFunc(1000, timer, g_counter);
    }
    if(g_counter%20 == 0)
    {
        speed += 0.03;
    }
}

void timertext()
{
    char text[32] = "TIME: 0";
    //text[0]='T'; text[1]='I'; text[2]='M'; text[3]='E'; text[4]=':'; text[5]=' '; text[6]=' ';
    int strt=7;
    if(g_counter<10)
        strt--;
    int tmp=g_counter;
    while(tmp)
    {
        text[strt--]=(tmp%10)+'0';
        tmp/=10;
    }
    glColor3f(0, 0, 0);
    glRasterPos3f( -200 , 200 , 0.0);
    for(int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}


void scoretext()
{
    char text[32] = "SCORE: 0";
    //text[0]='S'; text[1]='C'; text[2]='O'; text[3]='R'; text[4]='E'; text[5]=':'; text[6]=' '; text[7]=' '; text[8]=' ';
    int strt=8;
    if(score<10)
        strt--;
    int tmp=score;
    while(tmp)
    {
        text[strt--]=(tmp%10)+'0';
        tmp/=10;
    }
    glColor3f(0, 0, 0);
    glRasterPos3f( -99 , 89 , 0.0);
    for(int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
}


float distance(int x1, int y1, int x2, int y2)
{
    // Calculating distance
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    //printf('%f', & a);
}

void gameOverWindow(){
    glClear(GL_COLOR_BUFFER_BIT);
    //Racing Track at the middle start
    glColor3f(0.99f, 0.73f, 0.21f);
    glBegin(GL_QUADS);
    glVertex2f(-6, 10);
    glVertex2f(6, 10);
    glVertex2f(6, -10);
    glVertex2f(-6, -10);
    glEnd();

    showTextLarge("Game Over", 1, 0.4, 0.4, -3, 3, 0);

    char scoreprint[50];

    itoa(score, scoreprint, 10);
    showTextLarge("Score : ", 1, 0, 0, -3, 2, 0);
    showTextLarge(scoreprint, 1, 0, 0, -1.9, 2, 0);

    glFlush();
}


void ballupdate()
{
if(!flag){
    ball_y+=2;
    if(ball_y>20.0) flag=1;
}
if(flag){
    ball_y-=2;
    if(ball_y<-165) flag=0;
}

   ///collison logic

  /*if(distance(ball_x,ball_y,tx,ty-135)>= (ball_r + ball_r1) )
   {
       PlaySound("hitting.wav", NULL, SND_FILENAME| SND_ASYNC);
        printf("Collided");
       gameOverWindow();
            Sleep(50);
   }*/

}



void brick(){

        //brick10
    glPushMatrix();
    glColor3f(0.772549019, 0.309803921, 0.262745098);
    //glScalef(1,1,0.0);
    glTranslatef(193,-189,0);
    drawSquare(14,18);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.772549019, 0.309803921, 0.262745098);
    //glScalef(1,1,0.0);
    glTranslatef(184.5,-170,0);
    drawSquare(23,18);
    glPopMatrix();


        //brick9
    glPushMatrix();
    glColor3f(0.772549019, 0.309803921, 0.262745098);
    //glScalef(1,1,0.0);
    glTranslatef(158,-189,0);
    drawSquare(20,18);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.772549019, 0.309803921, 0.262745098);
    //glScalef(1,1,0.0);
    glTranslatef(140.5,-170,0);
    drawSquare(20,18);
    glPopMatrix();

    //brick8
    glPushMatrix();
    glColor3f(0.772549019, 0.309803921, 0.262745098);
    //glScalef(1,1,0.0);
    glTranslatef(117,-189,0);
    drawSquare(20,18);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.772549019, 0.309803921, 0.262745098);
    //glScalef(1,1,0.0);
    glTranslatef(100,-170,0);
    drawSquare(20,18);
    glPopMatrix();


     //brick7
    glPushMatrix();
    glColor3f(0.772549019, 0.309803921, 0.262745098);
    //glScalef(1,1,0.0);
    glTranslatef(76,-189,0);
    drawSquare(20,18);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.772549019, 0.309803921, 0.262745098);
    //glScalef(1,1,0.0);
    glTranslatef(59,-170,0);
    drawSquare(20,18);
    glPopMatrix();


    //brick6
    glPushMatrix();
    glColor3f(0.772549019, 0.309803921, 0.262745098);
    //glScalef(1,1,0.0);
    glTranslatef(35,-189,0);
    drawSquare(20,18);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.772549019, 0.309803921, 0.262745098);
    //glScalef(1,1,0.0);
    glTranslatef(18,-170,0);
    drawSquare(20,18);
    glPopMatrix();

    //brick5
    glPushMatrix();
    glColor3f(0.772549019, 0.309803921, 0.262745098);
    //glScalef(1,1,0.0);
    glTranslatef(-6.01,-189,0);
    drawSquare(20,18);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.772549019, 0.309803921, 0.262745098);
    //glScalef(1,1,0.0);
    glTranslatef(-23,-170,0);
    drawSquare(20,18);
    glPopMatrix();

    //brick4
    glPushMatrix();
    glColor3f(0.772549019, 0.309803921, 0.262745098);
    //glScalef(1,1,0.0);
    glTranslatef(-47,-189,0);
    drawSquare(20,18);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.772549019, 0.309803921, 0.262745098);
    //glScalef(1,1,0.0);
    glTranslatef(-64,-170,0);
    drawSquare(20,18);
    glPopMatrix();

    //brick3
    glPushMatrix();
    glColor3f(0.772549019, 0.309803921, 0.262745098);
    //glScalef(1,1,0.0);
    glTranslatef(-88,-189,0);
    drawSquare(20,18);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.772549019, 0.309803921, 0.262745098);
    //glScalef(1,1,0.0);
    glTranslatef(-105,-170,0);
    drawSquare(20,18);
    glPopMatrix();

    //brick2
    glPushMatrix();
    glColor3f(0.772549019, 0.309803921, 0.262745098);
    //glScalef(1,1,0.0);
    glTranslatef(-129,-189,0);
    drawSquare(20,18);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.772549019, 0.309803921, 0.262745098);
    //glScalef(1,1,0.0);
    glTranslatef(-145.8,-170,0);
    drawSquare(20,18);
    glPopMatrix();


    //brick1
    glPushMatrix();
    glColor3f(0.772549019, 0.309803921, 0.262745098);
    //glScalef(1,1,0.0);
    glTranslatef(-170,-189,0);
    drawSquare(20,18);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.772549019, 0.309803921, 0.262745098);
    //glScalef(1,1,0.0);
    glTranslatef(-187,-170,0);
    drawSquare(20,18);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.772549019, 0.309803921, 0.262745098);
    //glScalef(1,1,0.0);
    glTranslatef(-199,-189,0);
    drawSquare(8,18);
    glPopMatrix();

// background black
     glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    //glScalef(1,1,0.0);
    glTranslatef(0,-170,0);
    drawSquare(209,40);
    glPopMatrix();




}


void minion(void)
{

    glTranslatef(tx,ty-135,0);
    glScalef(2.5,2.5,0.0);
     glPushMatrix();

    //headEyeBlackCenter:
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glScalef(1,1,0.0);
    glTranslatef(tx1,ty1,0);
    circle(1,1);
    glPopMatrix();
    //headEyeBandLeft:
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glScalef(1,1,0.0);
    glTranslatef(tx1-4,ty1,0);
    glBegin(GL_POLYGON);
    glVertex2f(1.5, 0.5);
    glVertex2f(1.5, -0.5);
    glVertex2f(-1, -0.5);
    glVertex2f(-1, 0.5);
    glEnd();
    glPopMatrix();
    //headLip:
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glScalef(1,1,0.0);
    glTranslatef(tx1,ty1-4,0);
    glBegin(GL_POLYGON);
    glVertex2f(1, 0.1);
    glVertex2f(1, -0.2);
    glVertex2f(-1, -0.2);
    glVertex2f(-1, 0.1);
    glEnd();
    glPopMatrix();
    //headEyeBandRight:
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glScalef(1,1,0.0);
    glTranslatef(tx1+4,ty1,0);
    glBegin(GL_POLYGON);
    glVertex2f(1.5, 0.5);
    glVertex2f(1.5, -0.5);
    glVertex2f(-1, -0.5);
    glVertex2f(-1, 0.5);
    glEnd();
    glPopMatrix();


//headEyeWhite:
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glScalef(1,1,0.0);
    glTranslatef(tx1,ty1,0);
    circle(2.5,2.5);
    glPopMatrix();


    //headEyeBlack:
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glScalef(1,1,0.0);
    glTranslatef(tx1,ty1,0);
    circle(3,3);
    glPopMatrix();

    //headmiddle:
    glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
    glScalef(1,1,0.0);
    glTranslatef(tx1,ty1-5,0);
    glBegin(GL_POLYGON);
    glVertex2f(5, 5);
    glVertex2f(5, -1);
    glVertex2f(-5, -1);
    glVertex2f(-5, 5);
    glEnd();
    glPopMatrix();

       //headup:
   glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glScalef(1,1,0.0);
    glTranslatef(tx1,ty1,0);
    //circle(5,5);
    drawSphere1(ball_r1,30,30);
    glPopMatrix();

    //body:
        glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glScalef(1,1,0.0);
    glTranslatef(tx1,ty1-10,0);
    glBegin(GL_POLYGON);
    glVertex2f(4, 5);
    glVertex2f(4, 2.5);
    glVertex2f(-4, 2.5);
    glVertex2f(-4, 5);
    glEnd();
    glPopMatrix();

     glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glScalef(1,1,0.0);
    glTranslatef(tx1,ty1-12.5,0);
    glBegin(GL_POLYGON);
    glVertex2f(5, 5);
    glVertex2f(5, 3.5);
    glVertex2f(-5, 3.5);
    glVertex2f(-5, 5);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glScalef(1,1,0.0);
    glTranslatef(tx1,ty1-14,0);
    glBegin(GL_POLYGON);
    glVertex2f(5, 5);
    glVertex2f(5, 2.5);
    glVertex2f(-5, 2.5);
    glVertex2f(-5, 5);
    glEnd();
    glPopMatrix();
    //bodyLeft:
   glPushMatrix();
    glColor3f(1.0, 0.8, 0.0);
    glScalef(1,1,0.0);
    glTranslatef(tx1-4,ty1-6.5,0);
    glBegin(GL_POLYGON);
    glVertex2f(1, 1);
    glVertex2f(1, -1);
    glVertex2f(-1, -1);
    glVertex2f(-1, 1);
    glEnd();
    glPopMatrix();
    //bodyRight:
   glPushMatrix();
    glColor3f(1.0, 0.8, 0.0);
    glScalef(1,1,0.0);
    glTranslatef(tx1+4,ty1-6.5,0);
    glBegin(GL_POLYGON);
    glVertex2f(1, 1);
    glVertex2f(1, -1);
    glVertex2f(-1, -1);
    glVertex2f(-1, 1);
    glEnd();
    glPopMatrix();
    //bodyLegLeft:
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.7);
    glScalef(1,1,0.0);
    glTranslatef(tx1-1.1,ty1-12,0);
    glBegin(GL_POLYGON);
    glVertex2f(1, 1);
    glVertex2f(1, -1);
    glVertex2f(-1, -1);
    glVertex2f(-1, 1);
    glEnd();
    glPopMatrix();
    //bodyLegRight:
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.7);
    glScalef(1,1,0.0);
    glTranslatef(tx1+1.1,ty1-12,0);
    glBegin(GL_POLYGON);
    glVertex2f(1, 1);
    glVertex2f(1, -1);
    glVertex2f(-1, -1);
    glVertex2f(-1, 1);
    glEnd();
    glPopMatrix();
    //bodyLegLeftShoe:
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glScalef(1,1,0.0);
    glTranslatef(tx1-1.1,ty1-13.5,0);
    glBegin(GL_POLYGON);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);
    glVertex2f(-1.5, -0.5);
    glVertex2f(-1.5, 0.5);
    glEnd();
    glPopMatrix();
    //bodyLegRightShoe:
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glScalef(1,1,0.0);
    glTranslatef(tx1+1.1,ty1-13.5,0);
    glBegin(GL_POLYGON);
    glVertex2f(1.5, 0.5);
    glVertex2f(1.5, -0.5);
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glEnd();
    glPopMatrix();
    //bodyHandLeft:
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glScalef(1,1,0.0);
    glTranslatef(tx1-5,ty1-7.5,0);
    glBegin(GL_POLYGON);
    glVertex2f(0.5, 2);
    glVertex2f(0.5, -2);
    glVertex2f(-0.5, -2);
    glVertex2f(-0.5, 2);
    glEnd();
    glPopMatrix();
    //bodyHandRight:
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glScalef(1,1,0.0);
    glTranslatef(tx1+5,ty1-7.5,0);
    glBegin(GL_POLYGON);
    glVertex2f(0.5, 2);
    glVertex2f(0.5, -2);
    glVertex2f(-0.5, -2);
    glVertex2f(-0.5, 2);
    glEnd();
    glPopMatrix();
}


void ball(){

float b=0.0;

    glPushMatrix();
     //glColor3f(0,1,0);
     glTranslatef(incx,0,0);
   glTranslatef(ball_x,ball_y,ball_z);
    ballupdate();

    drawSphere(ball_r,30,30);
    glPopMatrix();


cout << distance(ball_x, ball_y, tx1, ty1);
printf("\n");
   ///collison logic

 if(distance(ball_x,ball_y,tx1,ty1)<= (ball_r + ball_r1) )
   {
      flag1=1;
   }
   if(flag1){
    PlaySound("hitting.wav", NULL, SND_FILENAME| SND_ASYNC);
        printf("Collided");
       gameOverWindow();
            Sleep(50);
   }


   /*if(ball_x >= distance(ball_x,tx,ball_y,ty-135) && ball_y <= distance(ball_x,tx,ball_y,ty-135) && distance(ball_x,tx,ball_y,ty-135)>= (ball_r + ball_r1)){
    PlaySound("hitting.wav", NULL, SND_FILENAME| SND_ASYNC);
        printf("Collided");
       gameOverWindow();
            Sleep(50);
   }*/


  /* if((ball_x == tx-6 && ball_x==tx+6) && (ball_y == ty-6 && ball_y == ty+6))
    {

      PlaySound("hitting.wav", NULL, SND_FILENAME| SND_ASYNC);
        printf("Collided");
       gameOverWindow();
            Sleep(50);
    }*/

     /* if(ball_x >= (ball_r + ball_r1) && ball_y <=(ball_r + ball_r1))
    {

      PlaySound("hitting.wav", NULL, SND_FILENAME| SND_ASYNC);
        printf("Collided");
       gameOverWindow();
            Sleep(50);
    }*/

     /*if(tx<-55)
        {
            tx=20;
            ty=rand() % 2 + 0;
        }
        if(tx<-5 && tx>-29 )
        {
            if(ty<-100)
            {
                 PlaySound("hitting.wav", NULL, SND_FILENAME| SND_ASYNC);
                gameOver=true;
                //cout<<"colide"<<endl;
                //eyeG=1,eyeB=1;
            }
        // cout<<"tree X :"<<posX<<endl;
        }
        if(ty<-47 && ty>-55 )
        {
            if(ty<-100)
            {
                 PlaySound("hitting.wav", NULL, SND_FILENAME| SND_ASYNC);
                gameOver=true;
               // cout<<"colide"<<endl;
                //eyeG=1,eyeB=1;
            }
        }*/

}





void just_line()
{
    glPushMatrix();
    glTranslatef(tx-5,ly-100,0);
    glColor3f(0.0f, 0.0f, 1.0f); //BLUE LINE
    glBegin(GL_LINES); // It can be any type Gl_POINT,_LINE



        glVertex2d(6.0,-9.0);
        glVertex2d(6.0,2.0);

    glEnd();
    glPopMatrix();

   // if(lx)

}




/*void gameOverCheck()
{
    if(((ball_z + 1.5 < ty1) && (ball_z > ty1- 11.5f)) && ((ball_z + 0.10 > tx1) && (ball_z + 0.10 < tx1 + 2.0f))){
            printf("Collided");
                 PlaySound("hitting.wav", NULL, SND_FILENAME| SND_ASYNC);
            gameOverWindow();
            Sleep(50);
            //Sleep(5);
    }

    /*if(((playerY + 1.5 < obs2Y) && (playerY > obs2Y - 11.5f)) && ((playerX - 0.5 > obs2X) && (playerX - 0.5  < obs2X + 3.0f))){
            printf("Collided");
             PlaySound("hitting.wav", NULL, SND_FILENAME| SND_ASYNC);
            gameOverWindow();
            Sleep(50);
    }
    if(((playerY - 1.5 > obs3Y) && (playerY < obs3Y + 11.5f)) && ((playerX - 0.5 > obs3X) && (playerX - 0.5  < obs3X + 3.0f))){
            printf("Collided");
             PlaySound("hitting.wav", NULL, SND_FILENAME| SND_ASYNC);
            gameOverWindow();
            Sleep(50);
    }

    //printf("asd%f %f\n", (lrIndex-oppCarX), opppCarY);
}
*/
void attack(){
    ly+=1;
    if(lx== ball_x && ly==ball_y){
            printf("Out");
    }
    if(ly>150){
        ly=ty;
      //  lx=tx;
       // printf("lx:%f\ntx:%f\n",lx,tx);

        glutIdleFunc(NULL);
    }
    glutPostRedisplay();
}

void key(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_LEFT:

		if(tx <= -195) return;
		tx--;
		//lx--;
      //  ball_x--;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
	 if(tx >= 195) return;
		tx++;
        //lx++;
		glutPostRedisplay();
		break;
    case GLUT_KEY_UP:
	 if(ly >=100) return;

        glutIdleFunc(attack);
		//glutPostRedisplay();
		break;



	}
}



void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,1,1,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(100,100,100,	0,0,0,	0,0,1);
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	gluLookAt(0,0,250,	0,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);



	//add objects

	//push_pop();
	//gameOverCheck();
	timertext();
	timer(1);
	ball();
	just_line();
	scoretext();
	//distance(int x1, int y1, int x2, int y2)



    brick();
    minion();

	//drawCircle(5,5);
	//drawAxes();

    //draw_rec();
   // push_pop();
    //simple_trans();
    //rec_animation();







	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){
    //rotation
    angle+=0.005;

	//codes for any changes in Models, Camera
	//linear_oscillation

    if(state ==0 && incx>400){ state =1;}
    if(state ==1 && incx <-5){state =0;}

    if(state == 0) incx+=0.2;
    else incx-=0.2;



    if(state1 ==0 && incy>300){ state1 =1;
    glRotated(45*angle,0,0,1);
    }
    if(state1 ==1 && incy <-300){state1 =0;
    glRotated(-angle,0,1,1);
    }

    if(state1 == 0)
    {

        incy+=0.5;
    }
    else{

        incy-=0.5;
    }


    /*if(state2 ==0 && incz>5){ state2 =1;}
    if(state2 ==1 && incz <-5){state2 =0;}

    if(state2 == 0) incz+=0.5;
    else incz-=0.5;*/

	glutPostRedisplay();
}



void init(){
	//codes for initialization
	/*drawgrid=0;
	drawaxes=1;
	cameraHeight=150.0;
	cameraAngle=1.0;
	angle=0;*/

	//clear the screen
	glClearColor(0,0,0,0);


	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	1000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(900, 700);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	//glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(key);
	//glutMouseFunc(mouseListener);
	glutTimerFunc(1000, timer, g_counter);

	glutMainLoop();		//The main loop of OpenGL


	return 0;
}


