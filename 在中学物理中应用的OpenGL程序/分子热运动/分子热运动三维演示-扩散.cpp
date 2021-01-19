#include <iostream>
#include <gl/glut.h>
#include "ViewerTrackball.h" 
#include <stdlib.h>
#include <time.h>//�ÿ��������������
#include <windows.h>//�ÿ����ڻ�������
#include <stdio.h>
#include <math.h>
#define MAX_CHAR 128
int xBall = 0; //ĳ�����λ�ú�����
float yBall = 0.0f; //ĳ�����λ��������
float d_t = 0.0f;//����ʱ����
float multi = 0.005f;//����λ�Ƶı��ʣ��������Ƴ��������ٶ�
int numMax = 0;//��������
int num_1 = 300;//���Ӽ���
int i = 0;//���Ӽ�����
int r = 0;//������������ڷ�����̬�ֲ�
int cols = 0;//��ײ������
int ASurface = 0,BSurface = 0,CSurface = 0,DSurface = 0,ESurface = 0,FSurface = 0;//���������ײ������
float *xCoord; //ĳ�����λ�ú�����
float *yCoord; //ĳ�����λ��������
float *zCoord; 
float *xSpeed;
float *ySpeed;
float *zSpeed;//ĳ������ٶ�
float rSpeed;//�����ٶȵ��м����
float x_rand;//�����������ڿ��Ƶ������˶�
int initi = 0;//���������ʼ�����
int setMode = 0;
static float xRot = 0.0f;
static float yRot = 0.0f;
static float zRot = 1.8f;
//�ӽ�λ��
char show_1[20] ;
int clourOne = 0;//ȡ����,������ɫ
void drawString(const char* str) {
    static int isFirstCall = 1;
    static GLuint lists;
    if( isFirstCall ) {
        isFirstCall = 0;
        lists = glGenLists(MAX_CHAR);
        wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
    }
    for(; *str!='\0'; ++str)
        glCallList(lists + *str);
}

namespace ViewerN {

bool   isListCreated (GL_FALSE);
float  bgdColor[3] = {0.7f, 0.7f, 0.7f};
float  fgdColor[3] = {0.0f, 0.0f, 1.0f};
int    flag(0); 

Trackball trackball;
void init(void);
void display(void);
void resize(int _width, int _height);
void mouse(int _button, int _state, int _x, int _y);
void motion(int _x, int _y);
void idle(void); 

void init(void) {
   trackball.init(GLUT_LEFT_BUTTON);  // <<================= !!!!

	glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS);
 
}

