#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream> //stringstream
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glewInit();

	std::cout << glGetString(GL_VERSION) << std::endl;

	{
		float positions[] = {
			100.0f, 100.0f, 0.0f, 0.0f, //0
			200.0f, 100.0f, 1.0f, 0.0f, //1
			200.0f, 200.0f, 1.0f, 1.0f, //2
			100.0f, 200.0f, 0.0f, 1.0f  //3
		};

		unsigned int indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		//Creating a triangle

		VertexArray va;
		VertexBuffer vb(positions, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);


		IndexBuffer ib(indices, 6);

		//intro to projection, we just have an orthographic projection matrix here
		glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f); //4:3 aspect ratio
		glm::mat4 view = glm::translate(glm::mat4(1.0), glm::vec3(-100, 0, 0));
		glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(200, 200, 0));
		glm::mat4 mvp = proj * view * model;

		Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		shader.setUniform4f("u_Color", 0.0f, 0.0f, 0.5f, 1.0f);
		shader.setUniformMat4f("u_MVP", mvp);

		Texture texture("res/Textures/jigsaw.png");
		texture.Bind();
		shader.setUniform1i("u_Texture", 0); //because we bound the texture to TEXTURE0 (Texture.cpp > line 36)

		va.Unbind();
		shader.Unbind();
		vb.Unbind();
		ib.Unbind();

		Renderer renderer;

		float r = 0.0f;
		float increment = 0.05f;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			renderer.Clear();
			
			shader.Bind(); 
			shader.setUniform4f("u_Color", r, 0.0f, 0.5f, 1.0f);
			renderer.Draw(va, ib, shader);
			

			if (r > 1.0f)
				increment = -0.05f;
			else if (r < 0.0f)
				increment = 0.05f;

			r += increment;
			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	glfwTerminate(); 
	return 0;
}