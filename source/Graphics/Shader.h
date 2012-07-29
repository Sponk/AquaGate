#ifndef __SHADER_H__
#define __SHADER_H__

class Shader
{
public:
	Shader(const char* vertexName, const char* fragmentName);

	void Apply();
	void Clear();

	unsigned int ExposeShader() { return m_FX; }

private:
	
	unsigned int m_FX;
	unsigned int m_VertShad;
	unsigned int m_PixShad;
};

#endif /*__SHADER_H__*/
