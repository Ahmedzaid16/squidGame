#define STB_IMAGE_IMPLEMENTATION
#include<windows.h>
#include <Gl\stb_image.h>
#include<GL\glut.h> 
#include<irrKlang.h>
#include<iostream>
#include<string>
using namespace irrklang;
ISoundEngine* engine = createIrrKlangDevice();
ISoundEngine* engine2 = createIrrKlangDevice();

unsigned int texture;
int width1, height, nrChannels;
unsigned char *data1 = NULL;
float glass_pos[16];
float glass_l[16];
float glass_r[16];
float bool_x=0,bool_y=0;
int life = 3;
void writeStr(float, float, std::string, void*);
float eyex, eyey, eyez, upx, upz=-50;
int s=0;
int move_ball=2;
float ratio, angle, a;
bool fullscreen = true;
bool t = true;
bool sound_t=true;
bool bool_up=true;
bool ball_right_flage = false , ball_left_flage =true;
void start();
void intit();
void mydraw();
void reshape(int, int);
void timer(int);
void keybord(unsigned char, int, int);
void specialkeybord(int, int, int);
void twosides();
void theEndoftheScene();
void theglasses();
void thestartofthegame();
void check (unsigned char*);
void load ( int);
void reset_engine(int);
int go_down(int);
void renderBitmapString(float, float, float , void*, const char*);



void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Glass Tiles Game");
	glutFullScreen();
	intit();
	glutDisplayFunc(mydraw);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);
	glutKeyboardFunc(keybord);
	glutSpecialFunc(specialkeybord);

	// background sound
	engine->play2D("../audio/gameaudio.wav", true);
	glutMainLoop();
}

void intit() {
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
}

void mydraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	

	glLoadIdentity();
	glColor3f(.0666666666666667, .3333333333333333, 0.2352941176470588);
	glTranslatef(0, 0, -7);
	glRotatef(a, 0, 0, 1);
	glutWireSphere(60, 30, 36);
	glLoadIdentity();

	gluLookAt(eyex, eyey-0.5, eyez,
		upx, eyey, upz,
		0, 1, 0);

	glTranslatef(1.5, 0, -7);
	glRotatef(angle, 0, 1, 0);
	twosides();
	theEndoftheScene();
	theglasses();
	thestartofthegame();
	glLoadIdentity();
	glColor3f(0.8627, 0.16, 0.749);
	glTranslatef(0+bool_x, -.6+bool_y, eyey-s);
	glutSolidSphere(0.1, 30, 36);
	glLoadIdentity();
	glTranslatef(-8.5, 5, -50);
	glColor3f(1.0, 1.0, 0);
	writeStr(5, 10,"L I F E S : " + std::to_string(life) ,  GLUT_BITMAP_TIMES_ROMAN_24);
	glutSwapBuffers();
}
void reshape(int w, int h)
{
	if (h == 0) h = 1;
	ratio = w / (float)h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, ratio, 1, 200);
	glMatrixMode(GL_MODELVIEW);
}
void thestartofthegame() {
	glColor3f(.0666666666666667, .3333333333333333, 0.2352941176470588);
	int z1 = 6, z2 = 3;
	glBegin(GL_QUADS);
	//top
	glVertex3f(-3.5, -1.5, z1);
	glVertex3f(.5, -1.5, z1);
	glVertex3f(.5, -1.5, z2);
	glVertex3f(-3.5, -1.5, z2);

	////dowm
	glVertex3f(-3.5, -1.6, z1);
	glVertex3f(.5, -1.6, z1);
	glVertex3f(.5, -1.6, z2);
	glVertex3f(-3.5, -1.6, z2);
	////R
	glVertex3f(.5, -1.75, z1);
	glVertex3f(.5, -1.5, z1);	
	glVertex3f(.5, -1.5, z2);
	glVertex3f(.5, -1.75, z2);
	////L
	glVertex3f(-3.5, -1.75, z1);
	glVertex3f(-3.5, -1.5, z1);
	glVertex3f(-3.5, -1.5, z2);
	glVertex3f(-3.5, -1.75, z2);

	//for
	glVertex3f(-3.5, -1.5, z1);
	glVertex3f(-3.5, -1.6, z1);
	glVertex3f(.5, -1.6, z1);
	glVertex3f(.5, -1.5, z1);

	////back
	glVertex3f(-3.5, -1.5, z2);
	glVertex3f(-3.5, -1.6, z2);
	glVertex3f(.5, -1.6, z2);
	glVertex3f(.5, -1.5, z2);


	glEnd();
}
void twosides() {
	glBegin(GL_QUADS);
	//L
	glColor3f(0.8627, 0.16, 0.749);
	glVertex3f(-3.5, -1.5, 3);
	glVertex3f(-3.3, -1.5, 3);
	glVertex3f(-3.3, -1.5, -30);
	glVertex3f(-3.5, -1.5, -30);
	//SL
	glColor3f(0.949, 0.482, 0.917);
	glVertex3f(-3.3, -1.5, 3);
	glVertex3f(-3.3, -1.75, 3);
	glVertex3f(-3.3, -1.75, -30);
	glVertex3f(-3.3, -1.5, -30);

	glColor3f(0.8627, 0.16, 0.749);
	glVertex3f(-3.5, -1.75, 3);
	glVertex3f(-3.3, -1.75, 3);
	glVertex3f(-3.3, -1.5, 3);
	glVertex3f(-3.5, -1.5, 3);

	//R
	glColor3f(0.8627, 0.16, 0.749);
	glVertex3f(0.3, -1.5, 3);
	glVertex3f(0.5, -1.5, 3);
	glVertex3f(0.5, -1.5, -30);
	glVertex3f(0.3, -1.5, -30);
	//SR
	glColor3f(0.949, 0.482, 0.917);
	glVertex3f(.3, -1.5, 3);
	glVertex3f(.3, -1.75, 3);
	glVertex3f(.3, -1.75, -30);
	glVertex3f(.3, -1.5, -30);

	glColor3f(0.8627, 0.16, 0.749);
	glVertex3f(.3, -1.75, 3);
	glVertex3f(.5, -1.75, 3);
	glVertex3f(.5, -1.5, 3);
	glVertex3f(.3, -1.5, 3);

	//center
	glColor3f(0.8627, 0.16, 0.749);
	glVertex3f(-1.55, -1.5, 3);
	glVertex3f(-1.45, -1.5, 3);
	glVertex3f(-1.45, -1.5, -30);
	glVertex3f(-1.55, -1.5, -30);

}
void theglasses() {
	load(1);
	glBegin(GL_QUADS);
	int j=0;
	for (float i = 2.5; i > -30; i -= 2)
	{
		glColor4f(1.0, 1.0, 1, 0.7);
		glTexCoord2d(0,0);glVertex3f(-3.3, -1.5, i);
		glTexCoord2d(0,1);glVertex3f(-1.55, -1.5, i);
		glTexCoord2d(1,1);glVertex3f(-1.55, -1.5, i - 1.7);
		glTexCoord2d(1,0);glVertex3f(-3.3, -1.5, i - 1.7);
		
		glColor4f(1.0, 1.0, 1.0, 0.5);
		glTexCoord2d(0,0);glVertex3f(-1.45, -1.5, i);
		glTexCoord2d(0,1);glVertex3f(0.3, -1.5, i);
		glTexCoord2d(1,1);glVertex3f(0.3, -1.5, i - 1.7);
		glTexCoord2d(1,0);glVertex3f(-1.45, -1.5, i - 1.7);
		glass_pos[j]=i;
		j++;

	}
	for (int i = 0; i <16; i++)
	{
		glass_l[i]=i;
		glass_r[i]=i;
	}
	glEnd();
}
void theEndoftheScene() {
	//the end of the game 
	//top
	glColor3f(.596078431372549, .1019607843137255, .1254901960784314);
	glBegin(GL_QUADS);
	glVertex3f(-5, -1.4, -40);
	glVertex3f(2, -1.4, -40);
	glVertex3f(2, -1.4, -30);
	glVertex3f(-5, -1.4, -30);
	////down
	glVertex3f(-5, -2, -40);
	glVertex3f(2, -2, -40);
	glVertex3f(2, -2, -30);
	glVertex3f(-5, -2, -30);
	//left
	glVertex3f(-5, -1.4, -40);
	glVertex3f(-5, -2, -40);
	glVertex3f(-5, -2, -30);
	glVertex3f(-5, -1.4, -30);
	//right
	glVertex3f(2, -1.4, -40);
	glVertex3f(2, -2, -40);
	glVertex3f(2, -2, -30);
	glVertex3f(2, -1.4, -30);
	//for
	glVertex3f(-5, -1.4, -30);
	glVertex3f(-5, -2, -30);
	glVertex3f(2, -2, -30);
	glVertex3f(2, -1.4, -30);
	//back
	glVertex3f(-5, -1.4, -40);
	glVertex3f(-5, -2, -40);
	glVertex3f(2, -2, -40);
	glVertex3f(2, -1.4, -40);
	glEnd();

	//stears
	glBegin(GL_QUAD_STRIP);

		glColor3f(.5, .5, .5);
		glVertex3f(-3.8, -1.4, -38);
		glVertex3f(0.8, -1.4, -38);
		glVertex3f(-3.8, -1, -38);
		glVertex3f(0.8, -1, -38);
		glVertex3f(-3.8, -1, -40);
		glVertex3f(0.8, -1, -40);

		glVertex3f(-3.8, -1, -40);
		glVertex3f(0.8, -1, -40);
		glVertex3f(-3.8, -0.6, -40);
		glVertex3f(0.8, -0.6, -40);
		glVertex3f(-3.8, -0.6, -42);
		glVertex3f(0.8, -0.6, -42);

		glVertex3f(-3.8, -.6, -42);
		glVertex3f(0.8, -.6, -42);
		glVertex3f(-3.8, -0.2, -42);
		glVertex3f(0.8, -0.2, -42);
		glVertex3f(-3.8, -0.2, -44);
		glVertex3f(0.8, -0.2, -44);

		glVertex3f(-3.8, -.2, -44);
		glVertex3f(0.8, -.2, -44);
		glVertex3f(-3.8, 0.2, -44);
		glVertex3f(0.8, 0.2, -44);
		glVertex3f(-3.8, 0.2, -46);
		glVertex3f(0.8, 0.2, -46);

		glVertex3f(-3.8, 0.2, -46);
		glVertex3f(0.8, 0.2, -46);
		glVertex3f(-3.8, 0.6, -46);
		glVertex3f(0.8, 0.6, -46);
		glVertex3f(-3.8, 0.6, -48);
		glVertex3f(0.8, 0.6, -48);
	glEnd();

	//the door 
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex3f(-2.7, 5, -46);
	glVertex3f(-2.7, 0.4, -46);
	glVertex3f(-0.3, 0.4, -46);
	glVertex3f(-0.3, 5, -46);
	glVertex3f(-1.2, 5.7, -46);
	glVertex3f(-1.8, 5.7, -46);
	glVertex3f(-2.7, 5, -46);
	glEnd();

}

