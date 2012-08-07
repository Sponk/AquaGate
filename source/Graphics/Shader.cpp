#include "Shader.h"
#include "Util/Util.h"
#include <MEngine.h>

Shader::Shader(const char* vertexName, const char* fragmentName)
: m_fx(0)
, m_vertShad(0)
, m_pixShad(0)
{
    sprintf(m_filenames[0], vertexName);
    sprintf(m_filenames[1], fragmentName);
}

void Shader::Apply()
{
    if(m_fx == 0 && !Init())
	return;
    
    MEngine* engine = MEngine::getInstance();
    if(MRenderingContext* render = engine->getRenderingContext())
	render->bindFX(m_fx);
}

void Shader::Clear()
{
    if(m_fx == 0)
	return;
    
    MEngine* engine = MEngine::getInstance();
    if(MRenderingContext* render = engine->getRenderingContext())
	render->bindFX(0);
}

void Shader::SetValue(const char* name, int val) const
{
    MEngine* engine = MEngine::getInstance();
    if(MRenderingContext* render = engine->getRenderingContext())
	render->sendUniformInt(m_fx , name, &val, 1);
}


void Shader::SetValue(const char* name, float val) const
{
    MEngine* engine = MEngine::getInstance();
    if(MRenderingContext* render = engine->getRenderingContext())
	render->sendUniformFloat(m_fx , name, &val, 1);
}

bool Shader::Init()
{
    MEngine* engine = MEngine::getInstance();
    MSystemContext* system = engine->getSystemContext();
    
    char pVertexName[0xff];
    getGlobalFilename(pVertexName, system->getWorkingDirectory(), m_filenames[0]);
    char pFragmentName[0xff];
    getGlobalFilename(pFragmentName, system->getWorkingDirectory(), m_filenames[1]);
    
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
	render->createVertexShader(&m_vertShad);
	render->sendShaderSource(m_vertShad, vertShader);
	
	render->createPixelShader(&m_pixShad);
	render->sendShaderSource(m_pixShad, fragShader);
	
	render->createFX(&m_fx, m_vertShad, m_pixShad);
    }
    
    delete[] vertShader;
    delete[] fragShader;

    return m_fx != 0;
}
