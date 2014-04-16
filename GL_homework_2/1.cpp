// �e�X���Ӧa�O(�]�t�K��) �B�i���d�P�i�ܪ�(�]�t�K��) �]�sĶ�ॿ�`����^(5 ��)�G		5
// �C�Ӯi���d�W���O��(�ܤ֨�ӬO Spot Light)�A�O�����ө����Ȱw��Ӯi�ܰ϶�(2 ��)�G  2
// �e�B��B���B�k��i�H�������Y�e�i�B��h�B���k�(1 ��)�G							1
// ���Y�i�H�ηƹ�����W�U���k�[��(1 ��)�G											1
// ���|��X��ɩФl (1 ��)�G														1
// ���@�Ӯi�ܪ����y�A�ӥB�]�w���ҶK�� (1��)�G
// ����Ӯi���d�A�ϥΥb�z�����覡�e�{ (1��)�G
// �ۦ�]�p���ʺA�ĪG�A�@�Ӥ@���A�Цۦ满��(2��)�G
// �Ѧҹ�H:�L
// �`���G																			10

#include <iostream>
#include <cstdlib>
#include <GL/glew.h>
#include <gl/glut.h>
#include <math.h>
#include <time.h>
#include <windows.h>

#define SCREEN_WIDTH    900
#define SCREEN_HWIDTH   450
#define SCREEN_HEIGHT   600
#define SCREEN_HHEIGHT  300

#ifndef PI
#  define PI 3.141592649
#endif /* !PI */

// �H�U�ܼƥΩ󱱨����Y���B��
float  RotateY = 0;
float  RotateX = 0;
float  ViewCX = 0, ViewCY = 0, ViewCZ = 7;	// ���Y����m�A
float  ViewOX = 0, ViewOY = 0, ViewOZ = 7;	// ���Y����m�A
float  DSpin = 0;	// �C���ֿn�����ਤ��
float  AngleY = 0;   // Y �b�����ਤ��
float  AngleX = 0;   // X �b�����ਤ��
float  VX = 0, VY = 0,VZ = 0 ; //��������m

float  CosTheta, SinTheta;

float  Speed = 2.0 ; //�������t��
float  JumpHight = 0;

bool Jump = false;

int X1 = 0 ;//�ƹ��Ϊ�

bool LightOn = true;
static GLfloat lightR = 0.0f; //����3���O������
static GLfloat lightCrazyX = 0.0f; //����5���O������
static GLfloat lightCrazyY = 0.0f; //����5���O������
static GLfloat lightCrazyZ = 0.0f; //����5���O������

static GLfloat diffu = 0.0f; //����6���O�����G

//-------------------------------------------------------------------------------------------

GLfloat pos1[4] ={-500,500,500,1};

GLfloat diffuse1[]={2.0, 2.0, 2.0, 1.0};
GLfloat ambient1[]={0.0, 0.0, 10.0, 1.0};
GLfloat specular1[]={1.0, 1.0, 1.0, 1.0};
//----------------------------------
GLfloat pos2[4] ={-500,500,-500,1};

GLfloat diffuse2[]={2.0, 2.0, 2.0, 1.0};
GLfloat ambient2[]={0.0, 0.0, 100.0, 1.0};
GLfloat specular2[]={1.0, 1.0, 1.0, 1.0};
//----------------------------------
GLfloat pos3[4] ={0 , 0 , -200 ,1};

GLfloat diffuse3[]={2.0, 2.0, 2.0, 1.0};
GLfloat ambient3[]={0.0, 0.0, 10.0, 1.0};
GLfloat specular3[]={1.0, 1.0, 1.0, 1.0};
//----------------------------------
GLfloat pos4[4] ={500,500,-1500,1};

GLfloat diffuse4[]={2.0, 2.0, 2.0, 1.0};
GLfloat ambient4[]={0.0, 0.0, 10.0, 1.0};
GLfloat specular4[]={1.0, 1.0, 1.0, 1.0};
//----------------------------------
GLfloat pos5[4] ={100,100,100,1};

