GLuint textures[4];

void loadTexture(GLuint texture,const char *filename) {
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	unsigned int error;
	unsigned char *image;
	unsigned int width, height;
	error = lodepng_decode32_file(&image, &width, &height, filename);
	if (error)  
		printf("ERROR %u: %s. FILENAME: %s\n", error, lodepng_error_text(error), filename);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	
		free(image);
}

/*
 * Put textures here
 */

void loadtextures(){
	glGenTextures(4, textures);
	loadTexture(textures[0],"./res/img/cu.png");
	//loadTexture(textures[1],"./res/img/notcu.png");
	loadTexture(textures[2],"./res/img/simcu.png");
	loadTexture(textures[3],"./res/img/DuumF1.png");
}
