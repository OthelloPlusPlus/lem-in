/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:42:47 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/28 20:44:09 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

#include <stdio.h>

/* ************************************************************************** */
/*                                  Includes                                  */
/* ************************************************************************** */
# pragma region Includes

# include <stddef.h>	// NULL
# include <stdbool.h>	// bool

# include <colors.h>
# include <libft.h>

# pragma endregion Includes

/* ************************************************************************** */
/*                                   Defines                                  */
/* ************************************************************************** */
# pragma region Defines

# define MOVE_FLAG	'L'

# define ERR_CALLOC					01, "Failed to calloc() @ %s[%i].", __func__, __LINE__

# define ERR_ROOM_NAME(room)		10, "Illegal Room name %s. Only alphanumerical characters allowed.", room, MOVE_FLAG
# define ERR_ROOM_NAME_L(room)		10, "Illegal Room name %s. Not allowed to start with %c.", room, MOVE_FLAG
# define ERR_ROOM_SPECIAL(room)		11, "Failed to set ##room %s.", room
# define ERR_ROOM_SPECIAL_DOUBLE(room)\
									12, "Double setting ##room %s.", room
# define ERR_ANTCOUNT(count)		13,	"Invalid ant count %i.", count
# define ERR_NO_ROOMS				14, "No rooms set"
# define ERR_NO_START				15, "Start room not set."
# define ERR_NO_END					16, "End room not set."
# define ERR_NO_LINKS				17, "No links set."
# define ERR_NO_PATHS				18, "No paths found."
# define ERR_NO_MOVES				19, "No moves found."

# define ERR_ANT_REMAIN(count)		20, "%i ant(s) remaining.", count
# define ERR_ROOM_NOT_FOUND(room)	21,	"Could not find room %s.", room
# define ERR_LINK_NOT_FOUND(r1, r2)	22,	"Could not find link %s > %s.",	r1, r2
# define ERR_ROOM_LINK(l1, l2)		23, "Could not find room %s to link to %s.", l1, l2

# pragma endregion Defines

/* ************************************************************************** */
/*                            Forward Declarations                            */
/* ************************************************************************** */
# pragma region Forward Declarations

typedef struct s_step		t_step;
typedef struct mlx_image	mlx_image_t;

# pragma endregion Forward Declarations

/* ************************************************************************** */
/*                                 Structures                                 */
/* ************************************************************************** */
# pragma region Structures

/**
 * @brief Container for all ants in the simulation.
 *
 * Stores the total number of ants and a pointer to the first ant node.
 *
 * @param count Total number of ants
 * @param ants Pointer to first ant in linked list
 *
 * @author Othello
 */
typedef struct s_ants
{
	u_int32_t		count;
	struct s_ant*	ants;
}	t_ants;

/**
 * @brief Represents a single ant entity.
 *
 * Tracks position, movement route, rendering data, and linked-list state.
 *
 * @param id Unique ant identifier
 * @param room Current room of the ant
 * @param x X position
 * @param y Y position
 * @param route Movement path route
 * @param img Render image handle
 * @param inst Instance index (renderer-specific)
 * @param prev Previous ant in list
 * @param next Next ant in list
 *
 * @author Othello
 */
typedef struct s_ant
{
	int				id;

	struct s_room	*room;
	u_int32_t		x;
	u_int32_t		y;

	t_step*			route;

	mlx_image_t*	img;
	int32_t			inst;

	struct s_ant*	prev;
	struct s_ant*	next;
}	t_ant;

/**
 * @brief Collection of all rooms in the farm.
 *
 * Stores room list and metadata for grid dimensions.
 *
 * @param list Linked list of rooms
 * @param start Start room
 * @param end End room
 * @param w Width of grid
 * @param h Height of grid
 *
 * @author Othello
 */
typedef struct s_rooms
{
	struct s_room*	list;
	struct s_room*	start;
	struct s_room*	end;
	u_int32_t		w;
	u_int32_t		h;
}	t_rooms;


/**
 * @brief Represents a room in the farm graph.
 *
 * Stores room position, graph connections, pathfinding state,
 * and rendering data used during simulation.
 *
 * @param name Room identifier
 * @param x X coordinate
 * @param y Y coordinate
 * 
 * @param links Connected room array
 * @param in Previous room in active path
 * @param out Next room in active path
 * 
 * @param parent BFS parent room
 * @param depth BFS traversal depth
 * @param visited BFS visitation state
 * 
 * @param ant Occupying ant
 * 
 * @param img Room render image
 * @param inst Render instance id
 * @param label Room label image
 * 
 * @param next Next room in list
 *
 * @author Othello
 */
