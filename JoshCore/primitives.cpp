#include "primitives.h"

mesh primitives::create_uv_sphere(float radius /*=1.0f*/, int sectors /*=36*/, int stacks /*= 18*/)
{
	float PI = 3.14159f;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> tex_coords;
	// vertex position
	float x, y, z, xy;
	// vertex normal
	float nx, ny, nz, lengthInv = 1.0f / radius;
	// vertex texCoord
	float s, t;

	float sectorStep = 2 * PI / sectors;
	float stackStep = PI / stacks;
	float sectorAngle, stackAngle;

    for (int i = 0; i <= stacks; ++i)
    {
        stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        xy = radius * cosf(stackAngle);             // r * cos(u)
        z = radius * sinf(stackAngle);              // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for (int j = 0; j <= sectors; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position (x, y, z)
            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);  
            // r * cos(u) * sin(v)
            vertices.push_back({ x,y,z });

            // normalized vertex normal (nx, ny, nz)
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            normals.push_back({ nx,ny,nz });

            // vertex tex coord (s, t) range between [0, 1]
            s = (float)j / sectors;
            t = (float)i / sectors;
            tex_coords.push_back({ s,t });
        }
    }

    // generate CCW index list of sphere triangles
    std::vector<int> indices;
    int k1, k2;
    for (int i = 0; i < stacks; ++i)
    {
        k1 = i * (sectors + 1);     // beginning of current stack
        k2 = k1 + sectors + 1;      // beginning of next stack

        for (int j = 0; j < sectors; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if (i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            // k1+1 => k2 => k2+1
            if (i != (stacks - 1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

    // Convert vertices to put in mesh
    std::vector<vertex> mesh_verts;
    for (size_t i = 0; i < vertices.size(); i++)
    {
        mesh_verts.push_back(vertex(vertices[i]));
    }

    // Create mesh
    mesh uv_sphere(mesh_verts, indices);

    // Return result
    return uv_sphere;
}
