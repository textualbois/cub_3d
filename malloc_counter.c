#include "malloc_counter.h"

void	malloc_counter(char* file, char* function, int line,int increment, int type, char *info)
{
	static int our_malloc_delta = 0;
	static int parser_delta = 0;
	static int new_images = 0;
	static int new_textures = 0;
	static int other_mallocs = 0;
	char *pwd = "/Users/isemin/Documents/all_study/cub3d/ours/first";

	FILE *fp_malloc = fopen("mallocs.log", "a");
	FILE *fp_free = fopen("frees.log", "a");

	if (!fp_malloc || !fp_free) {
		fprintf(stderr, "Error opening log files.\n");
		return;
	}
	char fullPath[256];
	snprintf(fullPath, sizeof(fullPath), "file://%s/%s", "/Users/isemin/Documents/all_study/cub3d/ours/first", file);
	if (info)
	{
		printf("%s:%d: %s: %s\n", fullPath, line, function, info);
	}
	if (type == MALLOC)
	{
		our_malloc_delta += increment;
		if (increment > 0)
		{
			fprintf(fp_malloc, "%s:%d: %s: Malloc: current delta %d\n", fullPath, line, function, our_malloc_delta);
			printf("Malloc: current delta %d\n", our_malloc_delta);
		}
		else
		{
			fprintf(fp_free, "%s:%d: %s: Free: current delta %d\n", fullPath, line, function, our_malloc_delta);
			printf("Free: current delta %d\n", our_malloc_delta);
		}
	}
	else if (type == IMAGE)
	{
		new_images += increment;
		if (increment > 0)
		{
			fprintf(fp_malloc, "%s:%d: %s: Malloc: current delta %d\n", fullPath, line, function, new_images);
			printf("New images: current delta %d\n", new_images);
		}
		else
		{
			fprintf(fp_free, "%s:%d: %s: Free: current delta %d\n", fullPath, line, function, new_images);
			printf("Free images: current delta %d\n", new_images);
		}
	}
	else if (type == TEXTURE)
	{
		new_textures += increment;
		if (increment > 0)
		{
			fprintf(fp_malloc, "%s:%d: %s: Malloc: current delta %d\n", fullPath, line, function, new_textures);
			printf("New textures: current delta %d\n", new_textures);
		}
		else
		{
			fprintf(fp_free, "%s:%d: %s: Free: current delta %d\n", fullPath, line, function, new_textures);
			printf("Free textures: current delta %d\n", new_textures);
		}
	}
	else if (type == OTHER)
	{
		other_mallocs += increment;
		if (increment > 0)
		{
			fprintf(fp_malloc, "%s:%d: %s: Malloc: current delta %d\n", fullPath, line, function, other_mallocs);
			printf("Other: current delta %d\n", increment);
		}
		else
		{
			fprintf(fp_free, "%s:%d: %s: Free: current delta %d\n", fullPath, line, function, other_mallocs);
			printf("Free other: current delta %d\n", increment);
		}
	}
	else if (type == PARSER)
	{
		parser_delta += increment;
		if (increment > 0)
		{
			fprintf(fp_malloc, "%s:%d: %s: Malloc: current delta %d\n", fullPath, line, function, parser_delta);
			printf("parser malloc: current delta %d\n", parser_delta);
		}
		else
		{
			fprintf(fp_malloc, "%s:%d: %s: Malloc: current delta %d\n", fullPath, line, function, parser_delta);
			printf("parser free: current delta %d\n", parser_delta);
		}
	}
	else
	{
		printf("results at end of program:\n");
		printf("main Malloc: %d\n", our_malloc_delta);
		printf("parser and libft: %d\n", parser_delta);
		printf("New images: %d\n", new_images);
		printf("New textures: %d\n", new_textures);
		printf("Other mallocs: %d\n", other_mallocs);
	}
	fflush(stdout);
}