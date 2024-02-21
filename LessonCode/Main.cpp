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
#include "tiny_obj_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;
using namespace models;
using namespace shaders;

//* Window Attributes
const float WINDOW_WIDTH  = 600.f;
const float WINDOW_HEIGHT = 600.f;
float FIELD_OF_VIEW       = 60.f;


Camera camera = Camera();
Shaders shader = Shaders();

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
    glEnable(GL_DEPTH_TEST);
    //* - - - - - END OF GLFW SETUP - - - - -

    //* - - - - - TEXTURE INITIALIZATION - - - - -
    int imageWidth;
    int imageHeight;
    int colorChannels;

    //* Flip Texture
    stbi_set_flip_vertically_on_load(true);

    //* Load Texture
    unsigned char* tex_bytes = stbi_load("Model/Ayaya.png", &imageWidth,
                                         &imageHeight, &colorChannels, 0);
    GLuint texture;
    //? 1 is the # of textures
    //* Create an OpenGL reference for the texture
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    //* Assign a texture to that reference
    switch (colorChannels) {
        case 3:
            glTexImage2D(GL_TEXTURE_2D, 0,  //? <- Texture Index
                         GL_RGB, imageWidth, imageHeight, 0, GL_RGB,
                         GL_UNSIGNED_BYTE, tex_bytes);
            break;
        case 4:
            glTexImage2D(GL_TEXTURE_2D, 0,  //? <- Texture Index
                         GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA,
                         GL_UNSIGNED_BYTE, tex_bytes);
            break;
    }
    //* Generate mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(tex_bytes);
    //* - - - - - END OF TEXTURE INITIALIZATION - - - - -

    //* - - - - - BASIC INPUT - - - - -
    glfwSetKeyCallback(window, Key_Callback);
    //* - - - - - END OF BASIC INPUT - - - - -

    shader.initializeShaders();
    shader.assignTexture(imageWidth, imageHeight, tex_bytes);

    //* - - - - - BUFFER SHAPES - - - - -
    //* Load 3D Model
    string path = "Model/Ayaya.obj";
    vector<tinyobj::shape_t> shapes;
    vector<tinyobj::material_t> material;
    string warning, error;
    tinyobj::attrib_t attributes;
    vector<GLuint> mesh_indices;

    //* - - - - - UV DATA - - - - -
    GLfloat UV[]{0.f, 1.f, 0.f, 0.f, 1.f, 1.f, 1.f, 0.f,
                 1.f, 1.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f};
    //* - - - - - END OF UV DATA - - - - -

    if (tinyobj::LoadObj(&attributes, &shapes, &material, &warning, &error,
                         path.c_str())) {
        for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
            mesh_indices.push_back(shapes[0].mesh.indices[i].vertex_index);
        }
    } else {
        cout << "Model Failed to Load." << endl;
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

    //? Convetional Vertex Attribute Indices:
    //? 0: Vertices
    //? 1: ???
    //? 2: UV

    //* Open Vertex Array for Editing
    glBindVertexArray(VAO);
    //* Load in the Vertices
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * attributes.vertices.size(),
                 attributes.vertices.data(), GL_STATIC_DRAW);
    //* Define that we are using 3 dimensions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void*)0);
    //* Load in the Edges
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh_indices.size(),
                 mesh_indices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);

    //* Bind UV Buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO_UV);
    //* Load UV Data
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * (sizeof(UV) / sizeof(UV[0])), &UV[0],
                 GL_DYNAMIC_DRAW);
    //*
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(2);

    //* Close Vertex Array and Buffers for Editing
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //* - - - - - END OF BUFFER SHAPES - - - - -

    //* - - - - - PROJECTION - - - - -
    //* Orthographic Projection
    //* Bounds Setting
    glm::mat4 projectionMatrix =
        glm::perspective(glm::radians(FIELD_OF_VIEW),   //? FOV
                         WINDOW_HEIGHT / WINDOW_WIDTH,  //? Aspect Ration
                         0.1f,                          //? Z - Near
                         100.f                          //? Z - Far
        );
    //* - - - - - END OF PROJECTION - - - - -

    //* - - - - - CAMERA SETUP - - - - -


    //* - - - - - END OF CAMERA SETUP - - - - -

    ModelObject model = ModelObject(shader.getShaderProgram(), &projectionMatrix, camera.getViewMatrix(), &texture);

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
