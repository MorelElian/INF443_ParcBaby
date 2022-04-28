#include "scene.hpp"
#include "elementar.hpp"
#include "racetrack.hpp"



using namespace cgp;


void scene_structure::initialize()
{
	// Basic set-up
	// global_frame.initialize(mesh_primitive_frame(), "Frame");
	// environment.camera.axis = camera_spherical_coordinates_axis::z;
	// environment.camera.look_at({ 2.0f,-4.0f,2.0f }, { 0,0,0 });

	global_frame.initialize(mesh_primitive_frame(), "Frame");
	environment.camera.axis = camera_spherical_coordinates_axis::z;
	environment.camera.look_at({ 15.0f,6.0f,6.0f }, { 0,0,0 });

	racetrack = create_racetrack_mesh_drawable();

}





void scene_structure::display()
{
	// Basic elements of the scene
	environment.light = environment.camera.position();
	if (gui.display_frame)
		draw(global_frame, environment);

	racetrack["racetrack1"].transform.translation = {0,0,-3};
	racetrack["racetrack1"].transform.rotation = cgp::rotation_transform::from_axis_angle({1,0,0}, M_PI/6.0);
	racetrack.update_local_to_global_coordinates();
	draw(racetrack, environment);
	
}


void scene_structure::display_gui()
{
	//ImGui::Checkbox("Frame", &gui.display_frame);
	//ImGui::SliderFloat("Time scale", &timer.scale, 0.0f, 2.0f);
	//ImGui::SliderFloat("Particle emission", &timer.event_period, 0.1f, 2.0f);

}


