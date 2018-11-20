#pragma once
#include <vector>
#include <string>
#include "../SceneManager/SceneManager.h"

enum TEXTURENUMBER
{
	NONE,
};

enum ACTIONPATTERN
{
	STATE,
	ATTACK1,
	ATTACK2,
	ATTACK3,
	MAGIC01,
	MAGIC02,
	DSTART,
	DEND,
	BUFFSTATE,
	NONEACTION
};

namespace Entity
{
	struct Sphere
	{
		D3DXVECTOR3 modelpos;
		float r;
	};
	struct SphereColision
	{
		Sphere colision01;
		Sphere colision02;
		D3DXVECTOR3 hit_position;
		float two_radius;
		D3DXVECTOR3 center_to_center;
		D3DXVECTOR3 hit_vector;
	};

	struct LightInfo
	{
		D3DLIGHT9 light;
		D3DXCOLOR color;
	};

	struct PLAYERSTATUS
	{
		bool hit;
		bool skill; 
		bool power;
		bool stamina;

		int attack_number;
		int skill_number;
		int buff_number;
		int debuff_number;
		int hit_number;
		int heal_number;

		double heal_amount;
		double helth_amount;
		double mana_amount;
		double power_amount;
	};

	struct BOSSSTATUS
	{
		bool hit;
		bool skill;
		bool magic;
		bool buff;
		bool debuff;
		bool heal;

		int attack_number;
		int skill_number;
		int magic_number;
		int buff_number;
		int debuff_number;
		int hit_number;
		int heal_number;

		float heal_amount;
		float health_amount;
		float mana_amount;
		float power_amount;
	};

	struct BOSSMOVESTATE
	{
		float basic_highspeed_;
		float basic_lowspeed_;
		float variable_speed_;
		int movestate_;
	};

	struct POLYGONSIZE
	{
		float        dx_;
		float        dy_;
		float        dw_;
		float        dh_;
		int          tcx_;
		int          tcy_;
		unsigned int tcw_;
		unsigned int tch_;
		D3DCOLOR	 color_;
		bool         affine_;
	};

	struct Dx9Buffer
	{
		LPDIRECT3DINDEXBUFFER9 index_buffer;
		LPDIRECT3DVERTEXBUFFER9 vertex_buffer;
	};

	struct EnemyStatePattern
	{
		ACTIONPATTERN action_;
		D3DXVECTOR3 position;
		D3DXVECTOR3 scale;
		D3DXVECTOR3 rotation;
	};
	struct YawPitchRoll
	{
		float yaw;	 //Y��
		float pitch; //X��
		float roll;  //Z��
	};
	struct CameraInfo
	{
		D3DXVECTOR3 at;
		D3DXVECTOR3 eye;
		D3DXVECTOR3 up;
		D3DXMATRIX view;
		D3DXMATRIX proj;
	};

	struct Model
	{
		LPD3DXMESH p_mesh;
		D3DMATERIAL9* p_meshmaterial;
		LPDIRECT3DTEXTURE9* p_meshtexture;
		DWORD dw_material;
		D3DXVECTOR3 position;
		D3DXVECTOR3 scall;
		D3DXCOLOR color;
		D3DXVECTOR3 rotation;
		D3DXMATRIX world;
	};

	struct FilePathData
	{
		int texturecount_;
		std::vector <std::string> texture_;
	};

	struct Textureinfomation
	{
		LPDIRECT3DTEXTURE9 texture;
	};

	struct CharactorStatus
	{
		int charaLv;
		int charaHP;
		int charaMP;
		int charaSP;
		float charaSTAMINA;
	};

