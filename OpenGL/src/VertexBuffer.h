#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID; //unique ID (integer) that specifies the buffer. This is the numeric ID for the OpenGL Renderer.

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};