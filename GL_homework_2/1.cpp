// 畫出六個地板(包含貼圖) 、展示櫃與展示物(包含貼圖) （編譯能正常執行）(5 分)：		5
// 每個展示櫃上有燈光(至少兩個是 Spot Light)，燈光的照明都僅針對該展示區塊(2 分)：  2
// 前、後、左、右鍵可以控制鏡頭前進、後退、左右橫移(1 分)：							1
// 鏡頭可以用滑鼠控制上下左右觀望(1 分)：											1
// 不會穿出整棟房子 (1 分)：														1
// 有一個展示物為球，而且設定環境貼圖 (1分)：
// 有兩個展示櫃，使用半透明的方式呈現 (1分)：
// 自行設計的動態效果，一個一分，請自行說明(2分)：
// 參考對象:無
// 總分：																			10

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

// 以下變數用於控制鏡頭的運鏡
float  RotateY = 0;
float  RotateX = 0;
float  ViewCX = 0, ViewCY = 0, ViewCZ = 7;	// 鏡頭的位置，
float  ViewOX = 0, ViewOY = 0, ViewOZ = 7;	// 鏡頭的位置，
float  DSpin = 0;	// 每次累積的旋轉角度
float  AngleY = 0;   // Y 軸的旋轉角度
float  AngleX = 0;   // X 軸的旋轉角度
float  VX = 0, VY = 0,VZ = 0 ; //眼睛的位置

float  CosTheta, SinTheta;

float  Speed = 2.0 ; //走路的速度
float  JumpHight = 0;

bool Jump = false;

int X1 = 0 ;//滑鼠用的

bool LightOn = true;
static GLfloat lightR = 0.0f; //控制3號燈的旋轉
static GLfloat lightCrazyX = 0.0f; //控制5號燈的旋轉
static GLfloat lightCrazyY = 0.0f; //控制5號燈的旋轉
static GLfloat lightCrazyZ = 0.0f; //控制5號燈的旋轉

static GLfloat diffu = 0.0f; //控制6號燈的明亮

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

//───────────────────────────────
// read_bmp.h ─＞ 讀取 BMP 檔案，read_tga.h ─＞ 讀取 tga 檔案

#include "read_bmp.h"
#include "read_tga.h"

//───────────────────────────────
int		g_iWinID;


int        Width;    // Width of window 
int        Height;   // Height of window 
BITMAPINFO *pTexInfo=NULL; // 儲存 BMP 檔案的相關資訊 
GLubyte    *pBmpTex=NULL; // 指向讀入的 BMP 檔案所儲存位置的開頭 

BITMAPINFO *pTexInfo1=NULL; // 儲存 BMP 檔案的相關資訊 
GLubyte    *pBmpTex1=NULL; // 指向讀入的 BMP 檔案所儲存位置的開頭

//──────────────────────────────────────────────
// 
// 對 BMP 檔案而言，利用 LoadDIBitmap 讀取時，必須利用 BITMAPINFO 所宣告的指標變數，取得相關的檔頭資訊
// 使用範例：
// pBmpTex = LoadDIBitmap("sample.bmp", &pTexInfo);
// 第一個引數是檔案的名稱字串，第二個引數會取得這個檔案的相關資料。其中
// pTexInfo->bmiHeader.biWidth 與 pTexInfo->bmiHeader.biHeight 代表影像的寬與高，
// 會用在 glTexImage2D 貼圖的設定上 
//
//──────────────────────────────────────────────

GLubyte    *pTgaTex=NULL; // 指向讀入的 TGA 檔案所儲存位置的開頭 
int iTgaWidth, iTgaHeight; // TGA 檔案的 Width 與 height

GLubyte	*pTgaGreenTex=NULL; // 指向讀入的 TGA 檔案所儲存位置的開頭 
int iGreenWidth, iGreenHeight; // TGA 檔案的 Width 與 height

GLubyte	*pTgaBlueTex=NULL; // 指向讀入的 TGA 檔案所儲存位置的開頭 
int iBlueWidth, iBlueHeight;


//──────────────────────────────────────────────
//
// 對 TGA 檔案而言，利用 tga_load 函式讀取時，必須指明該檔案是 24 bits (RGB), 還是32 bits (RGBA)
// 24 bit 使用 TGA_TRUECOLOR_24、 32 bit 使用 TGA_TRUECOLOR_32 
// 使用範例：
// pTgaTex = (GLubyte *)tga_load("devil.tga",&iTgaWidth, &iTgaHeight, TGA_TRUECOLOR_24);
// 第一個引數是檔案的名稱字串，第二個引數將會傳回該檔案的所有資訊二與三會傳回該檔案的寬與高、第四個參數則是告知這個檔案是 24 Bits
// devil.tga 為一 24 Bits 的 TGA 檔案
// 
// pTgaTex = (GLubyte *)tga_load("devil_alpha.tga",&iTgaWidth, &iTgaHeight, TGA_TRUECOLOR_32);
// 第一個引數是檔案的名稱字串，二與三會傳回該檔案的寬與高、第四個參數則是告知這個檔案是 32 Bits
// devil_alpha.tga 為一 32 Bits 的 TGA 檔案
//

