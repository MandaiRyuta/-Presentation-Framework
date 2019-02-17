#pragma once
#include <vector>
#include <string>
#include "../SceneManager/SceneManager.h"

/*���[�W�����ꗗ*/
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
	//���@�̏��
	struct MAGIC_WORK
	{
		bool IsDraw;					//�`��t���O	true : �`�悷��		false: �`�悵�Ȃ�
		D3DXVECTOR3 position;			//���W�i�`��ʒu�j
		D3DXVECTOR3 moveposition;		//�ړ����x
		D3DXVECTOR3 oldmoveposition;	//�ߋ��̈ړ����x
		float frame;					//�t���[����
	};
	//�G�t�F�N�g�`��p�̍\����
	struct EffectInfomation
	{
		D3DXVECTOR3 position;			//���W
		D3DXVECTOR3 scale;				//�傫��
		D3DXVECTOR3 rotation;			//��]
	};
	//���̍��W�A���a�̍\����
	struct Sphere
	{
		D3DXVECTOR3 modelpos;			//���W
		float r;						//���a
	};
	//�Փ˔���(��)
	struct SphereColision
	{
		Sphere colision01;				//�����01
		Sphere colision02;				//�����02
		D3DXVECTOR3 hit_position;		//�Փˈʒu
		float two_radius;				//��̋��̔��a�����킹�����l
		D3DXVECTOR3 center_to_center;	//��̋��̒��S�_�ƒ��S�_�����񂾒���
		D3DXVECTOR3 hit_vector;			//�߂肱��
	};
	//���C�g���
	struct LightInfo
	{
		D3DLIGHT9 light;				//���C�g�\����
		D3DXCOLOR color;				//���C�g�ɃZ�b�g����F���
	};

	//�{�X�̈ړ����
	struct BOSSMOVESTATE
	{
		float basic_highspeed;			//���x�@��
		float basic_middlespeed;		//���x�@��
		float basic_lowspeed;			//���x�@��
		float variable_movespeed;		//�ϑ��x
	};
	
	struct ENEMYMAGICINFO
	{
		bool magic_position_flag;		//���@��ł����ވʒu�擾�t���O
		bool magic_flag;				//���@�g�p�t���O
		int magic_cool_time;			//���@�̃N�[���^�C��
	};
	//�m�b�N�o�b�N���
	struct KNOCKBACKINFO
	{
		bool knockbackflag;			//�m�b�N�o�b�N�t���O
		D3DXVECTOR3 knockback;			//�m�b�N�o�b�N��
	};
	//�|���S�����
	struct POLYGONSIZE
	{
		float        dx_;				//�J�n�ʒu�@x
		float        dy_;				//�J�n�ʒu�@y
		float        dw_;				//����		x
		float        dh_;				//�c��		y
		int          tcx_;				//�e�N�X�`���ǂݍ��݈ʒu	x
		int          tcy_;				//�e�N�X�`���ǂݍ��݈ʒu	y
		unsigned int tcw_;				//�e�N�X�`���ǂݍ��݉���	x
		unsigned int tch_;				//�e�N�X�`���ǂݍ��ݏc��	y
		D3DCOLOR	 color_;			//�F
		bool         affine_;			//�A�t�B���ϊ�
	};

	//Directx9�o�b�t�@
	struct Dx9Buffer
	{
		LPDIRECT3DINDEXBUFFER9 index_buffer;		//�C���f�b�N�X�o�b�t�@
		LPDIRECT3DVERTEXBUFFER9 vertex_buffer;		//�o�[�e�b�N�X�o�b�t�@
	};
	//�G�̃X�e�[�g�p�^�[�����
	struct EnemyStatePattern
	{
		ACTIONPATTERN action_;						//�s���p�^�[��
		D3DXVECTOR3 position;						//���W
		D3DXVECTOR3 scale;							//�傫��
		D3DXVECTOR3 rotation;						//��]
	};

	//���[�s�b�`���[��
	struct YawPitchRoll
	{
		float yaw;	 //Y��
		float pitch; //X��
		float roll;  //Z��
	};

	//�J�������
	struct CameraInfo
	{
		D3DXVECTOR3 at;								//�J���������_
		D3DXVECTOR3 eye;							//�J�����z�u���W
		D3DXVECTOR3 up;								//�J����������x�N�g��
		D3DXMATRIX view;							//�r���[�s��
		D3DXMATRIX proj;							//�v���W�F�N�V�����s��
	};

	//���f�����
	struct Model
	{
		LPD3DXMESH p_mesh;							//���b�V�����
		D3DMATERIAL9* p_meshmaterial;				//�}�e���A�����
		LPDIRECT3DTEXTURE9* p_meshtexture;			//�e�N�X�`�����
		DWORD dw_material;							//���_��
		D3DXVECTOR3 position;						//�ʒu
		D3DXVECTOR3 scall;							//���f���̊g���
		D3DXCOLOR color;							//�F
		D3DXVECTOR3 rotation;						//��]
		D3DXMATRIX world;							//���[���h�s��
	};

	//�t�@�C���p�X�̏��
	struct FilePathData
	{
		int texturecount_;							//�e�N�X�`���ԍ�
		std::vector <std::string> texture_;			//�e�N�X�`���t�@�C���p�X
	};
	//�e�N�X�`�����
	struct Textureinfomation
	{
		LPDIRECT3DTEXTURE9 texture;					//�e�N�X�`�����
	};

	//�T�E���h�G�t�F�N�g�̃p�����[�^�[���
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

	//�C�̔g���
	struct WAVE 
	{
		int status;				//�X�e�[�^�X
		D3DXVECTOR3 position;	//�ʒu
		float ampliture;		//�U��
		float time;				//����
	};
	//�g�̒��_���
	struct WAVE_VERTEX
	{
		D3DXVECTOR3 position;	//���W
		DWORD color;			//�F
		D3DXVECTOR2 texcoord_;	//�e�N�X�`���[uv
	};
	//�C���X�^���V���O��������3D�̕`����
	struct VECTOR3D
	{
		D3DXVECTOR3 position;	//�ʒu
		D3DXVECTOR3 normal;		//�@��
		D3DCOLOR color;			//�F
		D3DXVECTOR2 texcoord;	//�e�N�X�`���[uv
	};
	//�C���X�^���V���O�p�̕`����
	struct INSTANCINGVECTOR3D
	{
		D3DXVECTOR3 position;	//�ʒu
		D3DXVECTOR2 texcoord;	//�e�N�X�`���[uv
		D3DCOLOR color;			//�F
	};
	//�`��ɕK�v�ȍs����
	struct MATRIX3D
	{
		D3DXMATRIX world;		//���[���h�s��
		D3DXMATRIX position;	//�ʒu�s��
		D3DXMATRIX rotation;	//��]�s��
		D3DXMATRIX scale;		//�g��s��
	};
	//3D�|���S���̕`����
	struct POLYGON3D
	{
		D3DXVECTOR3 position;	//�ʒu
		D3DXVECTOR2 uv;			//�e�N�X�`��uv
		D3DXVECTOR3 normal;		//�@��
	};
	//2D�|���S���̕`����
	struct VECTOR2D
	{
		D3DXVECTOR4 position;	//�ʒu
		D3DCOLOR color;			//�F
		D3DXVECTOR2 texcoord;	//�e�N�X�`���[uv
	};
	//���b�V���t�B�[���h���
	struct MeshFiledSize
	{
		int filed_x;			//�t�B�[���h�Ɏg�����_�� x
		int filed_z;			//�t�B�[���h�Ɏg�����_�� y
		float size_x;			//���_���m�̕�	x
		float size_z;			//���_���m�̕��@y
	};
	//�s��1�s��
	struct MODEL_WORLD1
	{
		float m11, m12, m13, m14;		//���[���h�s�� 11 ~ 14�Ԓn�ւ̔z�u�p�\����
	};
	//�s��2�s��
	struct MODEL_WORLD2
	{
		float m21, m22, m23, m24;		//���[���h�s�� 21 ~ 24�Ԓn�ւ̔z�u�p�\����
	};
	//�s��3�s��
	struct MODEL_WORLD3
	{
		float m31, m32, m33, m34;		//���[���h�s�� 31 ~ 34�Ԓn�ւ̔z�u�p�\����
	};
	//�s��4�s��
	struct MODEL_WORLD4
	{
		float m41, m42, m43, m44;		//���[���h�s�� 41 ~ 44�Ԓn�ւ̔z�u�p�\����
	};

	//�C���X�^���V���O�@�s����
	struct INSTANCINGWORLD
	{
		MODEL_WORLD1* pWorld1;			//�s����1�s��
		MODEL_WORLD2* pWorld2;			//�s����2�s��
		MODEL_WORLD3* pWorld3;			//�s����3�s��
		MODEL_WORLD4* pWorld4;			//�s����4�s��
	};

	//�C���X�^���V���O�p�̍\����
	struct INSTANCINGBUFFER
	{
		IDirect3DVertexBuffer9* pWorld1Buffer;
		IDirect3DVertexBuffer9* pWorld2Buffer;
		IDirect3DVertexBuffer9* pWorld3Buffer;
		IDirect3DVertexBuffer9* pWorld4Buffer;
		IDirect3DVertexDeclaration9* pDecl;
	};

	//Directx9�V�F�[�_�[���
	struct Dx9Shader
	{
		std::unordered_map<std::string, LPD3DXCONSTANTTABLE> VSConstantTable_;		//�萔�e�[�u��
		std::unordered_map<std::string, LPD3DXCONSTANTTABLE> PSConstantTable_;		//�萔�e�[�u��
		std::unordered_map<std::string, LPDIRECT3DVERTEXSHADER9> vertexshader_;		//���_�V�F�[�_�[
		std::unordered_map<std::string, LPDIRECT3DPIXELSHADER9> pixelshader_;		//�s�N�Z���V�F�[�_�[
	};
}
