#include "TestTexture2D.h"
#include "GLErrorManager.h"
#include "imgui/imgui.h"
#include "Renderer.h"


namespace test{

	TestTexture2D::TestTexture2D()
		: m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0),
		m_proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)), //4:3 aspect ratio
		m_view(glm::translate(glm::mat4(1.0), glm::vec3(0, 0, 0)))
	{
		float positions[] = {
			-50.0f, -50.0f, 0.0f, 0.0f, //0
			 50.0f, -50.0f, 1.0f, 0.0f, //1
			 50.0f,  50.0f, 1.0f, 1.0f, //2
			-50.0f,  50.0f, 0.0f, 1.0f  //3
		};

		unsigned int indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


		
		m_VAO = std::make_unique<VertexArray>();

		//Creating a triangle

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);

		m_VAO->AddBuffer(*m_VertexBuffer, layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);


		//intro to projection, we just have an orthographic projection matrix here
		

		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_Shader->Bind();
		m_Shader->setUniform4f("u_Color", 0.0f, 0.0f, 0.5f, 1.0f);


		m_Texture = std::make_unique<Texture>("res/Textures/jigsaw.png");
		m_Shader->setUniform1i("u_Texture", 0); //because we bound the texture to TEXTURE0 (Texture.cpp > line 36)
	}

	TestTexture2D::~TestTexture2D()
	{

	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{

	}

	void TestTexture2D::OnRender()
	{
		Renderer renderer;
		m_Texture->Bind();

		

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0), m_TranslationA);
			glm::mat4 mvp = m_proj * m_view * model;
			m_Shader->Bind();
			m_Shader->setUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0), m_TranslationB);
			glm::mat4 mvp = m_proj * m_view * model;
			m_Shader->Bind();
			m_Shader->setUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::SliderFloat3("TranslationA", &m_TranslationA.x, 0.0f, 960.0f);
		ImGui::SliderFloat3("TranslationB", &m_TranslationB.x, 0.0f, 960.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}