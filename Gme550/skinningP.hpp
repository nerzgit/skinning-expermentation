//
//  skinningP.hpp
//  Gme550
//
//  Created by IDE KENTARO on 2019/03/27.
//  Copyright © 2019 IdeKentaro. All rights reserved.
//

#ifndef skinningP_hpp
#define skinningP_hpp

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Bone
{
private:
    GLuint     boneVAO;
    GLuint     boneProgramID;
    GLuint     boneMatrixID;
    glm::mat4  boneMVP;
    GLuint     boneVBO;
    GLuint     boneCBO;
    
public:
    int                id;
    Bone               *boneCH = 0;
    Bone               *boneSL = 0;
    glm::vec3          T,R,S;
    glm::mat4          matOFFSET;
    glm::mat4          matINIT;
    glm::mat4          matBONE;
    glm::mat4          matLOCAL;
    std::vector<float> arrWeight;
    
    ~Bone();
    void initBone(const int &id, const glm::vec3 &T, const glm::vec3 &R, const glm::vec3 &S, const glm::vec3 &tail);
    void playBone(const glm::vec3 &T, const glm::vec3 &R, const glm::vec3 &S);
};

class Skin
{
private:
    GLFWwindow *window;
    int   fps;
    int   frame;
    std::vector<std::vector<glm::vec3>> bones_keyframe; // Keyframes rotate vec3 per frame
    std::vector<glm::mat4> defbones;                    // defuse bone
    
    float  currentTime;
    float  lastTime;
    int    per;
    
public:
    std::vector<Bone*> bones;
    Skin(GLFWwindow *window, const char *skinfile, const char *keyframefile);
    ~Skin();
    void convertToRelativeMatrix(Bone *me, glm::mat4 &matParentOFFSET);
    void updateBone(Bone *me, glm::mat4 &matParentWORLD);
    void playSkin();
    void initWeight(const char                      * object,
                    std::vector<Bone*>              & bones,
                    std::vector<glm::vec3>          & in_vertices,
                    std::vector<std::vector<float>> & out_weights);
};











//
//
// THE SAMPLE MODEL FOR USAGE SKIN CLS
// DON'T FORGET EDIT GLSL
//
//
//class Model
//{
//private:
//    GLFWwindow *window;
//
//    Skin       *skin;
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
//public:
//    void initOBJ(GLFWwindow *window);
//    void playOBJ(const glm::vec3 &T, const glm::vec3 &R, const glm::vec3 &S);
//};

#endif /* skinningP_hpp */
