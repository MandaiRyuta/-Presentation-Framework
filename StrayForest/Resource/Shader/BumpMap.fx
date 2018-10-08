// -------------------------------------------------------------
// �O���[�o���ϐ�
// -------------------------------------------------------------

float4x4 mWVP;		// ���W�ϊ��̍s��

float4 vLightDir;	// ���C�g�̕���
float4 vColor;		// ���C�g�����b�V���̐F
float3 vEyePos;		// �J�����̈ʒu�i���[�J�����W�n�j

// -------------------------------------------------------------
// �e�N�X�`��
// -------------------------------------------------------------
// �͗l�̃e�N�X�`��
texture DecaleTex;
sampler DecaleSamp = sampler_state
{
    Texture = <DecaleTex>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = Clamp;
    AddressV = Clamp;
};
// -------------------------------------------------------------
// �@���}�b�v
texture NormalMap;
sampler NormalSamp = sampler_state
{
    Texture = <NormalMap>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = Wrap;
    AddressV = Wrap;
};

// -------------------------------------------------------------
// ���_�V�F�[�_����s�N�Z���V�F�[�_�ɓn���f�[�^
// -------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos			: POSITION;
    float4 Color		: COLOR0;		// ���_�F
    float2 Tex			: TEXCOORD0;	// �f�J�[���e�N�X�`�����W
    float3 L			: TEXCOORD1;	// ���C�g�x�N�g��
    float3 E			: TEXCOORD2;	// �����x�N�g��
};
// -------------------------------------------------------------
// �V�[���̕`��
// -------------------------------------------------------------
VS_OUTPUT VS(
      float4 Pos      : POSITION,          // ���[�J���ʒu���W
      float3 Normal   : NORMAL,            // �@���x�N�g��
      float3 Tangent  : TANGENT0,          // �ڃx�N�g��
      float2 Texcoord : TEXCOORD0          // �@���x�N�g��
){
	VS_OUTPUT Out = (VS_OUTPUT)0;        // �o�̓f�[�^
	
	// ���W�ϊ�
	Out.Pos = mul(Pos, mWVP);
	
	// ���b�V���̐F
	Out.Color = vColor;
	
	// �f�J�[���p�̃e�N�X�`�����W
	Out.Tex = Texcoord;

	// ���W�n�̕ϊ����
	float3 N = Normal;
	float3 T = Tangent;
	float3 B = cross(N,T);

	// ���ʔ��˗p�̃x�N�g��
	float3 E = vEyePos - Pos.xyz;	// �����x�N�g��
	Out.E.x = dot(E,T);
	Out.E.y = dot(E,B);
	Out.E.z = dot(E,N);

	float3 L = -vLightDir.xyz;		// ���C�g�x�N�g��
	Out.L.x = dot(L,T);
	Out.L.y = dot(L,B);
	Out.L.z = dot(L,N);
	
	return Out;
}
// -------------------------------------------------------------
float4 PS(VS_OUTPUT In) : COLOR
{   
	float3 N = 2.0f*tex2D( NormalSamp, In.Tex ).xyz-1.0;// �@���}�b�v����̖@��
	float3 L = normalize(In.L);						// ���C�g�x�N�g��
	float3 R = reflect(-normalize(In.E), N);		// ���˃x�N�g��
	float amb = -vLightDir.w;						// �����̋���
	
    return In.Color * tex2D( DecaleSamp, In.Tex )	// �g�U���Ɗ����ɂ́A
			   * (max(0, dot(N, L))+amb)			// ���_�F�ƃe�N�X�`���̐F����������
			 + 0.3f * pow(max(0,dot(R, L)), 8);		// Phong ���ʔ��ˌ�
}

// -------------------------------------------------------------
// �e�N�j�b�N
// -------------------------------------------------------------
technique TShader
{
    pass P0
    {
        VertexShader = compile vs_1_1 VS();
        PixelShader  = compile ps_2_0 PS();
    }
}
