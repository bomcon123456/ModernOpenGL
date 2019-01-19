#include "Mesh.h"

Mesh::Mesh() : m_VAO(0), m_VBO(0), m_IBO(0), m_indexCount(0)
{
}

void Mesh::CreateMesh(float *vertices, unsigned int *indices, unsigned int numOfVerts, unsigned int numOfIndices)
{
    m_indexCount = numOfIndices;

    GLCall(glGenVertexArrays(1, &m_VAO));
    GLCall(glGenBuffers(1, &m_VBO));
    GLCall(glGenBuffers(1, &m_IBO));

    GLCall(glBindVertexArray(m_VAO));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
    GLCall(glBufferData(GL_ARRAY_BUFFER, numOfVerts * sizeof(vertices[0]), vertices, GL_STATIC_DRAW));

    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, numOfIndices * sizeof(indices[0]), indices, GL_STATIC_DRAW));

    GLCall(glVertexAttribPointer(PositionSlot, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0));
    GLCall(glEnableVertexAttribArray(PositionSlot));

    GLCall(glVertexAttribPointer(UVSlot, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 3)));
    GLCall(glEnableVertexAttribArray(UVSlot));

    GLCall(glVertexAttribPointer(NormalSlot, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 5)));
    GLCall(glEnableVertexAttribArray(NormalSlot));

    GLCall(glBindVertexArray(0));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void Mesh::RenderMesh()
{
    GLCall(glBindVertexArray(m_VAO));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));
    GLCall(glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0));
    GLCall(glBindVertexArray(0));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void Mesh::DeleteMesh()
{
    if (m_IBO != 0)
    {
        GLCall(glDeleteBuffers(1, &m_IBO));
        m_IBO = 0;
    }

    if (m_VBO != 0)
    {
        GLCall(glDeleteBuffers(1, &m_VBO));
        m_VBO = 0;
    }

    if (m_VAO != 0)
    {
        GLCall(glDeleteVertexArrays(1, &m_VAO));
        m_VAO = 0;
    }
}

Mesh::~Mesh()
{
    DeleteMesh();
}
