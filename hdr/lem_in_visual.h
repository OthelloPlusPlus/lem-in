/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_visual.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 19:40:39 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/28 20:59:58 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_VISUAL_H
# define LEM_IN_VISUAL_H

/* ************************************************************************** */
/*                                  Includes                                  */
/* ************************************************************************** */
# pragma region Includes

# include <MLX42/MLX42.h>
# include "common.h"

# pragma endregion Includes

/* ************************************************************************** */
/*                                    Enums                                   */
/* ************************************************************************** */
# pragma region Enums

/**
 * @brief UI execution mode for visualization loop.
 *
 * @param DONE Simulation finished state
 * @param STEP Manual step-by-step mode
 * @param AUTO Automatic playback mode
 * @param MODE_SIZE Enum boundary marker
 *
 * @author Othello
 */
typedef enum e_mode
{
	DONE,
	STEP,
	AUTO,
	MODE_SIZE,
}	t_mode;

# pragma endregion Enums

/* ************************************************************************** */
/*                                 Structures                                 */
/* ************************************************************************** */
# pragma region Structures

/**
 * @brief Runtime UI state controller.
 *
 * Controls simulation execution flow and input handling state.
 *
 * @param active Whether visualization is running
 * @param step Step execution flag
 * @param mode Current execution mode
 *
 * @author Othello
 */
typedef struct state
{
	bool	active;
	bool	step;
	t_mode	mode;
}	t_state;

/**
 * @brief Loaded texture resources.
 *
 * Stores raw PNG textures used for rendering entities.
 *
 * @param background Background texture
 * @param ant Ant sprite texture
 * @param room Room sprite texture
 * @param start Start room texture
 * @param end End room texture
 *
 * @author Othello
 */
typedef struct s_png
{
	mlx_texture_t*	background;
	mlx_texture_t*	ant;
	mlx_texture_t*	room;
	mlx_texture_t*	start;
	mlx_texture_t*	end;
}	t_png;

/**
 * @brief Rendered image instances.
 *
 * Holds MLX image objects created from textures.
 *
 * @param background Background image
 * @param room Room image
 * @param start Start room image
 * @param end End room image
 * @param mode HUD mode text
 * @param pause HUD pause text
 * @param info_ants HUD ant counter text
 * @param info_turns HUD turn counter text
 *
 * @author Othello
 */
typedef struct s_img
{
	mlx_image_t*	background;
	mlx_image_t*	room;
	mlx_image_t*	start;
	mlx_image_t*	end;
	mlx_image_t*	mode;
	mlx_image_t*	pause;
	mlx_image_t*	info_ants;
	mlx_image_t*	info_turns;
}	t_img;

/**
 * @brief Visualization subsystem container.
 *
 * Wraps MLX context, rendering resources, and runtime state.
 *
 * @param mlx MLX context handle
 * @param png Texture resources
 * @param img Rendered images
 * @param state UI runtime state
 * @param turns Current simulation turn counter
 *
 * @author Othello
 */
typedef struct s_visual
{
	mlx_t*		mlx;
	t_png		png;
	t_img		img;
	t_state		state;
	u_int32_t	turns;
	uint32_t	step_size;
}	t_visual;

/**
 * @brief Single movement instruction for an ant.
 *
 * Represents a transition of an ant to a room.
 *
 * @param id Movement identifier
 * @param ant Target ant
 * @param room Destination room
 * @param next Next movement in list
 *
 * @author Othello
 */
typedef struct s_move
{
	int				id;
	t_ant*			ant;
	t_room*			room;
	struct s_move*	next;
}	t_move;

/**
 * @brief Container for grouped movement sequences.
 *
 * Stores linked lists of moves per simulation step.
 *
 * @param moves Move sequence head
 * @param next Next move group
 *
 * @author Othello
 */
typedef struct s_moves
{
	t_move*			moves;
	struct s_moves*	next;
}	t_moves;

/**
 * @brief Global application superstructure.
 *
 * Combines farm simulation, visualization, and movement tracking.
 *
 * @param farm Core simulation state
 * @param visual Rendering subsystem
 * @param moves Movement history/queue
 *
 * @author Othello
 */
typedef struct s_superstruct
{
	t_farm		farm;
	t_visual	visual;
	t_moves*	moves;
}	t_ss;

# pragma endregion Structures

/* ************************************************************************** */
/*                                 Functions                                  */
/* ************************************************************************** */
# pragma region Functions

/* ************************************************************************** */
/*                              Parsing Functions                             */
/* ************************************************************************** */

/**
 * @brief Parses remaining visualization input data.
 *
 * @param ss Superstructure container
 *
 * @author Othello
 */
void	parse_remnant_visual(t_ss* ss);

/* ************************************************************************** */
/*                                  Movements                                 */
/* ************************************************************************** */

/**
 * @brief Creates a movement node.
 *
 * @param ants Ant container
 * @param id Movement identifier
 * @param list Room list
 * @param name Target room name
 *
 * @return Allocated move node
 *
 * @author Othello
 */
t_move*	create_move(t_ants* ants, int id, t_room* list, char* name);

/**
 * @brief Parses movement data into structured form.
 *
 * @param ss Superstructure container
 * @param array Input string array
 *
 * @return true if parsing succeeded
 *
 * @author Othello
 */
bool	parse_moves(t_ss* ss, char** array);

/**
 * @brief Frees a linked list of moves.
 *
 * Iterates through all nodes in the move list and releases each one.
 *
 * @param move Head of the move list to delete
 *
 * @author Othello
 */
