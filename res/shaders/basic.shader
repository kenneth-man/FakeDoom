#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
void main()
{
   gl_Position = position;
};

#shader fragment
#version 330 core
layout(location = 0) out vec4 color;
uniform vec4 uniformColor;
void main()
{
   //color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
   color = uniformColor;
};