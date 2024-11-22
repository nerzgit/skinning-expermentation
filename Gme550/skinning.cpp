////
////  skinning.cpp
////  Gme550
////
////  Created by PROPPACK DEVELOPER IDE on 2019/03/15.
////  Copyright © 2019 IdeKentaro. All rights reserved.
////
//
//#include "skinning.hpp"
//
//#include <iostream>
//#include <vector>
//#include <fstream>
//#include <cmath>
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
//#include <glm/gtx/string_cast.hpp>
//
//#include "common/shader.hpp"
//#include "common/texture.hpp"
//#include "common/objloader.hpp"
//#include "common/controls.hpp"
//#include "common/vboindexer.hpp"
//#include "common/quaternion_utils.hpp"
//
//using namespace glm;
//
//std::vector<Bone*> boneSet;
//
//void Bone::initBone()
//{
//    glGenVertexArrays(1, &boneVAO);
//    glBindVertexArray(boneVAO);
//    boneProgramID = LoadShaders( "Bone.vertexshader", "Bone.fragmentshader" );
//    boneMatrixID  = glGetUniformLocation(boneProgramID, "MVP");
//    static const GLfloat g_vertex_buffer_data[] = {
//         0.0f,  0.0f,  0.0f,
//         0.0f, -5.0f,  0.0f,
//    };
//    
//    static const GLfloat g_color_buffer_data[] = {
//        0.583f,  0.771f,  0.014f,
//        0.583f,  0.771f,  0.014f,
//    };
//    
//    glGenBuffers(1, &boneVBO);
//    glBindBuffer(GL_ARRAY_BUFFER, boneVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
//    
//    glGenBuffers(1, &boneCBO);
//    glBindBuffer(GL_ARRAY_BUFFER, boneCBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
//    
//    glEnable(GL_CULL_FACE);
//    glEnable(GL_LINE_SMOOTH);
//    glCullFace(GL_BACK);
//}
//
//void Bone::playBone(glm::vec3 &pos, glm::vec3 &rot, glm::vec3 &scl)
//{
//    
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//    glViewport(0, 0, 1024*2, 768*2);
//    
//    glm::mat4 RotationMatrix      = eulerAngleYXZ(rot.y, rot.x, rot.z);
//    glm::mat4 TranslationMatrix   = translate(glm::mat4(1.0), pos);
//    glm::mat4 ScalingMatrix       = scale(glm::mat4(1.0), scl);
//    localMat         = TranslationMatrix * RotationMatrix * ScalingMatrix;
//    if (id > 0) {
//        globalMat = boneSet[parent]->globalMat * localMat;
//    }else{
//        globalMat = localMat;
//    }
//    boneMVP = getProjectionMatrix() * getViewMatrix() * globalMat;
//    
//    glUseProgram(boneProgramID);
//    glUniformMatrix4fv(boneMatrixID, 1, GL_FALSE, &boneMVP[0][0]);
//    
//    glEnableVertexAttribArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, boneVBO);
//    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
//
//    glEnableVertexAttribArray(1);
//    glBindBuffer(GL_ARRAY_BUFFER, boneCBO);
//    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
//
//    glDrawElements(GL_LINES, 2, GL_UNSIGNED_SHORT, (void*)0);
//    
//    glDisableVertexAttribArray(0);
//    glDisableVertexAttribArray(1);
//}
//
//
//Skinning::Skinning(GLFWwindow *window)
//{
//    this -> window = window;
//    
//    // Setup all bone Cls from weight file
//    FILE * file = fopen("circle.wgt", "r");
//    char  line[128];
//    int   n = 0; // id
//    int   p;     // parent
//    float w;     // weight
//    while( 1 ){
//
//        int res = fscanf(file, "%s", line);
//        if (res == EOF)
//            break;
//
//        if ( strcmp( line, "i" ) == 0 ){
//            fscanf(file, "%i\n", &n);
//            Bone *bone = new Bone();
//            bone -> id = n;
//            boneSet.push_back(bone);
//        }else if ( strcmp( line, "p" ) == 0 ){
//            fscanf(file, "%i\n", &p);
//            boneSet[n] -> parent = p;
//        }else if ( strcmp( line, "w" ) == 0 ){
//            fscanf(file, "%f\n", &w);
//            boneSet[n] -> weightArr.push_back(w);
//        }
//
//    }
//    
//    
//    for (int i=0; i<boneSet.size(); i++) {
//        if (i==0) {
//            boneSet[i]->s = glm::vec3(1.0f, 1.0f, 1.0f);
//            boneSet[i]->t = glm::vec3(0.0f, 0.0f, 0.0f);
//            boneSet[i]->r = glm::vec3(0.0f, 0.0f, 0.0f);
//        }else if(i==1){
//            boneSet[i]->s = glm::vec3(1.0f, 1.0f, 1.0f);
//            boneSet[i]->t = glm::vec3(0.0f,-5.0f, 0.0f);
//            boneSet[i]->r = glm::vec3(0.0f, 0.0f, 0.0f);
//        }
//        boneSet[i]->initBone();
//    }
//
//}
//
//Skinning::~Skinning()
//{
//    for (int i=0; i<boneSet.size(); i++) {
//        delete boneSet[i];
//    }
//}
//
//void Skinning::initWeight(
//                          const char                      * object,
//                          std::vector<Bone*>              & boneSet,
//                          std::vector<glm::vec3>          & in_vertices,
//                          std::vector<std::vector<float>> & out_weights
//){
//    
//    std::vector<glm::vec3>          temp_vertices;
//    std::vector<std::vector<float>> temp_weights;
//    
//    // Get vertices from obj file
//    FILE * filevtx = fopen(object, "r");
//    while( 1 ){
//        char  line[128];
//        int res = fscanf(filevtx, "%s", line);
//        if (res == EOF)
//            break;
//        if ( strcmp( line, "v" ) == 0 ){
//            glm::vec3 vertex;
//            fscanf(filevtx, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
//            temp_vertices.push_back(vertex);
//        }
//    }
//    fclose(filevtx);
//    
//    // Sort weights in the order of indexed_vertices.
//    for (int z=0; z<boneSet.size(); z++) {
//        temp_weights.push_back({});
//        for (int i=0; i<in_vertices.size(); i++) {
//            for (int l=0; l<temp_vertices.size(); l++) {
//                if (in_vertices[i].x == temp_vertices[l].x &&
//                    in_vertices[i].y == temp_vertices[l].y &&
//                    in_vertices[i].z == temp_vertices[l].z) {
//                    temp_weights[z].push_back(boneSet[z]->weightArr[l]);
//                }
//            }
//        }
//    }
//    
//    out_weights = temp_weights;
//    
//}
//
//void Skinning::skeltering(Bone *rootBone)
//{
//    computeMatricesFromInputs();
//    for (int i=rootBone->id; i<boneSet.size(); i++) {
//        boneSet[i] -> playBone(boneSet[i] -> t, boneSet[i] -> r, boneSet[i] -> s);
//    }
//    
//}
//
//void Skinning::key()
//{
//    
//    if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
//        boneSet[0] -> r.x += 0.01;
//    }
//    
//    if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
//        boneSet[0] -> r.x -= 0.01;
//    }
//    
//    if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
//        boneSet[1] -> r.x -= 0.01;
//    }
//    
//    if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
//        boneSet[1] -> r.x += 0.01;
//    }
//    
//}
//
//
//
//Model::Model(GLFWwindow *window)
//{
//    this -> window = window;
//    skinning = new Skinning(window);
//    initOBJ();
//}
//
//Model::~Model()
//{
//    
//}
//
//void Model::initOBJ()
//{
//
//    for (int i=0; i<24; i++) { boneMatrix[i] = glm::mat4(1.0f); }
//    
//    glGenVertexArrays(1, &modelVAO);
//    glBindVertexArray(modelVAO);
//    modelProgramID = LoadShaders( "Model.vertexshader", "Model.fragmentshader" );
//    modelMatrixID = glGetUniformLocation(modelProgramID, "MVP");
//    boneMatrixID = glGetUniformLocation(modelProgramID, "BoneMatrix");
//    
//    const char *object = "circle.obj";
//    loadOBJ(object, vertices, uvs, normals);
//    indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);
//    skinning -> initWeight(object, boneSet, indexed_vertices, indexed_weights);
//    
////    for (int i=0; i<indexed_vertices.size(); i++) { indexed_vertices[i].y += 5.0f; } // To correct the problem of skinning slip
//    
//    glGenBuffers(1, &modelVBO[0]);
//    glBindBuffer(GL_ARRAY_BUFFER, modelVBO[0]);
//    glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_DYNAMIC_DRAW);
//    
//    glGenBuffers(1, &modelVBO[1]);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelVBO[1]);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);
//    
//    for (int i=0; i<boneSet.size(); i++) {
//        glGenBuffers(1, &weightVBO[i]);
//        glBindBuffer(GL_ARRAY_BUFFER, weightVBO[i]);
//        glBufferData(GL_ARRAY_BUFFER, indexed_weights[i].size() * sizeof(float), &indexed_weights[i][0], GL_STATIC_DRAW);
//    }
//    
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
//}
//
//void Model::playOBJ(glm::vec3 &pos, glm::vec3 &rot, glm::vec3 &scl)
//{
//    
//    skinning -> key();
//    skinning -> skeltering(boneSet[0]);
//
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//    glViewport(0, 0, 1024*2, 768*2);
//
//    glm::mat4 RotationMatrix      = eulerAngleYXZ(rot.y, rot.x, rot.z);
//    glm::mat4 TranslationMatrix   = translate(glm::mat4(1.0), pos);
//    glm::mat4 ScalingMatrix       = scale(glm::mat4(1.0), scl);
//    modelMVP = getProjectionMatrix() * getViewMatrix() * TranslationMatrix * RotationMatrix * ScalingMatrix;
//
//    for (int i=0; i<boneSet.size(); i++) { boneMatrix[i] = boneSet[i]->globalMat; }
//
//    glUseProgram(modelProgramID);
//    // MVP行列
//    glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMVP[0][0]);
//    // ボーン行列
//    glUniformMatrix4fv(boneMatrixID, 24, GL_FALSE, &boneMatrix[0][0][0]);
//
//    // 頂点
//    glEnableVertexAttribArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, modelVBO[0]);
//    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
//
//    glEnableVertexAttribArray(3);
//    glBindBuffer(GL_ARRAY_BUFFER, modelVBO[1]);
//    glVertexAttribPointer( 3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
//
//    // ウェイト
//    for (int i=0; i<boneSet.size(); i++) {
//        glEnableVertexAttribArray(i+1);
//        glBindBuffer(GL_ARRAY_BUFFER, weightVBO[i]);
//        glVertexAttribPointer( i+1, 1, GL_FLOAT, GL_FALSE, 0, (void*)0 );
//    }
//
//    glDrawElements(
//                   GL_LINES,
//                   (int)indices.size(),
//                   GL_UNSIGNED_SHORT,
//                   (void*)0
//                   );
//
//    glDisableVertexAttribArray(0);
//    glDisableVertexAttribArray(1);
//    glDisableVertexAttribArray(2);
//    glDisableVertexAttribArray(3);
//}
