#version 130

in vec3 vs_out_col;
in vec3 vs_out_pos;
out vec4 fs_out_col;

void main()
{
	float x = vs_out_pos.x;
	float y = vs_out_pos.y;
	if (abs(x*x + y*y - 1) < 0.01)
		fs_out_col = vec4(1, 0, 0, 1);
	else
		discard;
}

// 1.: draw a white rectangle

// 2.: by using uniform variables, let the application determine the color of the triangle

// 3.: draw a circle, use the discard command
