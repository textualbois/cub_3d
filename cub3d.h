#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MLX42/MLX42.h"
#include "libft/libft.h"
#include "world.h"
#include "movement.h"

// inits //

void	init_loops_n_hooks(t_World_Controller *world);

//hooks//
void ft_move_pc(void *param);

#endif