	struct EffectSoundParameter
	{
		//ReflectionDelay:�_�C���N�g�p�X�ɑ΂��鏉�����˂̒x�����ԁ@�w��͈͉\�͈́@0 ~ 300�~���b
		BYTE ReflectionsDelay;
		//ReverbDelay:�������˂ɑ΂��郊�o�[�u�̒x���A�w��͈͂�0�`85�~���b
		BYTE ReverbDelay;
		//RearDelay:������o�͋y�щE����o�͂̒x���@�w��\�͈� 0�`85�~���b
		BYTE RearDelay;
		//PositionLeft:�V�~�����[�V������Ԃɂ����鎋���҂ɑ΂��鍶���͂̈ʒu�B�@�w��\�͈͂� 0 ~ 30�@�i�P�ʂȂ��j
		BYTE PositionLeft;
		//PositionRight: PositionLeft�Ɠ��l�E���͂ɂ̂݉e�����܂��B�@�w��\�͈͂� 0 ~ 30(�P�ʂȂ��j
		BYTE PositionRight;
		//PositionMatrixRight&Left:�������王���҂܂ŋ����ɂ��C���v���b�V�����𑝌�������B�@�w��\�͈͂� 0 ~ 30�i�P�ʂȂ��j
		BYTE PositionMatrixLeft;
		BYTE PositionMatrixRight;
		//EarlyDiffusion:�X�̕ǂ̔��˓����𐧌䂵�܂��B��������ȕ\�ʃV�~�����[�g����ɂ͏����Ȓl��ݒ肵�A
		//�U�����̕\�ʂ��V�~�����[�g����ɂ͑傫�Ȓl��ݒ�B�@�w��\�͈� 0 ~15(�P�ʂȂ��j
		BYTE EarlyDiffusion;
		//LateDiffusion:�X�̕ǂ̃��o�[�u�����𐧌�B�w��\�͈� 0 ~ 15(�P�ʂȂ��j
		BYTE LateDiffusion;
		//LowEQGain: 1kHz�ɂ����錸�����Ԃ���ɂ��Ē���g���̌������Ԃ𒲐�. �w��\�͈� 0 ~ 12(�P�ʂȂ�)
		BYTE LowEQGain;
		//LowEQCutoff:�p�����[�^�[�ɂ�萧�䂳��郍�[�p�X�t�B���^�[�̐ܓ_���g����ݒ�B�w�芿���͈� 0 ~ 9 (�P�ʂȂ�)
		BYTE LowEQCutoff;
		//HighEQGain:�������Ԃ���ɂ��č����g���̌������Ԃ𒲐��B 0 �̏ꍇ�@�����g���̉���1khz�̏ꍇ�Ɠ��������Ō������܂��B�@�w��\�͈� 0 ~ 8(�P�ʂȂ�)
		BYTE HighEQGain;
		//HighEQCutoff: HighEQGain�p�����[�^�[�ɂ�萧�䂳���n�C�p�X�t�B���^�[�̐ړ_���g����ݒ�B�@�w��\�͈� 0 ~ 14(�P�ʂȂ��j
		BYTE HighEQCutoff;
		//RoomFilterFreq:�����G�t�F�N�g�̃��[�p�X�t�B���^�[�̐ړ_���g����ݒ�B�@�w��\�͈͂� 20 ~ 20,000Hz
		float RoomFilterFreq;
		//RoomFilterMain:�������˂ƌ���t�B�[���h�c���̗����ɓK�p����郍�[�p�X�t�B���^�[�̃p�X �o���h���x���x����ݒ�B�@�w��\�͈� -100 ~ 0dB
		float RoomFilterMain;
		//RoomfiletHF:�ړ_���g���ł̏������˂ƌ���t�B�[���h�c���̗����ɓK�p����郍�[�p�X�t�B���^�[�̃p�X�o���h���x���x����ݒ�B�w��\�͈� -100 ~ 0dB
		float RoomFilterHF;
		//ReflectionGain:�������˂̋��x/���x���𒲐����܂��B�w��\�͈͂�-100~20dB�B
		float ReflectionsGain;
		//ReverbGain:���o�[�u�̋��x/���x���𒲐����܂��B�w��\�͈͂� -100 ~ 20dB
		float ReverbGain;
		//DecayTime:1kHz�ɂ�����c���������Ԃł��B����́A�t���X�P�[���̓��͐M����60dB��������܂ł̎��Ԃł��B�w��\�͈͂�0.1 ~ �����i�b�j�ł��B
		float DecayTime;
		//����t�B�[���h�c���̃��[�h���x�𐧌䂵�܂��B���F (colorless) �̋�Ԃł́ADensity ���ő�l (100) �ɐݒ肷��K�v������܂��BDensity ������������ƁA
		//�T�E���h�͂����������� (�����`�t�B���^�[���K�p���ꂽ��) �ɂȂ�܂��B�T�C�����V�~�����[�V��������Ƃ��ɗL���ȃG�t�F�N�g�ł��B�w��\�͈͂� 0 �` 100 �ŁA�P�ʂ̓p�[�Z���g�ł��B
		float Density;
		//RoomSize:������Ԃ̌�������̃T�C�Y�ł��B�@�w��\�͈͂� 1(30.48cm) ~ 100�t�B�[�g(30.48m)
		float RoomSize;
		//WetDryMix:���̕ύX����ĂȂ��T�E���h�ƂȂ�o�͂̊����@���e�l�@0 ~ 100;
		float WetDryMix;
	};

