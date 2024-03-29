#version 330 core     
//in vec4 vertexColor;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;//uv�y��

struct Material {
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct LightPoint {
	float constant;
	float linear;
	float quadratic;
};

struct LightSpot {
	float cosPhyInner;
	float cosPhyOutter;
};

uniform Material material;
uniform LightPoint lightP;
uniform LightSpot lightS;

//uniform sampler2D ourTexture;
uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightDirUniform;
uniform vec3 lightColor;
uniform vec3 cameraPos;

out vec4 FragColor;   

void main(){
    vec3 norm = normalize(Normal);

	float dist = length(lightPos - FragPos);
	float attenuation = 1.0 / (lightP.constant + lightP.linear * dist + lightP.quadratic * (dist * dist));

	vec3 lightDir = normalize(lightPos - FragPos); // vector pointing to the light, from fragment pos
	vec3 reflectVec = reflect(-lightDir, norm);
	vec3 cameraVec = normalize(cameraPos - FragPos);

	// specular
	float specularAmount = pow(max(dot(reflectVec, cameraVec), 0.0), material.shininess);
	vec3 specular = texture(material.specular, TexCoord).rgb * specularAmount * lightColor;

	// diffuse
	vec3 diffuse = texture(material.diffuse, TexCoord).rgb * max(dot(lightDir, norm), 0.0) * lightColor; // use max() to ensure that dot(L,N) will not lower than 0.

	// ambient
	vec3 ambient = texture(material.diffuse, TexCoord).rgb * ambientColor;

	// emission
	vec3 emission = texture(material.emission, TexCoord).rgb;

	float cosTheta = dot( -lightDir, normalize(-1 * lightDirUniform));
	                  // clamp() constraint the first parameter between second and third parameters 
	float spotRatio = clamp((cosTheta - lightS.cosPhyOutter) / (lightS.cosPhyInner - lightS.cosPhyOutter), 0.0, 1.0);

	FragColor = vec4( (ambient + (diffuse + specular) * spotRatio) * objColor, 1.0f);
	
}   