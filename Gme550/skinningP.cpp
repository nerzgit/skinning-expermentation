//
//  skinningP.cpp
//  Gme550
//
//  Created by IDE KENTARO on 2019/03/27.
//  Copyright © 2019 IdeKentaro. All rights reserved.
//

#include "skinningP.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "common/shader.hpp"
#include "common/texture.hpp"
#include "common/objloader.hpp"
#include "common/controls.hpp"
#include "common/vboindexer.hpp"
#include "common/quaternion_utils.hpp"

using namespace glm;


Bone::~Bone()
{
    delete boneCH;
    delete boneSL;
}

void Bone::initBone(const int       &id,
                    const glm::vec3 &T,
                    const glm::vec3 &R,
                    const glm::vec3 &S,
                    const glm::vec3 &tail)
{
    
    // Parameter initialization
    this -> id = id;
    this -> T  = T;
    this -> R  = R;
    this -> S  = S;
    
    glm::mat4 TranslationMatrix = translate(glm::mat4(1.0), T);
    glm::mat4 RotationMatrix    = eulerAngleYXZ(R.y, R.x, R.z);
    glm::mat4 ScalingMatrix     = scale(glm::mat4(1.0), S);
    matINIT = TranslationMatrix * RotationMatrix * ScalingMatrix;
    
    this -> matOFFSET = glm::inverse(matINIT);
    
    
    // Rendering initialization
    glGenVertexArrays(1, &boneVAO);
    glBindVertexArray(boneVAO);
    
    boneProgramID = LoadShaders( "Bone.vertexshader", "Bone.fragmentshader" );
    boneMatrixID  = glGetUniformLocation(boneProgramID, "MVP");
    
    GLfloat bone_vbo_data[6] = {
        0,0,0,tail.x,tail.y,tail.z
    };
    
    GLfloat bone_color_data[6] = {
        0.0f, 0.47843137f, 1.0f,
        0.35294118f, 0.78431373, 0.98039216f,
    };
    
    glGenBuffers(1, &boneVBO);
    glBindBuffer(GL_ARRAY_BUFFER, boneVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bone_vbo_data), bone_vbo_data, GL_STATIC_DRAW);
    
    glGenBuffers(1, &boneCBO);
    glBindBuffer(GL_ARRAY_BUFFER, boneCBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bone_color_data), bone_color_data, GL_STATIC_DRAW);
    
    glEnable(GL_LINE_SMOOTH);
    
}

void Bone::playBone(const glm::vec3 &T,
                    const glm::vec3 &R,
                    const glm::vec3 &S)
{
    
    // Rendering bone
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, 1024*2, 768*2);
    
    glm::mat4 TranslationMatrix = translate(glm::mat4(1.0), T);
    glm::mat4 RotationMatrix    = eulerAngleYXZ(R.y, R.x, R.z);
    glm::mat4 ScalingMatrix     = scale(glm::mat4(1.0), S);
    glm::mat4 MVP = TranslationMatrix * RotationMatrix * ScalingMatrix;
    boneMVP = getProjectionMatrix() * getViewMatrix() * MVP * matBONE;
    
    glUseProgram(boneProgramID);
    glUniformMatrix4fv(boneMatrixID, 1, GL_FALSE, &boneMVP[0][0]);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, boneVBO);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
    
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, boneCBO);
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
    
    glDrawArrays(GL_LINES, 0, 2);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    
}





