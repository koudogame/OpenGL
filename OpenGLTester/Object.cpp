#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	reference_num_ = 0;
}

GLboolean Object::createVertexData(std::string ObjectName)
{
	if (!loadObject(ObjectName))
		return false;

	//頂点バッファの作成
	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);
	//バッファの作成
	glGenBuffers(1, &buffer_);

	//関連付け
	glBindBuffer(GL_ARRAY_BUFFER, buffer_);
	glBufferData(GL_ARRAY_BUFFER, vertex_data_.size() * sizeof(VertexData), vertex_data_.data(), GL_STATIC_DRAW);

	GLsizei size;
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

	//頂点情報
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLbyte*)(0));
	//UV情報
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLbyte*)(sizeof(VertexData::position)));
	//法線情報
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLbyte*)(sizeof(VertexData::position) + sizeof(VertexData::texcode)));

	return true;
}

void Object::loadTexture(const std::string &TextureName)
{
	//テクスチャの読み込み
	glGenTextures(1, &texture_id_);
	//バッファーの選択
	glBindTexture(GL_TEXTURE_2D, texture_id_);
	//テクスチャの読み込み
	cv::Mat img = cv::imread(TextureName.c_str(), cv::IMREAD_UNCHANGED);
	GLuint internalformat = GL_RGBA;
	GLuint sourceformat = GL_BGRA_EXT;

	if (img.channels() == 3)
	{
		internalformat = GL_RGB;
		sourceformat = GL_BGR_EXT;
	}

	//読み込んだテクスチャを結びつける
	glTexImage2D(GL_TEXTURE_2D, 0, internalformat,
		img.size().width, img.size().height,
		0, sourceformat,
		GL_UNSIGNED_BYTE,
		img.data);

	//パラメータ設定
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glActiveTexture(GL_TEXTURE0);
}

Object::~Object()
{
	//頂点配列オブジェクトを削除する
	glDeleteBuffers(1, &vao_);
	//頂点バッファオブジェクトを削除する
	glDeleteBuffers(1, &buffer_);

	//テクスチャの設定解除
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void Object::draw() const
{
	//透過設定
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//テクスチャマッピングを有効にする
	glEnable(GL_TEXTURE_2D);
	//使用テクスチャの設定
	glBindTexture(GL_TEXTURE_2D, texture_id_);

	//描画する頂点配列オブジェクトを指定する
	glBindVertexArray(vao_);
	for (auto itr : index_data_)
	{
		//図形の描画
		glDrawElements(GL_TRIANGLES, itr.second.size(), GL_UNSIGNED_INT, itr.second.data());
	}
}

GLboolean Object::loadObject(std::string ObjectName)
{
	std::ifstream file(ObjectName);
	std::vector<glm::vec3> vertex;
	std::vector<glm::vec2> uv;
	std::vector<glm::vec3> nomal;
	std::string mtl_id;
	std::unordered_map<std::string, std::vector<std::string>> word;
	if (file.fail())
		return false;

	//ポリゴンデータでの格納用変数
	std::vector<std::array<std::string, 3>> poligon;

	//データの読み込み
	while (!file.eof())
	{
		char keyword[_MAX_PATH] = {};
		std::string line;
		std::getline(file, line);
		sscanf_s(line.c_str(), "%s ", keyword, sizeof(keyword));

		//決まったデータの読み込み
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
			vector.t = 1.0F - vector.t;
			uv.push_back(vector);
		}
		else if (!std::strcmp(keyword, "vn"))
		{
			glm::vec3 vector;
			sscanf_s(line.c_str(), "vn %f %f %f", &vector.x, &vector.y, &vector.z);
			nomal.push_back(vector);
		}
		else if (!std::strcmp(keyword, "usemtl"))
		{
			char str[_MAX_PATH] = {};
			sscanf_s(line.c_str(), "usemtl %s", str, _MAX_PATH);
			mtl_id = str;
		}
		else if (!std::strcmp(keyword, "f"))
		{
			char block[3][_MAX_PATH] = {};

			sscanf_s(line.c_str(), "f %s %s %s", &block[0], sizeof(block[0]), &block[1], sizeof(block[1]), &block[2], sizeof(block[2]));

			std::array<std::string, 3> poli;

			for (int i = 0; i < 3; ++i)
			{
				word[mtl_id].push_back(block[i]);
				poli[i] = block[i];
			}
			poligon.push_back(poli);
		}
	}

	file.close();

	//データの仕分け
	std::unordered_map < std::string, GLuint> index_dictionary;
	GLuint index_num = 0;

	//データの引き抜き関数
	auto pull_data = [&](std::string PullData)->void {
		GLuint data[3];

		sscanf_s(PullData.c_str(), "%d/%d/%d", &data[0], &data[1], &data[2]);
		vertex_data_.push_back(VertexData());
		vertex_data_.back().position = vertex.at(data[0] - 1);
		vertex_data_.back().texcode = uv.at(data[1] - 1);
		vertex_data_.back().nomal = nomal.at(data[2] - 1);
	};

	//index情報と対応の頂点情報に仕分ける
	for (auto mtl : word)
	{
		for (auto& itr : mtl.second)
		{
			auto check = index_dictionary.find(itr);

			if (check == index_dictionary.end())
			{
				check = index_dictionary.insert(std::make_pair(itr, index_num++)).first;
				pull_data(check->first);
			}
			index_data_[mtl.first].push_back(check->second);
		}
	}
	return true;
}