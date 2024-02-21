// TODO: glad.h has to be included before glfw3.h
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "iostream"
#include "string"
#include "vector"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define X 0
#define Y 1
#define Z 2

#define POSITION_DATA_INDEX 0
#define NORMAL_DATA_INDEX 1
#define UV_DATA_INDEX 2

using namespace std;

//* Window Attributes
const float WINDOW_WIDTH  = 600.f;
const float WINDOW_HEIGHT = 600.f;
float FIELD_OF_VIEW       = 60.f;

//* Rates of Change
float movementSpeed       = 0.1f;
float rotateSpeed         = 10.f;
float scalingRate         = 0.05f;
float zoomRate            = 10.f;

//* Translation Vector
glm::vec3 translate       = glm::vec3(0.0f, 0.0f, -10.0f);
//* Scale Vector
glm::vec3 scale           = glm::vec3(1.0f, 1.0f, 1.0f);
//* Rotation Axes
glm::vec3 xRotationAxis   = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 yRotationAxis   = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 zRotationAxis   = glm::vec3(0.0f, 0.0f, 1.0f);
//* Rotation Thetas
glm::vec3 theta           = glm::vec3(0.0f, 0.0f, 0.0f);

void Key_Callback(GLFWwindow* window, int key, int scancode, int action,
                  int mods) {
    switch (key) {
        //* Moving:
        case GLFW_KEY_W:
            // if (action == GLFW_PRESS) {
            translate.y += movementSpeed;
            // }
            break;
        case GLFW_KEY_A:
            translate.x -= movementSpeed;
            break;
        case GLFW_KEY_S:
            translate.y -= movementSpeed;
            break;
        case GLFW_KEY_D:
            translate.x += movementSpeed;
            break;
        case GLFW_KEY_LEFT_SHIFT:
            translate.z -= movementSpeed;
            break;
        case GLFW_KEY_LEFT_CONTROL:
            translate.z += movementSpeed;
            break;
        //* Rotating:
        case GLFW_KEY_UP:
            theta.x -= rotateSpeed;
            break;
        case GLFW_KEY_DOWN:
            theta.x += rotateSpeed;
            break;
        case GLFW_KEY_LEFT:
            theta.y -= rotateSpeed;
            break;
        case GLFW_KEY_RIGHT:
            theta.y += rotateSpeed;
            break;
        case GLFW_KEY_R:
            theta.z -= rotateSpeed;
            break;
        case GLFW_KEY_T:
            theta.z += rotateSpeed;
            break;
        //* Scaling:
        case GLFW_KEY_Q:
            scale.x -= scalingRate;
            scale.y -= scalingRate;
            scale.z -= scalingRate;
            break;
        case GLFW_KEY_E:
            scale.x += scalingRate;
            scale.y += scalingRate;
            scale.z += scalingRate;
            break;
        //* Zooming:
        case GLFW_KEY_Z:
            FIELD_OF_VIEW -= zoomRate;
            break;
        case GLFW_KEY_X:
            FIELD_OF_VIEW += zoomRate;
            break;
    }

    //? Debug: What are the details of our model?
    if (action == GLFW_PRESS) {
        system("cls");
        cout << "Tx"
             << "\t"
             << "Ty"
             << "\t"
             << "Tz"
             << "\t"
             << "thetaX"
             << "\t"
             << "thetaY"
             << "\t"
             << "thetaZ"
             << "\t"
             << "Sx"
             << "\t"
             << "Sy"
             << "\t"
             << "Sz"
             << "\t" << endl;
        cout << translate.x << "\t" << translate.y << "\t" << translate.z
             << "\t" << theta.x << "\t" << theta.y << "\t" << theta.z << "\t"
             << scale.x << "\t" << scale.y << "\t\t" << scale.z << "\t" << endl;
    }
}

