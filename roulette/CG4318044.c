
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <time.h>
#include "myShape.h"


#define KEY_ESC 27
#define PAI 3.1415926536

void polarview(void);
void resetview(void);
unsigned char wireFlag = GL_TRUE;
unsigned char ShadeFlag = GL_TRUE;
unsigned char revolveFlag = GL_FALSE;
unsigned char ballFlag = GL_FALSE;
unsigned char ball2Flag = GL_FALSE;


float theta = 0.0;      //物体の回転角
float theta2 = 0.0;


float distance, twist, elevation, azimuth;
float xOrig = 0.0, yOrig = 0.0;
int mButton;
int xBegin, yBegin;

// silver
float diffuse2[] = { 0.6, 0.6, 0.6, 1.0 };
float specular2[] = { 0.5, 0.5, 0.5, 1.0 };
float ambient2[] = { 0.2, 0.2, 0.2, 1.0 };
float shininess2= 60.0;


//glod net
float diffuse3[] = { 0.75164, 0.60448, 0.22648, 1.0 };
float specular3[] = { 0.628281, 0.555802, 0.366065, 1.0 };
float ambient3[] = { 0.24725, 0.1995, 0.0745, 1.0 };
float shininess3 = 50.0;

//glod net
float diffuse1[] = { 1, 1, 1, 1.0 };
float specular1[] = { 0.628281, 0.555802, 0.366065, 1.0 };
float ambient1[] = { 0.24725, 0.1995, 0.0745, 1.0 };
float shininess1 = 50.0;

