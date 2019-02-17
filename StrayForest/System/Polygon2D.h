#pragma once

#include "../GameObjectManager/GameObjectManager.h"
#include "../Entity/Entity.h"
#include <string>

class Polygon2D : public GameObjectManager
{
private:
#define FVF_POLYGON2D ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

public:
	Polygon2D(
		int _priority,
		float _dx,
		float _dy,
		float _dw,
		float _dh,
		unsigned int _tcx,
		unsigned int _tcy,
		unsigned int _tcw,
		unsigned int _tch,
		D3DCOLOR _color,
		bool _affine,
		float _angle,
		float _rot_offsetx,
		float _rot_offsety,
		float _scale_offsetX,
		float _scale_offsetY,
		float _scaleX,
		float _scaleY,
		LPDIRECT3DTEXTURE9 _texture,
		bool _draw
		);
	~Polygon2D();
private:
	void CreateVertex(
		D3DCOLOR _color,
		float _dx,
		float _dy,
		float _dw,
		float _dh,
		int _tcx,
		int _tcy,
		int _tcw,
		int _tch
	);
	void CreateVertexAffine(
		D3DCOLOR _color,
		float _dx,
		float _dy,
		float _dw,
		float _dh,
		int _tcx,
		int _tcy,
		int _tcw,
		int _tch
	);
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
	
	void SetColor(D3DCOLOR _color);
	void SetPolygonScale(float _x, float _y);
	void SetDraw(bool _draw);
	void StatusSetUp(float status, float max_status);
	void SetPosition(float x, float y);
	void SetMoveAmount(float x, float y);
	void SetControllPosX(float axis);
	void SetControllPosY(float axis);
	bool GetDraw();
public:
	static Polygon2D* Create(
		int _priority,
		float _dx,
		float _dy,
		float _dw,
		float _dh,
		unsigned int _tcx,
		unsigned int _tcy,
		unsigned int _tcw,
		unsigned int _tch,
		D3DCOLOR _color,
		bool _affine,
		float _angle,
		float _rot_offsetx,
		float _rot_offsety,
		LPDIRECT3DTEXTURE9 _texture,
		bool _draw = false
	);
private:
	float initial_position_x_;
	float initial_position_y_;
	float moveamount_x_;
	float moveamount_y_;
	bool draw_;
	float max_dw_;
	LPDIRECT3DTEXTURE9 texture_;
	Entity::POLYGONSIZE infomation_;
	Entity::Dx9Buffer buffer_;
	float scaleX_, scaleY_;
	float angle_;
	float rot_offsetX_, rot_offsetY_;
	float scale_offsetX_, scale_offsetY_;
};