GLfloat diffuse5[]={2.0, 2.0, 2.0, 1.0};
GLfloat ambient5[]={0.0, 0.0, 10.0, 1.0};
GLfloat specular5[]={1.0, 1.0, 1.0, 1.0};
//----------------------------------
GLfloat pos6[4] ={500,500,500,1};

//GLfloat diffuse6[]={2.0, 2.0, 2.0, 1.0};
GLfloat ambient6[]={0.0, 0.0, 0.0, 1.0};
GLfloat specular6[]={1.0, 1.0, 1.0, 1.0};

GLfloat global_ambient[]={0.5, 0.5, 0.5, 1.0};

GLfloat spotDirect[] = {0, -1, 0};

//---------------------------------------------------------------------------------
int ifps = 0;
int icount = 0;
clock_t dstart = -1;
double delapse;

//�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w
// read_bmp.h �w�� Ū�� BMP �ɮסAread_tga.h �w�� Ū�� tga �ɮ�

#include "read_bmp.h"
#include "read_tga.h"

//�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w
int		g_iWinID;


int        Width;    // Width of window 
int        Height;   // Height of window 
BITMAPINFO *pTexInfo=NULL; // �x�s BMP �ɮת�������T 
GLubyte    *pBmpTex=NULL; // ���VŪ�J�� BMP �ɮש��x�s��m���}�Y 

BITMAPINFO *pTexInfo1=NULL; // �x�s BMP �ɮת�������T 
GLubyte    *pBmpTex1=NULL; // ���VŪ�J�� BMP �ɮש��x�s��m���}�Y

//�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w
// 
// �� BMP �ɮצӨ��A�Q�� LoadDIBitmap Ū���ɡA�����Q�� BITMAPINFO �ҫŧi�������ܼơA���o���������Y��T
// �ϥνd�ҡG
// pBmpTex = LoadDIBitmap("sample.bmp", &pTexInfo);
// �Ĥ@�Ӥ޼ƬO�ɮת��W�٦r��A�ĤG�Ӥ޼Ʒ|���o�o���ɮת�������ơC�䤤
// pTexInfo->bmiHeader.biWidth �P pTexInfo->bmiHeader.biHeight �N��v�����e�P���A
// �|�Φb glTexImage2D �K�Ϫ��]�w�W 
//
//�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w

GLubyte    *pTgaTex=NULL; // ���VŪ�J�� TGA �ɮש��x�s��m���}�Y 
int iTgaWidth, iTgaHeight; // TGA �ɮת� Width �P height

GLubyte	*pTgaGreenTex=NULL; // ���VŪ�J�� TGA �ɮש��x�s��m���}�Y 
int iGreenWidth, iGreenHeight; // TGA �ɮת� Width �P height

GLubyte	*pTgaBlueTex=NULL; // ���VŪ�J�� TGA �ɮש��x�s��m���}�Y 
int iBlueWidth, iBlueHeight;


//�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w
//
// �� TGA �ɮצӨ��A�Q�� tga_load �禡Ū���ɡA�����������ɮ׬O 24 bits (RGB), �٬O32 bits (RGBA)
// 24 bit �ϥ� TGA_TRUECOLOR_24�B 32 bit �ϥ� TGA_TRUECOLOR_32 
// �ϥνd�ҡG
// pTgaTex = (GLubyte *)tga_load("devil.tga",&iTgaWidth, &iTgaHeight, TGA_TRUECOLOR_24);
// �Ĥ@�Ӥ޼ƬO�ɮת��W�٦r��A�ĤG�Ӥ޼ƱN�|�Ǧ^���ɮת��Ҧ���T�G�P�T�|�Ǧ^���ɮת��e�P���B�ĥ|�ӰѼƫh�O�i���o���ɮ׬O 24 Bits
// devil.tga ���@ 24 Bits �� TGA �ɮ�
// 
// pTgaTex = (GLubyte *)tga_load("devil_alpha.tga",&iTgaWidth, &iTgaHeight, TGA_TRUECOLOR_32);
// �Ĥ@�Ӥ޼ƬO�ɮת��W�٦r��A�G�P�T�|�Ǧ^���ɮת��e�P���B�ĥ|�ӰѼƫh�O�i���o���ɮ׬O 32 Bits
// devil_alpha.tga ���@ 32 Bits �� TGA �ɮ�
//

//�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w
// �ŧi Texture Object
// Texture Object ���@���
//�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w
GLuint	TextureID[7];		// �ŧi5�� Texture Object

//�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w
/*
 * Functions...
 */

char strFPS[] = "FPS:0000";


void DrawText(float x, float y, char *string)
{
	int len, i;
	glRasterPos2f(x/SCREEN_HWIDTH, y/SCREEN_HHEIGHT);
	len = (int) strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	}
}

void DisplayText(int ifps)
{
	int i;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);
	i = ifps/1000;
	strFPS[4] = i+48;
	ifps = ifps - i*1000;
	i = ifps/100;
	strFPS[5] = i+48;
	ifps = ifps - i*100;
	strFPS[6] = ifps/10+48;
	strFPS[7] = ifps%10+48;
	DrawText(-450,282,strFPS);	// �b���w����m�B�A��ܫ��w���r�ꤺ�e
}
void DrawPlane()
{
	glBegin(GL_POLYGON);
		glNormal3f(0,1,0);
		glTexCoord2f(0, 1);
		glVertex3f (-1000.0, 500.0, -2000.0);

		glNormal3f(0,1,0);
		glTexCoord2f(1, 1);
		glVertex3f (1000.0, 500.0, -2000.0);

		glNormal3f(0,1,0);
		glTexCoord2f(1, 0);
		glVertex3f (1000.0, 500.0, 1000.0);

		glNormal3f(0,1,0);
		glTexCoord2f(0, 0);
		glVertex3f (-1000.0, 500.0, 1000.0);
	glEnd();
	int j, k , X_MAX = 1000 ,X_MIN = -1000 ,Z_MAX = 1000 , Z_MIN = -2000, STEP_SIZE = 20 ;
	int xa = 2000/STEP_SIZE ,zb = 3000/STEP_SIZE;
 
	float a , b;
	for( k = X_MIN , a= 0; k <  X_MAX , a < xa ; k+= STEP_SIZE ,a++)
		for( j = Z_MIN , b = zb; j <  Z_MAX , b >0; j+= STEP_SIZE , b--) 
		{
			glBegin(GL_POLYGON);
				glNormal3f(0, 1, 0);
				glTexCoord2f(a/xa, b/zb);
				glVertex3f (k, 0.0, j);
				
				glNormal3f(0, 1, 0);
				glTexCoord2f(a/xa, (b-1)/zb);
				glVertex3f (k, 0.0, j+STEP_SIZE);
				
				glNormal3f(0, 1, 0);
				glTexCoord2f((a+1)/xa, (b-1)/zb);
				glVertex3f (k+STEP_SIZE, 0.0, j+STEP_SIZE);
				
				glNormal3f(0, 1, 0);
				glTexCoord2f((a+1)/xa, b/zb);
				glVertex3f (k+STEP_SIZE, 0.0, j);
			glEnd();
		}

}
void DrawWall()
{
	glBegin(GL_POLYGON);
		glNormal3f(0,0,1);
		glTexCoord2f(0, 0);
		glVertex3f (-500.0, 0.0, 0.0);

		glNormal3f(0,0,1);
		glTexCoord2f(1, 0);
		glVertex3f (500.0, 0.0, 0.0);

		glNormal3f(0,0,1);
		glTexCoord2f(1, 1);
		glVertex3f (500.0, 500.0, 0.0);

		glNormal3f(0,0,1);
		glTexCoord2f(0, 1);
		glVertex3f (-500.0, 500.0, 0.0);
	glEnd();
			
}
void DrawCabinet()
{
	for(int i = 0; i<3 ; i++)
		for(int j = 0; j<2 ; j++)
		{
			glPushMatrix();
			glTranslatef(-500+1000*j,60,500-1000*i);
			glScalef (20, 12, 20);
			glColor3f(1.0, 1.0, 1.0);
			glutSolidCube(10);
			glPopMatrix();
		}
}
void DrawIExhibits()
{
	for(int i = 0; i<3 ; i++)
		for(int j = 0; j<2 ; j++)
		{
			glPushMatrix();
			glTranslatef(-500+1000*j,170,500-1000*i);
			glScalef (1, 1, 1);
			glColor3f(1.0, 1.0, 1.0);
			glutSolidTeapot(100);
			glPopMatrix();
		}
}

