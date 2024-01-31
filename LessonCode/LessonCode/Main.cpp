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
float FIELD_OF_VIEW = 60.f;

using namespace std;

class Point2D {
public:
    GLfloat x;
    GLfloat y;

public:
    Point2D(GLfloat x, GLfloat y) {
        this->x = x;
        this->y = y;
    }
};

void Notes() {
    float x                    = 0;
    float y                    = 0;
    float z                    = 0;
    float theta                = 0;

    glm::mat3 identity_matrix3 = glm::mat3(1.0f);
    glm::mat4 identity_matrix4 = glm::mat4(1.0f);

    //? Creates 3D Translation Matrix
    glm::mat4 translation =
        glm::translate(identity_matrix4, glm::vec3(x, y, z));

    //? Creates 3D Rotation Matrix
    glm::mat4 rotation =
        glm::rotate(identity_matrix4, glm::radians(theta), glm::vec3(x, y, z));
}

void Draw2D(vector<Point2D> vertices) {
    glBegin(GL_POLYGON);
    for (Point2D vertex : vertices) {
        glVertex2f(vertex.x, vertex.y);
    }
    glEnd();
}

glm::vec3 translate    = glm::vec3(0.0f, 0.0f, -5.0f);
glm::vec3 scale        = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);

float theta            = 0.0f;
float movementSpeed    = 0.1f;
float rotateSpeed      = 10.f;
float scalingRate      = 0.05f;
float zoomRate         = 10.f;

void Key_Callback(GLFWwindow* window, int key, int scancode, int action,
                  int mods) {
    switch (key) {
        case GLFW_KEY_W:
            if (action == GLFW_PRESS) {
                translate.y += movementSpeed;
            }
            break;
        case GLFW_KEY_A:
            if (action == GLFW_PRESS) {
                translate.x -= movementSpeed;
            }
            break;
        case GLFW_KEY_S:
            if (action == GLFW_PRESS) {
                translate.y -= movementSpeed;
            }
            break;
        case GLFW_KEY_D:
            if (action == GLFW_PRESS) {
                translate.x += movementSpeed;
            }
            break;
        case GLFW_KEY_LEFT_SHIFT:
            if (action == GLFW_PRESS) {
                translate.z -= movementSpeed;
            }
            break;
        case GLFW_KEY_LEFT_CONTROL:
            if (action == GLFW_PRESS) {
                translate.z += movementSpeed;
            }
            break;
        case GLFW_KEY_RIGHT:
            if (action == GLFW_PRESS) {
                rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
                theta += rotateSpeed;
            }
            break;
        case GLFW_KEY_LEFT:
            if (action == GLFW_PRESS) {
                rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
                theta -= rotateSpeed;
            }
            break;
        case GLFW_KEY_UP:
            if (action == GLFW_PRESS) {
                rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
                theta -= rotateSpeed;
            }
            break;
        case GLFW_KEY_DOWN:
            if (action == GLFW_PRESS) {
                rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
                theta += rotateSpeed;
            }
            break;
        case GLFW_KEY_Q:
            if (action == GLFW_PRESS) {
                scale.x -= scalingRate;
                scale.y -= scalingRate;
                scale.z -= scalingRate;
            }
            break;
        case GLFW_KEY_E:
            if (action == GLFW_PRESS) {
                scale.x += scalingRate;
                scale.y += scalingRate;
                scale.z += scalingRate;
            }
            break;
        case GLFW_KEY_Z:
            if (action == GLFW_PRESS) {
                FIELD_OF_VIEW -= zoomRate;
            }
            break;
        case GLFW_KEY_X:
            if (action == GLFW_PRESS) {
                FIELD_OF_VIEW += zoomRate;
            }
            break;
            // case GLFW_KEY_K:
            //     if (action == GLFW_PRESS) {
            //         scale.y -= scalingRate;
            //     }
            //     break;
            // case GLFW_KEY_L:
            //     if (action == GLFW_PRESS) {
            //         scale.x += scalingRate;
            //     }
            //     break;
            // case GLFW_KEY_U:
            //     if (action == GLFW_PRESS) {
            //         scale.z -= scalingRate;
            //     }
            //     break;
            // case GLFW_KEY_O:
            //     if (action == GLFW_PRESS) {
            //         scale.z += scalingRate;
            //     }
            //     break;
    }
    if (action == GLFW_PRESS) {
        system("cls");
        cout << "Tx"
             << "\t"
             << "Ty"
             << "\t"
             << "Tz"
             << "\t"
             << "theta"
             << "\t"
             << "Sx"
             << "\t"
             << "Sy"
             << "\t"
             << "Sz"
             << "\t" << endl;
        cout << translate.x << "\t" << translate.y << "\t" << translate.z
             << "\t" << theta << "\t" << scale.x << "\t" << scale.y << "\t"
             << scale.z << "\t" << endl;
    }
}

