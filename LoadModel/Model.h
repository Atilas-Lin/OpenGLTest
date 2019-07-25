#pragma once
#include "Mesh.h"
#include "Shader.h"
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
using namespace std;

class Model
{
public:
	Model(string const path);
	~Model();
	void Draw(Shader *shader);

private:
	/* Model data */
	vector<Mesh> meshes;
	string directroy;
	/* Function */
	void loadModel(string const path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};

