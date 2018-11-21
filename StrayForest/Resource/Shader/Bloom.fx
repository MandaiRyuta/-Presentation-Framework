///////////////////////////////////////////////////////////////////////////////////
//型定義
///////////////////////////////////////////////////////////////////////////////////
struct VS_OUT
{
	float4 Position : POSITION;
	float3 Light : TEXCOORD0;
	float3 Normal : TEXCOORD1;
	float2 uv : TEXCOORD2;
	float3 View : TEXCOORD3;
};

///////////////////////////////////////////////////////////////////////////////////
//グローバル
///////////////////////////////////////////////////////////////////////////////////
float4x4 mWVP;
float4x4 mWorld;
float4 vLightPos;
float4 vEye;
float4 Diffuse = { 0,0,0,0 };
texture g_colorTexture;
sampler2D colorSampler = sampler_state
{
	Texture = (g_colorTexture);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;
	AddressU = Clamp;
	AddressV = Clamp;
};
texture g_colorTexture2;
sampler2D colorSampler2 = sampler_state
{
	Texture = (g_colorTexture2);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;
	AddressU = Clamp;
	AddressV = Clamp;
};

///////////////////////////////////////////////////////////////////////////////////
//単なるフォンシェーダー　パス1、パス2用　バーテックス・シェーダー
///////////////////////////////////////////////////////////////////////////////////
VS_OUT PhongVS(float4 Pos : POSITION, float3 Normal : NORMAL, float2 uv : TEXCOORD)
{
	VS_OUT Out = (VS_OUT)0;
	Out.Position = mul(Pos, mWVP);
	
	float3 PosWorld = normalize(mul(Pos, mWorld));
	Out.Light = vLightPos - PosWorld;
	Out.View = vEye - PosWorld;
	Out.Normal = mul(Normal, mWorld);
	Out.uv = uv;

	return Out;
}
///////////////////////////////////////////////////////////////////////////////////
//単なるフォンシェーダー　パス1、パス2用　ピクセル・シェーダー
///////////////////////////////////////////////////////////////////////////////////
float4 PhongPS(VS_OUT In) : COLOR
{
	float3 Normal = normalize(In.Normal);
	float3 LightDir = normalize(In.Light);
	float3 ViewDir = normalize(In.View);
	float4 NL = saturate(dot(Normal, LightDir));
	float4 texColor = tex2D(colorSampler, In.uv);
	float3 Reflect = normalize(2 * NL * Normal - LightDir);
	float4 specular = pow(saturate(dot(Reflect, ViewDir)), 4);

	return (texColor + Diffuse)*NL+specular;
}

///////////////////////////////////////////////////////////////////////////////////
// テクニック
///////////////////////////////////////////////////////////////////////////////////
technique Phong
{
	pass p0
	{
		VertexShader = compile vs_2_0 PhongVS();
		PixelShader = compile ps_2_0 PhongPS();
	}
}

float2 g_texOffset;

///////////////////////////////////////////////////////////////////////////////////
//パス3、4用　バーテックス・シェーダー
///////////////////////////////////////////////////////////////////////////////////
VS_OUT BloomVS(float4 Pos : POSITION,  float2 uv : TEXCOORD)
{
	VS_OUT Out = (VS_OUT)0;
	Out.Position = Pos;
	Out.uv = uv;

	return Out;
}
///////////////////////////////////////////////////////////////////////////////////
//パス3用　ガウシアンブラー水平方向　ピクセル・シェーダー
///////////////////////////////////////////////////////////////////////////////////
float4 Bloom_HorizontalPS(VS_OUT In) : COLOR
{
	//当該テクセル水平方向（横1列）3つのテクセルをフェッチ
	float2 uv0 = In.uv + float2(-g_texOffset.x*3.0,0.0);
	float2 uv1 = In.uv + float2(-g_texOffset.x*2.0, 0.0);
	float2 uv2 = In.uv + float2(-g_texOffset.x, 0.0);
	float2 uv3 = In.uv + float2( 0.0, 0.0);
	float2 uv4 = In.uv + float2( g_texOffset.x, 0.0);
	float2 uv5 = In.uv + float2(g_texOffset.x*2.0, 0.0);
	float2 uv6 = In.uv + float2(g_texOffset.x*3.0, 0.0);

	float4 col0 = tex2D(colorSampler, uv0);
	float4 col1 = tex2D(colorSampler, uv1);
	float4 col2 = tex2D(colorSampler, uv2);
	float4 col3 = tex2D(colorSampler, uv3);
	float4 col4 = tex2D(colorSampler, uv4);
	float4 col5 = tex2D(colorSampler, uv5);
	float4 col6 = tex2D(colorSampler, uv6);

	float4 texColor1 =
		(
			1.0 * col0 + 6.0 * col1 + 15.0 * col2 + 20.0 * col3 + 15.0 * col4
			+ 6.0 * col5 + 1.0 * col6
			) / 64.0;

	//最終色
	float4 finalColor = texColor1 * 2;

	return finalColor;
}
///////////////////////////////////////////////////////////////////////////////////
//パス4用　ガウシアンブラー垂直方向　ピクセル・シェーダー ここでパス2の全体シーンとも重ねる
///////////////////////////////////////////////////////////////////////////////////
float4 Bloom_VerticalPS(VS_OUT In) : COLOR
{
	///当該テクセル垂直方向（縦1列）7つのテクセルをフェッチ
	float2 uv0 = In.uv + float2(0.0, -g_texOffset.y*3.0);
	float2 uv1 = In.uv + float2(0.0, -g_texOffset.y*2.0);
	float2 uv2 = In.uv + float2(0.0, -g_texOffset.y);
	float2 uv3 = In.uv + float2(0.0, 0.0);
	float2 uv4 = In.uv + float2(0.0, g_texOffset.y);
	float2 uv5 = In.uv + float2(0.0, g_texOffset.y*2.0);
	float2 uv6 = In.uv + float2(0.0, g_texOffset.y*3.0);
	
	float4 col0 = tex2D(colorSampler, uv0);
	float4 col1 = tex2D(colorSampler, uv1);
	float4 col2 = tex2D(colorSampler, uv2);
	float4 col3 = tex2D(colorSampler, uv3);
	float4 col4 = tex2D(colorSampler, uv4);
	float4 col5 = tex2D(colorSampler, uv5);
	float4 col6 = tex2D(colorSampler, uv6);

	float4 texColor1 =
	(
		1.0 * col0 + 6.0 * col1 + 15.0 * col2 + 20.0 * col3 + 15.0 * col4
		+ 6.0 * col5 + 1.0 * col6
	) / 64.0;

	//最終色 
	float4 finalColor = texColor1 * 2;

	//さらにシーン全体テクスチャーと重ねて完了
	float4 texColor2 = tex2D(colorSampler2, In.uv);
	finalColor += texColor2;

	return finalColor;
}
///////////////////////////////////////////////////////////////////////////////////
// テクニック
///////////////////////////////////////////////////////////////////////////////////
technique Bloom_Horizontal
{
	pass p0
	{
		VertexShader = compile vs_2_0 BloomVS();
		PixelShader = compile ps_2_0 Bloom_HorizontalPS();
	}
}
technique Bloom_Vertical
{
	pass p0
	{
		VertexShader = compile vs_2_0 BloomVS();
		PixelShader = compile ps_2_0 Bloom_VerticalPS();
	}
}