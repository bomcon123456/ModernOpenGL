#ifndef MESH_H
#define MESH_H
#include "Core.h"

class Mesh
{
  public:
    Mesh();
    ~Mesh();

    void CreateMesh(float* vertices, unsigned int* indices, unsigned int numOfVerts, unsigned int numOfIndices);
    void RenderMesh();
    void DeleteMesh();

  private:
    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_IBO;
    unsigned int m_indexCount;
    unsigned int PositionSlot = 0;
    unsigned int UVSlot = 1;
};

#endif