////
////  obj_ShadowMapping.h
////  play
////
////  Created by PROPPACK DEVELOPER IDE on 2018/10/22.
////  Copyright © 2018年 IdeKentaro. All rights reserved.
////
//
//#ifndef obj_ShadowMapping_hpp
//#define obj_ShadowMapping_hpp
//
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/quaternion.hpp>
//#include <glm/gtx/quaternion.hpp>
//
//#include <vector>
//
//class OBJ_ShadowMapping
//{
//private:
//
//    int screenWidth;
//    int screenHeight;
//    
//    GLuint vao;
//    GLuint vbos[4];
//    GLuint depthProgramID;
//    GLuint depthMatrixID;
//    GLuint Texture;
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
//    GLuint FramebufferName;
//    GLuint depthTexture;
//    GLuint quad_vertexbuffer;
//    GLuint quad_programID;
//    GLuint texID;
//    GLuint programID;
//    GLuint TextureID;
//    GLuint MatrixID;
//    GLuint ViewMatrixID;
//    GLuint ModelMatrixID;
//    GLuint DepthBiasID;
//    GLuint ShadowMapID;
//    GLuint lightInvDirID;
//    
//    bool gLookAtOther;
//    bool onEuler;
//    bool onQuaternion;
//    
//    glm::vec3 gPosition1;
//    glm::vec3 gOrientation1;
//    glm::vec3 gPosition2;
//    glm::quat gOrientation2;
//    glm::vec3 gScaling;
//    
//public:
//    
//    OBJ_ShadowMapping(GLFWwindow *window, const char *texture, const char *object);
//    ~OBJ_ShadowMapping();
//    
//    void initOBJ(GLFWwindow *window, const char *texture, const char *object);
//    void playOBJ(glm::vec3 &pos);
//    void deinitOBJ();
//
//    void getDepthTexture(GLuint &depthTex);
//    
//};
//
//#endif /* obj_ShadowMapping_h */
