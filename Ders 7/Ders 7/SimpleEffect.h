//
//  SimpleEffect.h
//  Ders 7
//
//  Created by Gurel Erceis on 4/15/13.
//  Copyright (c) 2013 Yogurt3D. All rights reserved.
//

#ifndef Ders_7_SimpleEffect_h
#define Ders_7_SimpleEffect_h
#include "Effect.h"
#include "SOIL.h"





class SimpleEffect: public Effect{
public:
	GLint ColorCorrMap;	
	GLint LoadGLTexture(const char *filename, int width, int height)
	{
		GLuint _texture;
    
    
		_texture = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture 
		(
		filename,
		SOIL_LOAD_AUTO,
		 SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT 
		);
    
		 // check for an error during the load process 
		if(_texture == 0)
		{
			 printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
		}
	
    
		glBindTexture(GL_TEXTURE_2D, _texture); // select our current texture
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  // texture should tile
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		return _texture;
	}
	SimpleEffect(int* screen_width, int* screen_height):Effect("effect_simple.frag",screen_width, screen_height){
		
		glActiveTexture(GL_TEXTURE1);
		ColorCorrMap = LoadGLTexture("ramp.bmp",*screen_width,1);
		UniTexture = glGetUniformLocation(programID, "ColorCorrMap");
        if (UniTexture == -1) {
            fprintf(stderr, "Could not bind attribute %s\n", "ColorCorrMap");
        }
    }
    virtual void draw(){
        glUseProgram(programID);
		//glUniform1i (ColorCorrMap, 1); 
		Effect::draw();
    }
private:
    GLuint UniTexture;
};

#endif