void load ( int imgnum ){
	if( imgnum == 1){
		
		data1= stbi_load("../texture/glass1.bmp", &width1, &height, &nrChannels, 0);
		check(data1);
	}
	else if( imgnum == 2){
		
		data1= stbi_load("container.jpg", &width1, &height, &nrChannels, 0);
		check(data1);
	}
}

void check (unsigned char *data1){
	if (data1)
		{
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data1);
}

void timer(int v)
{
	glutPostRedisplay();
	glutTimerFunc(30, timer, 0);
	//mute sound
	if(!sound_t)
		engine->setSoundVolume(0);
	else
		engine->setSoundVolume(1);

	if(t)
		angle += 0.5;
	else
		angle=0;
	a += 0.2;
	if (fullscreen)
		glutFullScreen();
	else
	{
		glutPositionWindow(10, 10);
		glutReshapeWindow(600, 600);
	}
	if(bool_y>=0.4)
		bool_up= false;
	else if (bool_y<=-.2)
		bool_up=true;
	if(bool_up )
	{
		bool_y+=0.1;
	}
	else
	{
		bool_y-=0.1;
	}
	// game over
	if(life==0){
		engine->setAllSoundsPaused(true);
		engine2->stopAllSounds();
		engine2->play2D("../audio/AUD-20230518-WA0018.wav", true);
		glutTimerFunc(8000,reset_engine,0);
		start();
	}
	//win
	if (move_ball>=18){
		engine->setAllSoundsPaused(true);
		engine2->stopAllSounds();
		engine2->play2D("../audio/Win sound effect no copyright(MP3_160K).wav", true);
		glutTimerFunc(4000,reset_engine,0);
		start();
	}
}
void reset_engine(int v)
{
	engine2->stopAllSounds();
	engine->setAllSoundsPaused(false);
}
int go_down(int x)
{
	int arr1[]={1,3,5,8,10,11,12,14}; //left to be broken
	int arr2[]={0,2,4,6,7,9,13,15};   //right to be broken
	bool l,r;
	for(int i=0;i<8;i++)
	{
		if (x==arr1[i])
			l=true;
		else if (x==arr2[i])
			r=true;
	}
	if(r)
		return 1;
	else 
		return 0;

}
void keybord(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
	else if(key==13)
	{
		t=!t;
		if(s==0)
			s=2;
		else
			s=0;
	}
	else if(key ==109 )
		sound_t=!sound_t;
}

