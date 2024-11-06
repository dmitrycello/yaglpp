// mesh.h
#pragma once
#define MAX_BONE_INFLUENCE 4
using namespace std;

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
	// bone indexes which will influence this vertex
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	// weights from each bone
	float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture {
    gl::Texture2D id;
    string type;
    string path;
};

class Mesh {
public:
    // mesh Data
    vector<Vertex>       vertices;
    vector<GLuint>       indices;
    vector<Texture>      textures;
    gl::VertexArray VAO;

    // constructor
    Mesh()
    {
        VAO.genVertexArray(GL_FALSE); // no autodelete
        VBO.genBuffer(GL_FALSE);
        EBO.genBuffer(GL_FALSE);
    }

    Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures) : Mesh()
    {
        Load(vertices, indices, textures);
    }

    // load the mesh
    void Load(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        // now that we have all the required data, set the vertex buffers and its attribute pointers.
        setupMesh();
    }

    // render the mesh
    void Draw(Shader &shader) 
    {
        // bind appropriate textures
        unsigned int diffuseNr  = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr   = 1;
        unsigned int heightNr   = 1;
        for(unsigned int i = 0; i < textures.size(); i++)
        {
            gl::activeTexture(i);
            // retrieve texture number (the N in diffuse_textureN)
            string number;
            string name = textures[i].type;
            if(name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if(name == "texture_specular")
                number = std::to_string(specularNr++); // transfer unsigned int to string
            else if(name == "texture_normal")
                number = std::to_string(normalNr++); // transfer unsigned int to string
             else if(name == "texture_height")
                number = std::to_string(heightNr++); // transfer unsigned int to string

            // now set the sampler to the correct texture unit
            gl::Uniform uSampler(shader, (name + number).c_str());
            if (uSampler.uniformLocation) uSampler.uniformTextureUnit(i);
            // and finally bind the texture
            textures[i].id.bindTexture();
        }
        
        // draw mesh
        VAO.bindVertexArray();
        gl::drawElements(gl::PrimitiveMode::Triangles, (GLsizei)indices.size(), gl::PrimitiveType::UnsignedInt, 0);
        VAO.unbindVertexArray();

        // always good practice to set everything back to defaults once configured.
        gl::activeTexture(0);
    }

private:
    // render data
    gl::ArrayBuffer VBO;
    gl::ElementArrayBuffer EBO;

    // initializes all the buffer objects/arrays
    void setupMesh()
    {
        // load data into vertex buffers
        // A great thing about structs is that their memory layout is sequential for all its items.
        // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
        // again translates to 3/2 floats which translates to a byte array.
        VAO.bindVertexArray();
        VBO.bufferData(vertices.size() * sizeof(Vertex), &vertices[0], gl::BufferUsage::StaticDraw);
        EBO.bufferData(indices.size() * sizeof(GLuint), &indices[0], gl::BufferUsage::StaticDraw);

        // set the vertex attribute pointers
        gl::VertexAttrib aPos(0), aNormal(1), aTexCoords(2), aTangent(3), aBitangent(4), aIds(5), aWeights(6);

        // vertex Positions
        aPos.enableVertexAttribArray();
        aPos.vertexAttribPointer(gl::VertexAttribSize::Triple, gl::VertexAttribType::Float,
            GL_FALSE, sizeof(Vertex), 0);

        // vertex normals
        aNormal.enableVertexAttribArray();
        aNormal.vertexAttribPointer(gl::VertexAttribSize::Triple, gl::VertexAttribType::Float,
            GL_FALSE, sizeof(Vertex), offsetof(Vertex, Normal));

        // vertex texture coords
        aTexCoords.enableVertexAttribArray();
        aTexCoords.vertexAttribPointer(gl::VertexAttribSize::Double, gl::VertexAttribType::Float,
            GL_FALSE, sizeof(Vertex), offsetof(Vertex, TexCoords));

        // vertex tangent
        aTangent.enableVertexAttribArray();
        aTangent.vertexAttribPointer(gl::VertexAttribSize::Triple, gl::VertexAttribType::Float,
            GL_FALSE, sizeof(Vertex), offsetof(Vertex, Tangent));

        // vertex bitangent
        aBitangent.enableVertexAttribArray();
        aBitangent.vertexAttribPointer(gl::VertexAttribSize::Triple, gl::VertexAttribType::Float,
            GL_FALSE, sizeof(Vertex), offsetof(Vertex, Bitangent));

		// ids
        aIds.enableVertexAttribArray();
        aIds.vertexAttribIPointer(gl::VertexAttribISize::Quadruple, gl::VertexAttribIType::Int,
            sizeof(Vertex), offsetof(Vertex, m_BoneIDs));

		// weights
        aWeights.enableVertexAttribArray();
        aWeights.vertexAttribPointer(gl::VertexAttribSize::Quadruple, gl::VertexAttribType::Float,
            GL_FALSE, sizeof(Vertex), offsetof(Vertex, m_Weights));

        VAO.unbindVertexArray();
    }
};
