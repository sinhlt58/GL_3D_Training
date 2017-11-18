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
	sampler2D specular;
	sampler2D diffuse;
	float shininess;
};

struct DirLight {
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;
};

uniform Material u_material;

#define NUM_POINT_LIGHT 4

uniform DirLight u_dirLight;
uniform PointLight u_pointLights[NUM_POINT_LIGHT];
uniform SpotLight u_spotLight;

//function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir, vec3 fragPos);

void main()
{
	vec4 texture = texture2D(u_texture, v_uv);
	vec4 cs = v_color;
	//gl_FragColor = texture.rgba;
	vec3 normal = normalize(v_normal);
	vec3 viewDir = normalize(u_lightViewPos - v_fragmentPos);

	vec3 result;
	//phase 1: directional light
	result += CalcDirLight(u_dirLight, normal, viewDir);

	//phase 2: point lights
	for (int i=0; i<NUM_POINT_LIGHT; i++){
		result += CalcPointLight(u_pointLights[i], normal, viewDir, v_fragmentPos);
	}

	//pahse 3: spot light
	result += CalcSpotLight(u_spotLight, normal, viewDir, v_fragmentPos);

	gl_FragColor = vec4(result, 1);
}

//calculates a color for a fragment from a directional light
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	//diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	//specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(reflectDir, viewDir), 0.0), u_material.shininess);
	//combine
	vec3 ambient = light.ambient * vec3(texture2D(u_material.diffuse, v_uv));
	vec3 diffuse = light.diffuse * diff * vec3(texture2D(u_material.diffuse, v_uv));
	vec3 specular = light.specular * spec * vec3(texture2D(u_material.specular, v_uv));

	return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos)
{
	vec3 lightDir = normalize(light.position - fragPos);
	//diffuse shading
	float diff = max(dot(lightDir, normal), 0.0);
	//specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(reflectDir, normal), 0.0), u_material.shininess);

	//attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

	//combine
	vec3 ambient = light.ambient * vec3(texture2D(u_material.diffuse, v_uv));
	vec3 diffuse = light.diffuse * diff * vec3(texture2D(u_material.diffuse, v_uv));
	vec3 specular = light.specular * spec * vec3(texture2D(u_material.specular, v_uv));

	ambient  *= attenuation;
	diffuse  *= attenuation;
	specular *= attenuation;

	return ambient + diffuse + specular;
}
	
//calculates a color for a fragment from a spot light
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir, vec3 fragPos)
{
	vec3 lightDir = normalize(light.position - fragPos);
	//diffuse shading
	float diff = max(dot(lightDir, normal), 0.0);
	//specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(reflectDir, normal), 0.0), u_material.shininess);

	//attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

	//spot light intensity
	float theta = max(dot(-lightDir, light.direction), 0.0);
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	//combine
	vec3 ambient = light.ambient * vec3(texture2D(u_material.diffuse, v_uv));
	vec3 diffuse = light.diffuse * diff * vec3(texture2D(u_material.diffuse, v_uv));
	vec3 specular = light.specular * spec * vec3(texture2D(u_material.specular, v_uv));

	ambient  *= attenuation * intensity;
	diffuse  *= attenuation * intensity;
	specular *= attenuation * intensity;

	return ambient + diffuse + specular;
}