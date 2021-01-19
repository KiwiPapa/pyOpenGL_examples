#include <math.h>
#include <gl/glut.h>
#include <stdlib.h>
#include <windows.h>//�ÿ����ڻ�������
#include <stdio.h>
// ASCII�ַ��ܹ�ֻ��0��127��һ��128���ַ�
#define MAX_CHAR 128
#define grav 6.67
//������������������Ϊ10��-11�η�ţ��ƽ����ÿƽ��ǧ��
float m_0 = 1.0f;//Ĭ�����������Ϊ̫���������������壩������Ϊ10��30�η�ǧ��
float angle_1 = 0.0f;//����1��ת�ĽǶ�
float r_1 = 1.0f;
float dAngle_1 = 6.0f;//��λʱ����ת���ĽǶȣ������ٶȣ�����ֱ�Ӹ�����ʼ���ٶ�
int n_1 = 0;//������
int n_2 = 0;//������
int n_3 = 0;//������
float angle_2 = 0.0f;
float r_2 = 1.5f;
float dAngle_2 = 0.0f;//�����������
float dAngle_3 = 0.0f;//���ٶȵĲ�ֵ
float angle_3 = 0.0f;//���ٶȲ�ֵ������
float ellipseAng=0.0f;//�Ƕ��ۼ���
static float xRot = 0.5f;
static float yRot = 0.0f;
static float zRot = 6.0f;
//�ӽ�λ��
int trackLines = 1;//�����л�����Ƿ���ʾ
int pause = 0 ;//��ͣ������
float bgc = 0.3f;//����ɫ
int sun_color = 255;//̫����ɫ����1
int flash_mode = 20;//��˸ָʾ��
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����һ����ע�ͣ���ôǰһ֡��ͼ�񲻻ᱻ���
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	gluLookAt(xRot, yRot, zRot, xRot, yRot, 0, 0, 1, 0);//��4~6��������������׷��ĳһ������
	glRasterPos3f(xRot+1.0f,yRot-1.5f,0.0f);//��ʾ���ֵ�����
	sprintf(show_1,"N1=%d",n_1);//Ψһ�õ�stdio.h�ĺ���
    drawString(show_1);//������ʾ����
	glColor3ub(255, 0, 255);
	glRasterPos3f(xRot+1.0f,yRot-1.8f,0.0f);
	sprintf(show_1,"N2=%d",n_2);
	drawString(show_1);
	glColor3ub(0, 255, 255);
	glRasterPos3f(xRot+1.0f,yRot-2.1f,0.0f);
	sprintf(show_1,"MEET=%d",n_3);
	drawString(show_1);
	glTranslatef(0.0f,0.0f,0.0f);	//(x,y,z)(x�ң�y�ϣ�zָ����ڣ�
	glColor3ub(255, 2, 0);//�����ɫ
	if(trackLines==1)
	{
//		glPointSize(1);
		for(ellipseAng=0.0f;ellipseAng<360.0f;ellipseAng+=0.1)
		{
		glRotatef(0.1f, 0.0f, 0.0f, 1.0f);
		glBegin(GL_POINTS);
		glVertex3f( r_1, 0.0f, 0.0f);
		glEnd();
			glBegin(GL_POINTS);
			glVertex3f( r_2, 0.0f, 0.0f);
			glEnd();
		}//����һ�����
	ellipseAng=0.0f;
	}
	glColor3ub(255, sun_color, 0);  //̫����ɫ����ɫ
	glutSolidSphere(0.06f, 18, 17);  // ����̫��//��Ⱦһ�����壬����Ϊԭ�㣨�뾶��double������Z�����߶�Ϊֱ���ֲ���Բ���ߵ�������Χ����Z����Χ���ߵ�������
	glColor3ub(0,0,255);   // ����1��ɫ
	glRotatef(angle_1, 0.0f, 0.0f, 1.0f);
	glTranslatef(r_1,0.0f,0.0f);//����1����
	glutSolidSphere(0.06f, 30, 17);
	glTranslatef(-r_1,0.0f,0.0f);
	glRotatef(-angle_1, 0.0f, 0.0f, 1.0f);//���껹ԭ
	angle_1 += (dAngle_1*pause);
	if(angle_1>=360.0f){angle_1 -= 360.0f;n_1++;}//���Ƕ���ֵ������0��360����ֹ�������
	glColor3ub(255,0,255);
	glRotatef(angle_2, 0.0f, 0.0f, 1.0f);
	glTranslatef(r_2,0.0f,0.0f);
	glutSolidSphere(0.06f, 30, 17);
	glRotatef(-angle_2, 0.0f, 0.0f, 1.0f);
	angle_2 += (dAngle_2*pause);
	if(angle_2>=360.0f){angle_2 -= 360.0f;n_2++;}
	angle_3 += (dAngle_3*pause);
	if(angle_3>=360.0f){angle_3 -= 360.0f;n_3++;flash_mode = 0;dAngle_1 = 0.0f;dAngle_2 = 0.0f;dAngle_3 = 0.0f;}
	if(flash_mode < 20){flash_mode++;if((flash_mode%2)==0)sun_color = 125;else sun_color = 0;if(flash_mode == 20){sun_color = 255;dAngle_1 = 6.0f;}dAngle_2 = dAngle_1*sqrt(r_1*r_1*r_1/r_2/r_2/r_2);dAngle_3 = dAngle_1 - dAngle_2;}
		glColor3ub(0, 0, 255); //���ֵ���ɫ
	glPopMatrix();	
	glutSwapBuffers();
}  
void SetupRC() {
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glClearColor(bgc, bgc, bgc, 0.0f );
} 
void TimerFunc(int value) {
   glutPostRedisplay();//����ǰ�Ĵ������»���
   glutTimerFunc(50, TimerFunc, 1);//(���������ص�����ָ�롢����ֵ��
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
		if(zRot<20.0f)zRot += 0.5f; break;
	case GLUT_LEFT_BUTTON:
		if(zRot>1.0f)zRot -= 0.5f; break;
	}

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
	   case 'q':  if(trackLines==1)trackLines=0;else trackLines=1;break;
	   case 'Q':  if(trackLines==1)trackLines=0;else trackLines=1;break;
	   case 'p':  if(pause==1)pause=0;else pause=1;break;
	   case 'P':  if(pause==1)pause=0;else pause=1;break;
//	   case GLUT_KEY_F2: trackLines = 1;  break;
//	   case GLUT_KEY_F3: trackLines = 0;  break;

	   case 27:   exit(0); 
	   default:   break;
   }
	glutPostRedisplay();
}
int main(int argc, char* argv[]) {
	dAngle_2 = dAngle_1*sqrt(r_1*r_1*r_1/r_2/r_2/r_2);
	dAngle_3 = dAngle_1 - dAngle_2;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(800, 600);
	glutCreateWindow("��P��ʼ/��ͣ����Q�ر�/�򿪹����");
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(myMouse);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(250, TimerFunc, 1);
	SetupRC();
	glutMainLoop();
	return 0;
}