void Redraw(void)
{
	icount++;
	if( dstart == -1 ) dstart = clock();
	else {
		delapse = (double)(clock() - dstart)/CLOCKS_PER_SEC;
		if( delapse >= 1.0f ) {
			ifps = icount;
			icount = 0;
			dstart = -1;
		}
	}
	glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	 
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1, 5000.0);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();  // M = I
	gluLookAt( VX+500 , VY+200 , VZ+900 , VX+ViewCX+500 , VY+ViewCY+200 , VZ+ViewCZ+900 , 0, 1, 0);

//-----------------------------------------------------------------------------------------------------------------	
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirect);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDirect);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spotDirect);
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spotDirect);
	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, spotDirect);
	glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, spotDirect);

	glPushMatrix();
		glLightfv(GL_LIGHT1, GL_POSITION, pos1);
	glPopMatrix();

	glPushMatrix();
		glLightfv(GL_LIGHT2, GL_POSITION, pos2);
	glPopMatrix();

	glPushMatrix();	
		glTranslatef(-500,500,-1500);
		glRotatef(lightR, 0.0, 1.0, 0.0);
		glLightfv(GL_LIGHT3, GL_POSITION, pos3);
	glPopMatrix();
	

	glPushMatrix();
		glLightfv(GL_LIGHT4, GL_POSITION, pos4);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(500,300,-500);
		glRotatef(lightCrazyX, 1.0, 0.0, 0.0);
		glRotatef(lightCrazyY, 0.0, 1.0, 0.0);
		glRotatef(lightCrazyZ, 0.0, 0.0, 1.0);
		glLightfv(GL_LIGHT5, GL_POSITION, pos5);
	glPopMatrix();

	glPushMatrix();
		glLightfv(GL_LIGHT6, GL_POSITION, pos6);
	glPopMatrix();

	GLfloat diffuse6[]={diffu, diffu, diffu, 1.0};
	glLightfv(GL_LIGHT6, GL_DIFFUSE, diffuse6);

//-----------------------------------------------------------------------------	
	if(Jump && JumpHight <180)
	{
		VY = 150*sin(JumpHight*PI/180.1f);
		JumpHight += 4;
	}
	if(JumpHight>=180)
	{
		JumpHight = 0;
		Jump = false;
	}

	//glBegin(GL_LINES);
	//	glColor3f(1,0,0); glVertex3f(-5000,0,0); glVertex3f(5000,0,0);	// X �b
	//	glColor3f(0,1,0); glVertex3f(0,-5000,0); glVertex3f(0,5000,0);	// Y �b
	//	glColor3f(0,0,1); glVertex3f(0,0,-5000); glVertex3f(0,0,5000);	// Z �b
	//glEnd();

	if(LightOn) glEnable(GL_LIGHTING);
	
