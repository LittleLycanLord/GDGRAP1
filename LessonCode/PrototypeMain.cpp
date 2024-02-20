// // TODO: glad.h has to be included before glfw3.h
// #include "glad/glad.h"
// #include "GLFW/glfw3.h"
// #include "glm/glm.hpp"
// #include "glm/gtc/matrix_transform.hpp"
// #include "glm/gtc/type_ptr.hpp"
// #include "iostream"
// #include "string"
// #include "vector"
// #include "fstream"
// #include "sstream"
// #include "Model/Entity/Texture/Texture.hpp"
// #define TINYOBJLOADER_IMPLEMENTATION
// #include "Model/Entity/Model3D/Model3D.hpp"
// #include "Model/Entity/Camera/Camera.hpp"

// using namespace std;
// using namespace models;
// using namespace components;

// extern float movementSpeed;
// extern float rotateSpeed;
// extern float scalingRate;
// extern float zoomRate;

// //* Window Attributes
// const float WINDOW_WIDTH  = 600.f;
// const float WINDOW_HEIGHT = 600.f;
// float FIELD_OF_VIEW       = 60.f;

// //* Rates of Change
// float movementSpeed       = 0.1f;
// float rotateSpeed         = 10.f;
// float scalingRate         = 0.05f;
// float zoomRate            = 10.f;

// //* - - - - - PROJECTION - - - - -
// //* Orthographic Projection
// //* Bounds Setting
// glm::mat4 projectionMatrix =
//     glm::perspective(glm::radians(FIELD_OF_VIEW),   //? FOV
//                      WINDOW_HEIGHT / WINDOW_WIDTH,  //? Aspect Ration
//                      0.1f,                          //? Z - Near
//                      100.f                          //? Z - Far
//     );
// //* - - - - - END OF PROJECTION - - - - -
// Camera* MainCamera;

// void Key_Callback(GLFWwindow* window, int key, int scancode, int action,
//                   int mods) {
//     switch (key) {
//         //* Moving:
//         case GLFW_KEY_W:
//             // if (action == GLFW_PRESS) {
//             MainCamera->translate(glm::vec3(0.0f, +movementSpeed, 0.0f));
//             // }
//             break;
//         case GLFW_KEY_A:
//             MainCamera->translate(glm::vec3(-movementSpeed, 0.0f, 0.0f));
//             break;
//         case GLFW_KEY_S:
//             MainCamera->translate(glm::vec3(0.0f, -movementSpeed, 0.0f));
//             break;
//         case GLFW_KEY_D:
//             MainCamera->translate(glm::vec3(+movementSpeed, 0.0f, 0.0f));
//             break;
//         case GLFW_KEY_LEFT_SHIFT:
//             MainCamera->translate(glm::vec3(0.0f, 0.0f, -movementSpeed));
//             break;
//         case GLFW_KEY_LEFT_CONTROL:
//             MainCamera->translate(glm::vec3(0.0f, 0.0f, +movementSpeed));
//             break;
//         //* Rotating:
//         case GLFW_KEY_UP:
//             MainCamera->rotate(glm::vec3(-rotateSpeed, 0.0f, 0.0f));
//             break;
//         case GLFW_KEY_DOWN:
//             MainCamera->rotate(glm::vec3(+rotateSpeed, 0.0f, 0.0f));
//             break;
//         case GLFW_KEY_LEFT:
//             MainCamera->rotate(glm::vec3(0.0f, -rotateSpeed, 0.0f));
//             break;
//         case GLFW_KEY_RIGHT:
//             MainCamera->rotate(glm::vec3(0.0f, +rotateSpeed, 0.0f));
//             break;
//         case GLFW_KEY_R:
//             MainCamera->rotate(glm::vec3(0.0f, 0.0f, -rotateSpeed));
//             break;
//         case GLFW_KEY_T:
//             MainCamera->rotate(glm::vec3(0.0f, 0.0f, +rotateSpeed));
//             break;
//         //* Scaling:
//         case GLFW_KEY_Q:
//             MainCamera->scale(
//                 glm::vec3(-scalingRate, -scalingRate, -scalingRate));
//             break;
//         case GLFW_KEY_E:
//             MainCamera->scale(glm::vec3(scalingRate, scalingRate, scalingRate));
//             break;
//         //* Zooming:
//         case GLFW_KEY_Z:
//             FIELD_OF_VIEW -= zoomRate;
//             break;
//         case GLFW_KEY_X:
//             FIELD_OF_VIEW += zoomRate;
//             break;
//     }

//     //? Debug: What are the details of our model?
//     if (action == GLFW_PRESS) {
//         cout << "Tx"
//              << "\t"
//              << "Ty"
//              << "\t"
//              << "Tz"
//              << "\t"
//              << "thetaX"
//              << "\t"
//              << "thetaY"
//              << "\t"
//              << "thetaZ"
//              << "\t"
//              << "Sx"
//              << "\t"
//              << "Sy"
//              << "\t"
//              << "Sz"
//              << "\t" << endl;
//         cout << MainCamera->getPosition().x << "\t"
//              << MainCamera->getPosition().y << "\t"
//              << MainCamera->getPosition().z << "\t"
//              << MainCamera->getRotation().x << "\t"
//              << MainCamera->getRotation().y << "\t"
//              << MainCamera->getRotation().z << "\t" << MainCamera->getScale().x
//              << "\t" << MainCamera->getScale().y << "\t\t"
//              << MainCamera->getScale().z << "\t" << endl;
//     }
// }

