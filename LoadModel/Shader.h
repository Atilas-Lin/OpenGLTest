#pragma once
#include<string>
#include<glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);

	std::string vertexString;
	std::string fragmentString;
	const char* vertexSource;
	const char* fragmentSource;
	unsigned int ID; //Shader Program ID
	void use();
	/*uinform setter*/
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec4(const std::string &name, float x, float y, float z, float w);
	void setMat4(const std::string &name, const glm::mat4 &mat) const;
private:
	void checkCompileErrors(unsigned int ID, std::string type);
};

