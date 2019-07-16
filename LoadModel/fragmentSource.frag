#version 330 core     
//in vec4 vertexColor;
//in vec2 TexCoord; //uv®y¼Ð
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;   

//uniform sampler2D ourTexture;
uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;

void main(){
    vec3 lightDir = normalize(lightPos - FragPos);
	vec3 diffuse = dot(lightDir, Normal) * lightColor;
	FragColor = vec4( (ambientColor + diffuse) * objColor, 1.0f);
}   