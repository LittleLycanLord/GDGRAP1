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

glm::vec3 WorldUp  = glm::vec3(0, 1.0f, 0);
Camera camera = Camera();
Shaders shader = Shaders();
Texture texture = Texture();
BaseObject tinyObject = BaseObject();
ModelObject* model = new ModelObject();

vector<ModelObject> modelTracker;

void Key_Callback(GLFWwindow* window, int key, int scancode, int action,
                  int mods) {
    //std::cout << "translate x value: " << model->getMatrix()->getTranslateVar('X') << std::endl;
   
        camera.updateCamera(key, action, &FIELD_OF_VIEW, WorldUp);
        if (action == GLFW_PRESS) {
            switch (key) {
                case GLFW_KEY_SPACE:
                    model->setModelInFrontOfCam(camera.getCameraPosition(), camera.getCenterPosition(), camera.getTheta());
                    modelTracker.push_back(*model);
                    //std::cout << "translate x value: " << model->getMatrix()->getTranslateVar('X') << std::endl;
                    break;
            }
        }
         
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
    shader.assignTexture(texture.getColorChannels(), texture.getImgWidth(), texture.getImgHeight(), texture.getTexBytes()); 
    texture.freeImgData(); 
    //* - - - - - END OF TEXTURE INITIALIZATION - - - - -
 
    //* - - - - - BUFFER SHAPES - - - - -
    //* Load 3D Model
    tinyObject.initialize();
    vector<GLuint> mesh_indices;

    for (int i = 0; i < (*tinyObject.getShapes())[0].mesh.indices.size(); i++) {
       mesh_indices.push_back((*tinyObject.getShapes())[0].mesh.indices[i].vertex_index);
    }

    //* Initialize Needed Parts
    GLuint VAO;     //? Vertex Array
    GLuint VBO;     //? Vertex Buffer

    //* Generate Vertex Array and Buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //* Open Vertex Array for Editing
    glBindVertexArray(VAO);
    //* Load in the Vertices
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //* Load in our Full Vertex Array
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * (*tinyObject.getFullVertexData()).size(),
                 (*tinyObject.getFullVertexData()).data(), GL_DYNAMIC_DRAW);
    //* Define our Full Vertex Array's layout
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    GLintptr normPtr = 3 * sizeof(float);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                          8 * sizeof(float), (void*)normPtr);
    glEnableVertexAttribArray(1);

    GLintptr uvPtr = 6 * sizeof(float);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                          8 * sizeof(float), (void*)uvPtr);
    glEnableVertexAttribArray(2);

    //* Close Vertex Array and Buffers for Editing
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //* - - - - - END OF BUFFER SHAPES - - - - -

    model->initialize(shader.getShaderProgram(), camera.getViewMatrix(), shader.getTexture());

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // std::cout << "size: " << modelTracker.size() << std::endl;
        camera.updateCamera(0, 0, &FIELD_OF_VIEW, WorldUp);
        model->setViewMatrix(*camera.getViewMatrix());
        model->updateModel(*camera.getCameraPosition());
       
        unsigned int viewLoc = glGetUniformLocation(*shader.getShaderProgram(), "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(*camera.getViewMatrix()));

        //* Use the shader
        glUseProgram(*shader.getShaderProgram());
        //* Load in the Vertex Array we made
        glBindVertexArray(VAO);

        if (modelTracker.size() != 0) {
            for (unsigned int i = 0; i < modelTracker.size(); i++) {
                modelTracker[i].drawModel(&mesh_indices, tinyObject.getFullVertexData(),
                                          *camera.getCameraPosition());
            }
        }

        glEnd();

        //* Swap front and back buffers
        glfwSwapBuffers(window);
        //* Poll for and process events
        glfwPollEvents();
    }

    //* Free up the memory we've used.
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
