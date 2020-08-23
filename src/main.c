#include "engine.h"

// angle of rotation for the camera direction
float angle = 0.0f;

// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;

// XZ position of the camera
float x=0.0f, z=5.0f;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;
float deltaMove2 = 0;
float activeKeys = 0;
int xOrigin = -1;

// Mouse warp
int lastX = 150;
int lastY = 150;
int curX, curY;

// scale of snowman
float scale = 1.0f;
int scrinheight;

// variables to compute frames per second
int frame;
long timeget, timebase;
char s[50];

// width and height of the window
int h,w;

void renderBitmapString(
		float x,
		float y,
		float z,
		void *font,
		char *string) {
  char *c;
  glRasterPos3f(x, y,z);
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }
}

void computePos2() {
	x += deltaMove2 * lz * 0.1f;
	z += deltaMove2 * (-lx) * 0.1f;
}

void computePos() {
	x += deltaMove * lx *0.1f;
	z += deltaMove * lz * 0.1f;
}

void lighting(void){ 
	glEnable( GL_ALPHA_TEST );
	glEnable (GL_DEPTH_TEST);
        glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL); 
	glEnable (GL_BLEND); 
	glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);	
	glDepthMask(GL_TRUE);
}

void drawSnowMan() {
	glScalef(scale, scale, scale);
}

