////
////  obj_Plane.h
////  play
////
////  Created by PROPPACK DEVELOPER IDE on 2018/12/06.
////  Copyright © 2018 IdeKentaro. All rights reserved.
////
//
//#ifndef obj_Plane_h
//#define obj_Plane_h
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
//class OBJ_Plane
//{
//private:
//    
//    int screenWidth;
//    int screenHeight;
//    
//    GLuint vao;
//    GLuint vbos[4];
//    
//    GLuint programID;
//    
//    GLuint MatrixID;
//    GLuint ViewMatrixID;
//    GLuint ModelMatrixID;
//    GLuint DepthBiasID;
//    GLuint ShadowMapID;
//    GLuint lightInvDirID;
//    
//    GLuint Texture;
//    GLuint TextureID;
//    
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
//    GLuint LightID;
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
//    OBJ_Plane(GLFWwindow *window, const char *texture, const char *object);
//    ~OBJ_Plane();
//    
//    void initOBJ(GLFWwindow *window, const char *texture, const char *object);
//    void playOBJ(glm::vec3 &pos, GLuint &dep);
//    void deinitOBJ();
//    
//};
//
//#endif /* obj_Plane_h */
