#version 330 core                               
layout(location = 0) in vec3 aPos;              
//layout(location = 1) in vec3 aColor; 
//layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aNormal;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectMat;

//out vec4 vertexColor;  
//out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

void main(){                    
   gl_Position = projectMat * viewMat * modelMat * vec4(aPos, 1.0f);
   Normal = mat3(modelMat) * aNormal;
   //FragPos = vec3(modelMat * vec4(aPos, 1.0f));
   //vertexColor = vec4(aColor, 1.0f);
   //TexCoord = aTexCoord;
} 