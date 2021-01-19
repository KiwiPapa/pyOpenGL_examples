#include <math.h>
#include <gl/glut.h>
#include <stdlib.h>
#include <windows.h>//�ÿ����ڻ�������
#include <stdio.h>
// ASCII�ַ��ܹ�ֻ��0��127��һ��128���ַ�
#define MAX_CHAR 128
float xPoint = 0; 
float yPoint = 0.0f; 
float d_t = 0.0f;//����ʱ����
int tHz = 20;//���ٺ���ˢ��һ��
static float xRot = 70.0f;
static float yRot = 0.0f;
static float zRot = 100.0f;
//�ӽ�λ��
int pause = 0;//��ͣģʽ
float Amplitude = 1.0f;//���
float Omega = 1.0f;//��
float velocity = 1.0f;//����u
float Phase = 0.0f;//��λ��
//�Შ����������
char show_1[10] ;
void drawString(const char* str) {
    static int isFirstCall = 1;
    static GLuint lists;
    if( isFirstCall ) { // ����ǵ�һ�ε��ã�ִ�г�ʼ��
                        // Ϊÿһ��ASCII�ַ�����һ����ʾ�б�
        isFirstCall = 0;
        // ����MAX_CHAR����������ʾ�б���
        lists = glGenLists(MAX_CHAR);
        // ��ÿ���ַ��Ļ������װ����Ӧ����ʾ�б���
        wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
    }
    // ����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�
    for(; *str!='\0'; ++str)
        glCallList(lists + *str);
}
void RenderScene(void) {
	//�õ�ǰ�����ɫ�������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����һ����ע�ͣ���ôǰһ֡��ͼ�񲻻ᱻ���
	//�������״̬��������ת
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	gluLookAt(70.0f, 0.0f, 100.0f, 70.0f, 0.0f, 0, 0, 1, 0);
	glRasterPos3f(100.0f,-15.0f,0.0f);//��ʾ���ֵ�����
	sprintf(show_1,"A=%f",Amplitude);//Ψһ�õ�stdio.h�ĺ���
    drawString(show_1);//������ʾ����
	glRasterPos3f(100.0f,-18.0f,0.0f);
	sprintf(show_1,"w=%f",Omega);
    drawString(show_1);
	glRasterPos3f(100.0f,-21.0f,0.0f);
	sprintf(show_1,"u=%f",velocity);
    drawString(show_1);
	glRasterPos3f(100.0f,-24.0f,0.0f);
	sprintf(show_1,"p=%f",Phase);
    drawString(show_1);
	glPointSize(2);
	glLineWidth(3);
	glShadeModel(GL_SMOOTH);
	glBegin(GL_LINES);
	glColor3ub(255, 0, 0);
	glVertex3f(-6.0f,  0.0f, 0.0f);
	glVertex3f( 160.0f,  0.0f, 0.0f);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f( 70.0f, -12.0f, 0.0f);
	glVertex3f( 70.0f,  12.0f, 0.0f);
	glEnd();//��������ϵ
	for(xPoint=0;xPoint<255;xPoint+=0.1f)
	{
		yPoint=Amplitude*sin(Omega*(d_t-xPoint/velocity)+Phase)*5;//����������
		glColor3ub(0, 255, 0);		
		glBegin(GL_POINTS);
		glVertex3f(xPoint, yPoint, 0.0f);
		glEnd();

	}
	if(pause==0)d_t++;else;
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
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f );
} 

void TimerFunc(int value) {
   glutPostRedisplay();//����ǰ�Ĵ������»���
   glutTimerFunc(tHz, TimerFunc, 1);//(���������ص�����ָ�롢����ֵ��
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

void keyboard (unsigned char key, int x, int y) {
   switch (key) {
	   case 'p':  if(pause == 0)pause = 1;else pause = 0;  break;
	   case 'P':  if(pause == 0)pause = 1;else pause = 0;  break;
	   case 'q':  Amplitude += 0.1f;  break;
	   case 'Q':  Amplitude += 0.1f;  break;
	   case 'w':  Amplitude -= 0.1f;  break;
	   case 'W':  Amplitude -= 0.1f;  break;
	   case 'a':  Omega += 0.1f;  break;
	   case 'A':  Omega += 0.1f;  break;
	   case 's':  Omega -= 0.1f;  break;
	   case 'S':  Omega -= 0.1f;  break;
	   case 'z': velocity += 0.1f;  break;
	   case 'Z': velocity += 0.1f;  break;
	   case 'x': if(velocity>0.1f)velocity -= 0.1f;  break;
	   case 'X': if(velocity>0.1f)velocity -= 0.1f;  break;
	   case 'e': Phase += 0.3927f;  break;
	   case 'E': Phase += 0.3927f;  break;
	   case 'r': Phase -= 0.3927f;  break;
	   case 'R': Phase -= 0.3927f;  break;
	   case 27:   exit(0); 
	   default:   break;
   }
	glutPostRedisplay();
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(800, 600);
	glutCreateWindow("���Ĳ�����p��ͣ��qw�����as���ٶȣ�zx���٣�er��λ");
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(250, TimerFunc, 1);
	SetupRC();
	glutMainLoop();
	return 0;
}