// GLFWwindow* createWindow() {
//     //* Create a windowed mode window and its OpenGL context
//     GLFWwindow* window = glfwCreateWindow(int(WINDOW_WIDTH), int(WINDOW_HEIGHT),
//                                           "U w U", NULL, NULL);
//     if (!window) {
//         glfwTerminate();
//         return NULL;
//     }
//     //* Make the window's context current
//     glfwMakeContextCurrent(window);
//     gladLoadGL();
//     glEnable(GL_DEPTH_TEST);
//     return window;
// }

// GLuint createShaderProgram() {
//     GLuint shaderProgram = glCreateProgram();

//     //* Load the shader files
//     fstream vertSrc("Shaders/sample.vert");
//     fstream fragSrc("Shaders/sample.frag");
//     stringstream vertBuff;
//     stringstream fragBuff;
//     //* Add the file stream to the string stream
//     vertBuff << vertSrc.rdbuf();
//     fragBuff << fragSrc.rdbuf();
//     //* Convert the stream to a char array
//     string vertS          = vertBuff.str();
//     string fragS          = fragBuff.str();
//     const char* v         = vertS.c_str();
//     const char* f         = fragS.c_str();
//     GLuint vertexShader   = glCreateShader(GL_VERTEX_SHADER);
//     GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//     glShaderSource(vertexShader, 1, &v, NULL);
//     glShaderSource(fragmentShader, 1, &f, NULL);
//     glCompileShader(vertexShader);
//     glCompileShader(fragmentShader);

//     glAttachShader(shaderProgram, vertexShader);
//     glAttachShader(shaderProgram, fragmentShader);

//     return shaderProgram;
// }

// int main(void) {
//     //* - - - - - GLFW SETUP - - - - -
//     //* Initialize the library
//     if (!glfwInit()) return -1;

//     GLFWwindow* window = createWindow();
//     if (window == NULL)
//         cout << "[ERROR]: FAILED TO CREATE WINDOW!";
//     else

//         cout << "[#-----]" << endl;
//     //* - - - - - END OF GLFW SETUP - - - - -

//     //* - - - - - INSTANTIATE MODELS - - - - -
//     vector<Model3D*> Models;
//     Models.push_back(
//         new Model3D("AyayaCube", "Model/AyayaCube.obj", "Model/Ayaya.png"));

//     cout << "[##----]" << endl;
//     //* - - - - - END OF INSTANTIATE MODELS - - - - -

//     //* - - - - - BASIC INPUT - - - - -
//     glfwSetKeyCallback(window, Key_Callback);
//     //* - - - - - END OF BASIC INPUT - - - - -

//     //* - - - - - SHADERS - - - - -
//     //* Create and link the shader program
//     GLuint shaderProgram = createShaderProgram();
//     glLinkProgram(shaderProgram);

//     cout << "[###---]" << endl;
//     //* - - - - - END OF SHADERS - - - - -

//     //* - - - - - UV DATA - - - - -
//     //! Sample only for AYAYA CUBE
//     Models[0]->getTexture()->setUVData({0.f, 1.f, 0.f, 0.f, 1.f, 1.f, 1.f, 0.f,
//                                         1.f, 1.f, 1.f, 0.f, 0.f, 1.f, 0.f,
//                                         0.f});

//     cout << "[####--]" << endl;
//     //* - - - - - END OF UV DATA - - - - -

//     //* - - - - - CAMERA SETUP - - - - -
//     MainCamera = new Camera("Main Camera");

//     cout << "[#####-]" << endl;
//     //* - - - - - END OF CAMERA SETUP - - - - -

//     //* - - - - - MODEL LOADING - - - - -
//     //* Load All Models
//     for (Model3D* model : Models) {
//         if (!model->checkIfLoaded()) {
//             cout << "3D Model Failed to Load : " << model->getModelName()
//                  << endl;
//         } else {
//             model->initializeModel();
//         }
//     }

//     cout << "[######]" << endl;
//     //* - - - - - END OF MODEL LOADING - - - - -

//     /* Loop until the user closes the window */
//     while (!glfwWindowShouldClose(window)) {
//         //* - - - - - CAMERA - - - - -
//         float x_mod = 0.0f;
//         MainCamera->moveCamera(glm::vec3(x_mod, 0, 10.f));
//         //* - - - - - END OF CAMERA - - - - -

//         /* Render here */
//         //* Clear the window.
//         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//         unsigned int projectionLoc =
//             glGetUniformLocation(shaderProgram, "projection");
//         glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,
//                            glm::value_ptr(projectionMatrix));

//         unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
//         glUniformMatrix4fv(viewLoc, 1, GL_FALSE,
//                            glm::value_ptr(MainCamera->getViewMatrix()));

//         for (Model3D* model : Models) {
//             unsigned int transformLoc =
//                 glGetUniformLocation(shaderProgram, "transform");
//             glUniformMatrix4fv(
//                 transformLoc, 1, GL_FALSE,
//                 glm::value_ptr(model->getTransformationMatrix()));
//         }

//         //* - - - - - END OF MODEL MOVEMENT - - - - -

//         for (Model3D* model : Models) {
//             model->draw(shaderProgram);
//         }

//         //* - - - - - SHADER RENDERING - - - - -

//         //* Swap front and back buffers
//         glfwSwapBuffers(window);
//         //* Poll for and process events
//         glfwPollEvents();
//     }

//     //* Free up the memory we've used.
//     for (Model3D* model : Models) {
//         model->cleanUp();
//     }

//     glfwTerminate();
//     return 0;
// }
