#ifndef __POST_PROCESSOR_H__
#define __POST_PROCESSOR_H__

#include "Shader.h"

#include <MEngine.h>

class PostProcessor
{
public:
    PostProcessor();

    bool Render();

    void SetShader(Shader* s);
    const Shader* GetShader() { return m_Shader; }
private:
    void Set2D(unsigned int w, unsigned int h);
    void DrawQuad(MVector2 scale);

    unsigned int m_BufferID;
    unsigned int m_ColourTexID;
    unsigned int m_DepthTexID;
    Shader*      m_Shader;
	int			 m_Resolution;
};

#endif/*__POST_PROCESSOR_H__*/
