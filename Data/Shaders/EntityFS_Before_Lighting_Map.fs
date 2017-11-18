precision mediump float;

//from vertex shader
varying vec3 v_normal;
varying vec3 v_fragmentPos;
varying vec4 v_color;
varying vec2 v_uv;

uniform sampler2D u_texture;

//lighting stuff
uniform vec3 u_lightViewPos;

//more organize
struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material u_material;
uniform Light u_light;

void main()
{
	vec4 texture = texture2D(u_texture, v_uv);
	vec4 cs = v_color;
	//gl_FragColor = texture.rgba;

	//lighting
	//ambient
	vec3 ambient = u_light.ambient * u_material.ambient;
	//diffuse
	vec3 lightDir = normalize(u_light.position - v_fragmentPos);
	vec3 nnormal  = normalize(v_normal);
	float dff = max(dot(lightDir, nnormal), 0.0);
	vec3 diffuse  = u_light.diffuse * (dff * u_material.diffuse);
	//specular
	vec3 viewDir = normalize(u_lightViewPos - v_fragmentPos);
	vec3 I = -lightDir;
	vec3 reflextDir = I - 2.0 * dot(nnormal, I) * nnormal;
	float spec = pow(max(dot(viewDir, reflextDir), 0.0), u_material.shininess);
	vec3 specular =  u_light.specular * (spec * u_material.specular);

	vec3 result = ambient + diffuse + specular;
	gl_FragColor = vec4(result, 1.0);
}
