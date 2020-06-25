//========================================================================
// Week 8 - Pixel Tests and Blending
//========================================================================
#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <stdio.h>
#include <stdlib.h>
#ifndef __APPLE__
#include <GL/glew.h>
#endif
#include <GL/glfw.h>
#include "W_Common.h"
#include "Cube.h"
#include <glm/glm.hpp>
#include "Camera.h"
#include "Scene.h"
#include <iostream>


//========================================================================
// This is needed for newer versions of Visual Studio
//========================================================================
FILE _iob[] = { *stdin, *stdout, *stderr };

using namespace std;



extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}
//========================================================================



int main( void )
{
    int width, height, x;
    double t;
    
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }
    
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Open a window and create its OpenGL context
    if( !glfwOpenWindow( 1280, 720, 0,0,0,0, 24,0, GLFW_WINDOW ) )
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        
        glfwTerminate();
        exit( EXIT_FAILURE );
    }
    
#ifndef __APPLE__
	glewExperimental = GL_TRUE;
	glewInit();
#endif
	// Leave this here! On windows machines in Lab, glewInit is generating some mysterious, but apparently
	// harmless, error - and we need it gone.
	glGetError();

    glfwSetWindowTitle( "Week 8" );
    
    // Ensure we can capture the escape key being pressed below
    glfwEnable( GLFW_STICKY_KEYS );
    
    // Enable vertical sync (on cards that support it)
    glfwSwapInterval( 1 );
    

	Scene* scene = Scene::Instance();
	scene->Init();


	Camera* pCamera = new Camera(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	pCamera->setStaticCamera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	scene->setCamera(pCamera);

	float pDeltat = 10.0f;
	bool pClicked = false;
	
	CameraMode pCurrentMode = CameraMode::Static;
	
    do
    {
		
		if (glfwGetKey('C') == GLFW_PRESS && !pClicked)
		{
			
			pClicked = true;
			if (pCurrentMode == CameraMode::Static)
			{
				pCamera->setMode(CameraMode::FirstPerson);
				pCurrentMode = CameraMode::FirstPerson;
			}
			else
			{
				pCamera->setMode(CameraMode::Static);
				pCurrentMode = CameraMode::Static;
				
			}
			

		}
		if (glfwGetKey('C') != GLFW_PRESS)
		{
			pClicked = false;
		}
		
        t = glfwGetTime();
        glfwGetMousePos( &x, NULL );
        
        // Get window size (may be different than the requested size)
        glfwGetWindowSize( &width, &height );
        
        // Special case: avoid division by zero below
        height = height > 0 ? height : 1;
        
        glViewport( 0, 0, width, height );
        
        // Clear color buffer to black
        glClearColor( 0.4f, 0.5f, 0.4f, 0.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
       
		scene->Update(0.0f);
        // Swap buffers
        glfwSwapBuffers();
        
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
          glfwGetWindowParam( GLFW_OPENED ) );
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    exit( EXIT_SUCCESS );
}


