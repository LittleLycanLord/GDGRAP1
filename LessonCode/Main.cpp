// TODO: glad.h has to be included before glfw3.h

#include "iostream"
#include "string"
#include "vector"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Model/Entity/ModelObject/ModelObject.hpp"
#include "Model/Entity/Camera/Camera.hpp"

#include "Shaders/Shaders.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include "Model/Entity/BaseObject/BaseObject.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "Model/Entity/Texture/Texture.hpp"

using namespace std;
using namespace models;
using namespace shaders;

//* Window Attributes
const float WINDOW_WIDTH  = 600.f;
const float WINDOW_HEIGHT = 600.f;
float FIELD_OF_VIEW       = 60.f;


Camera camera = Camera();
Shaders shader = Shaders();
Texture texture = Texture();
BaseObject tinyObject = BaseObject();
ModelObject model = ModelObject();

vector<ModelObject> modelTracker;


void Key_Callback(GLFWwindow* window, int key, int scancode, int action,
                  int mods) {
    camera.updateCamera(key, &FIELD_OF_VIEW);
}

int main(void) {
    //* - - - - - GLFW SETUP - - - - -
    GLFWwindow* window;

    //* Initialize the library
    if (!glfwInit()) return -1;

    //* Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(int(WINDOW_WIDTH), int(WINDOW_HEIGHT), "Repository",
                              NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    //* Make the window's context current
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSetKeyCallback(window, Key_Callback);
    glEnable(GL_DEPTH_TEST);

    //* - - - - - END OF GLFW SETUP - - - - -
    
    //* Load Texture
    texture.initializeTexture();
    shader.initializeShaders();
    shader.assignTexture(texture.getImgWidth(), texture.getImgHeight(), texture.getTexBytes()); 
    texture.freeImgData(); 
    //* - - - - - END OF TEXTURE INITIALIZATION - - - - -
 
    //* - - - - - BUFFER SHAPES - - - - -
    //* Load 3D Model
    tinyObject.initialize();
    vector<GLuint> mesh_indices;

    //* - - - - - UV DATA - - - - -
    GLfloat UV[]{0.f, 1.f, 0.f, 0.f, 1.f, 1.f, 1.f, 0.f,
                 1.f, 1.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f};
    //* - - - - - END OF UV DATA - - - - -
    for (int i = 0; i < (*tinyObject.getShapes())[0].mesh.indices.size(); i++) {
       mesh_indices.push_back((*tinyObject.getShapes())[0].mesh.indices[i].vertex_index);
    }

    //* Initialize Needed Parts
    GLuint VAO;     //? Vertex Array
    GLuint VBO;     //? Vertex Buffer
    GLuint VBO_UV;  //? Vertex Buffer for Texture
    GLuint EBO;     //? Element Buffer

    //* Generate Vertex Array and Buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VBO_UV);
    glGenBuffers(1, &EBO);

    //* Open Vertex Array for Editing
    glBindVertexArray(VAO);
    //* Load in the Vertices
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * (*tinyObject.getObjAttributes()).vertices.size(), (*tinyObject.getObjAttributes()).vertices.data(), GL_STATIC_DRAW);
    //* Define that we are using 3 dimensions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //* Load in the Edges
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh_indices.size(), mesh_indices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);

    //* Bind UV Buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO_UV);
    //* Load UV Data
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (sizeof(UV) / sizeof(UV[0])), &UV[0], GL_DYNAMIC_DRAW);
    //*
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(2);

    //* Close Vertex Array and Buffers for Editing
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //* - - - - - END OF BUFFER SHAPES - - - - -

    model.initialize(shader.getShaderProgram(), camera.getViewMatrix(), shader.getTexture());

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        model.updateModel(camera.getViewMatrix());
       
        //* Use the shader
        glUseProgram(*shader.getShaderProgram());
        //* Load in the Vertex Array we made
        glBindVertexArray(VAO);

        model.drawModel(&mesh_indices);

        glEnd();

        //* Swap front and back buffers
        glfwSwapBuffers(window);
        //* Poll for and process events
        glfwPollEvents();
    }

    //* Free up the memory we've used.
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &VBO_UV);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}