void display(void) { 
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����һ����ע�ͣ���ôǰһ֡��ͼ�񲻻ᱻ���
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	gluLookAt(xRot, yRot, zRot, xRot, yRot, 0, 0, 1, 0);
	trackball.matrix();
	trackball.isRedraw_ = GL_FALSE;
	glTranslatef(-0.5f,-0.5f,-0.5f);//�ƶ������ӽ�
	if(setMode == 0)
	{
		glRasterPos3f(xRot-0.3f,yRot+0.3f,0.0f);//��ʾ���ֵ�����
		drawString("Press e use point mode");//������ʾ����
		glRasterPos3f(xRot-0.3f,yRot-0.0f,0.0f);
		drawString("Press r use cube mode");
	}//��ӭ���棬ѡ����ģʽ
	if(setMode > 0)
	{
		if(numMax == 0)
		{
			glRasterPos3f(xRot-0.3f,yRot+0.3f,0.0f);
			drawString("Press v to increase");
			glRasterPos3f(xRot-0.3f,yRot+0.1f,0.0f);
			drawString("Press b to reduce");
			glRasterPos3f(xRot-0.3f,yRot-0.1f,0.0f);
			drawString("Press c to start"); 
			sprintf(show_1,"number=%d",num_1);
			glRasterPos3f(xRot-0.3f,yRot-0.3f,0.0f);
			drawString(show_1);
		}
	}//ѡ��������������600
	if(numMax>0)
	{
		if(initi==0)
		{
			xCoord = (float *)malloc(numMax * sizeof(float));
			yCoord = (float *) malloc(numMax * sizeof(float));//�����ڴ棬������̬����
			zCoord = (float *) malloc(numMax * sizeof(float));
			xSpeed = (float *) malloc(numMax * sizeof(float));
			ySpeed = (float *) malloc(numMax * sizeof(float));
			zSpeed = (float *) malloc(numMax * sizeof(float));
			if(setMode == 1)
			{
				for(i=0;i<numMax;i++)
				{
					if((i%2)==0)
						*(xCoord+i) = 0.25f;
					else
						*(xCoord+i) = 0.75f;
					*(yCoord+i) = 0.5f;
					*(zCoord+i) = 0.5f;
				}
			}
			if(setMode == 2)
			{
				for(i=0;i<numMax;i++)
				{
					*(xCoord+i) = rand()/(double)(RAND_MAX)/2;
					if((i%2)==1)
						*(xCoord+i) += 0.5f;		
					*(yCoord+i) = rand()/(double)(RAND_MAX);
					*(zCoord+i) = rand()/(double)(RAND_MAX);//���ÿ�����ӵ�λ��
					
				}//��ʼ��ÿ�����ӵ�λ��
			}
			for(i=0;i<numMax;i++)
			{
				*(xSpeed+i) = (rand()/(double)(RAND_MAX)-0.5f);
				*(ySpeed+i) = (rand()/(double)(RAND_MAX)-0.5f);
				*(zSpeed+i) = (rand()/(double)(RAND_MAX)-0.5f);
				rSpeed = (*(xSpeed+i))*(*(xSpeed+i))+(*(ySpeed+i))*(*(ySpeed+i))+(*(zSpeed+i))*(*(zSpeed+i));
				while(rSpeed > 0.75f)
				{
					*(xSpeed+i) = (rand()/(double)(RAND_MAX)-0.5f);
					*(ySpeed+i) = (rand()/(double)(RAND_MAX)-0.5f);
					*(zSpeed+i) = (rand()/(double)(RAND_MAX)-0.5f);
				}//ʹ�ò������ٶ�ʸ���ֲ���һ��Բ��
				rSpeed=sqrt(rSpeed);
				if(rSpeed>0)rSpeed = 1/rSpeed;else{rSpeed = 1;*(xSpeed+i) = 1.0f;}//��ֹ�����һ��Ϊ0��ʸ������bug
				*(xSpeed+i)=*(xSpeed+i)*rSpeed;
				*(ySpeed+i)=*(ySpeed+i)*rSpeed;
				*(zSpeed+i)=*(zSpeed+i)*rSpeed;
				//����һ����СΪ1������������ٶ�
				for(r=0;r<1000;r++)
				{
					*(xSpeed+i) +=(rand()/(double)(RAND_MAX)-0.5f)/20;
					*(ySpeed+i) +=(rand()/(double)(RAND_MAX)-0.5f)/20;
					*(zSpeed+i) +=(rand()/(double)(RAND_MAX)-0.5f)/20;
				}//ʹ���ٶȷ�����̬�ֲ����⼸���㷨����Ҫ�����û���⼸������ô�ٶ�һ��ʼ��ƽ���ֲ�������������ٶȲ��ϵظ��裬�ٶȻ��û��ҡ�
			}
			initi=1;
		}
	
			glShadeModel(GL_SMOOTH);
			glColor3ub(255, 0, 0);
			glBegin(GL_LINE_LOOP);
			glVertex3f(-0.01f, 1.01f, 0.0f);
			glColor3ub(255, 255, 0);
			glVertex3f(1.01f, 1.01f, 0.0f);
			glColor3ub(0, 255, 0);
			glVertex3f(1.01f, -0.01f, 0.0f);
			glColor3ub(255, 0, 255);
			glVertex3f(-0.01f, -0.01f, 0.0f);
			glEnd();
			glBegin(GL_LINE_LOOP);
			glVertex3f(-0.01f, 1.01f, 1.01f);
			glColor3ub(255, 255, 0);
			glVertex3f(1.01f, 1.01f, 1.01f);
			glColor3ub(0, 255, 0);
			glVertex3f(1.01f, -0.01f, 1.01f);
			glColor3ub(255, 0, 255);
			glVertex3f(-0.01f, -0.01f, 1.01f);
			glEnd();
			glBegin(GL_LINES);
			glVertex3f(-0.01f, 1.01f, 0.0f);
			glColor3ub(255, 255, 0);
			glVertex3f(-0.01f, 1.01f, 1.01f);
			glVertex3f(1.01f, 1.01f, 0.0f);
			glColor3ub(0, 255, 0);
			glVertex3f(1.01f, 1.01f, 1.01f);
			glVertex3f(1.01f, -0.01f, 0.0f);
			glColor3ub(255, 0, 255);
			glVertex3f(1.01f, -0.01f, 1.01f);
			glVertex3f(-0.01f, -0.01f, 0.0f);
			glVertex3f(-0.01f, -0.01f, 1.01f);
			glEnd();//���ƿ��

		

		for(i=0;i<numMax;i++)
		{
			glTranslatef(*(xCoord+i),*(yCoord+i),*(zCoord+i));//�ƶ���������ĵ�

				clourOne=i%2;
				switch(clourOne)
				{
					case 0:glColor3ub(255, 0, 0);break;//��ɫ
					case 1:glColor3ub(0, 0, 255);break;//��ɫ
				}
			glutSolidSphere(0.01f, 18, 17);
			glTranslatef(-*(xCoord+i),-*(yCoord+i),-*(zCoord+i));//�ƻ�ȥ

			*(xCoord+i)+=(*(xSpeed+i)*multi);
				if(*(xCoord+i)>1.0f){*(xCoord+i)=1.0f;*(xSpeed+i)=0.0f-*(xSpeed+i);}
				if(*(xCoord+i)<0.0f){*(xCoord+i)=0.0f;*(xSpeed+i)=0.0f-*(xSpeed+i);}

			*(yCoord+i)+=(*(ySpeed+i)*multi);
				if(*(yCoord+i)>1.0f){*(yCoord+i)=1.0f;*(ySpeed+i)=0.0f-*(ySpeed+i);}
				if(*(yCoord+i)<0.0f){*(yCoord+i)=0.0f;*(ySpeed+i)=0.0f-*(ySpeed+i);}

			*(zCoord+i)+=(*(zSpeed+i)*multi);
				if(*(zCoord+i)>1.0f){*(zCoord+i)=1.0f;*(zSpeed+i)=0.0f-*(zSpeed+i);}
				if(*(zCoord+i)<0.0f){*(zCoord+i)=0.0f;*(zSpeed+i)=0.0f-*(zSpeed+i);}

		}
	}
	glPopMatrix();
	glutSwapBuffers();
}
void resize(int _width, int _height) { 
   trackball.reshape(_width, _height);
   glViewport(0, 0, _width, _height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   float XYratio = (float)_width/(float)_height;
   gluPerspective(50.0, XYratio, 1.0,-1000);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void mouse(int _button, int _state, int _x, int _y) { 
   trackball.mouse(_button, _state, _x, _y);
   glutPostRedisplay();
}

void motion(int _x, int _y) { 
   trackball.motion(_x, _y); 
   glutPostRedisplay();
}
}


void SetupRC() {
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glClearColor(0.3f, 0.3f, 0.3f, 0.0f );
} 

void TimerFunc(int value) {
   glutPostRedisplay();//����ǰ�Ĵ������»���
   glutTimerFunc(15, TimerFunc, 1);//(���������ص�����ָ�롢����ֵ��
}

void keyboard (unsigned char key, int x, int y) {
      switch (key) {
	   case 'a':  xRot -= 0.2f;  break;
	   case 'A':  xRot -= 0.2f;  break;
	   case 'd':  xRot += 0.2f;  break;
	   case 'D':  xRot += 0.2f;  break;
	   case 'w':  yRot += 0.2f;  break;
	   case 'W':  yRot += 0.2f;  break;
	   case 's':  yRot -= 0.2f;  break;
	   case 'S':  yRot -= 0.2f;  break;
	   case 'z': if(multi>0.0f)multi -= 0.005f;  break;
	   case 'Z': if(multi>0.0f)multi -= 0.005f;  break;
	   case 'x': if(multi<0.05f)multi += 0.005f;  break;
	   case 'X': if(multi<0.05f)multi += 0.005f;  break;
	   case 'e': if(setMode==0)setMode=1;break;
	   case 'E': if(setMode==0)setMode=1;break;
	   case 'r': if(setMode==0)setMode=2;break;
	   case 'R': if(setMode==0)setMode=2;break;
	   case 'v': if(numMax==0){if(num_1<1000)num_1+=50;}break;
	   case 'V': if(numMax==0){if(num_1<1000)num_1+=50;}break;
	   case 'b': if(numMax==0){if(num_1>50)num_1-=50;}break;
	   case 'B': if(numMax==0){if(num_1>50)num_1-=50;}break;
	   case 'c': if(numMax==0)numMax=num_1;break;
	   case 'C': if(numMax==0)numMax=num_1;break;
	   case 27:   exit(0); 
	   default:   break;
   }
	glutPostRedisplay();
}

int main(int argc, char *argv[]) { 
	srand((unsigned) time(NULL));//��ʼ�������������
   glutInitWindowPosition(400, 0);
   glutInitWindowSize(620,620);
   glutInitDisplayMode (GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE );  
   if (glutCreateWindow ("��ɢ��ά��ʾ") == GL_FALSE)
      exit (1);
	ViewerN::init(); 
	glutDisplayFunc(ViewerN::display);
   glutReshapeFunc(ViewerN::resize);
   	glutKeyboardFunc(keyboard);
   glutMouseFunc(ViewerN::mouse);
   glutMotionFunc(ViewerN::motion);
   glutTimerFunc(250, TimerFunc, 1);
   SetupRC();
   glutMainLoop();
   return 0;
}
