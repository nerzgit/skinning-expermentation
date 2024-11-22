////
////  world.cpp
////  play
////
////  Created by PROPPACK DEVELOPER IDE on 2018/10/20.
////  Copyright © 2018 IdeKentaro. All rights reserved.
////
//
//#include "world.h"
//
//#include <iostream>
//#include <vector>
//#include <fstream>
//#include <cmath>
//
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/quaternion.hpp>
//#include <glm/gtx/quaternion.hpp>
//#include <glm/gtx/euler_angles.hpp>
//#include <glm/gtx/norm.hpp>
//#include <glm/gtx/string_cast.hpp>
//using namespace glm;
//
//#include "common/controls.hpp"
//#include "common/shader.hpp"
//#include "common/texture.hpp"
//#include "common/objloader.hpp"
//#include "common/vboindexer.hpp"
//#include "common/quaternion_utils.hpp"
//
//#include "obj_Plane.h"
//#include "obj_ShadowMapping.h"
//#include "obj_TextureRendering.h"
//
//World::World(GLFWwindow *window)
//{
//    obj_plane          = new OBJ_Plane( window, "uvmap.dds", "room.obj");
////    obj_shadowmapping  = new OBJ_ShadowMapping( window, "uvmap.dds", "suzanne.obj");
////    obj_shadowmapping1 = new OBJ_ShadowMapping( window, "uvmap.dds", "room2.obj" );
//    
//}
//
//World::~World()
//{
//
//    delete obj_plane;
//    delete obj_shadowmapping;
//    delete obj_shadowmapping1;
//    delete obj_texturerendering;
//    
//}
//
//float aaaaa = 0;
//void World::Render(GLFWwindow *window)
//{
//    computeMatricesFromInputs();
//    
//    glm::vec3 position = getPosition();
//    ProjectionMatrix = getProjectionMatrix();
//    ViewMatrix       = getViewMatrix();
//    
//    
//    aaaaa += 0.01f;
//    
//
//    glm::vec3 objsm1 = glm::vec3(2,0,0);
//    glm::vec3 objsm2 = glm::vec3(3,3,-6);
//    
//    objsm1.x = sin(aaaaa);
//    objsm2.x = sin(aaaaa);
//    
////    obj_shadowmapping  -> playOBJ(objsm1);
////    obj_shadowmapping1 -> playOBJ(objsm2);
//    GLuint dep;
////    obj_shadowmapping  -> getDepthTexture(dep);
//    obj_plane          -> playOBJ(objsm1, dep);
//    
//}
