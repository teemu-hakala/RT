SCENES = \
	a0_sphere.json \
	a1_plane.json \
	a2_cone.json \
	a3_cylinder.json \
	b4_spheres.json \
	b5_cylinder.json \
	c6_intersections.json \
	c6_intersections_multilight.json \
	c7_cylinders_plane.json \
	d8_x_axis.json \
	d9_y_axis.json \
	d10_z_axis.json \
	d11_axes.json \
	e12_sphere.json \
	e13_sphere.json \
	f14_sphere_shadow.json \
	f15_complex.json \
	f15_complex_debug.json \
	minimum.json \
	plane.json \
	cone.json \
	sphere.json \

test:
	make -C ..
	-for scene in  $(SCENES) ; do \
		echo "$$scene"; \
		../RTv1 $$scene ; \
	done
