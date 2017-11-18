attribute vec3 a_position;
attribute vec4 a_color;
attribute vec2 a_uv;

varying vec4 v_color;
varying vec2 v_uv;

uniform vec3 u_theta;

void main()
{
	vec3 angles = radians(u_theta);
	vec3 c = cos(angles);
	vec3 s = sin(angles);
	mat4 rx = mat4(1.0, 0.0, 0.0, 0.0,
				   0.0, c.x, s.x, 0.0,
				   0.0, -s.x, c.x, 0.0,
				   0.0, 0.0, 0.0, 1.0);
	mat4 ry = mat4(c.y, 0.0, -s.y, 0.0,
				   0.0, 1.0, 0.0, 0.0,
				   s.y, 0.0, c.y, 0.0,
				   0.0, 0.0, 0.0, 1.0);
	mat4 rz = mat4(c.z, -s.z, 0.0, 0.0,
				   s.z, c.z, 0.0, 0.0,
				   0.0, 0.0, 1.0, 0.0,
				   0.0, 0.0, 0.0, 1.0);
	
	gl_Position = rz * ry * rx * vec4(a_position, 1);
	v_color = a_color;
	v_uv = a_uv;
}
   