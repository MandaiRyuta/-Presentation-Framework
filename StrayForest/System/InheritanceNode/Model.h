#pragma once
#include "../System.h"
#include "../../Entity/Entity.h"

class XModel3D : public MySystem
{
public:
	XModel3D() {}
	~XModel3D() {}
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
private:
	Entity::Textureinfomation texture_;
	Entity::Model model_;
};