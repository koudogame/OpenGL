#pragma once

struct VertexData
{
	glm::vec3 position;
	glm::vec2 texcode;
	glm::vec3 nomal;
};

struct Matrial
{
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 anbient;
};

class Object
{
public:
	Object();
	~Object();

private:
	Object(const Object&) = delete;
	Object& operator=(const Object&) = delete;

public:
	GLboolean createVertexData(std::string ObjectName);
	GLboolean createMatrialData(std::string ObjectMatrialName);
	void loadTexture(const std::string &TextureName);
	void draw()const;

private:
	GLuint vao_;
	GLuint texture_id_;
	GLuint buffer_[2];

	//í∏ì_èÓïÒ
	std::vector<VertexData> vertex_data_;
	std::unordered_map<std::string,std::vector<GLuint>> index_data_;
	std::unordered_map<std::string, Matrial> matrial_data_;

private:
	GLboolean loadObject(std::string ObjectName);
};

