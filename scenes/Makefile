SCENES = \
	mandatory/v1.json \
	mandatory/v2.json \
	mandatory/v3.json \
	bonuses/ambient_light.json \
	bonuses/cube_slice.json \
	bonuses/disruptions/a0_sphere.json \
	bonuses/disruptions/a1_sphere.json \
	bonuses/disruptions/colour_dis_1.json \
	bonuses/disruptions/colour_dis_2.json \
	bonuses/parallel_light/parallel_light_0.json \
	bonuses/reflection_and_transparency/mirror.json \
	bonuses/reflection_and_transparency/cylinders.json \
	bonuses/reflection_and_transparency/transparency.json \
	bonuses/reflection_and_transparency/refraction_bend.json \
	bonuses/reflection_and_transparency/reflection_and_refraction.json \
	bonuses/reflection_and_transparency/sphere_within_sphere.json \
	bonuses/textures/one_object.json \
	bonuses/textures/4_objects.json \
	bonuses/textures/transformed_tex_scaled.json \
	bonuses/textures/transformed_tex_shifted.json \
	bonuses/textures/t1_skybox.json \
	bonuses/composed_elem.json \

test:
	echo "skipping $(N) first items"
	make -C ..
	-cd ..; a=-1; for scene in $(SCENES) ; do \
		((a=a+1)); \
		if [[ "$$a" -lt "$(N)" ]] ;then \
			echo "SKIPPED: scene $$a:	$$scene "; \
			continue; \
		fi;\
		echo "scene $$a: $$scene"; \
		./RT scenes/$$scene ; \
	done
