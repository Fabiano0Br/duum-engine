#include <SOIL/SOIL.h>										//Simple OpenGL Image Loading library. ( SOIL )
#include <unistd.h>
#include <string.h>											//String library to manipulate the directory and frame strings
#include <dirent.h>											//Directory operations to count the no of frames for initalization

int width, height;											//Width and height of the frames
GLint window;												//Integer reference for the window opened
int sleepdur;												//Duration of frame delay in microseconds
int p = 1;													//Play is P = 1. Pause is P = 0
int i = 0;													//Loop variable
int n = 0;													//Holds number of frames
GLfloat someColor[ 3 ][ 3 ] = { { 0.0, 1.0, 1.0 }, { 0.0, 1.0, 1.0 }, { 00, 1.0, 1.0 } };					
char *image_Arr[ 100000 ]; 									//Holds frame data

Mix_Chunk *videomusic;

void init( ) {												//Initializations : start init()
		
	char str[40];											//String for holding the complete frame address in filesystem
	int l;													//Loop variable
	char *formt;											//Holds formatted string
	char di[30];											//Holds frame directory name
	DIR *dp;												//DIRECTORY type pointer to point to the selected frame directory
	struct dirent *ep;										//Directory entry
	
	strcpy( di, "MOVIE" );
	sleepdur = 17285;
		
	//Open Directory
	dp = opendir( di );
	
	//If directory opened successfully
	if( dp != NULL ) 
	{
		//While the entry is  not null
		while( ep = readdir( dp ) ) 
		{
			
			//Avoid self pointer and parent pointer
			if( ( strcmp( ep->d_name, "." ) == 0 ) || ( strcmp( ep->d_name, ".." ) == 0 ) )
				continue;
			n++;											//Increment file counter
			
		}
		//After the count is finished close the directory
		( void ) closedir( dp );
	}
	
	//If directory opening is not successful
	else
		perror( "Could not open directory" );
	
	//Initializr image_Arr[] with the frame names
	for( l = 0; l < n; l++ ) {
		
		//Form formatted string
		sprintf( str, "%s/scene%.5d.jpg", di, ( l + 1 ) );
		//Assign memory to image_Arr[l] dynamically to hold string 
		image_Arr[ l ] = (char * ) malloc( (strlen(str)) * sizeof(char *) );
		//Copy into image_Arr[ l ] formatted string
		strcpy( image_Arr[ l ], str );
		
	}
	
	//Clear Background to black

    //Create Texture objecct to hold image as textures
    //integer to hold texture reference
    GLuint tex;
    glGenTextures( 1, &tex );								//Generate first availabe texture name
    glBindTexture( GL_TEXTURE_2D, tex );					//Create texture name
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    
    //Set projection mode for orthogonal view
    glMatrixMode( GL_PROJECTION );
    //Load identity matrix
    glLoadIdentity();
    //Set orthogonal clipping coordinates
    gluOrtho2D( 0.0, 800.0, 0.0, 400.0 );
    
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,2,4096);
     videomusic = Mix_LoadWAV("audio.wav");
	Mix_PlayChannel(-1,videomusic, 100);
}															//End init()



void display(){
			
    unsigned char *image;									//Unsugned byte type to hold the image data address
    
    glEnable( GL_TEXTURE_2D );    
    if( p == 1 ) 											//If condition is play, iterate through the images
    {
    
    	//Load up the image into image pointer by SOIL_load_image
     	image = SOIL_load_image( image_Arr[ i ], &width, &height, 0, SOIL_LOAD_RGB );
     	//Generate texture
       	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
        //Clear buffer to preset values
       	glClear( GL_COLOR_BUFFER_BIT );
        
        //Draw a quad with the texture attached to its vertices	
        glBegin( GL_QUADS );
        glColor3f( 1.0, 1.0, 1.0 );							//Background black
        	//Bottom-left
        	glTexCoord2f( 0.0f, 1.0f );						
        	glVertex2f( 0.0f, 0.0f  );
        	//Bottom-right
        	glTexCoord2f( 1.0f, 1.0f );
        	glVertex2f( 800.0f, 0.0f );
        	//Top-right
    		glTexCoord2f( 1.0f, 0.0f );
        	glVertex2f( 800.0f, 400.0f );
        	//Top-left
        	glTexCoord2f( 0.0f, 0.0f );
        	glVertex2f( 0.0f, 400.0f );
        glEnd();
        
	i++;												//Increment frame
    	i = i % n;											//Keep frame inside frame count limit
    	
    }
    /* no pause in use, so
    else 													//If condition is play
    {
    	
    	//load last static frame
      	image = SOIL_load_image( image_Arr[ i ], &width, &height, 0, SOIL_LOAD_RGB );
      	//Generate texture
       	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
        
        //Clear buffer to preset values
       	glClear( GL_COLOR_BUFFER_BIT );
       	
       	//Draw a quad with the texture attached to its vertices	
        glBegin( GL_QUADS );				
        glColor3f( 1.0, 1.0, 1.0 );							//Background black
        	//Bottom-left
        	glTexCoord2f( 0.0f, 1.0f );
        	glVertex2f( 0.0f, 0.0f  );
        	//Bottom-right
        	glTexCoord2f( 1.0f, 1.0f );
        	glVertex2f( 800.0f, 0.0f );
        	//Top-right
        	glTexCoord2f( 1.0f, 0.0f );
        	glVertex2f( 800.0f, 400.0f );
        	//Top-left
    		glTexCoord2f( 0.0f, 0.0f );
        	glVertex2f( 0.0f, 400.0f );
        glEnd();
        
    }*/
   	glDisable( GL_TEXTURE_2D );          											
    glFlush();												//Display all the generated contents
    SOIL_free_image_data( image );							//free up the image data at pointer
        
    usleep(sleepdur);   									//Introduce delay to prevent too-fast playback
}