Skin::Skin(GLFWwindow *window, const char *skinfile, const char *keyframefile)
{
    this -> window = window;
    
    //
    // Bone initialization
    //
    
    std::vector<int>                    op_i;    // arr_id
    std::vector<int>                    op_c;    // arr_child
    std::vector<int>                    op_s;    // arr_sibling
    std::vector<std::vector<float>>     op_w;    // arr_weight
    std::vector<glm::vec3>              op_h;    // arr_head
    std::vector<glm::vec3>              op_t;    // arr_tail
    
    FILE * file = fopen(skinfile, "r");
    while( 1 ){
        
        char      line[128];
        int       i = 0;           // id
        int       c;               // child
        int       s;               // sibling
        float     w;               // weight
        glm::vec3 h;               // head
        glm::vec3 t;               // tail
        
        int res = fscanf(file, "%s", line);
        
        // EOF
        if (res == EOF)
            break;
        
        // ID
        if ( strcmp( line, "i" ) == 0 ){
            fscanf(file, "%i\n", &i);
            op_i.push_back(i);
            op_w.push_back({});
            
            // CHILD
        }else if ( strcmp( line, "c" ) == 0 ){
            fscanf(file, "%i\n", &c);
            op_c.push_back(c);
            
            // SIBLING
        }else if ( strcmp( line, "s" ) == 0 ){
            fscanf(file, "%i\n", &s);
            op_s.push_back(s);
            
            // WEIGHT
        }else if ( strcmp( line, "w" ) == 0 ){
            fscanf(file, "%f\n", &w);
            op_w[op_i.back()].push_back(w);
            
            // HEAD
        }else if ( strcmp( line, "h" ) == 0 ){
            fscanf(file, "%f %f %f\n", &h.x, &h.z, &h.y);
            h.y *= -1;
            op_h.push_back(h);
            
            // TAIL
        }else if ( strcmp( line, "t" ) == 0 ){
            fscanf(file, "%f %f %f\n", &t.x, &t.z, &t.y);
            t.y *= -1;
            op_t.push_back(t);
            
        }
        
    }
    fclose(file);
    
    // Bone -> Add ID,WEIGHT,HEAD,TAIL
    for (int i=0; i<op_i.size(); i++) {
        Bone *bone = new Bone();
        std::cout << glm::to_string(op_h[i]) << std::endl;
        for (int l=0; l<op_w[i].size(); l++) {
            bone -> arrWeight.push_back(op_w[i][l]);
        }
        bone -> initBone(op_i[i], op_h[i], glm::vec3(0), glm::vec3(1), op_t[i] - op_h[i]);
        bones.push_back(bone);
        defbones.push_back(glm::mat4(1.0f));
    }
    
    // Bone -> Add CHILD
    for (int i=0; i<op_c.size(); i++) {
        if (op_c[i] != -1) {
            bones[i]->boneCH = bones[op_c[i]];
        }
    }
    
    // Bone -> Add SIBLING
    for (int i=0; i<op_s.size(); i++) {
        if (op_s[i] != -1) {
            bones[i]->boneSL = bones[op_s[i]];
        }
    }
    
    // Convert initial pose to relative pose on parent space (Run rootbone)
    glm::mat4 iden = glm::mat4(1.0f);
    convertToRelativeMatrix(bones[0], iden);
    
    
    
    
    //
    // KEYFRAME Initialization
    //
    
    std::vector<int>                    kf_i;                  // Bones id

    for (int i=0; i<op_i.size(); i++) { bones_keyframe.push_back({}); }  // Initialization of "kf_m" ONE DIMENSTIONAL ARRAY

    FILE * file2 = fopen(keyframefile, "r");
    while( 1 ){

        char      line[128];
        int       i;           // id
        glm::vec3 m;           // mat4

        int res = fscanf(file2, "%s", line);

        // EOF
        if (res == EOF)
            break;
        
        // FRAME
        if ( strcmp( line, "r" ) == 0 ){
            fscanf(file2, "%i\n", &frame);
        }

        // FPS
        if ( strcmp( line, "f" ) == 0 ){
            fscanf(file2, "%i\n", &fps);
        }

        // ID
        else if ( strcmp( line, "i" ) == 0 ){
            fscanf(file2, "%i\n", &i);
            kf_i.push_back(i);
        }

        // KEYFRAME
        else if ( strcmp( line, "m" ) == 0 ){
            fscanf(file2, "%f %f %f\n", &m.x, &m.y, &m.z);
            bones_keyframe[kf_i.back()].push_back(m);
        }

    }
    fclose(file2);

}

Skin::~Skin()
{
    for (int i=0; i<bones.size(); i++) { delete bones[i]; }
    delete window;
}

