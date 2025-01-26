#ifndef MOVEMENT_H
# define MOVEMENT_H

#include "world.h"

void ft_movement_input(void *param);
//void set_v_rotation(t_World_Controller *world, int angle_delta);
void set_h_rotation(t_World_Controller *world, int angle_delta);
void set_movement(t_World_Controller *world, t_DoublePair delta_x_y);
// void get

#endif