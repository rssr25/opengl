#include "Renderer.h"
#include <iostream>
#include "GLErrorManager.h"

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	GLCall(glClearColor(1.0, 1.0, 1.0, 1.0));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const 
{
	va.Bind();
	ib.Bind();
	shader.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}