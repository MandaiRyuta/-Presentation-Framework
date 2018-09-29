#pragma once
#include "../Entity.h"

class Texture : public Entity
{
public:
	Texture()
		: texturecount_(0)
	{}
	~Texture() {}
public:
	void StackTextureData(std::string _filepath)
	{
		texture_.push_back(_filepath);
		texturecount_++;
	}
	std::string GetTextureData(TEXTURENUMBER num)
	{
		if (num < texturecount_)
		{
			return texture_[num].c_str();
		}
		else
		{
			MessageBox(NULL, "テクスチャ情報がありません", "Eintity/InheritanceNode/Texture::Error", MB_OK);
			return;
		}
	}
private:
	int texturecount_;
	std::vector <std::string> texture_;
};
