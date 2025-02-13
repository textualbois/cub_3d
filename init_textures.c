/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:25:59 by vmamoten          #+#    #+#             */
/*   Updated: 2025/02/13 14:26:20 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

// Функция возвращает 0 при успехе, или ненулевое значение при ошибке
int init_textures(t_World_Controller *world, t_config *config)
{
    mlx_texture_t *tex;

    // Загрузка северной текстуры
    tex = mlx_load_png(config->no_texture);
    if (!tex)
    {
        printf("Failed to load NO texture from: %s\n", config->no_texture);
        return (1);
    }
    world->texture_no = mlx_texture_to_image(world->window, tex);
    if (!world->texture_no)
    {
        printf("Failed to create image from NO texture\n");
        return (1);
    }

    // Загрузка южной текстуры
    tex = mlx_load_png(config->so_texture);
    if (!tex)
    {
        printf("Failed to load SO texture from: %s\n", config->so_texture);
        return (1);
    }
    world->texture_so = mlx_texture_to_image(world->window, tex);
    if (!world->texture_so)
    {
        printf("Failed to create image from SO texture\n");
        return (1);
    }

    // Загрузка западной текстуры
    tex = mlx_load_png(config->we_texture);
    if (!tex)
    {
        printf("Failed to load WE texture from: %s\n", config->we_texture);
        return (1);
    }
    world->texture_we = mlx_texture_to_image(world->window, tex);
    if (!world->texture_we)
    {
        printf("Failed to create image from WE texture\n");
        return (1);
    }

    // Загрузка восточной текстуры
    tex = mlx_load_png(config->ea_texture);
    if (!tex)
    {
        printf("Failed to load EA texture from: %s\n", config->ea_texture);
        return (1);
    }
    world->texture_ea = mlx_texture_to_image(world->window, tex);
    if (!world->texture_ea)
    {
        printf("Failed to create image from EA texture\n");
        return (1);
    }

    return (0);
}
