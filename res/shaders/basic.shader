#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
// send data between shaders via a `varying`
out vec2 v_TexCoord;
void main()
{
	gl_Position = position;
	v_TexCoord = texCoord;
};

#shader fragment
#version 330 core
layout(location = 0) out vec4 color;
uniform sampler2D u_Texture;
in vec2 v_TexCoord;
void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	//color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	color = texColor;
};