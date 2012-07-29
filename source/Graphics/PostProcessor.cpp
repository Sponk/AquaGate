#include "PostProcessor.h"

#include "Util/Util.h"

PostProcessor::PostProcessor()
    : m_BufferID(0)
    , m_ColourTexID(0)
    , m_DepthTexID(0)
    , m_Shader(0)
{
    MRenderingContext * render = MEngine::getInstance()->getRenderingContext();
    MSystemContext * system = MEngine::getInstance()->getSystemContext();
    // screen size
    unsigned int screenWidth = 0;
    unsigned int screenHeight = 0;
    system->getScreenSize(&screenWidth, &screenHeight);

    m_Resolution = Util::Pow2(max(screenWidth, screenHeight));

    // create frame buffer
    render->createFrameBuffer(&m_BufferID);

    // create render textures
    render->createTexture(&m_ColourTexID);
    render->bindTexture(m_ColourTexID);
    render->setTextureFilterMode(M_TEX_FILTER_LINEAR, M_TEX_FILTER_LINEAR);
    render->setTextureUWrapMode(M_WRAP_CLAMP);
    render->setTextureVWrapMode(M_WRAP_CLAMP);
    render->texImage(0, m_Resolution, m_Resolution, M_UBYTE, M_RGB, 0);

    render->createTexture(&m_DepthTexID);
    render->bindTexture(m_DepthTexID);
    render->setTextureFilterMode(M_TEX_FILTER_NEAREST, M_TEX_FILTER_NEAREST);
    render->texImage(0, m_Resolution, m_Resolution, M_UBYTE, M_DEPTH, 0);
}

bool PostProcessor::Render()
{
    if(!m_Shader)
        return false;

    MEngine * engine = MEngine::getInstance(); // get the engine instance
    MRenderingContext * render = engine->getRenderingContext(); // get the rendering context
    MSystemContext * system = engine->getSystemContext();

    if(strcmp(engine->getRenderer()->getName(), "FixedRenderer") == 0)
        return false;


    // get level
    MLevel * level = MEngine::getInstance()->getLevel();
    if(! level)
        return false;

    // get current scene
    MScene * scene = level->getCurrentScene();
    if(! scene)
        return false;

    render->enableDepthTest();

    // get camera
    MOCamera * camera = scene->getCameraByIndex(scene->getCurrentCamera());

    // update listener
    camera->updateListener();

    // enable camera with current screen ratio
    camera->enable();
    render->setClearColor(*camera->getClearColor());


    // screen size
    unsigned int screenWidth = 0;
    unsigned int screenHeight = 0;
    system->getScreenSize(&screenWidth, &screenHeight);


    // render to texture
    render->bindFrameBuffer(m_BufferID);
    render->attachFrameBufferTexture(M_ATTACH_COLOR0, m_ColourTexID);
    render->attachFrameBufferTexture(M_ATTACH_DEPTH, m_DepthTexID);
    render->setViewport(0, 0, m_Resolution, m_Resolution); // change viewport


    render->clear(M_BUFFER_COLOR | M_BUFFER_DEPTH);

    // draw the scene
    scene->draw(camera);


    // finish render to texture
    render->bindFrameBuffer(0);


    // draw the rendered textured with a shader effect
    render->setViewport(0, 0, screenWidth, screenHeight);
    render->setClearColor(MVector3(1, 0, 0));
    render->clear(M_BUFFER_COLOR | M_BUFFER_DEPTH);

    Set2D(screenWidth, screenHeight);

    m_Shader->Apply();
    render->bindTexture(m_ColourTexID);
    render->bindTexture(m_DepthTexID, 1);
    DrawQuad(MVector2((float)screenWidth, (float)screenHeight));
    m_Shader->Clear();
    false;

    return true;
}

void PostProcessor::SetShader(Shader* s)
{
    m_Shader = s;
}

void PostProcessor::Set2D(unsigned int w, unsigned int h)
{
    MRenderingContext * render = MEngine::getInstance()->getRenderingContext();
    render->setViewport(0, 0, w, h);

    // set ortho projection
    render->setMatrixMode(M_MATRIX_PROJECTION);
    render->loadIdentity();

    render->setOrthoView(0.0f, (float)w, (float)h, 0.0f, 1.0f, -1.0f);

    render->setMatrixMode(M_MATRIX_MODELVIEW);
    render->loadIdentity();
}

void PostProcessor::DrawQuad(MVector2 scale)
{
    MRenderingContext * render = MEngine::getInstance()->getRenderingContext();

    int vertexAttrib;
    int texcoordAttrib;
    static MVector2 vertices[4];
    static MVector2 texCoords[4];

    vertices[0] = MVector2(0, 0);
    vertices[1] = MVector2(0, scale.y);
    vertices[3] = MVector2(scale.x, scale.y);
    vertices[2] = MVector2(scale.x, 0);

    texCoords[0] = MVector2(0, 1);
    texCoords[1] = MVector2(0, 0);
    texCoords[3] = MVector2(1, 0);
    texCoords[2] = MVector2(1, 1);

    // projmodelview matrix
    static MMatrix4x4 ProjMatrix;
    static MMatrix4x4 ModelViewMatrix;
    static MMatrix4x4 ProjModelViewMatrix;

    render->getProjectionMatrix(&ProjMatrix);
    render->getModelViewMatrix(&ModelViewMatrix);
    ProjModelViewMatrix = ProjMatrix * ModelViewMatrix;
    render->sendUniformMatrix(m_Shader->ExposeShader(), "ProjModelViewMatrix", &ProjModelViewMatrix);

    // Texture
    int texIds[4] = { 0, 1, 2, 3 };
    render->sendUniformInt(m_Shader->ExposeShader(), "Textures", texIds, 4);

    // Vertex
    render->getAttribLocation(m_Shader->ExposeShader(), "Vertex", &vertexAttrib);
    render->setAttribPointer(vertexAttrib, M_FLOAT, 2, vertices);
    render->enableAttribArray(vertexAttrib);

    // TexCoord
    render->getAttribLocation(m_Shader->ExposeShader(), "TexCoord", &texcoordAttrib);
    render->setAttribPointer(texcoordAttrib, M_FLOAT, 2, texCoords);
    render->enableAttribArray(texcoordAttrib);

    // draw
    render->drawArray(M_PRIMITIVE_TRIANGLE_STRIP, 0, 4);

    render->disableAttribArray(vertexAttrib);
    render->disableAttribArray(texcoordAttrib);
}
