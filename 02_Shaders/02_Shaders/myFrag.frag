#version 130

in vec3 vs_out_col;
in vec3 vs_out_pos;
out vec4 fs_out_col;

void main()
{
	fs_out_col = vec4(vs_out_col, 1);
}

// 1.: draw a white rectangle

// 2.: by using uniform variables, let the application determine the color of the triangle

// 3.: draw a circle, use the discard command
