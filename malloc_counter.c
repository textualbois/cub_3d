#include "malloc_counter.h"

#define MAX_TRACKED_PTRS 1024

// Simple static array for tracking pointers
static void *tracked_ptrs[MAX_TRACKED_PTRS] = {0};
static int tracked_count = 0;

void add_tracked_ptr(void *ptr) {
	if (tracked_count < MAX_TRACKED_PTRS) {
		tracked_ptrs[tracked_count++] = ptr;
	} else {
		fprintf(stderr, "Warning: pointer tracking array is full!\n");
	}
}

void remove_tracked_ptr(void *ptr) {
	for (int i = 0; i < tracked_count; i++) {
		if (tracked_ptrs[i] == ptr) {
			// Replace this pointer with the last one in the array
			tracked_ptrs[i] = tracked_ptrs[tracked_count - 1];
			tracked_ptrs[tracked_count - 1] = NULL;
			tracked_count--;
			return;
		}
	}
}

void print_tracked_ptrs(void) {

	FILE *fp = fopen("log_results.log", "a");
	if (tracked_count == 0) {
		printf("No unfreed pointers.\n");
		return;
	}
	fprintf(fp, "Unfreed pointers:\n");
	for (int i = 0; i < tracked_count; i++) {
		fprintf(fp, "%p\n, ", tracked_ptrs[i]);
	}
}

void	malloc_counter(const char* file, const char* function, int line,int increment, int type, char *info, void *ptr)
{
	static int our_malloc_delta = 0;
	static int parser_delta = 0;
	static int new_images = 0;
	static int new_textures = 0;
	static int other_mallocs = 0;
	char *pwd = "/Users/isemin/Documents/all_study/cub3d/ours/first";

	FILE *fp_malloc = fopen("log_mallocs.log", "a");
	FILE *fp_free = fopen("log_frees.log", "a");

	if (!fp_malloc || !fp_free) {
		fprintf(stderr, "Error opening log files.\n");
		return;
	}
	char fullPath[256];
	snprintf(fullPath, sizeof(fullPath), "file://%s/%s", pwd, file);

	printf("%s:%d: %s: %s\n", fullPath, line, function, info);
	if (type == MALLOC)
	{
		our_malloc_delta += increment;
		if (increment > 0)
		{
			add_tracked_ptr(ptr);
			fprintf(fp_malloc, "%s:%d: %s: %s - Malloc: current delta %d %p\n", fullPath, line, function, info, our_malloc_delta, ptr);
			printf("Malloc: current delta %d\n", our_malloc_delta);
		}
		else
		{
			remove_tracked_ptr(ptr);
			fprintf(fp_free, "%s:%d: %s: %s - Free: current delta %d %p\n", fullPath, line, function, info, our_malloc_delta, ptr);
			printf("Free: current delta %d\n", our_malloc_delta);
		}
	}
	else if (type == IMAGE)
	{
		new_images += increment;
		if (increment > 0)
		{
			add_tracked_ptr(ptr);
			fprintf(fp_malloc, "%s:%d: %s: %s - Malloc: current delta %d %p\n", fullPath, line, function, info, new_images, ptr);
			printf("New images: current delta %d\n", new_images);
		}
		else
		{
			remove_tracked_ptr(ptr);
			fprintf(fp_free, "%s:%d: %s: %s - Free: current delta %d %p\n", fullPath, line, function, info, new_images, ptr);
			printf("Free images: current delta %d\n", new_images);
		}
	}
	else if (type == TEXTURE)
	{
		new_textures += increment;
		if (increment > 0)
		{
			add_tracked_ptr(ptr);
			fprintf(fp_malloc, "%s:%d: %s: %s - Malloc: current delta %d %p\n", fullPath, line, function, info, new_textures, ptr);
			printf("New textures: current delta %d\n", new_textures);
		}
		else
		{
			remove_tracked_ptr(ptr);
			fprintf(fp_free, "%s:%d: %s: %s - Free: current delta %d %p\n", fullPath, line, function, info, new_textures, ptr);
			printf("Free textures: current delta %d\n", new_textures);
		}
	}
	else if (type == OTHER)
	{
		other_mallocs += increment;
		if (increment > 0)
		{
			add_tracked_ptr(ptr);
			fprintf(fp_malloc, "%s:%d: %s: %s - Malloc: current delta %d %p\n", fullPath, line, function, info, other_mallocs, ptr);
			printf("Other: current delta %d\n", increment);
		}
		else
		{
			remove_tracked_ptr(ptr);
			fprintf(fp_free, "%s:%d: %s: %s - Free: current delta %d %p\n", fullPath, line, function, info, other_mallocs, ptr);
			printf("Free other: current delta %d\n", increment);
		}
	}
	else if (type == PARSER)
	{
		parser_delta += increment;
		if (increment > 0)
		{
			add_tracked_ptr(ptr);
			fprintf(fp_malloc, "%s:%d: %s: %s - Malloc: current delta %d %p\n", fullPath, line, function, info, parser_delta, ptr);
			printf("parser malloc: current delta %d\n", parser_delta);
		}
		else
		{
			remove_tracked_ptr(ptr);
			fprintf(fp_free, "%s:%d: %s: %s - Malloc: current delta %d %p\n", fullPath, line, function, info, parser_delta, ptr);
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
		print_tracked_ptrs();
	}
	fflush(stdout);
}