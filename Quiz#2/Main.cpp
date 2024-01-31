// TODO: glad.h has to be included before glfw3.h
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "iostream"
#include "string"
#include "vector"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

const float WINDOW_WIDTH  = 600.f;
const float WINDOW_HEIGHT = 600.f;
float FIELD_OF_VIEW       = 60.f;

using namespace std;

glm::vec3 translate    = glm::vec3(0.8f, 0.0f, -2.0f);
glm::vec3 scale        = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);

float theta1           = 0.0f;
float theta2           = 120.0f;
float theta3           = 240.0f;
float movementSpeed    = 0.1f;
float rotateSpeed      = 1.0f;
float scalingRate      = 0.05f;
float zoomRate         = 10.f;

int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(int(WINDOW_WIDTH), int(WINDOW_HEIGHT), "Conrad Amadeus Carmelo C. Ubay",
                              NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGL();

    //* - - - - - SHADERS - - - - -
    //* Load the shader files
    fstream vertSrc("Shaders/sample.vert");
    fstream fragSrc("Shaders/sample.frag");
    stringstream vertBuff;
    stringstream fragBuff;
    //* Add the file stream to the string stream
    vertBuff << vertSrc.rdbuf();
    fragBuff << fragSrc.rdbuf();
    //* Convert the stream to a char array
    string vertS          = vertBuff.str();
    string fragS          = fragBuff.str();
    const char* v         = vertS.c_str();
    const char* f         = fragS.c_str();
    GLuint vertexShader   = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertexShader, 1, &v, NULL);
    glShaderSource(fragmentShader, 1, &f, NULL);
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    //* Create a shader program, then attached the shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    //* Link the shader program
    glLinkProgram(shaderProgram);
    //* - - - - - END OF SHADERS - - - - -

    //* - - - - - BUFFER SHAPES - - - - -
    //* Load 3D Model
    string path = "Model/bunny.obj";
    vector<tinyobj::shape_t> shapes;
    vector<tinyobj::material_t> material;
    string warning, error;
    tinyobj::attrib_t attributes;
    vector<GLuint> mesh_indices;

    if (tinyobj::LoadObj(&attributes, &shapes, &material, &warning, &error,
                         path.c_str())) {
        for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
            mesh_indices.push_back(shapes[0].mesh.indices[i].vertex_index);
        }
    } else {
        cout << "Model Failed to Load." << endl;
    }

    //* Initialize Needed Parts
    GLuint VAO;  //? Vertex Array
    GLuint VBO;  //? Vertex Buffer
    GLuint EBO;  //? Element Buffer

    //* Generate Vertex Array and Buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //* Open Vertex Array and Buffers for Editing
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //* Load in the Vertices
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * attributes.vertices.size(),
                 attributes.vertices.data(), GL_STATIC_DRAW);

    //* Define that we are using 3D Vertices : 3 Floats for x, y, and z
    //coordinates
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void*)0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    //* Using the Loaded Vertices, load in how they're connected
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh_indices.size(),
                 mesh_indices.data(), GL_STATIC_DRAW);

    //* Enable the Vertex Attribute Array : "This is what we'll render"
    glEnableVertexAttribArray(0);

    //* Close Vertex Array and Buffers for Editing
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //* - - - - - END OF BUFFER SHAPES - - - - -

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        //* Clear the window.
        glClear(GL_COLOR_BUFFER_BIT);

        //* Orthographic Projection
        //* Bounds Setting
        glm::mat4 projectionMatrix =
            glm::perspective(glm::radians(FIELD_OF_VIEW),   //? FOV
                             WINDOW_HEIGHT / WINDOW_WIDTH,  //? Aspect Ration
                             0.1f,                          //? Z - Near
                             100.f                          //? Z - Far
            );

        //* - - - - - MODEL MOVEMENT - - - - -
        //* Get the Transformation matrix
        glm::mat4 translate_matrix = glm::translate(glm::mat4(1.0f), translate);

        glm::mat4 scale_matrix     = glm::scale(glm::mat4(1.0f), scale);
        if (theta1 >= 360) {
            theta1 = 0;
        } else {
            theta1 += rotateSpeed;
        }
        glm::mat4 rotate_matrix =
            glm::rotate(glm::mat4(1.0f), glm::radians(theta1),
                        glm::normalize(rotationAxis));

        //* Move the model.
        glm::mat4 transformation_matrix =
            rotate_matrix * translate_matrix * scale_matrix;

        unsigned int projectionLoc =
            glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,
                           glm::value_ptr(projectionMatrix));

        unsigned int transformLoc =
            glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE,
                           glm::value_ptr(transformation_matrix));

        //* - - - - - END OF MODEL MOVEMENT - - - - -

        //* - - - - - SHADER RENDERING - - - - -
        //* Use the shader
        glUseProgram(shaderProgram);

        //* Load in the Vertex Array we made
        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, GLsizei(mesh_indices.size()),
                       GL_UNSIGNED_INT, 0);

        //* - - - - - MODEL MOVEMENT - - - - -
        //* Get the Transformation matrix
        if (theta2 >= 360) {
            theta2 = 0;
        } else {
            theta2 += rotateSpeed;
        }
        glm::mat4 rotate_matrix2 =
            glm::rotate(glm::mat4(1.0f), glm::radians(theta2),
                        glm::normalize(rotationAxis));

        //* Move the model.
        glm::mat4 transformation_matrix2 =
            rotate_matrix2 * translate_matrix * scale_matrix;

        unsigned int transformLoc2 =
            glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc2, 1, GL_FALSE,
                           glm::value_ptr(transformation_matrix2));

        //* Use the shader
        glUseProgram(shaderProgram);

        //* Load in the Vertex Array we made
        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, GLsizei(mesh_indices.size()),
                       GL_UNSIGNED_INT, 0);

        //* - - - - - MODEL MOVEMENT - - - - -
        //* Get the Transformation matrix
        if (theta3 >= 360) {
            theta3 = 0;
        } else {
            theta3 += rotateSpeed;
        }
        glm::mat4 rotate_matrix3 =
            glm::rotate(glm::mat4(1.0f), glm::radians(theta3),
                        glm::normalize(rotationAxis));

        //* Move the model.
        glm::mat4 transformation_matrix3 =
            rotate_matrix3 * translate_matrix * scale_matrix;

        unsigned int transformLoc3 =
            glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc3, 1, GL_FALSE,
                           glm::value_ptr(transformation_matrix3));

        //* Use the shader
        glUseProgram(shaderProgram);

        //* Load in the Vertex Array we made
        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, GLsizei(mesh_indices.size()),
                       GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    //* Free up the memory we've used.
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}
