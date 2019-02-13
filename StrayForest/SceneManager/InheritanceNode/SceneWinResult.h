#pragma once

#include "../SceneManager.h"
class Fade;
class MeshFiled;
class WinPlayer;
class Polygon2D;
class SceneWinResult : public SceneManager
{
public:
	SceneWinResult() {}
	~SceneWinResult() {}
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	static Fade* GetFade();
public:
	static MeshFiled* GetMeshFiled();
	static WinPlayer* GetWinPlayer();
	static Polygon2D* GetWinWord();
private:
	static MeshFiled* WinResultMeshFiled_;
	static WinPlayer* WinResultPlayer_;
	static Fade* fade_;
	static Polygon2D* WinWord_;
};