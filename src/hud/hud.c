/*
 * In-game hud and menus hud
 */

#include "../graphics/texloader.h"

void drawMenuHud(){
	// set a black sky color
	glClearColor(0.0, 0.0, 0.0, 0.0);	
	// switch to projection mode
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glLoadIdentity();

	// set a 2D orthographic projection
	glOrtho(-1.0f, 2.0f, -2.0f , 1.0f, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	// switch back to modelview mode
	glLoadIdentity();
	glDisable(GL_COLOR_MATERIAL);
	/*glBindTexture(GL_TEXTURE_2D, textures[1]);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBegin(GL_QUADS);
	glTexCoord3f(0,1,0); glVertex3f(0.05f, 0.1f, 0.0f);   // top-left
	glTexCoord3f(1,1,1); glVertex3f(0.95f, 0.1f, 0.0f);   // top-right
	glTexCoord3f(1,0,0); glVertex3f(0.95f, 0.8f, 0.0f);    // bottom-right
	glTexCoord3f(0,0,0); glVertex3f(0.05f, 0.8f, 0.0f);    // bottom-left
	glEnd();
	glDisable(GL_TEXTURE_2D);*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord3f(0,1,0); glVertex3f(-1.0f, -2.0f, 0.0f);   // top-left
	glTexCoord3f(1,1,1); glVertex3f(2.0f, -2.0f, 0.0f);   // top-right
	glTexCoord3f(1,0,0); glVertex3f(2.0f, 1.0f, 0.0f);    // bottom-right
	glTexCoord3f(0,0,0); glVertex3f(-1.0f, 1.0f, 0.0f);    // bottom-left
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
	glDepthMask( GL_TRUE );
}

void drawGameHud(){
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glLoadIdentity();

	glOrtho(-1.0f, 2.0f, -2.0f , 1.0f, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glDepthMask( GL_TRUE );
}
