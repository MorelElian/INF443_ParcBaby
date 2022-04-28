#include "elementar.hpp"
#include "math.h"

using namespace cgp;

mesh create_torus_mesh(float radius, float thickness, float start_angle, float end_angle, int radial_resolution, int tubular_resolution){
    mesh m;
    // generate vertices
    //m.position.resize(2*radial_resolution*tubular_resolution);
    //start_angle = fmod(start_angle, M_PI * 2.0);
    //end_angle = fmod(end_angle, M_PI * 2.0);
    if (end_angle == 0)
        end_angle = 2*M_PI;
    end_angle += 0.1;
    for (int i = 0; i < radial_resolution; i++) {
        for (int j = 0; j < tubular_resolution; j++) {
            float u = start_angle + (float)j / tubular_resolution * (end_angle - start_angle);
            float v =  (float)i  / radial_resolution *  M_PI * 2.0;
            float x = (radius + thickness * std::cos(v)) * std::cos(u);
            float y = (radius + thickness * std::cos(v)) * std::sin(u);
            float z = thickness * std::sin(v);
            //std::cout << x << ", " << y << ", " << z << std::endl;
            m.position.push_back(vec3{x, y, z});
        }
    }
    // add quad faces
    for (int i = 0; i < radial_resolution; i++) {
        int i_next = (i + 1) % radial_resolution;
        for (int j = 0; j < tubular_resolution-1; j++) {
            int j_next = (j + 1) % tubular_resolution;
            int i0 = i * tubular_resolution + j;
            int i1 = i * tubular_resolution + j_next;
            int i2 = i_next * tubular_resolution + j_next;
            int i3 = i_next * tubular_resolution + j;
            uint3 triangle_1 = {i1, i3, i0};
            uint3 triangle_2 = {i1, i2, i3};
            m.connectivity.push_back(triangle_1);
            m.connectivity.push_back(triangle_2);
        }
    }
    m.fill_empty_field();
    return m;
}

mesh mesh_primitive_parapede(float longueur, float largeur, float hauteur)
{
	mesh shape;
	shape.position = { vec3(0,0,0),vec3(0,longueur,0),vec3(largeur,longueur,0),vec3(largeur,0,0),
						vec3(0,0,-hauteur), vec3(0,longueur,-hauteur), vec3(largeur,longueur,-hauteur), vec3(largeur,0,-hauteur) };
	shape.connectivity = { {0,1,3},{1,2,3},{4,1,0},{1,4,5},{5,2,1},{2,5,6},{7,3,2},{7,2,6},{4,3,0},{4,7,3},
		{4,6,7},{4,5,6} };
	shape.fill_empty_field();
	return shape;
}

mesh mesh_primitive_smoothCylinder(float radius, float height)
{
    float radius2 = radius/5.0;
    vec3 p1 = {0,0,0};
    vec3 p2 = {0,0,height};
    mesh disc1 = mesh_primitive_disc(radius - radius2,p1);
    mesh disc2 = mesh_primitive_disc(radius- radius2,p2);
    
    vec3 p3 = {0,0,radius2};
    vec3 p4 = {0,0,height - radius2};
    mesh cylinder = mesh_primitive_cylinder(radius,p3,p4);

    mesh torus1 = mesh_primitive_torus(radius-radius2,radius2,p3);
    mesh torus2 = mesh_primitive_torus(radius-radius2,radius2,p4);

	cylinder.push_back(disc1);
    cylinder.push_back(disc2);
    cylinder.push_back(torus1);
    cylinder.push_back(torus2);
	return cylinder;
}