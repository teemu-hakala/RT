SCENES = \
	a0_sphere.json \
	a1_plane.json \
	a2_cone.json \
	a3_cylinder.json \
	a4_cube.json \
	b4_spheres.json \
	b5_cylinder.json \
	c6_intersections.json \
	c6_intersections_multilight.json \
	c7_cylinders_plane.json \
	christmastree.json \
	cone.json \
	d10_z_axis.json \
	d11_axes.json \
	d8_x_axis.json \
	d9_y_axis.json \
	e12_sphere.json \
	e13_sphere.json \
	f14_sphere_shadow.json \
	f15_complex.json \
	f15_complex_debug.json \
	f15_complex_parallel.json \
	g4_cube_checkered.json \
	g4_cube_pattern.json \
	light_parallel_sphere.json \
	light_spot_cylinder.json \
	light_spot_sphere.json \
	minimum.json \
	p0_spheres.json \
	p1_cylinder.json \
	plane.json \
	plane_patterns.json \
	sphere.json \
	t0_world.json \
	t1_skybox.json \
	rayacers/d0_default_world.json \
	rayacers/d1_default_world_test_3.json \
	rayacers/d2_default_world_test_4.json \
	rayacers/n0_two_spheres.json \
	rayacers/n1_two_spheres.json \
	rayacers/n2_three_spheres_spot.json \
	rayacers/n3_three_spheres_parallel.json \
	rayacers/n3_three_spheres_parallel_branch_traveler.json \
	rayacers/n4_three_spheres_spot.json \
	rayacers/r0_reflective_sphere.json \
	rayacers/r1_reflective_plane.json \
	rayacers/r2_reflective_cone.json \
	rayacers/r3_reflective_cylinder.json \
	rayacers/r4_sphere_shadow.json \
	rayacers/r5_livingroom.json \
	rayacers/r6_planes.json \
	rayacers/r7_raytrap.json \
	rayacers/r7_raytrap_sphere.json \
	rayacers/reflection_room.json \
	rayacers/room.json \


test:
	echo "skipping $(N) first items"
	make -C ..
	-cd ..; a=-1; for scene in  $(SCENES) ; do \
		((a=a+1)); \
		if [[ "$$a" -lt "$(N)" ]] ;then \
			echo "SKIPPED: scene $$a:	$$scene "; \
			continue; \
		fi;\
		echo "scene $$a: $$scene"; \
		./RT scenes/$$scene ; \
	done
