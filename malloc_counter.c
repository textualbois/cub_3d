#include "types_numeric.h"

void malloc_counter(int increment, int type, char* info)
{
	static int our_malloc_delta = 0;
	static int new_images = 0;
	static int new_textures = 0;

	if (info)
		printf("%s\n", info);
	if (type == MALLOC)
	{
		our_malloc_delta += increment;
		if (increment > 0)
			printf("Malloc: %d\n", our_malloc_delta);
		else
			printf("Free: %d\n", our_malloc_delta);
	}
	else if (type == IMAGE)
	{
		new_images += increment;
		if (increment > 0)
			printf("New images: %d\n", new_images);
		else
			printf("Free images: %d\n", new_images);
	}
	else if (type == TEXTURE)
	{
		new_textures += increment;
		if (increment > 0)
			printf("New textures: %d\n", new_textures);
		else
			printf("Free textures: %d\n", new_textures);
	}
	else if (type == OTHER)
	{
		if (increment > 0)
			printf("Other: %d\n", increment);
		else
			printf("Free other: %d\n", increment);
	} else {
		printf("results at end of program:\n");
		printf("Malloc: %d\n", our_malloc_delta);
		printf("New images: %d\n", new_images);
		printf("New textures: %d\n", new_textures);
	}
}