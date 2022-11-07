struct PS_INPUT
{
	float4 position: SV_POSITION;
	float3 color: COLOR;
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
	float3 tempColor = (0.0f, 0.0f, 0.0f);
	return float4(input.color, 0.0f);
}