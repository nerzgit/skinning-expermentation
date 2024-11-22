////
////  obj_Plane.cpp
////  play
////
////  Created by PROPPACK DEVELOPER IDE on 2018/12/06.
////  Copyright © 2018 IdeKentaro. All rights reserved.
////
//
//#include "obj_Plane.h"
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <vector>
//#include <iostream>
//
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <SDL/SDL_mixer.h>
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
//#include "common/controls.hpp"
//#include "common/vboindexer.hpp"
//#include "common/quaternion_utils.hpp"
//
//// 最低限の頂点情報
////  座標と各ボーンの重みそしてボーン行列番号があればスキンメッシュはできます！
//struct Vertex {
//    glm::vec3 coord;
//    glm::vec3 weight;
//    unsigned char matrixIndex[4];
//};
//
//OBJ_Plane::OBJ_Plane(GLFWwindow *window, const char *texture, const char *object)
//{
//    initOBJ(window, texture, object);
//}
//
//OBJ_Plane::~OBJ_Plane()
//{
//    deinitOBJ();
//}
//
//void OBJ_Plane::initOBJ(
//                        GLFWwindow *window,
//                        const char *texture,
//                        const char *object
//                        )
//{
//    // 回転用 (Eng: For Rotate)
//    onEuler = true;
//    onQuaternion = false;
//    gPosition1 = glm::vec3(0.0f, -3.0f, 0.0f);
//    gPosition2 = glm::vec3(0.0f, 0.0f, 0.0f);
//    gLookAtOther = true;
//    
//    // 拡大用
//    gScaling = glm::vec3(1.0f, 1.0f, 1.0f);
//    
//    // スクリーンサイズを取得
//    glfwGetWindowSize(window, &screenWidth, &screenHeight);
//    screenWidth *= 2;
//    screenHeight *= 2;
//    
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//    
//    // シェーダーをGLSLにコンパイル
//    programID = LoadShaders( "ShadowMapping.vertexshader", "ShadowMapping.fragmentshader" );
//    
//    MatrixID      = glGetUniformLocation(programID, "MVP");
//    ViewMatrixID  = glGetUniformLocation(programID, "V");
//    ModelMatrixID = glGetUniformLocation(programID, "M");
//    DepthBiasID   = glGetUniformLocation(programID, "DepthBiasMVP");
//    ShadowMapID   = glGetUniformLocation(programID, "shadowMap");
//    lightInvDirID = glGetUniformLocation(programID, "LightInvDirection_worldspace");
//    
//    // テクスチャのロード
//    Texture = loadDDS(texture);
//    TextureID = glGetUniformLocation(programID, "myTextureSampler");
//    
//    // objファイルロードtと重複頂点を省略
//    loadOBJ(object, vertices, uvs, normals);
//    indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);
//    
//    glGenBuffers(1, &vbos[0]);
//    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
//    glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);
//    glGenBuffers(1, &vbos[1]);
//    glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
//    glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);
//    glGenBuffers(1, &vbos[2]);
//    glBindBuffer(GL_ARRAY_BUFFER, vbos[2]);
//    glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);
//    glGenBuffers(1, &vbos[3]);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[3]);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);
//    
//    glUseProgram(programID);
//    LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
//    
//    // ブレンドを有効にすることで透明度を調整可能にする
//    // ###シャドウを使っていた場合おかしくなる
////    glEnable(GL_BLEND);
////    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    
//}
//
//void OBJ_Plane::playOBJ(glm::vec3 &pos, GLuint &dep)
//{
//    // レンダリング
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//    glViewport(0, 0, screenWidth, screenHeight);
//    
//    
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
//    
//    glUseProgram(programID);
//
//    
//    computeMatricesFromInputs();
//    glm::mat4 ProjectionMatrix = getProjectionMatrix();
//    glm::mat4 ViewMatrix = getViewMatrix();
//    glm::mat4 ModelMatrix = glm::mat4(1.0);
//    
//    // オイラー角
//    if (onEuler) {
//        gOrientation1 = glm::vec3(0.0f, 0.0f, 0.0f);
//        glm::mat4 RotationMatrix = eulerAngleYXZ(gOrientation1.y, gOrientation1.x, gOrientation1.z);
//        glm::mat4 TranslationMatrix = translate(mat4(1.0), gPosition1);
//        glm::mat4 ScalingMatrix = scale(mat4(1.0), gScaling);
//        ModelMatrix = RotationMatrix * TranslationMatrix * ScalingMatrix;
//    // クォーターニオン
//    }else if (onQuaternion) {
//        if (gLookAtOther) {
//            glm::vec3 desierdDir = gPosition1 - gPosition2;
//            glm::vec3 desierdUp = vec3(0.0f, 5.0f, 0.0f);
//            quat targetOrientation = normalize(LookAt(desierdDir, desierdUp));
//            gOrientation2 = quat(0, 0.0f, 0.0f, 0.0f);
//            gOrientation2 = RotateTowards(gOrientation2, targetOrientation, 1.0f);
//        }
//        glm::mat4 RotationMatrix = mat4_cast(gOrientation2);
//        glm::mat4 TranslationMatrix = translate(mat4(1.0), gPosition2);
//        glm::mat4 ScalingMatrix = scale(mat4(1.0), gScaling);
//        ModelMatrix = RotationMatrix * TranslationMatrix * ScalingMatrix;
//    }else {}
//    
//    glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
//    
//    
//    
//    
//    glm::vec3 lightInvDir = glm::vec3(pos.x,2,2);
//    // 正射影行列(ortho)でライトを照らす。
//    glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
//    // ライトのView行列。
//    // ※(通常はModel行列でカメラの位置を決めるように思えるが、ワールド空間から見た位置の方が太陽光には適している。)
//    glm::mat4 depthViewMatrix = glm::lookAt(
//                                            lightInvDir,      // 位置
//                                            glm::vec3(0,0,0), // どこに照射するか
//                                            glm::vec3(0,1,0)  // (0,-1,0)だと世界が逆になる
//                                            );
//    glm::mat4 depthModelMatrix = glm::mat4(1.0);
//    glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;
//    
//    glm::mat4 biasMatrix{
//        0.5, 0.0, 0.0, 0.0,
//        0.0, 0.5, 0.0, 0.0,
//        0.0, 0.0, 0.5, 0.0,
//        0.5, 0.5, 0.5, 1.0
//    };
//    
//    glm::mat4 depthBiasMVP = biasMatrix * depthMVP;
//    
//    // シェーダー内の各uniformに送信
//    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
//    glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
//    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
//    glUniformMatrix4fv(DepthBiasID, 1, GL_FALSE, &depthBiasMVP[0][0]);
//    glUniform3f(lightInvDirID, lightInvDir.x, lightInvDir.y, lightInvDir.z);
//    
//    glm::vec3 lightPos = glm::vec3(4,8,8);
//    glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
//    
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, Texture);
//    glUniform1i(TextureID, 0);
//    
//    
//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture(GL_TEXTURE_2D, dep);
//    glUniform1i(ShadowMapID, 1);
//    
//    // 頂点
//    glEnableVertexAttribArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
//    glVertexAttribPointer(
//                          0,
//                          3,
//                          GL_FLOAT,
//                          GL_FALSE,
//                          0,
//                          (void*)0
//                          );
//    
//    // UV
//    glEnableVertexAttribArray(1);
//    glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
//    glVertexAttribPointer(
//                          1,
//                          2,
//                          GL_FLOAT,
//                          GL_FALSE,
//                          0,
//                          (void*)0
//                          );
//    
//    // 法線
//    glEnableVertexAttribArray(2);
//    glBindBuffer(GL_ARRAY_BUFFER, vbos[2]);
//    glVertexAttribPointer(
//                          2,
//                          3,
//                          GL_FLOAT,
//                          GL_FALSE,
//                          0,
//                          (void*)0
//                          );
//    
//    // VBO
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[3]);
//    
//    glDrawElements(
//                   GL_TRIANGLES,
//                   (int)indices.size(),
//                   GL_UNSIGNED_SHORT,
//                   (void*)0
//                   );
//    
//    glDisableVertexAttribArray(0);
//    glDisableVertexAttribArray(1);
//    glDisableVertexAttribArray(2);
//    
//}
//
//void OBJ_Plane::deinitOBJ()
//{
//    glDeleteBuffers(1, &vbos[0]);
//    glDeleteBuffers(1, &vbos[1]);
//    glDeleteBuffers(1, &vbos[2]);
//    glDeleteBuffers(1, &vbos[3]);
//    glDeleteProgram(programID);
//    glDeleteTextures(1, &Texture);
//    glDeleteVertexArrays(1, &vao);
//}
