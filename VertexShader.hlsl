struct VS_INPUT
{
	float4 position: POSITION;
	float3 color: COLOR;
};

struct VS_OUTPUT
{
	float4 position: SV_POSITION;
	float3 color: COLOR;
};

cbuffer constant: register(b0)
{
	row_major float4x4 m_world;
	row_major float4x4 m_view;
	row_major float4x4 m_proj;
};

VS_OUTPUT vsmain( VS_INPUT input )
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	//output.position = lerp(input.position, input.position1, (sin(m_time / 1000.0f) + 1.0f) / 2.0f);

	//WORLD SPACE TRANSFORM
	output.position = mul(input.position, m_world);

	//VIEW SPACE TRANSFORM
	output.position = mul(output.position, m_view);

	//SCREEN SPACE TRANSFORM
	output.position = mul(output.position, m_proj);

	output.color = input.color;

	return output;
}