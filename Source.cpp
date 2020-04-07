#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader_s.h>

int width = 800;
int height = 600;

void framebuffer_size_callback(GLFWwindow* window, int wid, int hgt) {
    width = wid;
    height = hgt;
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

}

unsigned short Pmode = 0; //1 is solid, 0 is wireframe, 2 is point
bool canChange = true;
//this is for input
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && canChange) {
        canChange = false;
        if (Pmode == 0) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            Pmode++;
        }
        else if (Pmode == 1) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            Pmode++;
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            Pmode = 0;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
        canChange = true;
    }
}

int main()
{
    //Init glfw3
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //For MacOSx
    #endif

    //creating the window
    GLFWwindow* window = glfwCreateWindow(width, height, "PongGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    //initalize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, width, height);

    //Calls framebuffer_size_callback whenever window is resized
    

    //sets the clearing color
    //note: args can be in 1.0f - 0.0f; RGBA
    glClearColor(1,1,1,0);

    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    Shader shader("texture.vs", "texture.fs");

    //The window loop
    while (!glfwWindowShouldClose(window))
    {
        //input
        processInput(window);
        


        //put rendering under here...
        //clears the screen
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();



        //check and call events and swaps the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //end program
    glfwTerminate();
    return 0;
}