// in newer opengl es use "in" instead of "attribute"
attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec4 a_color;
attribute vec2 a_uv;

// in newer opengl es use "out" instead of "varying"
//ouput to fragment shader
varying vec3 v_normal;
varying vec3 v_fragmentPos;
varying vec4 v_color;
varying vec2 v_uv;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;
//opengl es 2.0 doesn't support transpose and inverse matrix
//so computed in application
uniform mat4 u_tranposeAndInverseModel;

void main()
{
	v_uv = a_uv;
	gl_Position = u_projection * u_view * u_model * vec4(a_position, 1);
	v_color = a_color;

	//light calculation to world space
	v_fragmentPos = vec3(u_model * vec4(a_position, 1));
	mat3 a = mat3(u_tranposeAndInverseModel);
	v_normal = mat3(u_tranposeAndInverseModel) * a_normal;
}
   