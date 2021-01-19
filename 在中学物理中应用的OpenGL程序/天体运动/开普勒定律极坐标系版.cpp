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
float a_1 = 0.9f;//����1����볤��
float b_1 = 0.8f;//����1��������
float c_1 = 0.0f;//���㵽���ľ���
float e_1 = 0.0f;//�����귽���е������ʣ�e=c/a,aΪ�볤�ᣬc=sqrt(a^2-b^2),b�ǰ����
float p_1 = 0.0f;//�����귽���е�׼��x=a^2/c,p=a^2/c+c,��׼�ߵ�����ľ���
float r_1 = 0.0f;//����1������������ľ��룬�����귽�̼���
float dAngle_1 = 2.0f;//��λʱ����ת���ĽǶȣ������ٶȣ�����ֱ�Ӹ�����ʼ���ٶ�
float v_1 = 0.0f;//����1���ٶ�
float cW_1 = 0.0f;//����1�ĽǶ�������
float cE_1 = 0.0f;//����1����������
float angle_2 = 0.0f;
float a_2 = 1.1f;
float b_2 = 0.9f;
float c_2 = 0.0f;
float e_2 = 0.0f;
float p_2 = 0.0f;
float r_2 = 0.0f;
float dAngle_2 = 2.0f;
float v_2 = 0.0f;
float cW_2 = 0.0f;
float cE_2 = 0.0f;//����2��Ӧ�ĸ�������
float ellipseAng = 0.0f;//��Բ�Ƕȣ����ڻ�����Բ���
//���ڼ����������������֮��ľ���
static float xRot = 0.5f;
static float yRot = 0.0f;
static float zRot = 6.0f;
//�ӽ�λ��
int trackLines = 1;//�����л�����Ƿ���ʾ
int invisible_2 = 1;//��������2�Ƿ�����

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
	sprintf(show_1,"w=%f",dAngle_1);//Ψһ�õ�stdio.h�ĺ���
    drawString(show_1);//������ʾ����
	glRasterPos3f(xRot+1.0f,yRot-1.8f,0.0f);
	sprintf(show_1,"r1=%f",r_1);
	drawString(show_1);//��ʾ����
	glRasterPos3f(xRot+1.0f,yRot-2.1f,0.0f);
	sprintf(show_1,"v1=%f",v_1);
	drawString(show_1);//��ʾ�ٶ�
	glTranslatef(0.0f,0.0f,0.0f);	//(x,y,z)(x�ң�y�ϣ�zָ����ڣ�
	glColor3ub(255, 2, 0);//�����ɫ
	if(trackLines==1)
	{
//		glPointSize(1);
		for(ellipseAng=0.0f;ellipseAng<360.0f;ellipseAng+=0.1)
		{
		glRotatef(0.1f, 0.0f, 0.0f, 1.0f);
		r_1=e_1*p_1/(1-e_1*cos(ellipseAng/180.0f*3.14159));//��Բ�����귽��
		glBegin(GL_POINTS);
		glVertex3f( r_1, 0.0f, 0.0f);
		glEnd();
		if(invisible_2==0)
		{
			glRotatef(30.0f, 0.0f, 0.0f, 1.0f);
			r_2=e_2*p_2/(1-e_2*cos(ellipseAng/180.0f*3.14159));
			glBegin(GL_POINTS);
			glVertex3f( r_2, 0.0f, 0.0f);
			glEnd();
			glRotatef(-30.0f, 0.0f, 0.0f, 1.0f);
		}
		}//����һ�����
	ellipseAng=0.0f;
	}
	glColor3ub(255, 255, 0);  //̫����ɫ����ɫ
	glutSolidSphere(0.06f, 18, 17);  // ����̫��//��Ⱦһ�����壬����Ϊԭ�㣨�뾶��double������Z�����߶�Ϊֱ���ֲ���Բ���ߵ�������Χ����Z����Χ���ߵ�������
	r_1=e_1*p_1/(1-e_1*cos(angle_1/180.0f*3.14159));//��Բ�����귽��
	glColor3ub(0,0,255);   // ����1��ɫ
	glRotatef(angle_1, 0.0f, 0.0f, 1.0f);
	glTranslatef(r_1,0.0f,0.0f);//����1����
	glutSolidSphere(0.06f, 30, 17);
	glTranslatef(-r_1,0.0f,0.0f);
	glRotatef(-angle_1, 0.0f, 0.0f, 1.0f);//���껹ԭ
	dAngle_1 = cW_1/(r_1*r_1);//�Ƕ����غ㣬�������յڶ�����
	v_1 = sqrt(2*(cE_1+(grav*m_0/(r_1*r_1))));//���������غ㶨�ɼ��������ٶȣ�ע�⣬����ýǶ�������rֻ�ܼ�����ٶ��ڴ�ֱr�����ϵķ���
	angle_1 += dAngle_1;
	if(angle_1>=360.0f)angle_1 -= 360.0f;//���Ƕ���ֵ������0��360����ֹ�������
	if(invisible_2==0)
	glColor3ub(255,0,255);
	else
	glColor3f(0.3f,0.3f,0.3f);
	r_2=e_2*p_2/(1-e_2*cos(angle_2/180.0f*3.14159));
	glRotatef((angle_2+30.0f), 0.0f, 0.0f, 1.0f);//������������
	glTranslatef(r_2,0.0f,0.0f);
	glutSolidSphere(0.06f, 30, 17);
	dAngle_2 = cW_2/(r_2*r_2);
	angle_2 += dAngle_2;
	if(angle_2>=360.0f)angle_2 -= 360.0f;
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
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f );
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
	   case 'e':  if(invisible_2==1)invisible_2=0;else invisible_2=1;break;
	   case 'E':  if(invisible_2==1)invisible_2=0;else invisible_2=1;break;
	   case GLUT_KEY_F2: trackLines = 1;  break;
	   case GLUT_KEY_F3: trackLines = 0;  break;

	   case 27:   exit(0); 
	   default:   break;
   }
	glutPostRedisplay();
}
int main(int argc, char* argv[]) {
	c_1 = sqrt(a_1*a_1-b_1*b_1);
	e_1 = c_1/a_1;
	p_1 = a_1*a_1/c_1+c_1;
	c_2 = sqrt(a_2*a_2-b_2*b_2);
	e_2 = c_2/a_2;
	p_2 = a_2*a_2/c_2+c_2;//���ݰ볤��Ͱ������������ʺ�׼��
	r_1 =  e_1*p_1/(1-e_1*cos(0));//��������1�ĳ�ʼ����������ľ���
	cW_1 = dAngle_1*r_1*r_1;//��������1�ĽǶ�������
	cE_1 = (r_1*dAngle_1*r_1*dAngle_1)/2-grav*m_0/(r_1*r_1);//��������1����������
	r_2 =  e_2*p_2/(1-e_2*cos(0));
	cW_2 = dAngle_2*r_2*r_2;
	cE_2 = (r_2*dAngle_2*r_2*dAngle_2)/2-grav*m_0/(r_2*r_2);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(800, 600);
	glutCreateWindow("Solar System");
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(myMouse);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(250, TimerFunc, 1);
	SetupRC();
	glutMainLoop();
	return 0;
}
