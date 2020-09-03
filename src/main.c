#include "engine.h"

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
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord3f(0, 0 ,0); glVertex3f(-2.0f, 0.2f, -2.0f);
	glTexCoord3f(1, 0 ,0); glVertex3f(-2.0f, 0.2f,  2.0f);
	glTexCoord3f(1 ,1, 1); glVertex3f( 2.0f, 0.2f,  2.0f);
	glTexCoord3f(0, 1, 0); glVertex3f( 2.0f, 0.2f, -2.0f);
	glEnd();
	for(int i = -3; i < 3; i++) 
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
		drawGameHud();

		glutSwapBuffers();
	}
	else if (is_in_menu == 1) {
		display();
		setOrthographicProjection();	
		glPushMatrix();
		glLoadIdentity();
		// kill me please
		// DOESNT WORK IN ARCH BTW
		if (wut == 0) {
			glColor3f(1.0, 1.0, 1.0);renderBitmapString(50,(glutGet(GLUT_WINDOW_HEIGHT) / 2),0,GLUT_BITMAP_HELVETICA_18,"->Play game");glColor3f(0.5, 0.5, 0.5);
		}
		else {
			glColor3f(0.5, 0.5, 0.5);renderBitmapString(50,(glutGet(GLUT_WINDOW_HEIGHT) / 2),0,GLUT_BITMAP_HELVETICA_18,"Play game");glColor3f(1.0, 1.0, 1.0);
		}
		if (wut == 1) {
			glColor3f(1.0, 1.0, 1.0);renderBitmapString(50,((glutGet(GLUT_WINDOW_HEIGHT) / 2) + 20),0,GLUT_BITMAP_HELVETICA_18,"->Exit");glColor3f(0.5, 0.5, 0.5);
		}
		else {
			glColor3f(0.5, 0.5, 0.5);renderBitmapString(50,((glutGet(GLUT_WINDOW_HEIGHT) / 2) + 20),0,GLUT_BITMAP_HELVETICA_18,"Exit");glColor3f(1.0, 1.0, 1.0);
		}
		glPopMatrix();
		restorePerspectiveProjection();
		drawMenuHud();
		glutSwapBuffers();

		frame++;
		timeget=glutGet(GLUT_ELAPSED_TIME);
		printf("FPS:%4.2f\n", frame*1000.0/(timeget-timebase));
		timebase = timeget;
		frame = 0;

	}
}

/*************************************
*               MAIN
**************************************/

int main(int argc, char *argv[]) {
	sysInfo();	

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE );
	glutInitWindowSize(960, 540);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-960)/2,
				(glutGet(GLUT_SCREEN_HEIGHT)-540)/2);
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
	init();
	// init mixer
	mixerInit();
	//	DUUM_SoundTest();
	// enter GLUT event processing cycle
	glutMainLoop();
	return 1;
}