typedef struct s_room
{
	char*			name;
	u_int32_t		x;
	u_int32_t		y;

	struct s_room**	links;
	struct s_room*	in;
	struct s_room*	out;

	struct s_room*	parent;
	int				depth;
	bool			visited;

	t_ant*			ant;

	mlx_image_t*	img;
	int32_t			inst;
	mlx_image_t*	label;

	struct s_room*	next;
}	t_room;

/**
 * @brief Root container of the entire simulation state.
 *
 * Aggregates ants, rooms, links, and temporary storage.
 *
 * @param ants Ant subsystem
 * @param rooms Room subsystem
 * @param links Link list head
 * @param storage Temporary parsing storage
 *
 * @author Othello
 */
typedef struct s_farm
{
	t_ants				ants;
	t_rooms				rooms;
	struct s_link*		links;
	struct s_storage*	storage;
}	t_farm;

/**
 * @brief Temporary storage container for parsed input data.
 *
 * Holds dynamically allocated string arrays in a linked sequence,
 * used during parsing before being committed to the main farm structure.
 *
 * @param array String array payload
 * @param prev Pointer to previous storage node
 * @param next Pointer to next storage node
 *
 * @author Othello
 */
typedef struct s_storage
{
	char**				array;
	struct s_storage*	prev;
	struct s_storage*	next;
}	t_storage;

/**
 * @brief Graph edge connecting two rooms.
 *
 * Represents a bidirectional or directional connection between rooms.
 *
 * @param name1 First room name
 * @param room1 First room pointer
 * @param name2 Second room name
 * @param room2 Second room pointer
 * @param next Next link in list
 *
 * @author Othello
 */
typedef struct s_link
{
	char*			name1;
	t_room*			room1;
	char*			name2;
	t_room*			room2;

	struct s_link*	next;
}	t_link;

# pragma endregion Structures

/* ************************************************************************** */
/*                                 Functions                                  */
/* ************************************************************************** */
# pragma region Functions

/* ************************************************************************** */
/*                              Parsing Functions                             */
/* ************************************************************************** */

/**
 * @brief Executes general parsing helper routines.
 *
 * @param farm Main simulation container
 *
 * @author Othello
 */
void	common_functions(t_farm* farm);

/**
 * @brief Parses input from file descriptor into farm structure.
 *
 * @param fd File descriptor to read from
 * @param farm Target simulation container
 *
 * @author Othello
 */
void	parse_from_fd(int fd, t_farm* farm);

/**
 * @brief Stores parsed raw input for later processing.
 *
 * @param farm Simulation container
 * @param array Parsed string array
 *
 * @author Othello
 */
void	store_for_later(t_farm* farm, char** array);

/**
 * @brief Removes an entry from temporary storage.
 *
 * @param first Pointer to storage list head
 * @param storage Node to remove
 *
 * @author Othello
 */
void	remove_from_storage(t_storage** first, t_storage* storage);

/* ************************************************************************** */
/*                              Farm Management                               */
/* ************************************************************************** */

/**
 * @brief Initializes farm state before execution.
 *
 * @param farm Simulation container
 *
 * @author Othello
 */
void	prepare_farm(t_farm* farm);

/**
 * @brief Validates farm configuration integrity.
 *
 * @param farm Simulation container
 *
 * @author Othello
 */
void	valid_farm(t_farm* farm);

/**
 * @brief Frees all allocated farm resources.
 *
 * @param farm Simulation container
 *
 * @author Othello
 */
void	destroy_farm(t_farm* farm);

/* ************************************************************************** */
/*                               Ant Functions                                */
/* ************************************************************************** */

/**
 * @brief Parses an ant definition from input line.
 *
 * @param farm Simulation container
 * @param line Input string
 *
 * @return true if parsing succeeded, false otherwise
 *
 * @author Othello
 */
bool	parse_ant(t_farm* farm, char* line);

/**
 * @brief Creates a new ant instance.
 *
 * @param id Ant identifier
 * @param pos Initial room position
 *
 * @return Pointer to newly allocated ant
 *
 * @author Othello
 */
t_ant*	create_ant(u_int32_t id, t_room* pos);