//──────────────────────────────────────────────
// 宣告 Texture Object
// Texture Object 為一整數
//──────────────────────────────────────────────
GLuint	TextureID[7];		// 宣告5個 Texture Object

//──────────────────────────────────────────────
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
	DrawText(-450,282,strFPS);	// 在指定的位置處，顯示指定的字串內容
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
	//	glColor3f(1,0,0); glVertex3f(-5000,0,0); glVertex3f(5000,0,0);	// X 軸
	//	glColor3f(0,1,0); glVertex3f(0,-5000,0); glVertex3f(0,5000,0);	// Y 軸
	//	glColor3f(0,0,1); glVertex3f(0,0,-5000); glVertex3f(0,0,5000);	// Z 軸
	//glEnd();

	if(LightOn) glEnable(GL_LIGHTING);
	
//----------------------------------------------------------------------------
	glEnable(GL_BLEND);  // 設定 2D Texure Mapping 有作用
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);  // 設定 2D Texure Mapping 有作用
	
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

	glDepthMask(GL_FALSE);// 深度為 只讀 以上是畫不透明的物體
	glDisable(GL_LIGHTING);
//---------------------------------------------------------------------------
	
	glDisable(GL_TEXTURE_2D); // 取消 2D Texure Mapping 的作用

    glFinish();
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);// 深度為 讀/寫 以上是畫半透明物體
//----------------------------------------------------------------------------------	
	DisplayText(ifps);	// 顯示FPS
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
	// 設定 Perspective Matrix

	glMatrixMode(GL_MODELVIEW);
	// 設定 MODELVIEW Matrix
	
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


void keyboard (unsigned char key, int x, int y) // 控制鏡頭
{
	switch (key) 
	{
      case 27:
		glutDestroyWindow(g_iWinID);
		exit(0);
		break;
	  case'w':	//鏡頭範圍50 與 外牆 的距離 是 兩倍的View
		   if( (VX+500-50>-1000-2*ViewCX)&&(VX+500+10<1000-2*ViewCX) && (VZ+900-50>-2000-2*ViewCZ)&&(VZ+900+50<1000-2*ViewCZ) )
		  {
			VX += ViewCX * Speed ; //這裡的ViewCX代表的是向量(at - look)，就是妳朝向哪的向量
			VZ += ViewCZ * Speed ;			
		  }
		  glutPostRedisplay();
		  break;
	  case'a'://左右的話 是用法向量
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
		case GLUT_LEFT_BUTTON:   // 目前按下的是滑鼠左鍵
			glutPostRedisplay();
			break;
		case GLUT_MIDDLE_BUTTON:  // 目前按下的是滑鼠中鍵
			break;
		case GLUT_RIGHT_BUTTON:   // 目前按下的是滑鼠右鍵
			break;
		default:
			break;
	} 
}
void mouseMotion(int x, int y) 
{
	int dx, dy;
	
	//用圓形的公式來改變 at 使 at 繞著 look 轉，使距離保持著
	// 左右到底各180度
	// 上下各 89 度

	dy = y - SCREEN_HHEIGHT;
	if( dy >= 0 ) RotateY = -89*dy/SCREEN_HHEIGHT;
	else RotateY = -89*(float)dy/SCREEN_HHEIGHT;

	AngleY = RotateY;

	CosTheta = cos(AngleY*PI/180.0f);
	SinTheta = sin(AngleY*PI/180.0f);

	ViewCZ = -( ViewOZ * CosTheta - ViewOY * SinTheta );
	ViewCY = ViewOZ * SinTheta + ViewOY * CosTheta; //上下

	dx = (x+X1) - SCREEN_HWIDTH;
	if( dx >= 0 ) RotateX = -180*dx/SCREEN_HWIDTH;
	else RotateX = -180*(float)dx/SCREEN_HWIDTH;

	AngleX = RotateX;

	CosTheta = cos(AngleX*PI/180.0f);
	SinTheta = sin(AngleX*PI/180.0f);

	ViewCX = ViewOX * CosTheta - ViewOZ * SinTheta;//左右
	ViewCZ = -( ViewOX * SinTheta + ViewOZ * CosTheta );
		
	if(x<=30 || x >= SCREEN_WIDTH-30)
	{
		if(x > 850) X1 += SCREEN_HWIDTH-30;
		if(x < 50 ) X1 -= SCREEN_HWIDTH-30;
		SetCursorPos(SCREEN_HWIDTH ,y);	//把滑鼠位置放到銀幕中間	
	}
	ShowCursor(false); //隱藏滑鼠	
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
    printf("OpenGL 版本：%s\n", version);

	glutMainLoop();
}