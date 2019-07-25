#include "Model.h"


Model::Model(string const path)
{
	loadModel(path);
}

Model::~Model()
{
}

void Model::Draw(Shader * shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(shader);
	}
}

void Model::loadModel(string const path)
{
	// read file via ASSIMP
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}
	// retrieve the directory path of the filepath
	directroy = path.substr(0, path.find_last_of('\\'));

	// process ASSIMP's root node recursively
	processNode(scene->mRootNode, scene);
}

// Processes a node in a recursive fashion. 
// Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
void Model::processNode(aiNode * node, const aiScene * scene)
{
	//std::cout << node->mName.data << std::endl;

	// process each mesh located at the current node
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* curMesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(curMesh, scene));
	}
	
	// after processed all of the meshes, then recursively process each of the children nodes
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

// Transform ASSIMP's aiMesh to our data struct 'Mesh'
Mesh Model::processMesh(aiMesh * mesh, const aiScene * scene)
{
	// data to fill
	vector<Vertex> tempVertices;
	vector<unsigned int> tempIndices;
	vector<Texture> tempTextures;

	glm::vec3 tempVec;
	// walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex tempVertex;

		tempVertex.Position.x = mesh->mVertices[i].x;
		tempVertex.Position.y = mesh->mVertices[i].y;
		tempVertex.Position.z = mesh->mVertices[i].z;

		tempVertex.Normal.x = mesh->mNormals[i].x;
		tempVertex.Normal.y = mesh->mNormals[i].y;
		tempVertex.Normal.z = mesh->mNormals[i].z;

		if (mesh->mTextureCoords[0]) {
			tempVertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
			tempVertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else {
			tempVertex.TexCoords = glm::vec2(0, 0);
		}

		tempVertices.push_back(tempVertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
		{
			tempIndices.push_back(mesh->mFaces[i].mIndices[j]);
		}	
	}

	return Mesh(tempVertices, tempIndices, tempTextures);
}

vector<Texture> Model::loadMaterialTextures(aiMaterial * mat, aiTextureType type, string typeName)
{
	vector<Texture> textures;

	return textures;
}
