//#include "obj_TextureRendering.h"
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <vector>
//#include <iostream>
//
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/quaternion.hpp>
//#include <glm/gtx/quaternion.hpp>
//#include <glm/gtx/euler_angles.hpp>
//#include <glm/gtx/norm.hpp>
//using namespace glm;
//
//#include "common/shader.hpp"
//#include "common/texture.hpp"
//#include "common/objloader.hpp"
//#include "common/vboindexer.hpp"
//#include "common/quaternion_utils.hpp"
//
//OBJ_TextureRendering::OBJ_TextureRendering(GLFWwindow *window, const char *texture, const char *object)
//{
//    initOBJ(window, texture, object);
//}
//
//OBJ_TextureRendering::~OBJ_TextureRendering()
//{
//    deinitOBJ();
//}
//
//void OBJ_TextureRendering::initOBJ(GLFWwindow *window, const char *texture, const char *object)
//{
//    
//    
//    glfwGetWindowSize(window, &screenwidth, &screenheight);
//    screenwidth *= 2;
//    screenheight *= 2;
//    
//    
//    
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//    
//    // Create and compile our GLSL program from the shaders
//    programID = LoadShaders( "StandardShadingRTT.vertexshader", "StandardShadingRTT.fragmentshader" );
//    
//    // Get a handle for our "MVP" uniform
//    MatrixID = glGetUniformLocation(programID, "MVP");
//    ViewMatrixID = glGetUniformLocation(programID, "V");
//    ModelMatrixID = glGetUniformLocation(programID, "M");
//    
//    // Load the texture
//    Texture = loadDDS("uvmap.DDS");
//    
//    // Get a handle for our "myTextureSampler" uniform
//    TextureID  = glGetUniformLocation(programID, "myTextureSampler");
//    
//    // Read our .obj file
//    loadOBJ("room.obj", vertices, uvs, normals);
//    
//    indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);
//    
//    // Load it into a VBO
//    
//    glGenBuffers(1, &vbo[0]);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
//    glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);
//    
//    glGenBuffers(1, &vbo[1]);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
//    glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);
//    
//    glGenBuffers(1, &vbo[2]);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
//    glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);
//    
//    glGenBuffers(1, &vbo[3]);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);
//    
//    // Get a handle for our "LightPosition" uniform
//    glUseProgram(programID);
//    LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
//    
//    
//    // ---------------------------------------------
//    // Render to Texture - specific code begins here
//    // ---------------------------------------------
//    
//    // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
//    FramebufferName = 0;
//    glGenFramebuffers(1, &FramebufferName);
//    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
//    
//    // The texture we're going to render to
//    glGenTextures(1, &renderedTexture);
//    
//    // "Bind" the newly created texture : all future texture functions will modify this texture
//    glBindTexture(GL_TEXTURE_2D, renderedTexture);
//    
//    // Give an empty image to OpenGL ( the last "0" means "empty" )
//    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, screenwidth, screenheight, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);
//    
//    // Poor filtering
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    
//    // The depth buffer
//    glGenRenderbuffers(1, &depthrenderbuffer);
//    glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
//    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, screenwidth, screenheight);
//    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);
//    
//    //// Alternative : Depth texture. Slower, but you can sample it later in your shader
//    //depthTexture;
//    glGenTextures(1, &depthTexture);
//    glBindTexture(GL_TEXTURE_2D, depthTexture);
//    glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT24, 1024, 768, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    
//    // Set "renderedTexture" as our colour attachement #0
////    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);
//    
//    //// Depth texture alternative :
//    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);
//    
//    
//    // Set the list of draw buffers.
//    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
//    glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
//    
//    // Always check that our framebuffer is ok
//    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//        printf(">> The bad Frame buffer status. X_X");
//    
//    
//    // The fullscreen quad's FBO
//    static const GLfloat g_quad_vertex_buffer_data[] = {
//        -1.0f, -1.0f, 0.0f,
//        1.0f, -1.0f, 0.0f,
//        -1.0f,  1.0f, 0.0f,
//        -1.0f,  1.0f, 0.0f,
//        1.0f, -1.0f, 0.0f,
//        1.0f,  1.0f, 0.0f,
//    };
//    
//    glGenBuffers(1, &quad_vertexbuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);
//    
//    // Create and compile our GLSL program from the shaders
//    quad_programID = LoadShaders( "Passthrough.vertexshader", "WobblyTexture.fragmentshader" );
//    texID = glGetUniformLocation(quad_programID, "renderedTexture");
//    timeID = glGetUniformLocation(quad_programID, "time");
//    
//}
//
//void OBJ_TextureRendering::playOBJ(glm::mat4 &ViewMatrix, glm::mat4 &ProjectionMatrix, glm::vec3 &pos)
//{
//    // Render to our framebuffer
//    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
//    glViewport(0,0,screenwidth,screenheight); // Render on the whole framebuffer, complete from the lower left corner to the upper right
//    
//    // Clear the screen
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    
//    // Use our shader
//    glUseProgram(programID);
//    
//    // Compute the MVP matrix from keyboard and mouse input
//    glm::mat4 ModelMatrix = translate(glm::mat4(1.0), pos);
//    glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
//    
//    // Send our transformation to the currently bound shader,
//    // in the "MVP" uniform
//    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
//    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
//    glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
//    
//    glm::vec3 lightPos = glm::vec3(4,4,4);
//    glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
//    
//    // Bind our texture in Texture Unit 0
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, Texture);
//    // Set our "myTextureSampler" sampler to use Texture Unit 0
//    glUniform1i(TextureID, 0);
//    
//    // 1rst attribute buffer : vertices
//    glEnableVertexAttribArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
//    glVertexAttribPointer(
//                          0,                  // attribute
//                          3,                  // size
//                          GL_FLOAT,           // type
//                          GL_FALSE,           // normalized?
//                          0,                  // stride
//                          (void*)0            // array buffer offset
//                          );
//    
//    // 2nd attribute buffer : UVs
//    glEnableVertexAttribArray(1);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
//    glVertexAttribPointer(
//                          1,                                // attribute
//                          2,                                // size
//                          GL_FLOAT,                         // type
//                          GL_FALSE,                         // normalized?
//                          0,                                // stride
//                          (void*)0                          // array buffer offset
//                          );
//    
//    // 3rd attribute buffer : normals
//    glEnableVertexAttribArray(2);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
//    glVertexAttribPointer(
//                          2,                                // attribute
//                          3,                                // size
//                          GL_FLOAT,                         // type
//                          GL_FALSE,                         // normalized?
//                          0,                                // stride
//                          (void*)0                          // array buffer offset
//                          );
//    
//    // Index buffer
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
//    
//    // Draw the triangles !
//    glDrawElements(
//                   GL_TRIANGLES,      // mode
//                   (int)indices.size(),    // count
//                   GL_UNSIGNED_SHORT, // type
//                   (void*)0           // element array buffer offset
//                   );
//    
//    glDisableVertexAttribArray(0);
//    glDisableVertexAttribArray(1);
//    glDisableVertexAttribArray(2);
//    
//    
//    
//    // Render to the screen
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//    // Render on the whole framebuffer, complete from the lower left corner to the upper right
//    glViewport(0,0,screenwidth,screenheight);
//    
//    // Clear the screen
//    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    
//    // Use our shader
//    glUseProgram(quad_programID);
//    
//    // Bind our texture in Texture Unit 0
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, renderedTexture);
//    // Set our "renderedTexture" sampler to use Texture Unit 0
//    glUniform1i(texID, 0);
//    
//    glUniform1f(timeID, (float)(glfwGetTime()*10.0f) );
//    
//    // 1rst attribute buffer : vertices
//    glEnableVertexAttribArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
//    glVertexAttribPointer(
//                          0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
//                          3,                  // size
//                          GL_FLOAT,           // type
//                          GL_FALSE,           // normalized?
//                          0,                  // stride
//                          (void*)0            // array buffer offset
//                          );
//    
//    // Draw the triangles !
//    glDrawArrays(GL_TRIANGLES, 0, 6); // 2*3 indices starting at 0 -> 2 triangles
//    
//    glDisableVertexAttribArray(0);
//
//}
//
//void OBJ_TextureRendering::deinitOBJ()
//{
//    // Cleanup VBO and shader
//    glDeleteBuffers(4, vbo);
//    glDeleteProgram(programID);
//    glDeleteTextures(1, &Texture);
//    
//    glDeleteFramebuffers(1, &FramebufferName);
//    glDeleteTextures(1, &renderedTexture);
//    glDeleteRenderbuffers(1, &depthrenderbuffer);
//    glDeleteBuffers(1, &quad_vertexbuffer);
//    glDeleteVertexArrays(1, &vao);
//}
//
