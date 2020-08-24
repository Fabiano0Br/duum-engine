#include "../exit.c"

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

void mouseMove(int x, int y) {
	int lastX, lastY;
	lastX = x;
        lastY = y;
	int deltaX = x - lastX;
        int deltaY = y - lastY;
	
	int windowX     = glutGet( GLUT_WINDOW_X );
	int windowY     = glutGet( GLUT_WINDOW_Y );
	int screenWidth     = glutGet( GLUT_SCREEN_WIDTH );
	int screenHeight    = glutGet( GLUT_SCREEN_HEIGHT );

	int screenLeft = -windowX;
	int screenTop = -windowY;
	int screenRight = screenWidth - windowX;
	int screenBottom = screenHeight - windowY;
	
	// update deltaAngle
	deltaAngle = (x - xOrigin) * 0.001f;

	// update camera's direction
	lx = sin(angle + deltaAngle);
	lz = -cos(angle + deltaAngle);

        if( deltaX == 0 && deltaY == 0 ) return;

	if( x <= screenLeft+10 || (y) <= screenTop+10 || x >= screenRight-10 || y >= screenBottom - 10) {
        	lastX = 150;
        	lastY = 150;
		angle += deltaAngle;
		xOrigin = -1;
        	glutWarpPointer( lastX, lastY );
        }
}
