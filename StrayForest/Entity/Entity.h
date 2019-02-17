#pragma once
#include <vector>
#include <string>
#include "../SceneManager/SceneManager.h"

/*モージョン一覧*/
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
	//魔法の情報
	struct MAGIC_WORK
	{
		bool IsDraw;					//描画フラグ	true : 描画する		false: 描画しない
		D3DXVECTOR3 position;			//座標（描画位置）
		D3DXVECTOR3 moveposition;		//移動速度
		D3DXVECTOR3 oldmoveposition;	//過去の移動速度
		float frame;					//フレーム数
	};
	//エフェクト描画用の構造体
	struct EffectInfomation
	{
		D3DXVECTOR3 position;			//座標
		D3DXVECTOR3 scale;				//大きさ
		D3DXVECTOR3 rotation;			//回転
	};
	//球の座標、半径の構造体
	struct Sphere
	{
		D3DXVECTOR3 modelpos;			//座標
		float r;						//半径
	};
	//衝突判定(球)
	struct SphereColision
	{
		Sphere colision01;				//球情報01
		Sphere colision02;				//球情報02
		D3DXVECTOR3 hit_position;		//衝突位置
		float two_radius;				//二つの球の半径を合わせた数値
		D3DXVECTOR3 center_to_center;	//二つの球の中心点と中心点を結んだ長さ
		D3DXVECTOR3 hit_vector;			//めりこみ
	};
	//ライト情報
	struct LightInfo
	{
		D3DLIGHT9 light;				//ライト構造体
		D3DXCOLOR color;				//ライトにセットする色情報
	};

	//ボスの移動情報
	struct BOSSMOVESTATE
	{
		float basic_highspeed;			//速度　高
		float basic_middlespeed;		//速度　中
		float basic_lowspeed;			//速度　低
		float variable_movespeed;		//可変速度
	};
	
	struct ENEMYMAGICINFO
	{
		bool magic_position_flag;		//魔法を打ち込む位置取得フラグ
		bool magic_flag;				//魔法使用フラグ
		int magic_cool_time;			//魔法のクールタイム
	};
	//ノックバック情報
	struct KNOCKBACKINFO
	{
		bool knockbackflag;			//ノックバックフラグ
		D3DXVECTOR3 knockback;			//ノックバック量
	};
	//ポリゴン情報
	struct POLYGONSIZE
	{
		float        dx_;				//開始位置　x
		float        dy_;				//開始位置　y
		float        dw_;				//横幅		x
		float        dh_;				//縦幅		y
		int          tcx_;				//テクスチャ読み込み位置	x
		int          tcy_;				//テクスチャ読み込み位置	y
		unsigned int tcw_;				//テクスチャ読み込み横幅	x
		unsigned int tch_;				//テクスチャ読み込み縦幅	y
		D3DCOLOR	 color_;			//色
		bool         affine_;			//アフィン変換
	};

	//Directx9バッファ
	struct Dx9Buffer
	{
		LPDIRECT3DINDEXBUFFER9 index_buffer;		//インデックスバッファ
		LPDIRECT3DVERTEXBUFFER9 vertex_buffer;		//バーテックスバッファ
	};
	//敵のステートパターン情報
	struct EnemyStatePattern
	{
		ACTIONPATTERN action_;						//行動パターン
		D3DXVECTOR3 position;						//座標
		D3DXVECTOR3 scale;							//大きさ
		D3DXVECTOR3 rotation;						//回転
	};

	//ヨーピッチロール
	struct YawPitchRoll
	{
		float yaw;	 //Y軸
		float pitch; //X軸
		float roll;  //Z軸
	};

	//カメラ情報
	struct CameraInfo
	{
		D3DXVECTOR3 at;								//カメラ注視点
		D3DXVECTOR3 eye;							//カメラ配置座標
		D3DXVECTOR3 up;								//カメラ上向きベクトル
		D3DXMATRIX view;							//ビュー行列
		D3DXMATRIX proj;							//プロジェクション行列
	};

	//モデル情報
	struct Model
	{
		LPD3DXMESH p_mesh;							//メッシュ情報
		D3DMATERIAL9* p_meshmaterial;				//マテリアル情報
		LPDIRECT3DTEXTURE9* p_meshtexture;			//テクスチャ情報
		DWORD dw_material;							//頂点数
		D3DXVECTOR3 position;						//位置
		D3DXVECTOR3 scall;							//モデルの拡大量
		D3DXCOLOR color;							//色
		D3DXVECTOR3 rotation;						//回転
		D3DXMATRIX world;							//ワールド行列
	};

	//ファイルパスの情報
	struct FilePathData
	{
		int texturecount_;							//テクスチャ番号
		std::vector <std::string> texture_;			//テクスチャファイルパス
	};
	//テクスチャ情報
	struct Textureinfomation
	{
		LPDIRECT3DTEXTURE9 texture;					//テクスチャ情報
	};

	//サウンドエフェクトのパラメーター情報
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

	//海の波情報
	struct WAVE 
	{
		int status;				//ステータス
		D3DXVECTOR3 position;	//位置
		float ampliture;		//振幅
		float time;				//時間
	};
	//波の頂点情報
	struct WAVE_VERTEX
	{
		D3DXVECTOR3 position;	//座標
		DWORD color;			//色
		D3DXVECTOR2 texcoord_;	//テクスチャーuv
	};
	//インスタンシングを除いた3Dの描画情報
	struct VECTOR3D
	{
		D3DXVECTOR3 position;	//位置
		D3DXVECTOR3 normal;		//法線
		D3DCOLOR color;			//色
		D3DXVECTOR2 texcoord;	//テクスチャーuv
	};
	//インスタンシング用の描画情報
	struct INSTANCINGVECTOR3D
	{
		D3DXVECTOR3 position;	//位置
		D3DXVECTOR2 texcoord;	//テクスチャーuv
		D3DCOLOR color;			//色
	};
	//描画に必要な行列情報
	struct MATRIX3D
	{
		D3DXMATRIX world;		//ワールド行列
		D3DXMATRIX position;	//位置行列
		D3DXMATRIX rotation;	//回転行列
		D3DXMATRIX scale;		//拡大行列
	};
	//3Dポリゴンの描画情報
	struct POLYGON3D
	{
		D3DXVECTOR3 position;	//位置
		D3DXVECTOR2 uv;			//テクスチャuv
		D3DXVECTOR3 normal;		//法線
	};
	//2Dポリゴンの描画情報
	struct VECTOR2D
	{
		D3DXVECTOR4 position;	//位置
		D3DCOLOR color;			//色
		D3DXVECTOR2 texcoord;	//テクスチャーuv
	};
	//メッシュフィールド情報
	struct MeshFiledSize
	{
		int filed_x;			//フィールドに使う頂点数 x
		int filed_z;			//フィールドに使う頂点数 y
		float size_x;			//頂点同士の幅	x
		float size_z;			//頂点同士の幅　y
	};
	//行列1行目
	struct MODEL_WORLD1
	{
		float m11, m12, m13, m14;		//ワールド行列 11 ~ 14番地への配置用構造体
	};
	//行列2行目
	struct MODEL_WORLD2
	{
		float m21, m22, m23, m24;		//ワールド行列 21 ~ 24番地への配置用構造体
	};
	//行列3行目
	struct MODEL_WORLD3
	{
		float m31, m32, m33, m34;		//ワールド行列 31 ~ 34番地への配置用構造体
	};
	//行列4行目
	struct MODEL_WORLD4
	{
		float m41, m42, m43, m44;		//ワールド行列 41 ~ 44番地への配置用構造体
	};

	//インスタンシング　行列情報
	struct INSTANCINGWORLD
	{
		MODEL_WORLD1* pWorld1;			//行列情報1行目
		MODEL_WORLD2* pWorld2;			//行列情報2行目
		MODEL_WORLD3* pWorld3;			//行列情報3行目
		MODEL_WORLD4* pWorld4;			//行列情報4行目
	};

	//インスタンシング用の構造体
	struct INSTANCINGBUFFER
	{
		IDirect3DVertexBuffer9* pWorld1Buffer;
		IDirect3DVertexBuffer9* pWorld2Buffer;
		IDirect3DVertexBuffer9* pWorld3Buffer;
		IDirect3DVertexBuffer9* pWorld4Buffer;
		IDirect3DVertexDeclaration9* pDecl;
	};

	//Directx9シェーダー情報
	struct Dx9Shader
	{
		std::unordered_map<std::string, LPD3DXCONSTANTTABLE> VSConstantTable_;		//定数テーブル
		std::unordered_map<std::string, LPD3DXCONSTANTTABLE> PSConstantTable_;		//定数テーブル
		std::unordered_map<std::string, LPDIRECT3DVERTEXSHADER9> vertexshader_;		//頂点シェーダー
		std::unordered_map<std::string, LPDIRECT3DPIXELSHADER9> pixelshader_;		//ピクセルシェーダー
	};
}
