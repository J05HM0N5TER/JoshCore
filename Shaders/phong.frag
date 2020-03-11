// classic Phong fragment shader
#version 410

in vec4 v_position;
in vec3 v_normal; 
in vec2 final_texture_coodinates;
in vec3 v_tangent;
in vec3 v_bitangent;
out vec4 frag_colour; 

uniform sampler2D diffuse_texture; // Diffuse texture
uniform sampler2D normal_texture;  // Normal texture

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

void main() 
{
	vec4 texture_colour = texture(diffuse_texture, final_texture_coodinates);
	if (texture_colour.a < 0.0001)
		discard;

	// Normal stuff
	vec4 normal_col = texture(normal_texture, final_texture_coodinates);
	vec3 textureNormal = normal_col.xyz * 2.0 - 1.0;
	//Ensure normal and light direction are normalised 
	vec3 N = normalize(v_normal);
	vec3 T = normalize(v_tangent);
	vec3 B = normalize(v_bitangent); 

	mat3 TBN = mat3(T, B, N); 

	// Normal useing normal map
	vec3 perturbedNormal = TBN * textureNormal;
	// Nagate new normal (testing only)
	//perturbedNormal = v_normal;


	// ---- Light 1 ----
	// ensure normal and light direction are normalised
	vec3 light1 = normalize(LightDirection1);

	// calculate lambert term (negate light1 direction)
	float lambertTerm1 = max(0, min(1, dot(perturbedNormal, -light1)));

	// calculate view vector and reflection vector 
	vec3 direction = normalize(cameraPosition - v_position.xyz); 
	vec3 reflection1 = reflect( light1, -perturbedNormal ); 
	
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
	float lambertTerm2 = max(0, min(1, dot(perturbedNormal, -light2)));

	// calculate view vector and reflection vector 
	vec3 reflection2 = reflect( light1, -perturbedNormal ); 
	
	// calculate specular term 
	float specularTerm2 = pow( max( 0, dot( direction, reflection2 ) ), 
		/* 50.0 */specularPower );

	// calculate each colour property
	vec3 diffuse2 = Id2 * Kd * lambertTerm2;
	vec3 specular2 = Is2 * Ks * specularTerm2;
	
	// Merge lights	
	vec3 light_effect = ambient + (diffuse1 + specular1 + diffuse2 + specular2);
	
	// output final colour
	frag_colour = texture_colour * vec4( light_effect, 1 );
	//frag_colour = vec4(normal_col.rgb, 1);
}