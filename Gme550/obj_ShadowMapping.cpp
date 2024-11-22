////
////  obj_ShadowMapping.cpp
////  play
////
////  Created by PROPPACK DEVELOPER IDE on 2018/10/22.
////  Copyright © 2018年 IdeKentaro. All rights reserved.
////
//
//#include "obj_ShadowMapping.h"
//
//#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
//#include <vector>
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
//#include "common/controls.hpp"
//#include "common/objloader.hpp"
//#include "common/vboindexer.hpp"
//#include "common/quaternion_utils.hpp"
//
//OBJ_ShadowMapping::OBJ_ShadowMapping(GLFWwindow *window, const char *texture, const char *object)
//{
//    initOBJ(window, texture, object);
//}
//
//OBJ_ShadowMapping::~OBJ_ShadowMapping()
//{
//    deinitOBJ();
//}
//
//void OBJ_ShadowMapping::initOBJ(
//                                GLFWwindow *window,
//                                const char *texture,
//                                const char *object
//                                )
//{
//    // 回転用 (Eng: For Rotate)
//    onEuler = true;
//    onQuaternion = false;
//    gPosition1 = glm::vec3(0.0f, 0.0f, 0.0f);
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
//    // GLSLプログラムをシェーダーより作成しコンパイルする
//    depthProgramID = LoadShaders("DepthRTT.vertexshader", "DepthRTT.fragmentshader");
//    
//    // "MVP"uniform変数ハンドルを取得
//    depthMatrixID = glGetUniformLocation(depthProgramID, "depthMVP");
//    
//    // テクスチャのロード
//    Texture = loadDDS(texture);
//    
//    loadOBJ(object, vertices, uvs, normals);
//
//    indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);
//    
//    glGenBuffers(1, &vbos[0]);
//    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
//    glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size()*sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);
//    glGenBuffers(1, &vbos[1]);
//    glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
//    glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size()*sizeof(glm::vec3), &indexed_uvs[0], GL_STATIC_DRAW);
//    glGenBuffers(1, &vbos[2]);
//    glBindBuffer(GL_ARRAY_BUFFER, vbos[2]);
//    glBufferData(GL_ARRAY_BUFFER, indexed_normals.size()*sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);
//    glGenBuffers(1, &vbos[3]);
//    glBindBuffer(GL_ARRAY_BUFFER, vbos[3]);
//    glBufferData(GL_ARRAY_BUFFER, indices.size()*sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);
//    
//    
//    
//    FramebufferName = 0;
//    glGenFramebuffers(1, &FramebufferName);
//    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
//    
//    // 影用
//    glGenTextures(1, &depthTexture);
//    glBindTexture(GL_TEXTURE_2D, depthTexture);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, screenWidth, screenWidth, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
//    
//    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);
//    
//    // カラーを出力せずに深度値にのみ適用させる。
//    glDrawBuffer(GL_NONE);
//    
//    // フレームバッファが適切かどうか常に判断する。
//    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//        printf(">> The bad Frame buffer status. X_X");
//    
//    // シャドウマップ視覚化。(6vtx -> 4vtx after FBO)
//    static const GLfloat g_quad_vertex_buffer_data[] = {
//        -1.0f, -1.0f, 0.0f,
//         1.0f, -1.0f, 0.0f,
//        -1.0f,  1.0f, 0.0f,
//        -1.0f,  1.0f, 0.0f,
//         1.0f, -1.0f, 0.0f,
//         1.0f,  1.0f, 0.0f,
//    };
//    
//    glGenBuffers(1, &quad_vertexbuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);
//    
//    quad_programID = LoadShaders("Passthrough.vertexshader", "SimpleTexture.fragmentshader");
//    texID = glGetUniformLocation(quad_programID, "texture");
//    
//    programID = LoadShaders("ShadowMapping.vertexshader", "ShadowMapping.fragmentshader");
//    TextureID = glGetUniformLocation(programID, "myTextureSampler");
//    
//    MatrixID      = glGetUniformLocation(programID, "MVP");
//    ViewMatrixID  = glGetUniformLocation(programID, "V");
//    ModelMatrixID = glGetUniformLocation(programID, "M");
//    DepthBiasID   = glGetUniformLocation(programID, "DepthBiasMVP");
//    ShadowMapID   = glGetUniformLocation(programID, "shadowMap");
//    lightInvDirID = glGetUniformLocation(programID, "LightInvDirection_worldspace");
//    
//}
//
//void OBJ_ShadowMapping::playOBJ(glm::vec3 &pos)
//{
//    
//    // レンダリング
//    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
//    glViewport(0, 0, screenWidth, screenWidth);
//    
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
//    
//    glUseProgram(depthProgramID);
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
//    // シェーダー内の"depthMVP"uniformに送信
//    glUniformMatrix4fv(depthMatrixID, 1, GL_FALSE, &depthMVP[0][0]);
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
//    );
//    // vbo
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[3]);
//    glDrawElements(
//                   GL_TRIANGLES,
//                   (int)indices.size(),
//                   GL_UNSIGNED_SHORT,
//                   (void*)0
//                   );
//    glDisableVertexAttribArray(0);
//    
//    
//    
//    // レンダリング
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//    glViewport(0, 0, screenWidth, screenHeight);
//    
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
//    
//    glUseProgram(programID);
//    
//    computeMatricesFromInputs();
//    glm::mat4 ProjectionMatrix = getProjectionMatrix();
//    glm::mat4 ViewMatrix = getViewMatrix();
//    glm::mat4 ModelMatrix = glm::mat4(1.0);
//    
//    
//    gPosition1 = pos;
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
//    // 行列を合わせる
//    glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
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
//    // テクスチャUnit0にバインド
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, Texture);
//    
//    // テクスチャUnit0を使うために"myTextureSampler"サンプラーをセット
//    glUniform1i(TextureID, 0);
//    
//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture(GL_TEXTURE_2D, depthTexture);
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
//    // vbo
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
//void OBJ_ShadowMapping::deinitOBJ()
//{
//    // VBO,shaderを削除
//    glDeleteVertexArrays(1, &vao);
//    glDeleteBuffers(1, &vbos[0]);
//    glDeleteBuffers(1, &vbos[1]);
//    glDeleteBuffers(1, &vbos[2]);
//    glDeleteBuffers(1, &vbos[3]);
//    glDeleteProgram(programID);
//    glDeleteProgram(depthProgramID);
//    glDeleteProgram(quad_programID);
//    glDeleteTextures(1, &Texture);
//    glDeleteFramebuffers(1, &FramebufferName);
//    glDeleteTextures(1, &depthTexture);
//    glDeleteBuffers(1, &quad_vertexbuffer);
//}
//
//void OBJ_ShadowMapping::getDepthTexture(GLuint &depthTex)
//{
//    depthTex = depthTexture;
//}
