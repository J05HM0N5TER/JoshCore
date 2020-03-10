// classic Phong fragment shader
#version 410

in vec4 vPosition;
in vec3 vNormal;

uniform vec3 Ia; // ambient light colour

uniform vec3 Id1; // diffuse light colour 
uniform vec3 Is1; // specular light colour
uniform vec3 LightDirection1;

uniform vec3 Id2; // diffuse light colour 
uniform vec3 Is2; // specular light colour
uniform vec3 LightDirection2;

uniform vec3 Ka; // ambient material colour 
uniform vec3 Kd; // diffuse material colour 
uniform vec3 Ks; // specular material colour
uniform float specularPower; // material specular power

uniform vec3 cameraPosition;

// The colour of the pixel
out vec4 FragColour;

void main() 
{
	// ---- Light 1 ----
	// ensure normal and light direction are normalised
	vec3 normal = normalize(vNormal);
	vec3 light1 = normalize(LightDirection1);

	// calculate lambert term (negate light1 direction)
	float lambertTerm1 = max(0, min(1, dot(normal, -light1)));

	// calculate view vector and reflection vector 
	vec3 direction = normalize(cameraPosition - vPosition.xyz); 
	vec3 reflection1 = reflect( light1, -normal ); 
	
	// calculate specular term 
	float specularTerm1 = pow( max( 0, dot( direction, reflection1 ) ), 
		/* 50.0 */specularPower );

	// calculate each colour property
	vec3 ambient = Ia * Ka;
	vec3 diffuse1 = Id1 * Kd * lambertTerm1;
	vec3 specular1 = Is1 * Ks * specularTerm1;
	
	// ---- Light 2 ----
	
	vec3 light2 = normalize(LightDirection2);

	// calculate lambert term (negate light1 direction)
	float lambertTerm2 = max(0, min(1, dot(normal, -light2)));

	// calculate view vector and reflection vector 
	vec3 reflection2 = reflect( light1, -normal ); 
	
	// calculate specular term 
	float specularTerm2 = pow( max( 0, dot( direction, reflection2 ) ), 
		/* 50.0 */specularPower );

	// calculate each colour property
	vec3 diffuse2 = Id2 * Kd * lambertTerm2;
	vec3 specular2 = Is2 * Ks * specularTerm2;
	
	// Merge lights	
	vec3 light_effect = ambient + (diffuse1 + specular1 + diffuse2 + specular2);
	
	// output final colour
	FragColour = vec4( light_effect, 1 );
}