#include "stdafx.h"
#include "Object.h"


Object::Object()
{
}

GLboolean Object::createVertexData(std::string ObjectName)
{
	if (!loadObject(ObjectName))
		return false;

	//���_�o�b�t�@�̍쐬
	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);
	//�o�b�t�@�̍쐬
	glGenBuffers(1, &vertex_buffer_);
	glBufferData(GL_ARRAY_BUFFER, vertex_data_.size() * sizeof(VertexData), vertex_data_.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	//�֘A�t��
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLbyte*)(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLbyte*)(sizeof(VertexData::position)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLbyte*)(sizeof(VertexData::position) + sizeof(VertexData::texcode)));

	//�C���f�b�N�X�����֘A�t����
	glGenBuffers(1, &index_buffer_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_data_.size() * sizeof(GLuint), index_data_.data(), GL_STATIC_DRAW);

	return true;
}

void Object::loadTexture(const std::string &TextureName)
{
	//�e�N�X�`���̓ǂݍ���
	glGenTextures(1, &texture_id_);
	//�o�b�t�@�[�̑I��
	glBindTexture(GL_TEXTURE_2D, texture_id_);
	//�e�N�X�`���̓ǂݍ���
	cv::Mat img = cv::imread(TextureName.c_str(), cv::IMREAD_UNCHANGED);
	GLuint internalformat = GL_RGBA;
	GLuint sourceformat = GL_BGRA_EXT;

	if (img.channels() == 3)
	{
		internalformat = GL_RGB;
		sourceformat = GL_BGR_EXT;
	}

	//�ǂݍ��񂾃e�N�X�`�������т���
	glTexImage2D(GL_TEXTURE_2D, 0, internalformat,
		img.size().width, img.size().height,
		0, sourceformat,
		GL_UNSIGNED_BYTE,
		img.data);

	//�p�����[�^�ݒ�
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glActiveTexture(GL_TEXTURE0);
}

Object::~Object()
{
	//���_�z��I�u�W�F�N�g���폜����
	glDeleteBuffers(1, &vao_);
	//���_�o�b�t�@�I�u�W�F�N�g���폜����
	glDeleteBuffers(1, &vertex_buffer_);
	glDeleteBuffers(1, &index_buffer_);

	//�e�N�X�`���̐ݒ����
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void Object::draw() const
{
	////���ߐݒ�
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	////�e�N�X�`���}�b�s���O��L���ɂ���
	//glEnable(GL_TEXTURE_2D);
	////�g�p�e�N�X�`���̐ݒ�
	//glBindTexture(GL_TEXTURE_2D, texture_id_);

	//�`�悷�钸�_�z��I�u�W�F�N�g���w�肷��
	glBindVertexArray(vao_);
	//�}�`�̕`��
	glDrawElements(GL_TRIANGLES, index_data_.size(), GL_UNSIGNED_INT, 0);
}

GLboolean Object::loadObject(std::string ObjectName)
{
	std::ifstream file(ObjectName);
	std::vector<glm::vec3> vertex;
	std::vector<glm::vec2> uv;
	std::vector<glm::vec3> nomal;
	std::vector<std::string> word;

	if (file.fail())
		return false;

	//�f�[�^�̓ǂݍ���
	while (!file.eof())
	{
		char keyword[_MAX_PATH] = {};
		std::string line;
		std::getline(file, line);
		sscanf_s(line.c_str(), "%s ", keyword,sizeof(keyword));

		//���܂����f�[�^�̓ǂݍ���
		if (!std::strcmp(keyword, "v"))
		{
			glm::vec3 vector;
			sscanf_s(line.c_str(), "v %f %f %f", &vector.x, &vector.y, &vector.z);
			vertex.push_back(vector);
		}
		else if (!std::strcmp(keyword, "vt"))
		{
			glm::vec2 vector;
			sscanf_s(line.c_str(), "vt %f %f", &vector.s, &vector.t);
			uv.push_back(vector);
		}
		else if (!std::strcmp(keyword, "vn"))
		{
			glm::vec3 vector;
			sscanf_s(line.c_str(), "vn %f %f %f", &vector.x, &vector.y, &vector.z);
			nomal.push_back(vector);
		}
		else if (!std::strcmp(keyword, "f"))
		{
			char block[3][_MAX_PATH] = {};

			sscanf_s(line.c_str(), "f %s %s %s", &block[0], sizeof(block[0]), &block[1], sizeof(block[1]), &block[2], sizeof(block[2]));
			for (auto& itr : block)
			{
				word.push_back(itr);
			}
		}
	}

	file.close();

	//�f�[�^�̎d����
	std::unordered_map < std::string, GLuint> index_dictionary;
	GLuint index_num = 0;

	//�f�[�^�̈��������֐�
	auto pull_data = [&](std::string PullData)->void{
			GLuint data[3];

			sscanf_s(PullData.c_str(), "%d/%d/%d", &data[0], &data[1], &data[2]);
			vertex_data_.push_back(VertexData());
			vertex_data_.back().position = vertex.at(data[0] - 1);
			vertex_data_.back().texcode = uv.at(data[1] - 1);
			vertex_data_.back().nomal = nomal.at(data[2] - 1);
	};

	//index���ƑΉ��̒��_���Ɏd������
	for (auto& itr : word)
	{
		auto check = index_dictionary.find(itr);

		if (check == index_dictionary.end())
		{
			check = index_dictionary.insert(std::make_pair(itr, index_num++)).first;
			pull_data(check->first);
		}
			index_data_.push_back(check->second);

	}
	return true;
}
