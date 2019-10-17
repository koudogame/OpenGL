#pragma once
#include "Object.h"
class Model
{
public:
	Model();
	~Model();

public:
	bool init();
	void updata();
	void draw();

private:
	std::unique_ptr<Object> object_;
	glm::mat4 position_;
	GLuint program_;

	GLuint textrue_location_;
	GLuint view_location_;
	GLuint projection_location_;
	GLuint position_location_;

	template<typename T>
	struct VertexData
	{
		GLuint location;
		std::vector<T> vertex;
		GLint size;

		VertexData(GLuint Location, std::vector<T>& Vertex, GLint Size)
		{
			location = Location;
			vertex.resize(Vertex.size());
			vertex.swap(Vertex);
			size = Size;
		}
	};

	std::vector<VertexData<GLfloat>> vertex_data_;
	std::vector<VertexData<GLint>> index_data_;

private:
	GLuint getUniformLocation(std::string VariableName);
	void loadVertexData(std::string ObjectName);
};