float diff = 5.0; //回転のスピード
float diff2 = 3.0; //回転のスピード

 
void display( void )
{
    glPopMatrix();//これがないとクリックすると表示消える
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glPushMatrix();//( 0.0, 0.0, 0.0 );を中心として保存
    polarview();
   
    glPushMatrix();

    //白い球
    glRotatef(theta2, 0.0, 1.0, 0.0);/*ここで回転軸変える*/
    glTranslatef(8 * cos(-1 * PAI / 10), 1.2, 8 * sin(-1 * PAI / 10));
    if (ballFlag == GL_TRUE) {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess1);
        glEnable(GL_LIGHTING);
        glPushMatrix();
        glutSolidSphere(0.6, 10.0, 100);//　球　半径　　分割数 
        glPopMatrix();
        glDisable(GL_LIGHTING);
    }
    glPopMatrix();

   
    glPushMatrix();


    //盤面

    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/
    
    glColor3f(255, 0, 0);//赤色
    if (wireFlag == GL_TRUE) {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse3);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular3);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient3);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess3);
        glEnable(GL_LIGHTING);
        glPushMatrix();
        mySolidCylinder(10.0, 1.0, 100);//半径　高さ　分割数 
        glPopMatrix();
        glDisable(GL_LIGHTING);
    }
    else if (ShadeFlag == GL_TRUE) 
        myWireCylinder(10.0, 1.0, 100);//半径　高さ　分割数  円柱  
    else
         mySolidCylinder(10.0, 1.0, 100);


    
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    //円筒はz軸方向向きに頂点が向くから　頂点をｙ座標に戻している。　x軸を軸にしてー９０度回転
    //これによって今書いた物体はy軸に方向に変わってる



    //盤面のふち
    glColor3f(0.2, 0, 0);//金色 
    if (wireFlag == GL_TRUE) {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse3);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular3);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient3);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess3);
        glEnable(GL_LIGHTING);
        glPushMatrix();
        glutSolidTorus(1.0, 11.0, 100.0, 100.0);//トーラス（ドーナツ）内直　外径　断面の分割数　管に沿った分割数
        glPopMatrix();
        glDisable(GL_LIGHTING);
    }
    else if (ShadeFlag == GL_TRUE) 
        glutWireTorus(1.0, 11.0, 100.0, 100.0);//トーラス（ドーナツ）内直　外径　断面の分割数　管に沿った分割数
    else
        glutSolidTorus(1.0, 11.0, 100.0, 100.0);

    glRotatef(-90.0, 1.0, 0.0, 0.0);
    


      //盤面の場所わけ 9か所 白黒
    glColor3f(0.0, 0.5, 0.0);//深緑
    glBegin(GL_POLYGON);
    glVertex3f(0.0, -0.6, 0.0);
    glVertex3f(10.5, -0.6, 0.0);
    glVertex3f(10.5 * cos(1 * PAI / 10), -0.6, 10.5 * sin(1 * PAI / 10));
    glVertex3f(10.5 * cos(2 * PAI / 10), -0.6, 10.5 * sin(2 * PAI / 10));
    glEnd();

    glColor3f(0.0, 0.0, 0.0);//黒
    glBegin(GL_POLYGON);
    glVertex3f(0.0, -0.6, 0.0);
    glVertex3f(10.5 * cos(2 * PAI / 10), -0.6, 10.5 * sin(2 * PAI / 10));
    glVertex3f(10.5 * cos(3 * PAI / 10), -0.6, 10.5 * sin(3 * PAI / 10));
    glVertex3f(10.5 * cos(4 * PAI / 10), -0.6, 10.5 * sin(4 * PAI / 10));
    glEnd();

    glColor3f(1.0, 0.0, 0.0);//赤
    glBegin(GL_POLYGON);
    glVertex3f(0.0, -0.6, 0.0);
    glVertex3f(10.5 * cos(4 * PAI / 10), -0.6, 10.5 * sin(4 * PAI / 10));
    glVertex3f(10.5 * cos(5 * PAI / 10), -0.6, 10.5 * sin(5 * PAI / 10));
    glVertex3f(10.5 * cos(6 * PAI / 10), -0.6, 10.5 * sin(6 * PAI / 10));
    glEnd();

    glColor3f(0.0, 0.0, 0.0);//黒
    glBegin(GL_POLYGON);
    glVertex3f(0.0, -0.6, 0.0);
    glVertex3f(10.5 * cos(6 * PAI / 10), -0.6, 10.5 * sin(6 * PAI / 10));
    glVertex3f(10.5 * cos(7 * PAI / 10), -0.6, 10.5 * sin(7 * PAI / 10));
    glVertex3f(10.5 * cos(8 * PAI / 10), -0.6, 10.5 * sin(8 * PAI / 10));
    glEnd();

    glColor3f(1.0, 0.0, 0.0);//赤
    glBegin(GL_POLYGON);
    glVertex3f(0.0, -0.6, 0.0);
    glVertex3f(10.5 * cos(8 * PAI / 10), -0.6, 10.5 * sin(8 * PAI / 10));
    glVertex3f(10.5 * cos(9 * PAI / 10), -0.6, 10.5 * sin(9 * PAI / 10));
    glVertex3f(10.5 * cos(10 * PAI /10), -0.6, 10.5 * sin(10 * PAI / 10));
    glEnd();

    glColor3f(0.0, 0.0, 0.0);//黒
    glBegin(GL_POLYGON);
    glVertex3f(0.0, -0.6, 0.0);
    glVertex3f(10.5 * cos(10 * PAI / 10), -0.6, 10.5 * sin(10 * PAI / 10));
    glVertex3f(10.5 * cos(11 * PAI / 10), -0.6, 10.5 * sin(11 * PAI / 10));
    glVertex3f(10.5 * cos(12 * PAI / 10), -0.6, 10.5 * sin(12 * PAI / 10));
    glEnd();

    glColor3f(1.0, 0.0, 0.0);//赤
    glBegin(GL_POLYGON);
    glVertex3f(0.0, -0.6, 0.0);
    glVertex3f(10.5 * cos(12 * PAI / 10), -0.6, 10.5 * sin(12 * PAI / 10));
    glVertex3f(10.5 * cos(13 * PAI / 10), -0.6, 10.5 * sin(13 * PAI / 10));
    glVertex3f(10.5 * cos(14 * PAI / 10), -0.6, 10.5 * sin(14 * PAI / 10));
    glEnd();

    glColor3f(0.0, 0.0, 0.0);//黒
    glBegin(GL_POLYGON);
    glVertex3f(0.0, -0.6, 0.0);
    glVertex3f(10.5 * cos(14 * PAI / 10), -0.6, 10.5 * sin(14 * PAI / 10));
    glVertex3f(10.5 * cos(15 * PAI / 10), -0.6, 10.5 * sin(15 * PAI / 10));
    glVertex3f(10.5 * cos(16 * PAI / 10), -0.6, 10.5 * sin(16 * PAI / 10));
    glEnd();

    glColor3f(1.0, 0.0, 0.0);//赤
    glBegin(GL_POLYGON);
    glVertex3f(0.0, -0.6, 0.0);
    glVertex3f(10.5 * cos(16 * PAI / 10), -0.6, 10.5 * sin(16 * PAI / 10));
    glVertex3f(10.5 * cos(17 * PAI / 10), -0.6, 10.5 * sin(17 * PAI / 10));
    glVertex3f(10.5 * cos(18 * PAI / 10), -0.6, 10.5 * sin(18 * PAI / 10));
    glEnd();

    glColor3f(0.0, 0.0, 0.0);//黒
    glBegin(GL_POLYGON);
    glVertex3f(0.0, -0.6, 0.0);
    glVertex3f(10.5 * cos(18* PAI / 10), -0.6, 10.5 * sin(18 * PAI / 10));
    glVertex3f(10.5 * cos(19 *PAI / 10), -0.6, 10.5 * sin(19 * PAI / 10));
    glVertex3f(10.5 * cos(20 * PAI / 10), -0.6, 10.5 * sin(20 * PAI / 10));
    glEnd();
   
    glPopMatrix();

    glPushMatrix();

    //文字の表示

    
    // 1
     glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/

    glTranslatef(8 * cos(-1* PAI / 10), 0.6, 8 * sin(-1 * PAI / 10));
    glRotatef(18.0, 0.0, 1.0, 0.0);
    glScalef(1.5, 0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

    // 2

    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/
        
    glTranslatef(8 * cos(-2.9 * PAI / 10), 0.6, 8 * sin(-2.9 * PAI / 10));
    glRotatef(54.0, 0.0, 1.0, 0.0);
    glScalef(1.5, 0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();


    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/
        
    glTranslatef(8 * cos(-3.1 * PAI / 10), 0.6, 8 * sin(-3.1 * PAI / 10));
    glRotatef(54.0, 0.0, 1.0, 0.0);
    glScalef(1.5, 0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

    //3
    
    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/
        
    glTranslatef(8 * cos(-5.2 * PAI / 10), 0.6, 8 * sin(-5.2 * PAI / 10));
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(1.5, 0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();


    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/
        
    glTranslatef(8 * cos(-4.8 * PAI / 10), 0.6, 8 * sin(-4.8 * PAI / 10));
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(1.5, 0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/
        
    glTranslatef(8 * cos(-5.0 * PAI / 10), 0.6, 8 * sin(-5.0 * PAI / 10));
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(1.5, 0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

    //4


    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/
        
    glTranslatef(8 * cos(-7.2 * PAI / 10), 0.6, 8 * sin(-7.2 * PAI / 10));
    glRotatef(126.0, 0.0, 1.0, 0.0);
    glScalef(1.5, 0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/
        
    glTranslatef(8 * cos(-7.0* PAI / 10), 0.6, 8 * sin(-7.0 * PAI / 10));
    glRotatef(126+18, 0.0, 1.0, 0.0);
    glScalef(1.5, 0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

 
    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/
        
    glTranslatef(8 * cos(-6.8 * PAI / 10), 0.6, 8 * sin(-6.8 * PAI / 10));
    glRotatef(126-18, 0.0, 1.0, 0.0);
    glScalef(1.5, 0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

    //5

    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/
       
    glTranslatef(8 * cos(-9.1 * PAI / 10), 0.6, 8 * sin(-9.1 * PAI / 10));
    glRotatef(162 + 18, 0.0, 1.0, 0.0);
    glScalef(1.5, 0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();


    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/
        
    glTranslatef(8 * cos(-8.9 * PAI / 10), 0.6, 8 * sin(-8.9 * PAI / 10));
    glRotatef(162 - 18, 0.0, 1.0, 0.0);
    glScalef(1.5, 0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

    //6

    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/

    glTranslatef(8 * cos(-10.8 * PAI / 10), 0.6, 8 * sin(-10.8 * PAI / 10));
    glRotatef(198.0, 0.0, 1.0, 0.0);
    glScalef(1.5, 0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/

    glTranslatef(8 * cos(-11.0 * PAI / 10), 0.6, 8 * sin(-11.0 * PAI / 10));
    glRotatef(198 - 18, 0.0, 1.0, 0.0);
    glScalef(1.5, 0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/

    glTranslatef(8 * cos(11.2 * PAI / 10), 0.6, 8 * sin(-11.2 * PAI / 10));
    glRotatef(198 + 19, 0.0, 1.0, 0.0);
    glScalef(1.5, 0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

    //7


    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/

    glTranslatef(8 * cos(-12.7 * PAI / 10), 0.6, 8 * sin(-12.7 * PAI / 10));
    glRotatef(234.0, 0.0, 1.0, 0.0);
    glScalef(1.5, 0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

  
    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/
  
    glTranslatef(8 * cos(-12.9 * PAI / 10), 0.6, 8 * sin(-12.9 * PAI / 10));
    glRotatef(234.0, 0.0, 1.0, 0.0);
    glScalef(1.5, 0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();


    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/

    glTranslatef(8 * cos(-13.1 * PAI / 10), 0.6, 8 * sin(-13.1 * PAI / 10));
    glRotatef(234 - 18, 0.0, 1.0, 0.0);
    glScalef(1.5, 0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();


    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/

    glTranslatef(8 * cos(-13.3 * PAI / 10), 0.6, 8 * sin(-13.3 * PAI / 10));
    glRotatef(234 + 20, 0.0, 1.0, 0.0);
    glScalef(1.5, 0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

    //8

   
    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/ 

    glTranslatef(8 * cos(-14.6 * PAI / 10), 0.6, 8 * sin(-14.6 * PAI / 10));
    glRotatef(270.0, 0.0, 1.0, 0.0);
    glScalef(1.5, 0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/

    glTranslatef(8 * cos(-14.8 * PAI / 10), 0.6, 8 * sin(-14.8 * PAI / 10));
    glRotatef(270.0, 0.0, 1.0, 0.0);
    glScalef(1.5, 0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

 
    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/
    glTranslatef(8 * cos(-15.0 * PAI / 10), 0.6, 8 * sin(-15.0 * PAI / 10));
    glRotatef(270.0, 0.0, 1.0, 0.0);
    glScalef(1.5, 0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

   
    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/

    glTranslatef(8 * cos(-15.2 * PAI / 10), 0.6, 8 * sin(-15.2 * PAI / 10));
    glRotatef(270 - 16, 0.0, 1.0, 0.0);
    glScalef(1.5, 0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

    
    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/
    glTranslatef(8 * cos(-15.4 * PAI / 10), 0.6, 8 * sin(-15.4 * PAI / 10));
    glRotatef(270 + 22, 0.0, 1.0, 0.0);
    glScalef(1.5, 0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

    //9 

    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/
  
    glTranslatef(8 * cos(-17.2 * PAI / 10), 0.6, 8 * sin(-17.2 * PAI / 10));
    glRotatef(306.0, 0.0, 1.0, 0.0);
    glScalef(1.5, 0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/

    glTranslatef(8 * cos(-16.9 * PAI / 10), 0.6, 8 * sin(-16.9 * PAI / 10));
    glRotatef(306 - 36, 0.0, 1.0, 0.0);
    glScalef(1.8, 0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/

    glTranslatef(8 * cos(-16.9 * PAI / 10), 0.6, 8 * sin(-16.9 * PAI / 10));
    glRotatef(306 + 36, 0.0, 1.0, 0.0);
    glScalef(1.8,  0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

    //10


    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/

    glTranslatef(8 * cos(-19 * PAI / 10), 0.6, 8 * sin(-19 * PAI / 10));
    glRotatef(342 - 36, 0.0, 1.0, 0.0);
    glScalef(1.8, 0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();


    glRotatef(theta, 0.0, 1.0, 0.0);/*ここで回転軸変える*/

    glTranslatef(8 * cos(-19 * PAI / 10), 0.6, 8 * sin(-19 * PAI / 10));
    glRotatef(342 + 36, 0.0, 1.0, 0.0);
    glScalef(1.8, 0.2, 0.2);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();



    //盤面の中心
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    if (wireFlag == GL_TRUE) {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse3);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular3);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient3);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess3);
        glEnable(GL_LIGHTING);
        glPushMatrix();
        glutSolidCone(7.0, 2.0, 100.0,100.0);//円錐　半径　高さ　分割数
        glPopMatrix();
        glDisable(GL_LIGHTING);
    }
    else if (ShadeFlag == GL_TRUE)
        glutWireCone(7.0, 2.0, 100.0, 100.0);//円錐　半径　高さ　分割数
    else
        glutWireCone(7.0, 2.0, 100.0, 100.0);//円錐　半径　高さ　分割数
  
    glPopMatrix();

    glPushMatrix();


    //盤面の中心の上
    glTranslatef(0.0, 1.0, 0.0);
    if (wireFlag == GL_TRUE) {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse2);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular2);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient2);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess2);
        glEnable(GL_LIGHTING);
        glPushMatrix();
        mySolidCylinder(1.5, 2.5, 100);//半径　高さ　分割数 円柱
        glPopMatrix();
        glDisable(GL_LIGHTING);
    }
    else if (ShadeFlag == GL_TRUE)
        myWireCylinder(1.5, 2.5, 100);//半径　高さ　分割数 円柱
    else
        mySolidCylinder(1.5, 2.5, 100);//半径　高さ　分割数 円柱


    glPopMatrix();

    glPushMatrix();


    glTranslatef(0.0, 2.0, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    if (wireFlag == GL_TRUE) {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse2);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular2);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient2);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess2);
        glEnable(GL_LIGHTING);
        glPushMatrix();
        glutSolidCone(1.3, 2.3, 100.0, 100.0);//円錐　半径　高さ　分割数
        glPopMatrix();
        glDisable(GL_LIGHTING);
    }
    else if (ShadeFlag == GL_TRUE)
        glutWireCone(1.3, 2.3, 100.0, 100.0);//円錐　半径　高さ　分割数
    else
        glutSolidCone(1.3, 2.3, 100.0, 100.0);//円錐　半径　高さ　分割数


    //数字を刺す針

    glRotatef(theta2, 0.0, 1.0, 0.0);/*ここで回転軸変える*/
    glTranslatef(0.0, -2.1, 0.0);
    if (wireFlag == GL_TRUE) {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse2);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular2);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient2);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess2);
        glEnable(GL_LIGHTING);
        glPushMatrix();
        mySolidCylinder(0.2, 7.0, 100);//半径　高さ　分割数 円柱
        glPopMatrix();
        glDisable(GL_LIGHTING);
    }
    else if (ShadeFlag == GL_TRUE)
        myWireCylinder(0.2, 7.0, 100);//半径　高さ　分割数 円柱
    else
        mySolidCylinder(0.2, 7.0, 100);//半径　高さ　分割数 円柱


    glTranslatef(0.0, -3.6, 0.0);
    if (wireFlag == GL_TRUE) {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse2);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular2);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient2);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess2);
        glEnable(GL_LIGHTING);
        glPushMatrix();
        glutSolidSphere(0.4, 100.0, 100);//　球　半径　　分割数 
        glPopMatrix();
        glDisable(GL_LIGHTING);
    }
    else if (ShadeFlag == GL_TRUE)
        glutWireSphere(0.4, 100.0, 100);//　球　半径　　分割数
    else
        glutSolidSphere(0.4, 100.0, 100);//　球　半径　　分割数


    glPopMatrix();

    glPushMatrix();


    glTranslatef(0.0, 4.2, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    if (wireFlag == GL_TRUE) {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse2);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular2);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient2);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess2);
        glEnable(GL_LIGHTING);
        glPushMatrix();
        glutSolidSphere(0.5, 100.0, 100);//　球　半径　　分割数 
        glPopMatrix();
        glDisable(GL_LIGHTING);
    }
    else if (ShadeFlag == GL_TRUE)
        glutWireSphere(0.5, 100.0, 100);//　球　半径　　分割数
    else
        glutSolidSphere(0.5, 100.0, 100);//　球　半径　　分割数



    glPopMatrix();

    glPushMatrix();

    glTranslatef(0.0, 4.8, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    if (wireFlag == GL_TRUE) {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse2);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular2);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient2);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess2);
        glEnable(GL_LIGHTING);
        glPushMatrix();
        glutSolidTorus(0.4, 0.7, 100.0, 100.0);//トーラス（ドーナツ）内直　外径　断面の分割数　管に沿った分割数
        glPopMatrix();
        glDisable(GL_LIGHTING);
    }
    else if (ShadeFlag == GL_TRUE)
        glutWireTorus(0.4, 0.7, 100.0, 100.0);//トーラス（ドーナツ）内直　外径　断面の分割数　管に沿った分割数
    else
        glutSolidTorus(0.4, 0.7, 100.0, 100.0);//トーラス（ドーナツ）内直　外径　断面の分割数　管に沿った文化数


    glPopMatrix();

    glPushMatrix();

    glTranslatef(0.0, 6.0, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    if (wireFlag == GL_TRUE) {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse2);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular2);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient2);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess2);
        glEnable(GL_LIGHTING);
        glPushMatrix();
        glutSolidCone(0.35, 1.5, 100.0, 100.0);//円錐　半径　高さ　分割数
        glPopMatrix();
        glDisable(GL_LIGHTING);
    }
    else if (ShadeFlag == GL_TRUE)
        glutWireCone(0.35, 1.5, 100.0, 100.0);//円錐　半径　高さ　分割数
    else
        glutSolidCone(0.35, 1.5, 100.0, 100.0);//円錐　半径　高さ　分割数



    glPopMatrix();

    glPushMatrix();

    glTranslatef(0.0, 6.0, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    if (wireFlag == GL_TRUE) {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse2);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular2);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient2);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess2);
        glEnable(GL_LIGHTING);
        glPushMatrix();
        glutSolidSphere(0.4, 100.0, 100);//　球　半径　　分割数 
        glPopMatrix();
        glDisable(GL_LIGHTING);
    }
    else if (ShadeFlag == GL_TRUE)
        glutWireSphere(0.4, 100.0, 100);//　球　半径　　分割数 
    else
        glutSolidSphere(0.4, 100.0, 100);//　球　半径　　分割数 


    //円盤の中心の上終了

    
    glPopMatrix();
   

    glDisable(GL_DEPTH_TEST);
    glFlush();
}
   



