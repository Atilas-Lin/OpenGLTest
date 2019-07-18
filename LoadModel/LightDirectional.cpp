#include "LightDirectional.h"


LightDirectional::LightDirectional(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color) :
	position(_position), angles(_angles), color(_color)
{
	UpdateDirecrion();
}

LightDirectional::~LightDirectional()
{
}

void LightDirectional::UpdateDirecrion() {
	direction = glm::vec3(0, 0, 1.0f); // pointing to z (forward)
	direction = glm::rotateZ(direction, angles.z);
	direction = glm::rotateX(direction, angles.x);
	direction = glm::rotateY(direction, angles.y);
	direction = -1.0f * direction; // origion point aim to light point
}