void setOrthographicProjection() {
	// switch to projection mode
	glMatrixMode(GL_PROJECTION);
	// save previous matrix which contains the settings for the perspective projection
	glPushMatrix();

	// reset matrix
	glLoadIdentity();

	// set a 2D orthographic projection
	gluOrtho2D(0, w, h, 0);

	// switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}
// draws hud 

void setOrthographicProjectionHUD() {
	glClearColor(0.0, 0.0, 0.0, 0.0);	
	// switch to projection mode
	glMatrixMode(GL_PROJECTION);
	// save previous matrix which contains the settings for the perspective projection
	glPushMatrix();

	// reset matrix
	glLoadIdentity();

	// set a 2D orthographic projection
	glOrtho(-1.0f, 2.0f, -2.0f , 1.0f, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	// switch back to modelview mode
	glLoadIdentity();
	//loadTexture("notcu.png"); // we may have to wait to load this texture to get away from errors
	glDisable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBegin(GL_QUADS);
	glTexCoord3f(0,1,0); glVertex3f(0.05f, 0.1f, 0.0f);   // top-left
	glTexCoord3f(1,1,1); glVertex3f(0.95f, 0.1f, 0.0f);   // top-right
	glTexCoord3f(1,0,0); glVertex3f(0.95f, 0.8f, 0.0f);    // bottom-right
	glTexCoord3f(0,0,0); glVertex3f(0.05f, 0.8f, 0.0f);    // bottom-left
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	// revert to original projection matrix
	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();
	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
	glDepthMask( GL_TRUE );
}
// draws in game hud ()
void setOrthographicProjectionINGAMEHUD() {
	// switch to projection mode
	glMatrixMode(GL_PROJECTION);
	// save previous matrix which contains the settings for the perspective projection
	glPushMatrix();

	// reset matrix
	glLoadIdentity();

	// set a 2D orthographic projection
	glOrtho(-1.0f, 2.0f, -2.0f , 1.0f, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	// switch back to modelview mode
	glLoadIdentity();
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBegin(GL_QUADS);
	glTexCoord3f(0,1,0); glVertex3f(1.0f, -2.0f, 0.0f);   // top-left
	glTexCoord3f(1,1,1); glVertex3f(1.9f, -2.0f, 0.0f);   // top-right
	glTexCoord3f(1,0,0); glVertex3f(1.9f, -0.5f, 0.0f);    // bottom-right
	glTexCoord3f(0,0,0); glVertex3f(1.0f, -0.5f, 0.0f);    // bottom-left
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	// revert to original projection matrix
	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
	glDepthMask( GL_TRUE );
}

void restorePerspectiveProjection() {
	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void changeSize(int ww, int hh) {
	h = hh;
	w = ww;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {
	if (deltaMove) 
		computePos();

	if (deltaMove2)
		computePos2();
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	glClear(GL_COLOR_BUFFER_BIT);
	if (is_in_menu == 0) {
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	gluLookAt(	x, 1.0f, z,
			x+lx, 1.0f,  z+lz,
			0.0f, 1.0f,  0.0f);
	 
	// sky color 
	glClearColor(0.5, 0.0, 0.0, 0.0); // UGLY
	// Draw ground
	loadtextures();
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord3f(0, 0 ,0); glVertex3f(-2.0f, 0.2f, -2.0f);
	glTexCoord3f(1, 0 ,0); glVertex3f(-2.0f, 0.2f,  2.0f);
	glTexCoord3f(1 ,1, 1); glVertex3f( 2.0f, 0.2f,  2.0f);
	glTexCoord3f(0, 1, 0); glVertex3f( 2.0f, 0.2f, -2.0f);
	glEnd();
	for(int i = -3; i < 3; i++) 
		for(int j=-3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*10.0f, 0.0f, j * 10.0f);
			drawSnowMan();
			glPopMatrix();
		}
		glBegin(GL_POLYGON);
		glTexCoord3f(0, 0, 0); glVertex3f(  0.5, -0.5, 0.5 );
		glTexCoord3f(0, 1, 0); glVertex3f(  0.5,  0.5, 0.5 );
		glTexCoord3f(1, 1, 1); glVertex3f( -0.5,  0.5, 0.5 );
		glTexCoord3f(0, 1, 0); glVertex3f( -0.5, -0.5, 0.5 );
		glEnd();
		
		// Lado roxo - DIREITA
		glBegin(GL_POLYGON);
		glTexCoord3f(1, 0, 0);
		glVertex3f( 0.5, -0.5, -0.5 );
		glVertex3f( 0.5,  0.5, -0.5 );
		glVertex3f( 0.5,  0.5,  0.5 );
		glVertex3f( 0.5, -0.5,  0.5 );
		glEnd();

		// Lado verde - ESQUERDA
		glBegin(GL_POLYGON);
		glTexCoord3f(1, 1, 1);
		glVertex3f( -0.5, -0.5,  0.5 );
		glVertex3f( -0.5,  0.5,  0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
		glVertex3f( -0.5, -0.5, -0.5 );
		glEnd();

		// Lado azul - TOPO
		glBegin(GL_POLYGON);
		glTexCoord3f(0, 1, 0);
		glVertex3f(  0.5,  0.5,  0.5 );
		glVertex3f(  0.5,  0.5, -0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
		glVertex3f( -0.5,  0.5,  0.5 );
		glEnd();

		// Lado vermelho - BASE
		glBegin(GL_POLYGON);
		glTexCoord3f(1, 1, 0);
		glVertex3f(  0.5, -0.5, -0.5 );
		glVertex3f(  0.5, -0.5,  0.5 );
		glVertex3f( -0.5, -0.5,  0.5 );
		glVertex3f( -0.5, -0.5, -0.5 );
		glEnd();
		glDisable(GL_TEXTURE_2D);
		setOrthographicProjectionINGAMEHUD();

		glutSwapBuffers();
	}
	else if (is_in_menu == 1) {
		setOrthographicProjectionHUD();
		setOrthographicProjection();
		glPushMatrix();
		glLoadIdentity();
		// kill me please
		// DOESNT WORK IN ARCH BTW
		if (wut == 0) {
			glColor3f(1.0, 1.0, 1.0);renderBitmapString(50,(glutGet(GLUT_SCREEN_HEIGHT) / 2),0,GLUT_BITMAP_HELVETICA_18,"Play gayme");glColor3f(0.5, 0.5, 0.5);
		}
		else {
			glColor3f(0.5, 0.5, 0.5);renderBitmapString(50,(glutGet(GLUT_SCREEN_HEIGHT) / 2),0,GLUT_BITMAP_HELVETICA_18,"Play gayme");glColor3f(1.0, 1.0, 1.0);
		}
		if (wut == 1) {
			glColor3f(1.0, 1.0, 1.0);renderBitmapString(50,((glutGet(GLUT_SCREEN_HEIGHT) / 2) + 50),0,GLUT_BITMAP_HELVETICA_18,"Exit this crap");glColor3f(0.5, 0.5, 0.5);
		}
		else {
			glColor3f(0.5, 0.5, 0.5);renderBitmapString(50,((glutGet(GLUT_SCREEN_HEIGHT) / 2) + 50),0,GLUT_BITMAP_HELVETICA_18,"Exit this crap");glColor3f(1.0, 1.0, 1.0);
		}
		glPopMatrix();
		restorePerspectiveProjection();
		glutSwapBuffers();

		frame++;
		timeget=glutGet(GLUT_ELAPSED_TIME);
		printf("FPS:%4.2f\n", frame*1000.0/(timeget-timebase));
		timebase = timeget;
		frame = 0;

	}
}

void bestfuncever() {
	DUUM_SoundTest2();
	if (wut == 1) {
	exit(0);
	glutDestroyMenu(mainMenu);
	glutDestroyMenu(fillMenu);
	glutDestroyMenu(colorMenu);
	glutDestroyMenu(fontMenu);
	glutDestroyMenu(Fullscreen);
}
else {
	is_in_menu = 0;
}}

// -----------------------------------
//             KEYBOARD
// -----------------------------------

void processNormalKeys(unsigned char key, int xx, int yy) {
	switch (key) {
		case 27:is_in_menu = 1;break;
		case 119:deltaMove = 0.5f; break;
		case 115:deltaMove = -0.5f; break;
		case 97:deltaMove2 = 0.5; break;
		case 100 : deltaMove2 = -0.5; break;
		case 13 : bestfuncever(); break;
	}
}

void pressKey(int key, int xx, int yy) { 
	switch (key) {
		/*case GLUT_KEY_UP : deltaMove = 0.5f; break;
		case GLUT_KEY_DOWN : deltaMove = -0.5f; activeKeys += 1; break;
		case GLUT_KEY_LEFT : deltaMove2 = 0.5f;break;
		case GLUT_KEY_RIGHT : deltaMove2 = -0.5f;break;*/
		case GLUT_KEY_UP : wut = 0;DUUM_SoundTest2();break;
		case GLUT_KEY_DOWN : wut = 1;DUUM_SoundTest2();break;// nes megaman title screen vibes
	}
}

void releaseKey(int key, int x, int y) {
	switch (key) {
		/*case GLUT_KEY_UP :  
		case GLUT_KEY_DOWN : deltaMove = 0; activeKeys += -1;break;
		case GLUT_KEY_LEFT :
		case GLUT_KEY_RIGHT : deltaMove2 = 0;break;
	*/}
}
void releaseNormalKeys(unsigned char key, int x, int y) {
	switch (key) {
		case 119 : 
		case 115 : deltaMove = 0;break;
		case 97 : 
		case 100 : deltaMove2 = 0;break;
	}
}
// -----------------------------------
//             MOUSE
// -----------------------------------

void mouseMove(int x, int y) {
	// update deltaAngle
	deltaAngle = (x - xOrigin) * 0.001f;

	// update camera's direction
	lx = sin(angle + deltaAngle);
	lz = -cos(angle + deltaAngle);
	int deltaX = x - lastX;
        int deltaY = y - lastY;

        lastX = x;
        lastY = y;

        if( deltaX == 0 && deltaY == 0 ) return;

	int windowX     = glutGet( GLUT_WINDOW_X );
	int windowY     = glutGet( GLUT_WINDOW_Y );
	int screenWidth     = glutGet( GLUT_SCREEN_WIDTH );
	int screenHeight    = glutGet( GLUT_SCREEN_HEIGHT );

	int screenLeft = -windowX;
	int screenTop = -windowY;
	int screenRight = screenWidth - windowX;
	int screenBottom = screenHeight - windowY;

	if( x <= screenLeft+10 || (y) <= screenTop+10 || x >= screenRight-10 || y >= screenBottom - 10) {
        	lastX = 150;
        	lastY = 150;
		angle += deltaAngle;
		xOrigin = -1;
        	glutWarpPointer( lastX, lastY );
        }
    	curX += deltaX;
   	curY -= deltaY;
}

//void mouseButton(int button, int state, int x, int y) {

//	if (button == GLUT_LEFT_BUTTON) {
		// when the button is released
//		if (state == GLUT_UP) {
//			angle += deltaAngle;
//			xOrigin = -1;
//		}
//		else  {// state = GLUT_DOWN
//			xOrigin = x;
//	}
//}


//}

// -----------------------------------
//             MAIN
// -----------------------------------

int main(int argc, char *argv[]) {
	sysInfo();	

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE );
	glutInitWindowPosition(320,320);
	glutCreateWindow("DuuM");

	lighting();
	loadtextures();
	
	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
	glutKeyboardUpFunc(releaseNormalKeys);
	glutSetCursor(GLUT_CURSOR_NONE);
	
	// here are the two new functions
	glutPassiveMotionFunc(mouseMove);
	
	// OpenGL init
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE); 
	
	// init Menus
	createPopupMenus();
	// init mixer
	mixerInit();
	DUUM_SoundTest();
	// enter GLUT event processing cycle
	glutMainLoop();
	return 1;
}
