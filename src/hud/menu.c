/*
 * GLUT menus
 */

// Menu status
int menuFlag = 0;

// Constant definitions for Menus
#define RED 1
#define GREEN 2
#define BLUE 3
#define ORANGE 4

#define FILL 1
#define LINE 2
#define FULLSCREEN 1 

// Menu identifiers
int fillMenu, fontMenu, mainMenu, colorMenu, Fullscreen;

// Default font
void *font = GLUT_BITMAP_TIMES_ROMAN_24;

// Font definitions for menus
#define INT_GLUT_BITMAP_8_BY_13 1
#define INT_GLUT_BITMAP_9_BY_15 2
#define INT_GLUT_BITMAP_TIMES_ROMAN_10  3
#define INT_GLUT_BITMAP_TIMES_ROMAN_24  4
#define INT_GLUT_BITMAP_HELVETICA_10  5
#define INT_GLUT_BITMAP_HELVETICA_12  6
#define INT_GLUT_BITMAP_HELVETICA_18  7

void processMenuStatus(int status, int x, int y) {

	if (status == GLUT_MENU_IN_USE)
		menuFlag = 1;
	else
		menuFlag = 0;
}

void processMainMenu(int option) {}
void processFillMenu(int option) {

	switch (option) {

		case FILL: glPolygonMode(GL_FRONT, GL_FILL); break;
		case LINE: glPolygonMode(GL_FRONT, GL_LINE); break;
	}
}

void processFullscreen(int option) {
	switch (option) {
		case FULLSCREEN:
			glutFullScreen();
			break;
	}
}

void processFontMenu(int option) {
	switch (option) {
		case INT_GLUT_BITMAP_8_BY_13:
			font = GLUT_BITMAP_8_BY_13;
			break;
		case INT_GLUT_BITMAP_9_BY_15:
			font = GLUT_BITMAP_9_BY_15;
			break;
		case INT_GLUT_BITMAP_TIMES_ROMAN_10:
			font = GLUT_BITMAP_TIMES_ROMAN_10;
			break;
		case INT_GLUT_BITMAP_TIMES_ROMAN_24:
			font = GLUT_BITMAP_TIMES_ROMAN_24;
			break;
		case INT_GLUT_BITMAP_HELVETICA_10:
			font = GLUT_BITMAP_HELVETICA_10;
			break;
		case INT_GLUT_BITMAP_HELVETICA_12:
			font = GLUT_BITMAP_HELVETICA_12;
			break;
	 	case INT_GLUT_BITMAP_HELVETICA_18:
			font = GLUT_BITMAP_HELVETICA_18;
			break;
	}
}

void createPopupMenus() {
	fontMenu = glutCreateMenu(processFontMenu);

	glutAddMenuEntry("BITMAP_8_BY_13 ",INT_GLUT_BITMAP_8_BY_13 );
	glutAddMenuEntry("BITMAP_9_BY_15",INT_GLUT_BITMAP_9_BY_15 );
	glutAddMenuEntry("BITMAP_TIMES_ROMAN_10 ",INT_GLUT_BITMAP_TIMES_ROMAN_10  );
	glutAddMenuEntry("BITMAP_TIMES_ROMAN_24",INT_GLUT_BITMAP_TIMES_ROMAN_24  );
	glutAddMenuEntry("BITMAP_HELVETICA_10 ",INT_GLUT_BITMAP_HELVETICA_10  );
	glutAddMenuEntry("BITMAP_HELVETICA_12",INT_GLUT_BITMAP_HELVETICA_12  );
	glutAddMenuEntry("BITMAP_HELVETICA_18",INT_GLUT_BITMAP_HELVETICA_18  );

	fillMenu = glutCreateMenu(processFillMenu);

	glutAddMenuEntry("Fill",FILL);
	glutAddMenuEntry("Line",LINE);
	
	Fullscreen = glutCreateMenu(processFullscreen);
	glutAddMenuEntry("Fullscreen", FULLSCREEN);

	mainMenu = glutCreateMenu(processMainMenu);

	glutAddSubMenu("Polygon Mode", fillMenu);
	glutAddSubMenu("Color", colorMenu);
	glutAddSubMenu("Font", fontMenu);
	glutAddSubMenu("Window", Fullscreen);
	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// this will allow us to know if the menu is active
	glutMenuStatusFunc(processMenuStatus);
}
