#pragma once

class IndexBuffer
{
private:
	unsigned int m_RendererID; //unique ID (integer) that specifies the buffer. This is the numeric ID for the OpenGL Renderer.
	unsigned int m_Count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count); //size means byte and count means the number of elements
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }
};