/**
 * @brief Deletes a single ant from the ant list.
 *
 * @param ants Ant container
 * @param ant Ant to remove
 *
 * @author Othello
 */
void	delete_ant(t_ants* ants, t_ant* ant);

/**
 * @brief Deletes all ants in the ant list in the container.
 * 
 * Frees all ants in the ant list in the container.
 * Does not free container itself.
 *
 * @param ants Ant container
 * @param ant Ant to remove
 *
 * @author Othello
 */
void	delete_all_ants(t_ants* ants);

/**
 * @brief Inserts all ants into the farm simulation.
 *
 * @param farm Simulation container
 *
 * @author Othello
 */
void	add_ants_to_farm(t_farm* farm);

/* ************************************************************************** */
/*                              Room Functions                                */
/* ************************************************************************** */

/**
 * @brief Parses a room definition.
 *
 * @param farm Simulation container
 * @param array Input token array
 * @param dst Output room pointer
 *
 * @return true if parsing succeeded, false otherwise
 *
 * @author Othello
 */
bool	parse_room(t_farm* farm, char** array, t_room** dst);

/**
 * @brief Checks whether a room name is valid.
 *
 * Valid names must be alphanumerical and may contain '_'.
 * Names starting with MOVE_FLAG (default 'L') are rejected.
 *
 * @param str Room name to validate
 *
 * @return true if the name is valid, false otherwise.
 *
 * @author Othello
 */
bool	valid_room_name(const char* str);

/**
 * @brief Creates a new room node.
 *
 * @param name Room name
 * @param x X coordinate
 * @param y Y coordinate
 *
 * @return Pointer to allocated room
 *
 * @author Othello
 */
t_room*	create_room(char* name, u_int32_t x, u_int32_t y);

/**
 * @brief Frees all rooms in the simulation.
 *
 * @param rooms Room container
 *
 * @author Othello
 */
void	delete_rooms(t_rooms* rooms);

/**
 * @brief Adds a room into the farm structure.
 *
 * @param farm Simulation container
 * @param room Room to insert
 * @param dst Destination pointer
 *
 * @author Othello
 */
void	add_room_to_farm(t_farm* farm, t_room* room, t_room** dst);

/**
 * @brief Finds a room by its name.
 *
 * @param list Room list head
 * @param name Target name
 *
 * @return Pointer to matching room or NULL if not found
 *
 * @author Othello
 */
t_room*	find_room_by_name(t_room* list, char* name);

/* ************************************************************************** */
/*                              Link Functions                                */
/* ************************************************************************** */

/**
 * @brief Parses a link definition line.
 *
 * @param farm Simulation container
 * @param line Input string
 *
 * @return true if parsing succeeded
 *
 * @author Othello
 */
bool	parse_link(t_farm* farm, char *line);

/**
 * @brief Creates a new link between two rooms.
 *
 * @param name1 First room name
 * @param name2 Second room name
 *
 * @return Pointer to allocated link
 *
 * @author Othello
 */
t_link*	create_link(char* name1, char* name2);

/**
 * @brief Frees all links in the farm.
 *
 * @param farm Simulation container
 *
 * @author Othello
 */
void	delete_links(t_farm* farm);

/**
 * @brief Adds a link to the farm structure.
 *
 * @param farm Simulation container
 * @param link Link to add
 *
 * @author Othello
 */
void	add_link_to_farm(t_farm* farm, t_link* link);

/**
 * @brief Resolves room pointers inside links.
 *
 * @param farm Simulation container
 *
 * @author Othello
 */
void	connect_links(t_farm* farm);

/* ************************************************************************** */
/*                              Debug Functions                               */
/* ************************************************************************** */

/**
 * @brief Prints full farm state.
 *
 * @param farm Simulation container
 *
 * @author Othello
 */
void	print_farm(t_farm* farm);

/**
 * @brief Prints all rooms.
 *
 * @param rooms Room container
 *
 * @author Othello
 */
void	print_rooms(t_rooms* rooms);

/**
 * @brief Prints a single room.
 *
 * @param room Room to print
 *
 * @author Othello
 */
void	print_room(t_room* room);

/**
 * @brief Prints all links.
 *
 * @param links Link list head
 *
 * @author Othello
 */
void	print_links(t_link* links);

/**
 * @brief Exits program with formatted error message.
 *
 * @param __status Exit status code
 * @param msg Format string message
 *
 * @author Othello
 */
void	error_exit(int __status, const char *msg, ...);

# pragma endregion Functions

#endif