void specialkeybord(int key, int x, int y){
	if (key == GLUT_KEY_F11)
		fullscreen = !fullscreen;
	if (key == GLUT_KEY_RIGHT) {
		if(bool_x<0.3){
			if(ball_left_flage)
				bool_x+=0.85;
			else
				bool_x+=0.85*2;}
			
			if(go_down(glass_r[move_ball])==0){
				engine->setAllSoundsPaused(true);
				engine2->play2D("../audio/glass.wav", true);
				bool_y=-5;
				glutTimerFunc(2000,reset_engine,0);
				life--;
			}
			else{
			eyez=glass_pos[move_ball]+-0.85;
			move_ball++;
			}
			ball_left_flage=false;
			
	}

	if (key == GLUT_KEY_LEFT) {
		if(bool_x>-0.8){
			if(ball_left_flage)
				bool_x-=0.85;
			else
				bool_x-=0.85*2;}
		if(go_down(glass_r[move_ball])==1){
				engine->setAllSoundsPaused(true);
				engine2->play2D("../audio/glass.wav", true);
				bool_y=-5;
				glutTimerFunc(2000,reset_engine,0);
				life--;
			}
		else{
			std::cout<<eyez;
			
			eyez=glass_pos[move_ball]+-0.85;
			move_ball++;	
		}
		ball_left_flage=false;
	}
		
	if (key == GLUT_KEY_UP) {
	glTranslatef(-8.5, 5, -50);
	glColor3f(1.0, 1.0, 0);
		 renderBitmapString(0, 2, -10, GLUT_BITMAP_TIMES_ROMAN_24, "START");

	}
	if (key == GLUT_KEY_DOWN) {
		if (eyez <= 0) {
			eyez += 1;
			eyey = .1 * abs(cos(angle));
		}	
	}
	
}

void writeStr(float x, float y, std::string  str, void* font)
{
	int len = str.length();
	glRasterPos2f(x, y);
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, str[i]);
	}
}
void start ()
{
	 bool_x=0,bool_y=0;
	 life = 3;
	 eyex=0, eyey=0, eyez=0, upx=0, upz=-50;
	 s=0;
	 move_ball=2;
	 ratio=0, angle=0, a=0;
	 fullscreen = true;
	 t = true;
	 sound_t=true;
	 bool_up=true;
	 ball_right_flage = false , ball_left_flage =true;

}
void renderBitmapString(float x, float y, float z, void* font, const char* string) {
    const char* c;
    glRasterPos3f(x, y, z);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}