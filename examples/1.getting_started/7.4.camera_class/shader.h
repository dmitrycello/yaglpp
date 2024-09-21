/*LearnOpenGL: not really necessary while using YAGL++, included just in the context of the tutorial*/
class Shader : public gl::Program
{
public:
    /*LearnOpenGL: constructor with 2 resource ids to keep application portable*/
    Shader(int vsid, int fsid)
    {
        gl::VertexShader vertexShader(vsid);
        vertexShader.compileShader();
        gl::FragmentShader fragmentShader(fsid);
        fragmentShader.compileShader();
        attachShaders(vertexShader, fragmentShader);
        linkProgram();
    }
    /*LearnOpenGL: set shader's boolean uniform*/
    void setBool(const GLchar* name, GLboolean value)
    {
        getUniformLocation(name).uniform(value);
    }
    /*LearnOpenGL: set shader's integer uniform*/
    void setInt(const GLchar* name, GLint value)
    {
        getUniformLocation(name).uniform(value);
    }
    /*LearnOpenGL: set shader's float uniform*/
    void setFloat(const GLchar* name, GLfloat value)
    {
        getUniformLocation(name).uniform(value);
    }
    /*LearnOpenGL: (1) set shader's vec2 uniform*/
    void setVec2(const GLchar* name, const glm::vec2& value)
    {
        getUniformLocation(name).uniform(1, &value);
    }
    /*LearnOpenGL: (2) set shader's vec2 uniform*/
    void setVec2(const GLchar* name, GLfloat x, GLfloat y)
    {
        getUniformLocation(name).uniform(x, y);
    }
    /*LearnOpenGL: (1) set shader's vec3 uniform*/
    void setVec3(const GLchar* name, const glm::vec3& value)
    {
        getUniformLocation(name).uniform(1, &value);
    }
    /*LearnOpenGL: (2) set shader's vec3 uniform*/
    void setVec3(const GLchar* name, GLfloat x, GLfloat y, GLfloat z)
    {
        getUniformLocation(name).uniform(x, y, z);
    }
    /*LearnOpenGL: (1) set shader's vec4 uniform*/
    void setVec4(const GLchar* name, const glm::vec4& value)
    {
        getUniformLocation(name).uniform(1, &value);
    }
    /*LearnOpenGL: (2) set shader's vec4 uniform*/
    void setVec4(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
    {
        getUniformLocation(name).uniform(x, y, z, w);
    }
    /*LearnOpenGL: set shader's float uniform*/
    void setMat2(const GLchar* name, const glm::mat2& mat)
    {
        getUniformLocation(name).uniformMatrix2(1, GL_FALSE, &mat[0][0]);
    }
    /*LearnOpenGL: set shader's float uniform*/
    void setMat3(const GLchar* name, const glm::mat3& mat)
    {
        getUniformLocation(name).uniformMatrix3(1, GL_FALSE, &mat[0][0]);
    }
    /*LearnOpenGL: set shader's float uniform*/
    void setMat4(const GLchar* name, const glm::mat4& mat)
    {
        getUniformLocation(name).uniformMatrix4(1, GL_FALSE, &mat[0][0]);
    }
};