//----------------------------------------------------------------------------
	glEnable(GL_BLEND);  // �]�w 2D Texure Mapping ���@��
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);  // �]�w 2D Texure Mapping ���@��
	
	glBindTexture(GL_TEXTURE_2D, TextureID[2]);
	for(int i = 0; i<2 ; i++)
		for(int j = 0; j<2 ; j++)
		{
			glPushMatrix();
			glTranslatef((-500+1000*i),0,(1000-3000*j));
			DrawWall();
			glPopMatrix();
		}
	for(int i = 0; i<2 ; i++)
		for(int j = 0; j<3 ; j++)
		{
			glPushMatrix();
			glTranslatef((1000-2000*i),0,(500-1000*j));
			glRotatef(90,0,1,0);
			DrawWall();
			glPopMatrix();
		}

	glBindTexture(GL_TEXTURE_2D, TextureID[2]);
	DrawCabinet();

	glBindTexture(GL_TEXTURE_2D, TextureID[2]);
	DrawIExhibits();

	glBindTexture(GL_TEXTURE_2D, TextureID[1]);
	DrawPlane();

	glDepthMask(GL_FALSE);// �`�׬� �uŪ �H�W�O�e���z��������
	glDisable(GL_LIGHTING);
//---------------------------------------------------------------------------
	
	glDisable(GL_TEXTURE_2D); // ���� 2D Texure Mapping ���@��

    glFinish();
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);// �`�׬� Ū/�g �H�W�O�e�b�z������
//----------------------------------------------------------------------------------	
	DisplayText(ifps);	// ���FPS
	glutSwapBuffers();

}

void reshape(int w, int h)
{
	// viewport transformation 
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// projection transformation
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1, 5000.0);
	// �]�w Perspective Matrix

	glMatrixMode(GL_MODELVIEW);
	// �]�w MODELVIEW Matrix
	
    glEnable(GL_LIGHTING);
//---------------------------------------------------------------
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 65.0f);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 25.5f); 
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1);
//---------------------------------------------------------------
	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular2);

	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 65.1f);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 15.5f); 
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1);
//---------------------------------------------------------------
	glEnable(GL_LIGHT3);
	glLightfv(GL_LIGHT3, GL_AMBIENT, ambient3);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse3);
	glLightfv(GL_LIGHT3, GL_SPECULAR, specular3);

	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 65.0f);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 30.5f); 
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 1);
//---------------------------------------------------------------
	glEnable(GL_LIGHT4);
	glLightfv(GL_LIGHT4, GL_AMBIENT, ambient4);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuse4);
	glLightfv(GL_LIGHT4, GL_SPECULAR, specular4);

	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 65.0f);
	glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 25.5f); 
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 1);
//---------------------------------------------------------------
	glEnable(GL_LIGHT5);
	glLightfv(GL_LIGHT5, GL_AMBIENT, ambient5);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, diffuse5);
	glLightfv(GL_LIGHT5, GL_SPECULAR, specular5);

	glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 65.0f);
	glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 25.5f); 
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, 1);
//---------------------------------------------------------------
	glEnable(GL_LIGHT6);
	glLightfv(GL_LIGHT6, GL_AMBIENT, ambient6);
//	glLightfv(GL_LIGHT6, GL_DIFFUSE, diffuse6);
	glLightfv(GL_LIGHT6, GL_SPECULAR, specular6);

	glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, 65.0f);
	glLightf(GL_LIGHT6, GL_SPOT_EXPONENT, 5.5f); 
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightf(GL_LIGHT6, GL_CONSTANT_ATTENUATION, 1);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
}


