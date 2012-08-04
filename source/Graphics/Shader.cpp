#include "Shader.h"
#include "Util/Util.h"
#include <MEngine.h>

Shader::Shader(const char* vertexName, const char* fragmentName)
: m_FX(0)
, m_VertShad(0)
, m_PixShad(0)
{
	MEngine* engine = MEngine::getInstance();
	MSystemContext* system = engine->getSystemContext();

	char pVertexName[0xff];
	getGlobalFilename(pVertexName, system->getWorkingDirectory(), vertexName);
	char pFragmentName[0xff];
	getGlobalFilename(pFragmentName, system->getWorkingDirectory(), fragmentName);

	// Load the vertex shader
	MFile* vertFP = M_fopen(pVertexName, "rb+");
	M_fseek(vertFP, 0L, SEEK_END);
	long vsize = M_ftell(vertFP);
	M_fseek(vertFP, 0L, SEEK_SET);

	char* vertShader = new char[vsize+1];
	M_fread(vertShader, 1, vsize, vertFP);
	M_fclose(vertFP);
	vertShader[vsize] = 0;

	// Load the fragment shader
	MFile* fragFP = M_fopen(pFragmentName, "rb+");
	M_fseek(fragFP, 0L, SEEK_END);
	long fsize = M_ftell(fragFP);
	M_fseek(fragFP, 0L, SEEK_SET);

	char* fragShader = new char[fsize+1];
	M_fread(fragShader, 1, fsize, fragFP);
	M_fclose(fragFP);
	fragShader[fsize] = 0;

	if(MRenderingContext* render = engine->getRenderingContext())
	{
		render->createVertexShader(&m_VertShad);
		render->sendShaderSource(m_VertShad, vertShader);

		render->createPixelShader(&m_PixShad);
		render->sendShaderSource(m_PixShad, fragShader);

		render->createFX(&m_FX, m_VertShad, m_PixShad);
	}

	delete[] vertShader;
	delete[] fragShader;
}

void Shader::Apply()
{
	if(m_FX == 0)
		return;

	MEngine* engine = MEngine::getInstance();
	if(MRenderingContext* render = engine->getRenderingContext())
		render->bindFX(m_FX);
}

void Shader::Clear()
{
	if(m_FX == 0)
		return;

	MEngine* engine = MEngine::getInstance();
	if(MRenderingContext* render = engine->getRenderingContext())
		render->bindFX(0);
}

void Shader::SetValue(const char* name, int val) const
{
    MEngine* engine = MEngine::getInstance();
    if(MRenderingContext* render = engine->getRenderingContext())
	render->sendUniformInt(m_FX , name, &val, 1);
}


void Shader::SetValue(const char* name, float val) const
{
    MEngine* engine = MEngine::getInstance();
    if(MRenderingContext* render = engine->getRenderingContext())
	render->sendUniformFloat(m_FX , name, &val, 1);
}