void idle(void)
{
    // 剰余演算法による乱数幅の決定
    srand((unsigned int)time(0));
    rand(); rand(); rand(); rand(); rand();

    // 10で割った余りを取得すれば、0～9の値が得られる
   /* int     ran1 = rand() % 10;*/
    
    int  ran2 = rand() % 720+360;
   
    
    if (revolveFlag == GL_TRUE) {
        diff -= 0.006;
        if (diff <= 0.0)
            diff = 0.0;
    }
   
    if (ball2Flag == GL_TRUE) {
            diff2 -= 0.006;
            if (diff2 <= 0.0)
                diff2 = 0.0;
    }

    theta = fmod(theta + diff, ran2);
    theta2 = fmod(theta2 + diff2, ran2);
    
     glutPostRedisplay();
    
}


void myKbd(unsigned char key, int x, int y)
{
    if (key == KEY_ESC) exit(0);
    switch (key) {
    case 'w':
        wireFlag = !wireFlag;
        break;
    case 's':
        ShadeFlag = !ShadeFlag;
        break;
    case 'R':
        resetview();
        break;
    case 't':
        diff = 5.0;
        break;
    case 'h':
        diff2 = 3.0;
        break;
    case 'f':
        ballFlag = !ballFlag;
        break;
    case 'r':
        revolveFlag = !revolveFlag;
        if (!revolveFlag == GL_FALSE) {
            diff2 = 0;
            glutIdleFunc(idle);
        }
        else 
            glutIdleFunc(NULL);
        break;
    case 'g':
         ball2Flag = !ball2Flag;
         if (!ball2Flag == GL_FALSE) {
             diff = 0;
             glutIdleFunc(idle);
         }
         else  
             glutIdleFunc(NULL);
         break;
    case KEY_ESC:
        exit(0);
    }
    glutPostRedisplay();

}


void myMouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN) {
        switch (button) {
        case GLUT_LEFT_BUTTON:
            mButton = button;
            break;
        case GLUT_MIDDLE_BUTTON:
           mButton = button;
            break;
        case GLUT_RIGHT_BUTTON:
            mButton = button;
            break;
        }
        xBegin = x;
        yBegin = y;
    }
}

void myMotion(int x, int y)
{
    int xDisp, yDisp;

    xDisp = x - xBegin;
    yDisp = y - yBegin;

    switch (mButton) {
    case GLUT_LEFT_BUTTON:
        azimuth += (float)xDisp / 2.0;
        elevation -= (float)yDisp / 2.0;
        break;
    case GLUT_RIGHT_BUTTON:
        distance += (float)yDisp / 40.0;
        break;
    case GLUT_MIDDLE_BUTTON:
        twist += (float)xDisp / 2.0;
        break;
    }
    xBegin = x;
    yBegin = y;
    glutPostRedisplay();
}


void myReshape(int width, int height)
{
    float aspect = (float)width / (float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, aspect, 1.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

void resetview(void)
{
    distance = 40.0;
    twist = 0.0;
    elevation = -30.0;
    azimuth = 0.0;
  
}

void polarview(void)
{
    glTranslatef(0.0, 0.0, -distance);
    glRotatef(-twist, 0.0, 0.0, 1.0);
    glRotatef(-elevation, 1.0, 0.0, 0.0);
    glRotatef(-azimuth, 0.0, 1.0, 0.0);
}


void myInit (char *progname)
{
    int width = 300, height = 600;
    float aspect = (float) width / (float) height;

    glutInitWindowPosition(0, 0);
    glutInitWindowSize( width, height );
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);/*院面処理  */
    glutCreateWindow(progname);
    glClearColor (0.0, 0.0, 0.0, 1.0);
    glutKeyboardFunc( myKbd );
    glutMouseFunc(myMouse);
    glutMotionFunc(myMotion);
    glEnable(GL_LIGHT0);
    resetview();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, aspect, 1.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    myInit(argv[0]);
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(NULL);
    glutMotionFunc(myMotion);
    glutMainLoop();
    return(0);
}