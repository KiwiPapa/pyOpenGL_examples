#include <iostream>
#include <gl/glut.h>
#include "ViewerTrackball.h" 

int xBall = 0; //ĳ�����λ�ú�����
float yBall = 0.0f; //ĳ�����λ��������
float zBall = 0.0f;//������ά��ʾ
float d_t = 0.0f;//����ʱ����
int tHz = 50;//���ٺ���ˢ��һ��
int clourMode = 1;//��ɫģʽ
int clourOne = 0;//ģʽ1�µ�ȡ����
static float xRot = 0.0f;
static float yRot = 0.0f;
static float zRot = 100.0f;
//�ӽ�λ��
namespace ViewerN {
//��������
bool   isListCreated (GL_FALSE);             //�����Ƿ�����������ʾ�б� 
float  bgdColor[3] = {0.7f, 0.7f, 0.7f};     //����ɫ
float  fgdColor[3] = {0.0f, 0.0f, 1.0f};     //ǰ��ɫ 
int    flag(0);
Trackball trackball; 

void init(void);
void display(void);
void resize(int _width, int _height);
void mouse(int _button, int _state, int _x, int _y);
void motion(int _x, int _y);
void idle(void); 
 
void init(void) { //OGL��ʼ������
   trackball.init(GLUT_LEFT_BUTTON);

	glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS);
 
}

void display(void) {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	gluLookAt(xRot, yRot, zRot, xRot, yRot, 0, 0, 1, 0);
	trackball.matrix(); //��ת  // <<================= !!!!
	trackball.isRedraw_ = GL_FALSE;
	glBegin(GL_LINES);
	glLineWidth(8);
	glShadeModel(GL_SMOOTH);
	glColor3ub(255, 0, 0);
	glVertex3f(-160.0f,  0.0f, 0.0f);
	glVertex3f( 160.0f,  0.0f, 0.0f);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f( 0.0f, -12.0f, 0.0f);
	glVertex3f( 0.0f,  12.0f, 0.0f);
	glEnd();//��������ϵ
	glTranslatef(-100.0f,0,0);
	for(xBall=0;xBall<255;xBall++)
	{
		yBall=sin(xBall+d_t*0.1)*5;//����������
		zBall=cos(xBall+d_t*0.1)*5;
		glTranslatef(0.0f,yBall,zBall);//�ƶ���������ĵ�
		if(clourMode==0)
		{
			if(yBall>4.0f)
				glColor3ub(255, 0, 0);
				else if(yBall>3.0f)
				glColor3ub(255, 125, 0);
				else if(yBall>2.0f)
				glColor3ub(255, 255, 0);
				else if(yBall>1.0f)
				glColor3ub(0, 255, 0);
				else if(yBall>0.0f)
				glColor3ub(0, 0, 255);
				else if(yBall>-1.0f)
				glColor3ub(0, 255, 255);
				else if(yBall>-2.0f)
				glColor3ub(255, 0, 255);
				else if(yBall>-4.0f)
				glColor3ub(255, 125, 255);
				else
					glColor3ub(255, 255, 255);


		}
		else if(clourMode==1)
		{
			clourOne=(xBall)%7;
			switch(clourOne)
			{
			case 0:glColor3ub(255, 0, 0);break;//��ɫ
			case 1:glColor3ub(255, 125, 0);break;//��ɫ
			case 2:glColor3ub(255, 255, 0);break;//��ɫ
			case 3:glColor3ub(0, 255, 0);break;//��ɫ
			case 4:glColor3ub(0, 0, 255);break;//��ɫ
			case 5:glColor3ub(0, 255, 255);break;//��ɫ
			case 6:glColor3ub(255, 0, 255);break;//��ɫ
			}
		}

		glutSolidSphere(0.5f, 18, 17);
		glTranslatef(1.0f,-yBall,-zBall);//�ƶ�����һ�����ƽ���
	}
	d_t++;
	glPopMatrix();	
	glutSwapBuffers();
}
void resize(int _width, int _height) {   //����ȷ�����ڴ�С
   trackball.reshape(_width, _height);
   glViewport(0, 0, _width, _height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   float XYratio = (float)_width/(float)_height;
   gluPerspective(20.2, XYratio, 1.0,-1000);

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
   glutTimerFunc(tHz, TimerFunc, 1);//(���������ص�����ָ�롢����ֵ��
}

void keyboard (unsigned char key, int x, int y) {
   switch (key) {
	   case 'a':  xRot -= 1.0f;  break;
	   case 'A':  xRot -= 1.0f;  break;
	   case 'd':  xRot += 1.0f;  break;
	   case 'D':  xRot += 1.0f;  break;
	   case 'w':  yRot += 1.0f;  break;
	   case 'W':  yRot += 1.0f;  break;
	   case 's':  yRot -= 1.0f;  break;
	   case 'S':  yRot -= 1.0f;  break;
	   case 'z': if(tHz>9)tHz -= 5;  break;
	   case 'Z': if(tHz>9)tHz -= 5;  break;
	   case 'x': if(tHz<50)tHz += 5;  break;
	   case 'X': if(tHz>9)tHz += 5;  break;
	   case 'c': {clourMode++;if(clourMode>2)clourMode=0;} break;
	   case 27:   exit(0); 
	   default:   break;
   }
	glutPostRedisplay();
}
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) { 
   glutInitWindowPosition(400, 0);
   glutInitWindowSize(620,620);
   glutInitDisplayMode (GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE );  
   if (glutCreateWindow ("�Შ��ά��ʾ") == GL_FALSE)
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
