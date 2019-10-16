#pragma once

struct VertexData
{
	glm::vec3 position;
	glm::vec2 texcode;
	glm::vec3 nomal;
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

	void loadTexture(const std::string &TextureName);
	void draw()const;

private:
	GLuint vao_;
	GLuint texture_id_;
	GLuint buffer_[2];

	//í∏ì_èÓïÒ
	std::vector<VertexData> vertex_data_;
	std::vector<GLuint> index_data_;

private:
	GLboolean loadObject(std::string ObjectName);
};

