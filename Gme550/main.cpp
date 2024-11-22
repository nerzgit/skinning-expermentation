//
//#include <stdio.h>
//#include <stdlib.h>
//#include <vector>
//
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//GLFWwindow* window;
//
////#include <SDL/SDL_mixer.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//using namespace glm;
//
//#include "common/shader.hpp"
//#include "common/texture.hpp"
//#include "common/controls.hpp"
//#include "common/objloader.hpp"
//#include "common/vboindexer.hpp"
//
//#include "world.h"
//
//
//
//
//void initOpenGL();
//void playAudio();
//
//int main( void )
//{
//    initOpenGL();
//    
//    playAudio();
//    
//    World *world;
//    world = new World(window);
//    
//    do{
//        
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        world -> Render(window);
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//        
//    }while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
//    
//    delete world;
//
//    glfwTerminate();
//
//    return 0;
//}
//
//void initOpenGL()
//{
//    
//    if( !glfwInit() )
//    {
//        fprintf( stderr, "Failed to initialize GLFW\n" );
//        getchar();
//    }
//    
//    glfwWindowHint(GLFW_SAMPLES, 4);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // Opengl 4.X
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1); // Opengl X.1 !!!4.1 supported from MacBook Early 2015!!!
//    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    
//    int windowWidth = 1024;
//    int windowHeight = 768;
//    
//    window = glfwCreateWindow( windowWidth, windowHeight, "PLAY", NULL, NULL);
//    if( window == NULL ){
//        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
//        getchar();
//        glfwTerminate();
//    }
//    glfwMakeContextCurrent(window);
//    
//    int frameBufferWidth = windowWidth;
//    int frameBufferHeight = windowHeight;
//    
//    glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
//    
//    glewExperimental = true;
//    if (glewInit() != GLEW_OK) {
//        fprintf(stderr, "Failed to initialize GLEW\n");
//        getchar();
//        glfwTerminate();
//    }
//    
//    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//    
//    glfwPollEvents();
//    glfwSetCursorPos(window, windowWidth/2, windowHeight/2);
//    
//    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
//    
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LESS);
//    glEnable(GL_CULL_FACE);
//
//}
//
//void playAudio()
//{
//    
//    
//    //
//    // OPENAL
//    //
//    
//    
//    
//    
//    
//    //
//    // SDL_Mixer
//    //
//    
////    Mix_Init(0);
////    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
////
//////    Mix_Chunk *wave;
//////    wave = Mix_LoadWAV_RW(SDL_RWFromFile("sound.wav", "rb"), 1);
//////    Mix_PlayChannel(-1, wave, 0);
//////    Mix_FreeChunk(wave);
////
////    Mix_Music *sound;
////    sound = Mix_LoadMUS("sound.wav");
////    Mix_VolumeMusic(64);
////    Mix_PlayMusic(sound, -1);
////    Mix_Music *sound2;
////    sound2 = Mix_LoadMUS("sound2.wav");
////    Mix_VolumeMusic(64);
////    Mix_PlayMusic(sound2, -1);
//////    Mix_HaltMusic();
//////    Mix_FreeMusic(sound);
//    
//    
//}