void keyboard (unsigned char key, int x, int y) // �������Y
{
	switch (key) 
	{
      case 27:
		glutDestroyWindow(g_iWinID);
		exit(0);
		break;
	  case'w':	//���Y�d��50 �P �~�� ���Z�� �O �⭿��View
		   if( (VX+500-50>-1000-2*ViewCX)&&(VX+500+10<1000-2*ViewCX) && (VZ+900-50>-2000-2*ViewCZ)&&(VZ+900+50<1000-2*ViewCZ) )
		  {
			VX += ViewCX * Speed ; //�o�̪�ViewCX�N���O�V�q(at - look)�A�N�O�p�¦V�����V�q
			VZ += ViewCZ * Speed ;			
		  }
		  glutPostRedisplay();
		  break;
	  case'a'://���k���� �O�Ϊk�V�q
		  if( (VX+500-50>-1000-2*ViewCZ)&&(VX+500+10<1000-2*ViewCZ) && (VZ+900-50>-2000+2*ViewCX)&&(VZ+900+50<1000+2*ViewCX) )
		  {
			VX += ViewCZ * Speed ;
			VZ += -ViewCX * Speed ;
		  }
		  glutPostRedisplay();
		  break;
	  case's':
		  if( (VX+500-50>-1000+2*ViewCX)&&(VX+500+10<1000+2*ViewCX) && (VZ+900-50>-2000+2*ViewCZ)&&(VZ+900+50<1000+2*ViewCZ) )
		  {
			VX -= ViewCX * Speed ;
			VZ -= ViewCZ * Speed ;
		  }
		  glutPostRedisplay();
		  break;
	  case'd':	  
		   if( (VX+500-50>-1000+2*ViewCZ)&&(VX+500+10<1000+2*ViewCZ) && (VZ+900-50>-2000-2*ViewCX)&&(VZ+900+50<1000-2*ViewCX) )
		  {
			 VX -= ViewCZ * Speed ;
			 VZ -= -ViewCX * Speed ;
		  }
		  break;
	  case'n':
		  LightOn =! LightOn;
		  glutPostRedisplay();
		  break;
	  case' ':
		  Jump = true;
		  glutPostRedisplay();
		  break;
      default:
         break;
   }
}
void mouse(int button, int state, int x, int y) 
{

	switch(button) {
		case GLUT_LEFT_BUTTON:   // �ثe���U���O�ƹ�����
			glutPostRedisplay();
			break;
		case GLUT_MIDDLE_BUTTON:  // �ثe���U���O�ƹ�����
			break;
		case GLUT_RIGHT_BUTTON:   // �ثe���U���O�ƹ��k��
			break;
		default:
			break;
	} 
}
void mouseMotion(int x, int y) 
{
	int dx, dy;
	
	//�ζ�Ϊ������ӧ��� at �� at ¶�� look ��A�϶Z���O����
	// ���k�쩳�U180��
	// �W�U�U 89 ��

	dy = y - SCREEN_HHEIGHT;
	if( dy >= 0 ) RotateY = -89*dy/SCREEN_HHEIGHT;
	else RotateY = -89*(float)dy/SCREEN_HHEIGHT;

	AngleY = RotateY;

	CosTheta = cos(AngleY*PI/180.0f);
	SinTheta = sin(AngleY*PI/180.0f);

	ViewCZ = -( ViewOZ * CosTheta - ViewOY * SinTheta );
	ViewCY = ViewOZ * SinTheta + ViewOY * CosTheta; //�W�U

	dx = (x+X1) - SCREEN_HWIDTH;
	if( dx >= 0 ) RotateX = -180*dx/SCREEN_HWIDTH;
	else RotateX = -180*(float)dx/SCREEN_HWIDTH;

	AngleX = RotateX;

	CosTheta = cos(AngleX*PI/180.0f);
	SinTheta = sin(AngleX*PI/180.0f);

	ViewCX = ViewOX * CosTheta - ViewOZ * SinTheta;//���k
	ViewCZ = -( ViewOX * SinTheta + ViewOZ * CosTheta );
		
	if(x<=30 || x >= SCREEN_WIDTH-30)
	{
		if(x > 850) X1 += SCREEN_HWIDTH-30;
		if(x < 50 ) X1 -= SCREEN_HWIDTH-30;
		SetCursorPos(SCREEN_HWIDTH ,y);	//��ƹ���m���ȹ�����	
	}
	ShowCursor(false); //���÷ƹ�	
	glutPostRedisplay();		
}


