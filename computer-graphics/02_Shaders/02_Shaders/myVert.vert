#version 130

// vertex attributes
in vec3 vs_in_pos;
in vec3 vs_in_col;

// output vertex attributes
out vec3 vs_out_pos;
out vec3 vs_out_col;

void main()
{
	gl_Position = vec4( vs_in_pos, 1 );
	vs_out_pos = vs_in_pos;
	vs_out_col = vs_in_col;
}