	struct WAVE 
	{
		int status;				//�X�e�[�^�X
		D3DXVECTOR3 position;	//�ʒu
		float ampliture;		//�U��
		float time;				//����
	};

	struct WAVE_VERTEX
	{
		D3DXVECTOR3 position;
		DWORD color;
		D3DXVECTOR2 texcoord_;
	};

	struct VECTOR3D
	{
		D3DXVECTOR3 position;
		D3DXVECTOR3 normal;
		D3DCOLOR color;
		D3DXVECTOR2 texcoord;
	};

	struct INSTANCINGVECTOR3D
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texcoord;
		D3DCOLOR color;
	};

	struct MATRIX3D
	{
		D3DXMATRIX world;
		D3DXMATRIX position;
		D3DXMATRIX rotation;
		D3DXMATRIX scale;
	};

	struct VECTOR2D
	{
		D3DXVECTOR4 position;
		D3DCOLOR color;
		D3DXVECTOR2 texcoord;
	};

	struct MeshFiledSize
	{
		int filed_x;
		int filed_z;
		float size_x;
		float size_z;
	};

	struct MODEL_WORLD1
	{
		float m11, m12, m13, m14;
	};

	struct MODEL_WORLD2
	{
		float m21, m22, m23, m24;
	};

	struct MODEL_WORLD3
	{
		float m31, m32, m33, m34;
	};

	struct MODEL_WORLD4
	{
		float m41, m42, m43, m44;
	};

	struct INSTANCINGWORLD
	{
		MODEL_WORLD1* pWorld1;
		MODEL_WORLD2* pWorld2;
		MODEL_WORLD3* pWorld3;
		MODEL_WORLD4* pWorld4;
	};

	struct INSTANCINGBUFFER
	{
		IDirect3DVertexBuffer9* pWorld1Buffer;
		IDirect3DVertexBuffer9* pWorld2Buffer;
		IDirect3DVertexBuffer9* pWorld3Buffer;
		IDirect3DVertexBuffer9* pWorld4Buffer;
		IDirect3DVertexDeclaration9* pDecl;
	};
	struct Dx9Shader
	{
		/// <summary>
		/// �萔�e�[�u��
		/// </summary>
		std::unordered_map<std::string, LPD3DXCONSTANTTABLE> VSConstantTable_;
		/// <summary>
		/// �萔�e�[�u��
		/// </summary>
		std::unordered_map<std::string, LPD3DXCONSTANTTABLE> PSConstantTable_;
		/// <summary>
		/// ���_�V�F�[�_�[
		/// </summary>
		std::unordered_map<std::string, LPDIRECT3DVERTEXSHADER9> vertexshader_;
		/// <summary>
		/// �s�N�Z���V�F�[�_�[
		/// </summary>
		std::unordered_map<std::string, LPDIRECT3DPIXELSHADER9> pixelshader_;
	};
}
