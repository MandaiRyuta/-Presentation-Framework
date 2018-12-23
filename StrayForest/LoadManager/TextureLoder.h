#pragma once
#include "../Entity/Entity.h"
//****************************************************
// �񋓌^
//****************************************************
enum LOADTEXTURE
{
	FLOOR01,
	FLOOR02,
	FLOOR01NORMAL,
	FLOOR02NORMAL,
	SEA,
	TEX_PARTICLE,
	MOTIONEFFECT,
	STATUS,
	HP,
	MANA,
	PAUSEWAKU,
	PAUSESTART,
	PAUSEEND,
	TEXTUREMAX,	//�e�N�X�`���̍ő��
};

//****************************************************
// class TextureLoder
//****************************************************
class TextureLoder
{
private:
	TextureLoder() {}
	~TextureLoder() {}
public:
	/// <summary>
	/// ���[�h�f�[�^
	/// </summary>
	//****************************************************
	// @ _filename : �t�@�C���p�X
	// @ _LoadType : ��荞�ތ`���@0�ԁF�e�N�X�`���@1��: ���f��
	//****************************************************
	static void LoadData(std::string _filename);
public:
	//****************************************************
	// �Q�b�^�[
	//****************************************************
	/// <summary>
	/// �e�N�X�`���[�f�[�^�[�̃Q�b�^�[
	/// </summary>
	//****************************************************
	// @ number : �e�N�X�`���i���o�[
	//****************************************************
	static LPDIRECT3DTEXTURE9 GetTextureData(int _targettexture);
	static void RelaseAll();
private:
	//****************************************************
	// �����o�[�ϐ�
	//****************************************************
	/// <summary>
	/// �e�N�X�`���[�i�[�ϐ�
	/// </summary>
	static std::vector<LPDIRECT3DTEXTURE9> texture_;
	/// <summary>
	/// �e�N�X�`���[�̃J�E���^�[
	/// </summary>
	static int TextureCounter_;
};