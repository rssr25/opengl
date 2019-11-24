#pragma once
#include "Test.h"
#include <memory>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"


namespace test{

	class TestTexture2D: public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;
		glm::vec3 m_TranslationA, m_TranslationB;
		glm::mat4 m_proj, m_view;
	};
}