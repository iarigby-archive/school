#version 130

in vec3 vs_out_col;
in vec2 vs_out_tex0;
out vec4 fs_out_col;

uniform sampler2D texture;
uniform sampler2D texture2;

void main()
{
	fs_out_col = texture2D(texture, vs_out_tex0.st);
}