uniform mat4 matViewProjection;
uniform vec3 lightPosition; // ��Դλ��
uniform vec3 eyePosition; // ��λ��
uniform vec4 ambient; // ��������ɫ
uniform vec3 lightColor; // ��Դ��ɫ
uniform float Ns; // �߹���ɫ
uniform float attenuation; // ���ߵ�˥��ϵ��
varying vec4 color; // ��Ƭ����ɫ��ר�ݵĲ���

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