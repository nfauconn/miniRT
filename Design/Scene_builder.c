t_scene *scene_builder(t_sceneparam param)
{
	t_scene scene;


	return (scene);
}
/*
Max size of space -100,-100,-100 to 100,100,100?
Tout sur la stack?
How?
chained list of every elements? tree to find precisely the element fast?
list of elements with list of raycaster and list of shapes
list of shapes contain list of plans, sphere and cylinder?

once a precise element is selected, it's probably not too hard to modify
a single parameter of the shape (size, center, axis, colors, checker, etc.)
but only center, sizes and vector are mandatory
*/