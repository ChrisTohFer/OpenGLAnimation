#include "model_import.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <iostream>

Mesh import_fbx(const char* filepath)
{
    Assimp::Importer importer;
    std::string full_path("../assets/");
    full_path += filepath;
    const aiScene* scene = importer.ReadFile(full_path, aiProcess_Triangulate | aiProcess_FlipUVs);

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indicies;

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return Mesh(vertices, indicies);
    }

    aiMesh* imported_mesh = scene->mMeshes[0];
    const auto num_vertices = imported_mesh->mNumVertices;
    vertices.reserve(num_vertices);
    for (int i = 0; i < num_vertices; ++i)
    {
        auto vertex = imported_mesh->mVertices[i];
        auto normal = imported_mesh->mNormals[i];
        vertices.push_back(Vertex{ glm::vec3(vertex.x, vertex.y, vertex.z), glm::vec3(normal.x, normal.y, normal.z) });
    }
    const auto num_faces = imported_mesh->mNumFaces;
    vertices.reserve(num_vertices * 3);
    for (int i = 0; i < num_faces; ++i)
    {
        auto face = imported_mesh->mFaces[i];
        indicies.push_back(face.mIndices[0]);
        indicies.push_back(face.mIndices[1]);
        indicies.push_back(face.mIndices[2]);
    }

    return Mesh(vertices, indicies);
}