void Skin::initWeight(const char                      * object,
                      std::vector<Bone*>              & bones,
                      std::vector<glm::vec3>          & in_vertices,
                      std::vector<std::vector<float>> & out_weights
                      ){
    
    std::vector<glm::vec3>          temp_vertices;
    std::vector<std::vector<float>> temp_weights;
    
    // Get vertices from obj file
    FILE * filevtx = fopen(object, "r");
    while( 1 ){
        char  line[128];
        int res = fscanf(filevtx, "%s", line);
        if (res == EOF)
            break;
        if ( strcmp( line, "v" ) == 0 ){
            glm::vec3 vertex;
            fscanf(filevtx, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            temp_vertices.push_back(vertex);
        }
    }
    fclose(filevtx);
    
    // Sort weights in the order of indexed_vertices.
    for (int z=0; z<bones.size(); z++) {
        temp_weights.push_back({});
        for (int i=0; i<in_vertices.size(); i++) {
            for (int l=0; l<temp_vertices.size(); l++) {
                if (in_vertices[i].x == temp_vertices[l].x &&
                    in_vertices[i].y == temp_vertices[l].y &&
                    in_vertices[i].z == temp_vertices[l].z) {
                    temp_weights[z].push_back(bones[z]->arrWeight[l]);
                }
            }
        }
    }
    
    out_weights = temp_weights;
    
}


void Skin::playSkin()
{
    
    // Timer
    currentTime = glfwGetTime();
    if ( currentTime - lastTime >= 1.0/float(fps) ) {
        lastTime = currentTime;
        per ++;
        if (per > frame) {
            per = 0;
        }
    }
    
    // 4: Calculate the amount of change for each bone
    for (int i=0; i<bones.size(); i++) {
        defbones[i] = eulerAngleYXZ(bones_keyframe[i][per].x,
                                    bones_keyframe[i][per].z,
                                    bones_keyframe[i][per].y);
    }
    
    // 5: Calculate matrix after change of each bone
    for (int i=0; i<bones.size(); i++) {
        bones[i]->matBONE = bones[i]->matINIT * defbones[i];
    }
    
    // 6: Convert from parent space base to local space base
    glm::mat4 iden = glm::mat4(1.0f);
    updateBone(bones[0], iden);
    
}

void Skin::convertToRelativeMatrix(Bone *me, glm::mat4 &matParentOFFSET)
{
    me -> matINIT = matParentOFFSET * me -> matINIT;
    if (me -> boneCH) {
        convertToRelativeMatrix(me->boneCH, me->matOFFSET);
    }
    if (me -> boneSL) {
        convertToRelativeMatrix(me->boneSL, matParentOFFSET);
    }
}

void Skin::updateBone(Bone *me, glm::mat4 &matParentWORLD)
{
    me -> matBONE  = matParentWORLD * me -> matBONE;
    me -> matLOCAL = me -> matBONE  * me -> matOFFSET;
    if (me -> boneCH) {
        updateBone(me -> boneCH, me -> matBONE);
    }
    if (me -> boneSL) {
        updateBone(me -> boneSL, matParentWORLD);
    }
}











//
//
// THE SAMPLE MODEL FOR USAGE SKIN CLS
// DON'T FORGET EDIT GLSL
//
//
//void Model::initOBJ(GLFWwindow *window)
//{
//    
//    this -> window = window;
//
// IMPORTANT =============================================================
//    // Skin initialization
//    skin = new Skin(window, "circle.wgt", "circle.kfm");
// =======================================================================
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
//
// IMPORTANT =============================================================
//    skin -> initWeight(object, skin->bones, indexed_vertices, indexed_weights);
// =======================================================================
//    
//    glGenBuffers(1, &modelVBO[0]);
//    glBindBuffer(GL_ARRAY_BUFFER, modelVBO[0]);
//    glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_DYNAMIC_DRAW);
//    
//    glGenBuffers(1, &modelVBO[1]);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelVBO[1]);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);
//
// IMPORTANT =============================================================
//    for (int i=0; i<skin->bones.size(); i++) {
//        glGenBuffers(1, &weightVBO[i]);
//        glBindBuffer(GL_ARRAY_BUFFER, weightVBO[i]);
//        glBufferData(GL_ARRAY_BUFFER, indexed_weights[i].size() * sizeof(float), &indexed_weights[i][0], GL_STATIC_DRAW);
//    }
// =======================================================================
//    
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
//}
//
//void Model::playOBJ(const glm::vec3 &T,
//                    const glm::vec3 &R,
//                    const glm::vec3 &S)
//{
//    
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//    glViewport(0, 0, 1024*2, 768*2);
//    
//    glm::mat4 TranslationMatrix   = translate(glm::mat4(1.0), T);
//    glm::mat4 RotationMatrix      = eulerAngleYXZ(R.y, R.x, R.z);
//    glm::mat4 ScalingMatrix       = scale(glm::mat4(1.0), S);
//    modelMVP = getProjectionMatrix() * getViewMatrix() * TranslationMatrix * RotationMatrix * ScalingMatrix;
//
// IMPORTANT =============================================================
//    skin -> playSkin();                                  // Play skin
//    for (int i=0; i<skin->bones.size(); i++) {
//        skin->bones[i]->playBone(T, R, S);               // Play skinning with bone
//        boneMatrix[i] = skin->bones[i]->matLOCAL;        // Get skinning bone's matrices
//    }
// =======================================================================
//    
//    glUseProgram(modelProgramID);
//    // MVP行列
//    glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMVP[0][0]);

// IMPORTANT =============================================================
//    // ボーン行列
//    glUniformMatrix4fv(boneMatrixID, 24, GL_FALSE, &boneMatrix[0][0][0]);
// =======================================================================
//    
//    // 頂点
//    glEnableVertexAttribArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, modelVBO[0]);
//    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
//    
//    glEnableVertexAttribArray(1);
//    glBindBuffer(GL_ARRAY_BUFFER, modelVBO[1]);
//    glVertexAttribPointer( 3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
//
// IMPORTANT =============================================================
//    // ウェイト
//    for (int i=0; i<skin->bones.size(); i++) {
//        glEnableVertexAttribArray(i+2);
//        glBindBuffer(GL_ARRAY_BUFFER, weightVBO[i]);
//        glVertexAttribPointer( i+2, 1, GL_FLOAT, GL_FALSE, 0, (void*)0 );
//    }
// =======================================================================
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
