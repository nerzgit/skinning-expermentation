////
////  obj_TextureRendering.h
////  Gme550
////
////  Created by PROPPACK DEVELOPER IDE on 2019/02/22.
////  Copyright © 2019 IdeKentaro. All rights reserved.
////
//
//#ifndef obj_TextureRendering_h
//#define obj_TextureRendering_h
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
////class OBJ_TextureRendering
//{
//private:
//    
//    int screenwidth;
//    int screenheight;
//    
//    GLuint vao;
//    GLuint vbo[4];
//    GLuint programID;
//    GLuint MatrixID;
//    GLuint ViewMatrixID;
//    GLuint ModelMatrixID;
//    GLuint Texture;
//    GLuint TextureID;
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
//    GLuint renderedTexture;
//    GLuint depthrenderbuffer;
//    GLuint depthTexture;
//    GLuint quad_vertexbuffer;
//    GLuint quad_programID;
//    GLuint texID;
//    GLuint timeID;
//    GLuint LightID;
//    
//    
//public:
//    OBJ_TextureRendering(GLFWwindow *window, const char *texture, const char *object);
//    ~OBJ_TextureRendering();
//    
//    void initOBJ(GLFWwindow *window, const char *texture, const char *object);
//    void playOBJ(glm::mat4 &ViewMatrix, glm::mat4 &ProjectionMatrix, glm::vec3 &pos);
//    void deinitOBJ();
//    
//};
//
//#endif /* obj_TextureRendering_h */
