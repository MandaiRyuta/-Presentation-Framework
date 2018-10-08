#include "TextureLoder.h"
//****************************************************
// 静的メンバ―変数の宣言
//****************************************************
/// <summary>
/// テクスチャー格納変数の宣言
/// </summary>
std::vector<LPDIRECT3DTEXTURE9> TextureLoder::texture_;
/// <summary>
/// テクスチャーカウンターの宣言
/// </summary>
int TextureLoder::TextureCounter_ = 0;

void TextureLoder::LoadData(std::string _filename)
{
	/// <summary>
	///　テクスチャ情報格納
	/// </summary>
	//****************************************************
	// @ CRenderer::GetDevice() : CRendererのデバイスゲッター
	// @ _filename.c_str() : ファイルパス
	// @ texture_[TextureCounter_] : テクスチャー格納番地が指定されたテクスチャ変数
	//****************************************************
	LPDIRECT3DTEXTURE9 texture;
	D3DXCreateTextureFromFile(GetDevice(), _filename.c_str(), &texture);
	texture_.push_back(texture);
	TextureCounter_++;
}

LPDIRECT3DTEXTURE9 TextureLoder::GetTextureData(int _targettexture)
{
	/// <summary>
	/// 現在保持しているテクスチャの数情報より、指定された数値が越えていたらエラー処理に入る。
	/// </summary>
	if (_targettexture > TEXTUREMAX)
	{
		MessageBox(NULL, "テクスチャの情報を呼び出せませんでした", "TextureLoderError", MB_OK);
		PostQuitMessage(0);
	}

	return texture_[_targettexture];
}

void TextureLoder::RelaseAll()
{
	for (auto itr = texture_.begin(); itr != texture_.end(); itr++)
	{
		(*itr)->Release();
		(*itr) = nullptr;
	}
}
