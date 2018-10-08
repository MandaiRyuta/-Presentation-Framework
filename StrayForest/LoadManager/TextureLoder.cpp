#include "TextureLoder.h"
//****************************************************
// �ÓI�����o�\�ϐ��̐錾
//****************************************************
/// <summary>
/// �e�N�X�`���[�i�[�ϐ��̐錾
/// </summary>
std::vector<LPDIRECT3DTEXTURE9> TextureLoder::texture_;
/// <summary>
/// �e�N�X�`���[�J�E���^�[�̐錾
/// </summary>
int TextureLoder::TextureCounter_ = 0;

void TextureLoder::LoadData(std::string _filename)
{
	/// <summary>
	///�@�e�N�X�`�����i�[
	/// </summary>
	//****************************************************
	// @ CRenderer::GetDevice() : CRenderer�̃f�o�C�X�Q�b�^�[
	// @ _filename.c_str() : �t�@�C���p�X
	// @ texture_[TextureCounter_] : �e�N�X�`���[�i�[�Ԓn���w�肳�ꂽ�e�N�X�`���ϐ�
	//****************************************************
	LPDIRECT3DTEXTURE9 texture;
	D3DXCreateTextureFromFile(GetDevice(), _filename.c_str(), &texture);
	texture_.push_back(texture);
	TextureCounter_++;
}

LPDIRECT3DTEXTURE9 TextureLoder::GetTextureData(int _targettexture)
{
	/// <summary>
	/// ���ݕێ����Ă���e�N�X�`���̐������A�w�肳�ꂽ���l���z���Ă�����G���[�����ɓ���B
	/// </summary>
	if (_targettexture > TEXTUREMAX)
	{
		MessageBox(NULL, "�e�N�X�`���̏����Ăяo���܂���ł���", "TextureLoderError", MB_OK);
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
