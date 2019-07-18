#pragma once

#include "Shader.h"

class Material
{
public:
	Shader *shader;
	unsigned int diffuse;
	unsigned int specular;
	unsigned int emission;
	glm::vec3 ambient;
	float shininess;

	Material(Shader* _shader, unsigned int _diffuse, unsigned int _specular, unsigned int _emission, glm::vec3 _ambient, float _shininess);
	~Material();
};

