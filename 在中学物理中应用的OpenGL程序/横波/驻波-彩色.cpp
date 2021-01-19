#include <math.h>
#include <gl/glut.h>
#include <stdlib.h>

int xBall = 0; //ĳ�����λ�ú�����
int xdraw = 0; //��������
float yBall = 0.0f; //ĳ�����λ��������
float d_t = 0.0f;//����ʱ����
float tHz = 1.0f;//���ٺ���ˢ��һ��
static float xRot = 50.0f;
static float yRot = 0.0f;
static float zRot = 100.0f;
//�ӽ�λ��
float border_line = 80.0f;
int clourMode = 1;//��ɫģʽ
int clourOne = 0;//ģʽ1�µ�ȡ����
float x_Max = 0.0f ;//����ʱ��λ��
void RenderScene(void) {
	//�õ�ǰ�����ɫ�������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����һ����ע�ͣ���ôǰһ֡��ͼ�񲻻ᱻ���
	//�������״̬��������ת
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	gluLookAt(xRot, yRot, zRot, xRot, yRot, 0, 0, 1, 0);
	glBegin(GL_LINES);
	glLineWidth(8);
	glShadeModel(GL_SMOOTH);
	glColor3ub(255, 0, 0);
	glVertex3f(-6.0f,  0.0f, 0.0f);
	glVertex3f( border_line,  0.0f, 0.0f);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f( border_line, -80.0f, 0.0f);
	glVertex3f( border_line,  80.0f, 0.0f);
 	glEnd();//��������ϵ
	for(xBall=0;xBall<160;xBall++)
	{
		if(xBall<x_Max)
		{
			if(xBall<border_line)
				yBall=sin(xBall-d_t*0.1)*5;//����������
			else
				yBall=sin(xBall-d_t*0.1)*5;
		}
		else
			yBall=0.0f;
		if(xBall<border_line)
		{
			yBall+=30;
			xdraw=xBall;
		}
		else
		{
			xdraw=2*border_line-xBall;
		}
		glTranslatef(xdraw,yBall,0.0f);//�ƶ���������ĵ�
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
			clourOne=xBall%7;
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
		glTranslatef(-xdraw,-yBall,0.0f);//�ָ�����
		if(x_Max<border_line)
		{
			if(xBall<border_line)
			{
				if(xBall>x_Max)
					yBall=0.0f;
				else
					yBall=sin(xBall-d_t*0.1)*5;//+sin((2*border_line-xBall)-d_t*0.1)*5;
				yBall-=30;
				xdraw=xBall;
				glTranslatef(xdraw,yBall,0.0f);
				glutSolidSphere(0.5f, 18, 17);
				glTranslatef(-xdraw,-yBall,0.0f);
			}//����פ��
		}
		else
		{
			if(xBall>border_line)
			{
				if(xBall>x_Max)
					yBall=sin((2*border_line-xBall)-d_t*0.1)*5;
				else
					yBall=sin(xBall-d_t*0.1)*5+sin((2*border_line-xBall)-d_t*0.1)*5;
				yBall-=30;
				xdraw=2*border_line-xBall;
				glTranslatef(xdraw,yBall,0.0f);
				glutSolidSphere(0.5f, 18, 17);
				glTranslatef(-xdraw,-yBall,0.0f);
			}//����פ��
		}
		
	}
	
	if(x_Max<161.0f)
	{
		if(x_Max<border_line)
			x_Max=x_Max+tHz*0.1f;
		else
			x_Max=x_Max+tHz*0.1f;
	}
	d_t+=tHz;
	if(d_t>31415)
		d_t-=31415;
	//�ָ�����״̬
	glPopMatrix();
	glutSwapBuffers();//����������������ָ��
} 

void SetupRC() {
	glEnable(GL_DEPTH_TEST);	// ����֮��glֻ�������ǰ��һ�㣬gl���鵱ǰ����ǰ���Ƿ��б�����أ����������ص��������������Ͳ������
	glFrontFace(GL_CCW);
	//GL_CCW ��ʾ����������ͶӰ����εĶ���˳��Ϊ��ʱ�뷽��ı���Ϊ���档GL_CW ��ʾ����˳��Ϊ˳ʱ�뷽��ı���Ϊ���档
	glEnable(GL_CULL_FACE);		// �����޳�����Ч��
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glClearColor(0.3f, 0.3f, 0.3f, 0.0f );
} 

void TimerFunc(int value) {
   glutPostRedisplay();//����ǰ�Ĵ������»���
   glutTimerFunc(15, TimerFunc, 1);//(���������ص�����ָ�롢����ֵ��
}


void ChangeSize(int w, int h) {//��֤��������󲻷����α�
    float fAspect;
    if (h == 0)  h = 1;
    glViewport(0, 0, w, h);
    fAspect = (float)w/(float)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, fAspect, 1.0, 455.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void myMouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_RIGHT_BUTTON:
		if(zRot<150.0f)zRot += 5.0f; break;
	case GLUT_LEFT_BUTTON:
		if(zRot>50.0f)zRot -= 5.0f; break;
	}
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
	   case 'z': if(tHz>0.1f)tHz -= 0.2f;  break;
	   case 'Z': if(tHz>0.1f)tHz -= 0.2f;  break;
	   case 'x': if(tHz<5.0f)tHz += 0.2f;  break;
	   case 'X': if(tHz<5.0f)tHz += 0.2f;  break;
	   case 'c': {clourMode++;if(clourMode>2)clourMode=0;} break;
	   case 'C': {clourMode++;if(clourMode>2)clourMode=0;} break;
	   case 'q': x_Max = 0.0f;d_t = 0.0f; break;
	   case 'Q': x_Max = 0.0f;d_t = 0.0f; break;
	   case 27:   exit(0); 
	   default:   break;
   }
	glutPostRedisplay();
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(800, 600);
	glutCreateWindow("פ��-��ɫ��wasd�����ӽǣ�zx�����ٶȣ�c������ɫ��q����");
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(myMouse);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(250, TimerFunc, 1);
	SetupRC();
	glutMainLoop();
	return 0;
}
