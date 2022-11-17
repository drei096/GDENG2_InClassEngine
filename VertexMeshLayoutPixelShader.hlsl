Texture2D Texture : register(t0);
sampler TextureSampler : register(s0);


struct PS_INPUT
{
	float4 position: SV_POSITION;
	float2 texcoord: TEXCOORD0;
};

cbuffer constant: register(b0)
{
	row_major float4x4 m_world;
	row_major float4x4 m_view;
	row_major float4x4 m_proj;
	float m_angle;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
	float3 pixelColor = Texture.Sample(TextureSampler, input.texcoord * 0.5);
	return float4(pixelColor, 0.0f);
}