int main(void) {
    //* - - - - - GLFW SETUP - - - - -
    GLFWwindow* window;

    //* Initialize the library
    if (!glfwInit()) return -1;

    //* Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(int(WINDOW_WIDTH), int(WINDOW_HEIGHT), "U w U",
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
    unsigned char* tex_bytes = stbi_load("Model/partenza.jpg", &imageWidth,
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
    string path = "Model/djSword.obj";
    vector<tinyobj::shape_t> shapes;
    vector<tinyobj::material_t> material;
    string warning, error;
    tinyobj::attrib_t attributes;
    vector<GLuint> mesh_indices;

    vector<GLfloat> fullVertexData;

    //* - - - - - UV DATA - - - - -
    // GLfloat UV[]{0.f, 1.f, 0.f, 0.f, 1.f, 1.f, 1.f, 0.f,
    //              1.f, 1.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f};
    //* - - - - - END OF UV DATA - - - - -

    if (tinyobj::LoadObj(&attributes, &shapes, &material, &warning, &error,
                         path.c_str())) {
        // for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
        //     mesh_indices.push_back(shapes[0].mesh.indices[i].vertex_index);
        // }
        for (tinyobj::index_t vData : shapes[0].mesh.indices) {
            //*Insert Vertex Position Data: (X, Y, Z)
            fullVertexData.push_back(
                attributes.vertices[(vData.vertex_index * 3)]);
            fullVertexData.push_back(
                attributes.vertices[(vData.vertex_index * 3) + 1]);
            fullVertexData.push_back(
                attributes.vertices[(vData.vertex_index * 3) + 2]);
            //*Insert Normals Position Data: (X, Y, Z)
            fullVertexData.push_back(
                attributes.normals[(vData.normal_index * 3)]);
            fullVertexData.push_back(
                attributes.normals[(vData.normal_index * 3) + 1]);
            fullVertexData.push_back(
                attributes.normals[(vData.normal_index * 3) + 2]);
            //* Insert UV Data: (U, V)
            fullVertexData.push_back(
                attributes.texcoords[(vData.texcoord_index * 2)]);
            fullVertexData.push_back(
                attributes.texcoords[(vData.texcoord_index * 2) + 1]);
        }

        // for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
        //     tinyobj::index_t vData = shapes[0].mesh.indices[i];
        //     //*Insert Vertex Position: (X, Y, Z)
        //     fullVertexData.push_back(
        //         attributes.vertices[(vData.vertex_index * 3)]);
        //     fullVertexData.push_back(
        //         attributes.vertices[(vData.vertex_index * 3) + 1]);
        //     fullVertexData.push_back(
        //         attributes.vertices[(vData.vertex_index * 3) + 2]);
        //     //* Insert UV Data: (U, V)
        //     fullVertexData.push_back(
        //         attributes.texcoords[(vData.texcoord_index * 2)]);
        //     fullVertexData.push_back(
        //         attributes.texcoords[(vData.texcoord_index * 2) + 1]);
        // }
    } else {
        cout << "Model Failed to Load." << endl;
    }

    //* Initialize Needed Parts
    GLuint VAO;  //? Vertex Array
    GLuint VBO;  //? Vertex Buffer
    // GLuint VBO_UV;  //? Vertex Buffer for Texture
    // GLuint EBO;     //? Element Buffer

    //* Generate Vertex Array and Buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // glGenBuffers(1, &VBO_UV);
    // glGenBuffers(1, &EBO);

    //? Convetional Vertex Attribute Indices:
    //? 0: Vertices
    //? 1: Normals
    //? 2: UV

    //* Open Vertex Array for Editing
    glBindVertexArray(VAO);
    //* Load in the Vertices
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //* Load in our Full Vertex Array
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * fullVertexData.size(),
                 fullVertexData.data(), GL_DYNAMIC_DRAW);
    //* Define our Full Vertex Array's layout
    glVertexAttribPointer(POSITION_DATA_INDEX, 3, GL_FLOAT, GL_FALSE,
                          8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    GLintptr normPtr = 3 * sizeof(float);
    glVertexAttribPointer(NORMAL_DATA_INDEX, 3, GL_FLOAT, GL_FALSE,
                          8 * sizeof(float), (void*)normPtr);
    glEnableVertexAttribArray(1);

    GLintptr uvPtr = 6 * sizeof(float);
    glVertexAttribPointer(UV_DATA_INDEX, 2, GL_FLOAT, GL_FALSE,
                          8 * sizeof(float), (void*)uvPtr);
    glEnableVertexAttribArray(2);

    //* - - - - - BASIC VERTEX BUFFERING - - - - -
    // glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) *
    // attributes.vertices.size(),
    //              attributes.vertices.data(), GL_STATIC_DRAW);
    //* Define that we are using 3 dimensions
    // glVertexAttribPointer(POSITION_DATA_INDEX, 3, GL_FLOAT, GL_FALSE, 3 *
    // sizeof(float),
    //                       (void*)0);
    //* - - - - - END OF BASIC VERTEX BUFFERING - - - - -

    //* Load in the Edges
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) *
    // mesh_indices.size(),
    //              mesh_indices.data(), GL_STATIC_DRAW);

    //* Bind UV Buffer
    // glBindBuffer(GL_ARRAY_BUFFER, VBO_UV);
    //* Load UV Data
    // glBufferData(GL_ARRAY_BUFFER,
    //              sizeof(GLfloat) * (sizeof(UV) / sizeof(UV[0])), &UV[0],
    //              GL_DYNAMIC_DRAW);
    //* Define that we are using 2 dimensions
    // glVertexAttribPointer(UV_DATA_INDEX, 2, GL_FLOAT, GL_FALSE, 2 *
    // sizeof(float),
    //                       (void*)0);

    //* Close Vertex Array and Buffers for Editing
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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
    //* Initialize World Up & Camera Center
    glm::vec3 WorldUp   = glm::vec3(0, 1.0f, 0);
    glm::vec3 Center    = glm::vec3(0, 3.0f, 0);
    //* Camera Position
    glm::vec3 cameraPos = glm::vec3(0, 0, 10.f);
    glm::mat4 cameraPositionMatrix =
        glm::translate(glm::mat4(1.0f), cameraPos * -1.0f);

    glm::vec3 forwardVector =
        glm::normalize(glm::vec3(Center - cameraPos));  //* Set Forward Vector
    glm::vec3 rightVector = glm::normalize(
        glm::cross(forwardVector, WorldUp));  //* Set Right Vector
    glm::vec3 upVector = glm::normalize(
        glm::cross(rightVector, forwardVector));  //* Set Up Vector

    //* Set Camera Orientation
    glm::mat4 cameraOrientation = glm::mat4(1.f);
    cameraOrientation[X][X]     = rightVector.x;
    cameraOrientation[Y][X]     = rightVector.y;
    cameraOrientation[Z][X]     = rightVector.z;
    cameraOrientation[X][Y]     = upVector.x;
    cameraOrientation[Y][Y]     = upVector.y;
    cameraOrientation[Z][Y]     = upVector.z;
    cameraOrientation[X][Z]     = -forwardVector.x;
    cameraOrientation[Y][Z]     = -forwardVector.y;
    cameraOrientation[Z][Z]     = -forwardVector.z;

    //* Set View Matrix
    glm::mat4 viewMatrix =
        // cameraOrientation * cameraPositionMatrix;
        glm::lookAt(cameraPos, Center, WorldUp);

    //* - - - - - END OF CAMERA SETUP - - - - -

    //* - - - - - LIGHTING - - - - -
    glm::vec3 lightPos     = glm::vec3(-10, 3, 0);
    glm::vec3 lightColor   = glm::vec3(1, 1, 1);
    float ambientStrength  = 0.5f;
    glm::vec3 ambientColor = lightColor;
    float specStrength     = 0.5f;
    float specPhong        = 16;  //? Usually 16 - 25
    //* - - - - - END OF LIGHTING - - - - -

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        //* - - - - - CAMERA - - - - -
        float x_mod = 0.f;
        cameraPos   = glm::vec3(x_mod, 0, 10.f);
        ;
        viewMatrix = glm::lookAt(cameraPos, Center, WorldUp);
        //* - - - - - END OF CAMERA - - - - -

        /* Render here */
        //* Clear the window.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //* - - - - - MODEL MOVEMENT - - - - -
        //* Get the Transformation matrix
        glm::mat4 tranlateMatrix = glm::translate(glm::mat4(1.0f), translate);

        glm::mat4 scaleMatrix    = glm::scale(glm::mat4(1.0f), scale);

        glm::mat4 rotateMatrix =
            glm::rotate(glm::mat4(1.0f), glm::radians(theta.x),
                        glm::normalize(xRotationAxis)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(theta.y),
                        glm::normalize(yRotationAxis)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(theta.z),
                        glm::normalize(zRotationAxis));

        //* Provide the shader's needed data
        glm::mat4 transformationMatrix =
            tranlateMatrix * scaleMatrix * rotateMatrix;

        unsigned int projectionLoc =
            glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,
                           glm::value_ptr(projectionMatrix));

        unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

        unsigned int transformLoc =
            glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE,
                           glm::value_ptr(transformationMatrix));

        //* - - - - - END OF MODEL MOVEMENT - - - - -

        //* - - - - - SHADER RENDERING - - - - -
        //* Use the shader
        glUseProgram(shaderProgram);

        //* Load in the Vertex Array we made
        glBindVertexArray(VAO);

        //* Use textures
        GLuint tex0Address = glGetUniformLocation(shaderProgram, "tex0");
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(tex0Address, 0);

        //* Use lighting
        GLuint lightAddress = glGetUniformLocation(shaderProgram, "lightPos");
        glUniform3fv(lightAddress, 1, glm::value_ptr(lightPos));

        GLuint lightColorAddress =
            glGetUniformLocation(shaderProgram, "lightColor");
        glUniform3fv(lightColorAddress, 1, glm::value_ptr(lightColor));

        GLuint ambientAddress =
            glGetUniformLocation(shaderProgram, "ambientStr");
        glUniform1f(ambientAddress, ambientStrength);

        GLuint ambientColorAddress =
            glGetUniformLocation(shaderProgram, "ambientColor");
        glUniform3fv(ambientColorAddress, 1, glm::value_ptr(ambientColor));

        GLuint cameraPosAddress =
            glGetUniformLocation(shaderProgram, "cameraPos");
        glUniform3fv(cameraPosAddress, 1, glm::value_ptr(cameraPos));

        GLuint specStrAddress = glGetUniformLocation(shaderProgram, "specStr");
        glUniform1f(specStrAddress, specStrength);

        GLuint specPhongAddress =
            glGetUniformLocation(shaderProgram, "specPhong");
        glUniform1f(specPhongAddress, specPhong);

        // glDrawElements(
        //     GL_TRIANGLES, GLsizei(mesh_indices.size()), GL_UNSIGNED_INT,
        //     0);  // the GLsizei() is just to remove
        //          // a warning, since glDrawElements has a parameter of it,
        //          and
        //          // it wants us to make sure we only plug GLsizei's in it.
        glDrawArrays(GL_TRIANGLES, 0, fullVertexData.size() / 8);

        //* Swap front and back buffers
        glfwSwapBuffers(window);
        //* Poll for and process events
        glfwPollEvents();
    }

    //* Free up the memory we've used.
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &VBO_UV);
    // glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}