void	delete_move_list(t_move* move);

/**
 * @brief Frees a single t_moves container and its associated move list.
 *
 * Deletes all t_move nodes owned by the container, then removes the
 * container itself from the linked list chain.
 * Advances the pointer to the next node.
 *
 * @param moves Double pointer to the current t_moves node to delete.
 *
 * @author Othello
 */
void	delete_moves_from_list(t_moves** moves);

/**
 * @brief Frees the entire linked list of t_moves containers.
 *
 * Iteratively removes every t_moves node and its associated move list
 * until the structure is fully deallocated.
 *
 * @param moves Head of the t_moves list
 *
 * @author Othello
 */
void	delete_all_moves(t_moves* moves);

/**
 * @brief Transfers ants into movement tracking system.
 *
 * @param farm Simulation container
 * @param moves Move container
 *
 * @author Othello
 */
void	add_ants_to_moves(t_farm* farm, t_moves* moves);

/* ************************************************************************** */
/*                                MLX System                                  */
/* ************************************************************************** */

/**
 * @brief Initializes visualization subsystem.
 *
 * @param visual Visualization container
 *
 * @author Othello
 */
void	prepare_visual(t_visual* visual);

/**
 * @brief Frees all graphical resources used by the visualizer.
 *
 * Releases all loaded textures and rendered images associated with the
 * MLX rendering context. This includes static UI elements (background,
 * rooms, UI overlays) as well as dynamically created ant images.
 *
 * The function ensures that both texture memory and runtime image
 * instances are properly destroyed to prevent leaks in the graphics layer.
 *
 * @param visual Main visualizer container holding MLX context and assets
 * @param ants   Ant container used to iterate and free per-ant images
 *
 * @author Othello
 */
void	delete_visuals(t_visual* visual, t_ants* ants);

/**
 * @brief Starts MLX rendering loop.
 *
 * @param visual Visualization container
 *
 * @author Othello
 */
void	start_mlx(t_visual* visual);

/**
 * @brief Keyboard input event handler.
 *
 * @param keydata Key event data
 * @param param User context pointer
 *
 * @author Othello
 */
void	key_hook(mlx_key_data_t keydata, void* param);

/**
 * @brief Main render loop callback.
 *
 * @param param User context pointer
 *
 * @author Othello
 */
void	loop_hook(void* param);

/**
 * @brief Sets visualization execution mode.
 *
 * @param visual Visualization container
 * @param mode Execution mode
 *
 * @author Othello
 */
void	set_mode(t_visual* visual, t_mode mode);

/* ************************************************************************** */
/*                               MLX Helpers                                  */
/* ************************************************************************** */

/**
 * @brief Centers an image at a position.
 *
 * @param img Image to position
 * @param inst Instance index
 * @param posx X coordinate
 * @param posy Y coordinate
 *
 * @author Othello
 */
void	center_image(mlx_image_t* img, int32_t inst, int32_t posx, int32_t posy);

/**
 * @brief Scales image to target dimensions.
 *
 * @param img Image to scale
 * @param width Target width
 * @param height Target height
 *
 * @author Othello
 */
void	scale_image_to(mlx_image_t* img, double width, double height);

/**
 * @brief Packs RGBA color components into integer.
 *
 * @param r Red channel
 * @param g Green channel
 * @param b Blue channel
 * @param a Alpha channel
 *
 * @return Packed RGBA value
 *
 * @author Othello
 */
uint32_t	rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

/**
 * @brief Packs RGB color components into integer.
 *
 * @param r Red channel
 * @param g Green channel
 * @param b Blue channel
 *
 * @return Packed RGB value
 *
 * @author Othello
 */
uint32_t	rgb(uint8_t r, uint8_t g, uint8_t b);

/* ************************************************************************** */
/*                                Render Farm                                 */
/* ************************************************************************** */

/**
 * @brief Adds rooms to visualization scene.
 *
 * @param rooms Room container
 * @param visual Visualization subsystem
 *
 * @author Othello
 */
void	add_rooms_to_visual(t_rooms* rooms, t_visual* visual);

/**
 * @brief Adds ants to visualization scene.
 *
 * @param farm Simulation container
 * @param visual Visualization subsystem
 *
 * @author Othello
 */
void	add_ants_to_visual(t_farm* farm, t_visual* visual);

/**
 * @brief Draws links between rooms.
 *
 * @param farm Simulation container
 * @param img Image container
 *
 * @author Othello
 */
void	draw_links(t_farm* farm, t_img* img);

/* ************************************************************************** */
/*                                Render HUD                                  */
/* ************************************************************************** */

/**
 * @brief Displays full HUD information overlay.
 *
 * @param visual Visualization container
 * @param farm Simulation container
 *
 * @author Othello
 */
void	put_info_strings(t_visual* visual, t_farm* farm);

/**
 * @brief Displays current mode indicator.
 *
 * @param visual Visualization container
 *
 * @author Othello
 */
void	put_info_mode(t_visual* visual);

/**
 * @brief Displays pause state indicator.
 *
 * @param visual Visualization container
 *
 * @author Othello
 */
void	put_info_pause(t_visual* visual);

/**
 * @brief Displays ant count HUD element.
 *
 * @param visual Visualization container
 * @param num Ant count value
 *
 * @author Othello
 */
void	put_info_ants(t_visual* visual, u_int32_t num);

/**
 * @brief Displays turn counter HUD element.
 *
 * @param visual Visualization container
 *
 * @author Othello
 */
void	put_info_turns(t_visual* visual);

# pragma endregion Functions

#endif