void init() 
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//---------------------------------------------------------------
	glShadeModel(GL_SMOOTH);

	//---------------------------------------------------------------
	glEnable(GL_DEPTH_TEST);

    pBmpTex = LoadDIBitmap("ground.bmp", &pTexInfo);
	pBmpTex1 = LoadDIBitmap("Wood.bmp", &pTexInfo1);
	pTgaTex = (GLubyte *)tga_load("Window.tga",&iTgaWidth, &iTgaHeight, TGA_TRUECOLOR_32);
	pTgaGreenTex = (GLubyte *)tga_load("Green.tga",&iGreenWidth, &iGreenHeight, TGA_TRUECOLOR_32);
	pTgaBlueTex = (GLubyte *)tga_load("Blue.tga",&iBlueWidth, &iBlueHeight, TGA_TRUECOLOR_32);

	glGenTextures(5, &TextureID[0]);

	glBindTexture(GL_TEXTURE_2D, TextureID[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// GL_NEAREST
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// GL_NEAREST
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );		// GL_CLAMP
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT  );		// GL_CLAMP
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iTgaWidth,iTgaHeight, 1, GL_RGBA,  GL_UNSIGNED_BYTE, pTgaTex);

	glBindTexture(GL_TEXTURE_2D, TextureID[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pTexInfo->bmiHeader.biWidth, 
		pTexInfo->bmiHeader.biHeight, 1, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBmpTex);

	glBindTexture(GL_TEXTURE_2D, TextureID[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pTexInfo->bmiHeader.biWidth, 
		pTexInfo1->bmiHeader.biHeight, 1, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBmpTex1);

	glBindTexture(GL_TEXTURE_2D, TextureID[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iGreenWidth, iGreenHeight, 1, GL_RGBA, GL_UNSIGNED_BYTE, pTgaGreenTex);

	glBindTexture(GL_TEXTURE_2D, TextureID[4]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iBlueWidth, iBlueHeight, 1, GL_RGBA, GL_UNSIGNED_BYTE, pTgaBlueTex);


	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);			// Set The Texture Generation Mode For S To Sphere Mapping ( NEW )
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);			// Set The Texture Generation Mode For T To Sphere Mapping ( NEW )

	if( pBmpTex != NULL ) free(pBmpTex);
	if( pBmpTex1 != NULL ) free(pBmpTex1);
	if( pTgaTex != NULL ) free(pTgaTex);
	if( pTgaGreenTex != NULL ) free(pTgaGreenTex);
	if( pTgaBlueTex != NULL ) free(pTgaBlueTex);
	if( pTexInfo != NULL ) free(pTexInfo);
	if( pTexInfo1 != NULL ) free(pTexInfo1);
}
void idle()
{
	lightR += 1.0;
	if(lightR > 360.0) lightR -= 360.0; 

	lightCrazyX += 10;
	if(lightCrazyX > 360.0) lightCrazyX -= 360.0;

	lightCrazyY += 20;
	if(lightCrazyY > 360.0) lightCrazyY -= 360.0;

	lightCrazyZ += 50;
	if(lightCrazyZ > 360.0) lightCrazyZ -= 360.0;

	diffu += 0.01;
	if(diffu > 10) diffu -= 10;

	glutPostRedisplay();
}

void main(int  argc,  char *argv[])
{
    glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    g_iWinID = glutCreateWindow("homework2");

	init();

	glutDisplayFunc(Redraw);
    glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	glutPassiveMotionFunc(mouseMotion);

	const char* version = (const char*)glGetString(GL_VERSION);
    printf("OpenGL �����G%s\n", version);

	glutMainLoop();
}