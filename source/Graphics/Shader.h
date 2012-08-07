#ifndef __SHADER_H__
#define __SHADER_H__

class Shader
{
public:
    Shader(const char* vertexName, const char* fragmentName);
    
    void Apply();
    void Clear();
    
    unsigned int ExposeShader() { return m_fx; }
    
    void SetValue(const char* name, int val) const;
    void SetValue(const char* name, float val) const;
private:
    bool Init();
    
    unsigned int m_fx;
    unsigned int m_vertShad;
    unsigned int m_pixShad;
    
    char         m_filenames[2][256];
};

#endif /*__SHADER_H__*/