int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(int(WINDOW_WIDTH), int(WINDOW_HEIGHT), "U w U",
                              NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGL();

    //* - - - - - BASIC INPUT - - - - -
    glfwSetKeyCallback(window, Key_Callback);

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
    string path = "Model/Furina.obj";
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

    //* Initialize Existing Vertices
    GLfloat vertices[]{
       // x     //y     //z
       0.f,   0.5f,  0.f,  //*Point 0
       -0.5f, -0.5f, 0.f,  //*Point 1
       0.5f,  -0.5f, 0.f   //*Point 2
    };

    //* Initialize Triangles
    GLuint indices[]{0, 1, 2};

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
    //? For 2D Polygons
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
    // GL_STATIC_DRAW);
    //? For 3D Models
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * attributes.vertices.size(),
                 attributes.vertices.data(), GL_STATIC_DRAW);

    //* Define that we are using 3D Vertices : 3 Floats for x, y, and z
    // coordinates
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void*)0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    //* Using the Loaded Vertices, load in how they're connected
    //? For Multiple Polygons
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
    //              GL_STATIC_DRAW);
    //? For 3D Models
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
            // glm::ortho(-2.f,  //? Left
            //            2.f,   //? Right
            //            -2.f,  //? Bottom
            //            2.f,   //? Top
            //            -1.f,  //? Z - Near
            //            1.f    //? Z - Far
            // );
            glm::perspective(glm::radians(FIELD_OF_VIEW),   //? FOV
                             WINDOW_HEIGHT / WINDOW_WIDTH,  //? Aspect Ration
                             0.1f,                          //? Z - Near
                             100.f                          //? Z - Far
            );

        //* - - - - - MODEL MOVEMENT - - - - -
        //* Get the Transformation matrix
        glm::mat4 tranlate_matrix = glm::translate(glm::mat4(1.0f), translate);

        glm::mat4 scale_matrix    = glm::scale(glm::mat4(1.0f), scale);

        glm::mat4 rotate_matrix   = glm::rotate(
            glm::mat4(1.0f), glm::radians(theta), glm::normalize(rotationAxis));

        //* Move the model.
        // unsigned int xLoc = glGetUniformLocation(shaderProgram, "x");
        // unsigned int yLoc = glGetUniformLocation(shaderProgram, "y");
        // unsigned int zLoc = glGetUniformLocation(shaderProgram, "z");

        // glUniform1f(xLoc, x_mod);
        // glUniform1f(yLoc, y_mod);
        // glUniform1f(zLoc, z_mod);

        glm::mat4 transformation_matrix =
            tranlate_matrix * scale_matrix * rotate_matrix;

        unsigned int projectionLoc =
            glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,
                           glm::value_ptr(projectionMatrix));

        unsigned int transformLoc =
            glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE,
                           glm::value_ptr(transformation_matrix));

        //* - - - - - END OF MODEL MOVEMENT - - - - -

        //? Draw 2D Triangle
        // Draw2D(
        //     {Point2D(-0.5f, -0.5f), Point2D(0.0f, 0.5f), Point2D(0.5f,
        //     -0.5f)});

        //* - - - - - SHADER RENDERING - - - - -
        //* Use the shader
        glUseProgram(shaderProgram);

        //* Load in the Vertex Array we made
        glBindVertexArray(VAO);
        //? Drawing using 'just' the Vertex Array
        // glDrawArrays(GL_TRIANGLES, 0, 3);

        //? Drawing using an Element Array: For Multiple Polygons
        // glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
        //? Drawing using an Element Array: For 3D Models
        glDrawElements(
            GL_TRIANGLES, GLsizei(mesh_indices.size()), GL_UNSIGNED_INT,
            0);  // the GLsizei() is just to remove
                 // a warning, since glDrawElements has a parameter of it, and
                 // it wants us to make sure we only plug GLsizei's in it.

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
