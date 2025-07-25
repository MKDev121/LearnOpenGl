#version 330 core
in vec3 vertexColor;
out vec4 ourColor;
void main(){
	ourColor=vec4(vertexColor,1.0f);
}