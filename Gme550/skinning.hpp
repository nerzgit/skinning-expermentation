////
////  skinning.hpp
////  Gme550
////
////  Created by PROPPACK DEVELOPER IDE on 2019/03/15.
////  Copyright © 2019 IdeKentaro. All rights reserved.
////
//
//#ifndef skinning_hpp
//#define skinning_hpp
//
//#include <vector>
//
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//
//
//// BONE
//class Bone
//{
//private:
//    GLuint     boneVAO;
//    GLuint     boneProgramID;
//    GLuint     boneMatrixID;
//    glm::mat4  boneMVP;
//    GLuint     boneVBO;
//    GLuint     boneCBO;
//    
//public:
//    int        id;
//    int        parent;
//    glm::mat4  localMat;
//    glm::mat4  globalMat;
//    glm::vec3  t,r,s;
//    std::vector<float> weightArr;
//    
//public:
//    void initBone();
//    void playBone(glm::vec3 &pos, glm::vec3 &rot, glm::vec3 &scl);
//};
//
//
//
//class Skinning
//{
//private:
//    GLFWwindow *window;
//    
//public:
//    Bone *upperArm;
//    Bone *lowerArm;
//    
//    Skinning(GLFWwindow *window);
//    ~Skinning();
//    void initWeight(
//                    const char                      * object,
//                    std::vector<Bone*>              & boneSet,
//                    std::vector<glm::vec3>          & in_vertices,
//                    std::vector<std::vector<float>> & out_weights);
//    void skeltering(Bone *rootBone);
//    void key();
//};
//
//
//
//class Model
//{
//    
//private:
//    GLFWwindow *window;
//    
//    Skinning   *skinning;
//    
//    GLuint     modelVAO;
//    GLuint     modelProgramID;
//    GLuint     modelMatrixID;
//    glm::mat4  boneMatrix[24];
//    GLuint     boneMatrixID;
//    glm::mat4  modelMVP;
//    GLuint     modelVBO[2];
//    GLuint     weightVBO[2];
//    GLuint     modelCBO;
//    
//    std::vector<glm::vec3> vertices;
//    std::vector<glm::vec2> uvs;
//    std::vector<glm::vec3> normals;
//    
//    std::vector<unsigned short> indices;
//    std::vector<glm::vec3> indexed_vertices;
//    std::vector<glm::vec2> indexed_uvs;
//    std::vector<glm::vec3> indexed_normals;
//    
//    std::vector<std::vector<float>> indexed_weights;
//    
//public:
//    Model(GLFWwindow *window);
//    ~Model();
//    void initOBJ();
//    void playOBJ(glm::vec3 &pos, glm::vec3 &rot, glm::vec3 &scl);
//    
//};
//
//
//#endif /* skinning_hpp */
