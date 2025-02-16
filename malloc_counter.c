#include "malloc_counter.h"

void malloc_counter(int increment, int type, char* info)
{
	static int our_malloc_delta = 0;
	static int parser_delta = 0;
	static int new_images = 0;
	static int new_textures = 0;

	if (info)
		printf("%s\n", info);
	if (type == MALLOC)
	{
		our_malloc_delta += increment;
		if (increment > 0)
			printf("Malloc: current delta %d\n", our_malloc_delta);
		else
			printf("Free: current delta %d\n", our_malloc_delta);
	}
	else if (type == IMAGE)
	{
		new_images += increment;
		if (increment > 0)
			printf("New images: current delta %d\n", new_images);
		else
			printf("Free images: current delta %d\n", new_images);
	}
	else if (type == TEXTURE)
	{
		new_textures += increment;
		if (increment > 0)
			printf("New textures: current delta %d\n", new_textures);
		else
			printf("Free textures: current delta %d\n", new_textures);
	}
	else if (type == OTHER)
	{
		if (increment > 0)
			printf("Other: current delta %d\n", increment);
		else
			printf("Free other: current delta %d\n", increment);
	} else if (type == PARSER)
	{
		parser_delta += increment;
		if (increment > 0)
			printf("parser malloc: current delta %d\n", parser_delta);
		else
			printf("parser free: current delta %d\n", parser_delta);
	} else {
		printf("results at end of program:\n");
		printf("main Malloc: %d\n", our_malloc_delta);
		printf("parser and libft: %d\n", parser_delta);
		printf("New images: %d\n", new_images);
		printf("New textures: %d\n", new_textures);
	}
	fflush(stdout);
}