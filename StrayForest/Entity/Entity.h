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
		float yaw;	 //Y軸
		float pitch; //X軸
		float roll;  //Z軸
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
		//ReflectionDelay:ダイレクトパスに対する初期反射の遅延時間　指定範囲可能範囲　0 ~ 300ミリ秒
		BYTE ReflectionsDelay;
		//ReverbDelay:初期反射に対するリバーブの遅延、指定範囲は0～85ミリ秒
		BYTE ReverbDelay;
		//RearDelay:左後方出力及び右後方出力の遅延　指定可能範囲 0～85ミリ秒
		BYTE RearDelay;
		//PositionLeft:シミュレーション空間における視聴者に対する左入力の位置。　指定可能範囲は 0 ~ 30　（単位なし）
		BYTE PositionLeft;
		//PositionRight: PositionLeftと同様右入力にのみ影響します。　指定可能範囲は 0 ~ 30(単位なし）
		BYTE PositionRight;
		//PositionMatrixRight&Left:音源から視聴者まで距離によるインプレッションを増減させる。　指定可能範囲は 0 ~ 30（単位なし）
		BYTE PositionMatrixLeft;
		BYTE PositionMatrixRight;
		//EarlyDiffusion:個々の壁の反射特性を制御します。堅く平らな表面シミュレートするには小さな値を設定し、
		//散乱性の表面をシミュレートするには大きな値を設定。　指定可能範囲 0 ~15(単位なし）
		BYTE EarlyDiffusion;
		//LateDiffusion:個々の壁のリバーブ特性を制御。指定可能範囲 0 ~ 15(単位なし）
		BYTE LateDiffusion;
		//LowEQGain: 1kHzにおける減衰時間を基準にして低周波数の減衰時間を調整. 指定可能範囲 0 ~ 12(単位なし)
		BYTE LowEQGain;
		//LowEQCutoff:パラメーターにより制御されるローパスフィルターの折点周波数を設定。指定漢方範囲 0 ~ 9 (単位なし)
		BYTE LowEQCutoff;
		//HighEQGain:減衰時間を基準にして高周波数の減衰時間を調整。 0 の場合　高周波数の音が1khzの場合と同じ割合で減衰します。　指定可能範囲 0 ~ 8(単位なし)
		BYTE HighEQGain;
		//HighEQCutoff: HighEQGainパラメーターにより制御されるハイパスフィルターの接点周波数を設定。　指定可能範囲 0 ~ 14(単位なし）
		BYTE HighEQCutoff;
		//RoomFilterFreq:室内エフェクトのローパスフィルターの接点周波数を設定。　指定可能範囲は 20 ~ 20,000Hz
		float RoomFilterFreq;
		//RoomFilterMain:初期反射と後期フィールド残響の両方に適用されるローパスフィルターのパス バンド強度レベルを設定。　指定可能範囲 -100 ~ 0dB
		float RoomFilterMain;
		//RoomfiletHF:接点周波数での初期反射と後期フィールド残響の両方に適用されるローパスフィルターのパスバンド強度レベルを設定。指定可能範囲 -100 ~ 0dB
		float RoomFilterHF;
		//ReflectionGain:初期反射の強度/レベルを調整します。指定可能範囲は-100~20dB。
		float ReflectionsGain;
		//ReverbGain:リバーブの強度/レベルを調整します。指定可能範囲は -100 ~ 20dB
		float ReverbGain;
		//DecayTime:1kHzにおける残響減衰時間です。これは、フルスケールの入力信号が60dB減衰するまでの時間です。指定可能範囲は0.1 ~ 無限（秒）です。
		float DecayTime;
		//後期フィールド残響のモード密度を制御します。無色 (colorless) の空間では、Density を最大値 (100) に設定する必要があります。Density を小さくすると、
		//サウンドはくぐもった音 (くし形フィルターが適用された音) になります。サイロをシミュレーションするときに有効なエフェクトです。指定可能範囲は 0 ～ 100 で、単位はパーセントです。
		float Density;
		//RoomSize:音響空間の見かけ上のサイズです。　指定可能範囲は 1(30.48cm) ~ 100フィート(30.48m)
		float RoomSize;
		//WetDryMix:元の変更されてないサウンドとなる出力の割合　許容値　0 ~ 100;
		float WetDryMix;
	};

	struct WAVE 
	{
		int status;				//ステータス
		D3DXVECTOR3 position;	//位置
		float ampliture;		//振幅
		float time;				//時間
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
		/// 定数テーブル
		/// </summary>
		std::unordered_map<std::string, LPD3DXCONSTANTTABLE> VSConstantTable_;
		/// <summary>
		/// 定数テーブル
		/// </summary>
		std::unordered_map<std::string, LPD3DXCONSTANTTABLE> PSConstantTable_;
		/// <summary>
		/// 頂点シェーダー
		/// </summary>
		std::unordered_map<std::string, LPDIRECT3DVERTEXSHADER9> vertexshader_;
		/// <summary>
		/// ピクセルシェーダー
		/// </summary>
		std::unordered_map<std::string, LPDIRECT3DPIXELSHADER9> pixelshader_;
	};
}
