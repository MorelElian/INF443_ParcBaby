#pragma once
#include "cgp/cgp.hpp"
#define M_PI 3.1415


cgp::mesh create_torus_mesh(float radius, float thickness, float start_angle, float end_angle, int radial_resolution, int tubular_resolution);
cgp::mesh mesh_primitive_parapede(float longueur, float largeur, float hauteur);
cgp::mesh mesh_primitive_smoothCylinder(float radius, float height);