uniform mat4 matViewProjection;
uniform vec3 lightPosition; // 光源位置
uniform vec3 eyePosition; // 眼位置
uniform vec4 ambient; // 环境光颜色
uniform vec3 lightColor; // 光源颜色
uniform float Ns; // 高光颜色
uniform float attenuation; // 光线的衰减系数
varying vec4 color; // 向片断着色器专递的参数

void main(void)
{
   vec3 ECPosition = vec3(gl_ModelViewMatrix * gl_Vertex);
   vec3 N = normalize(gl_NormalMatrix * gl_Normal);
   vec3 L = normalize(lightPosition - ECPosition);
   vec3 V = normalize(eyePosition - ECPosition);
   vec3 H = normalize(V + L);
   vec3 diffuse = lightColor * max(dot(N, L), 0);
   vec3 specular = lightColor * pow(max(dot(N, H), 0), Ns) * attenuation;
   color = vec4(clamp(diffuse + specular, 0.0f, 1.0f), 1.0);
   color += ambient;
   gl_Position = ftransform();
}