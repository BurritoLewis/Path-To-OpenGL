#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "shader.h"
#include "VertexBufferLayout.h"






int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
  
    glfwSwapInterval(1);


    if (glewInit() != GLEW_OK)
        std::cout << "glue Error" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        float positions[] = {
            -0.5f, -0.5f,  
             0.5f, -0.5f,  
             0.5f,  0.5f,  
            -0.5f,  0.5f
        };

        unsigned int indecies[] = {
            0,1,2,
            2,3,0
        };

        
        VertexArray va;
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));

        VertexBufferLayout layout;
		layout.Push<float>(2);
        va.AddBuffer(vb,layout);
        

        IndexBuffer ib(indecies, 6);

        Shader shader("res/shaders/Basic.glsl");
        shader.Bind();

        shader.SetUniform4f("u_color", 0.0f, 0.0f, 1.0f, 1.0f);

        Renderer renderer;

        vb.Unbind();
        ib.Unbind(); 
        va.Unbind();
        shader.Unbind();

        float r = 0.0f;

        float increment = 0.5f;



        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            r += increment;
            /* Render here */
            renderer.Clear();

            shader.SetUniform4f("u_Color", r, 0.0f, 1.0f, 1.0f);

            renderer.Draw(va,ib,shader);

            if (r > 1.0f)
                increment = -0.09f;

            else if (r < 0.0f)
                increment = 0.09f;



            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        
    }

    glfwTerminate();
    return 0;
}