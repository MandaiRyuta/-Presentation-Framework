#pragma once
#include "../../../Renderer/GameManager.h"
class Polygon2D;
class PolygonColorChanger : public GameObjectManager
{
public:
	PolygonColorChanger(int _Priority);
	~PolygonColorChanger();
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
	static PolygonColorChanger* Create(int _Priority);

	void LoadPolygon(Polygon2D* target);
	void LoadPolygon2(Polygon2D* target);
	void LoadSepiaPolygon(Polygon2D* target);
private:
	Polygon2D* polygon_;
	Polygon2D* polygon2_;
	Polygon2D* polygon3_;
	int alpha_;
	int alpha2_;
	int sepiaalpha_;
	bool changeflag_;
};