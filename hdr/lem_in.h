/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:41:36 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/28 16:27:06 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

/* ************************************************************************** */
/*                                  Includes                                  */
/* ************************************************************************** */
# pragma region Includes

# include "common.h"

# pragma endregion Includes

/* ************************************************************************** */
/*                                 Structures                                 */
/* ************************************************************************** */
# pragma region Structures

/**
 * @brief BFS queue node.
 *
 * Holds a room reference used during BFS traversal.
 *
 * @param room Current room in queue
 * @param next Next queue node
 *
 * @author Othello
 */
typedef struct s_bfs
{
	t_room*			room;
	struct s_bfs*	next;
}	t_bfs;

/**
 * @brief FIFO queue used for BFS traversal.
 *
 * Stores BFS nodes in insertion order for graph search.
 *
 * @param first First element in queue
 * @param last Last element in queue
 *
 * @author Othello
 */
typedef struct s_bfs_queue
{
	t_bfs*	first;
	t_bfs*	last;
}	t_bfs_queue;

/**
 * @brief Path representation as a linked sequence of steps.
 *
 * A path is a ordered list of rooms from start to end.
 * It also stores runtime metadata used for distribution
 * of entities across multiple paths.
 *
 * @param length Number of steps in the path
 * @param ants Number of ants assigned to this path
 * @param first First step in the path
 * @param last Last step in the path
 * @param next Next path in list
 *
 * @author Othello
 */
typedef struct s_path
{
	int				length;
	int				ants;
	struct s_step*	first;
	struct s_step*	last;
	struct s_path*	next;
}	t_path;

/**
 * @brief Container for all computed paths.
 *
 * Stores global path metadata used for optimisation,
 * including total path count, longest path length,
 * and estimated number of turns.
 *
 * @param first First path in list
 * @param last Last path in list
 * @param turns Estimated number of turns for completion
 * @param count Total number of paths
 * @param longest Length of the longest path
 *
 * @author Othello
 */
typedef struct s_paths
{
	t_path*	first;
	t_path*	last;
	int		turns;
	int		count;
	int		longest;
}	t_paths;

/**
 * @brief Single step in a computed path.
 *
 * Represents one room in a path sequence.
 *
 * @param room Room at this step
 * @param next Next step in the path
 *
 * @author Othello
 */
struct s_step
{
	t_room*			room;
	struct s_step*	next;
};

/**
 * @brief Queue node used for ant movement scheduling.
 *
 * Implements a simple linked queue of ants waiting to move.
 *
 * @param ant Ant stored in queue node
 * @param next Next queue element
 *
 * @author Othello
 */
typedef struct s_queue
{
	t_ant*			ant;
	struct s_queue*	next;
}	t_queue;

# pragma endregion Structures

/* ************************************************************************** */
/*                                 Functions                                  */
/* ************************************************************************** */
# pragma region Functions

/* ************************************************************************** */
/*                               Path Search                                  */
/* ************************************************************************** */

/**
 * @brief Finds the most efficient set of valid paths.
 *
 * Modified Edmonds-Karp using room-capacity instead of edge capacity.
 * Each room can belong to only one active path.
 * BFS is used to find augmenting paths in the residual graph.
 *
 * After each successful augmentation, the new path set is evaluated
 * against the current best result. The search stops once no better
 * solution can be produced.
 *
 * @param farm Simulation container
 *
 * @return Most efficient discovered path set.
 *
 * @see https://en.wikipedia.org/wiki/Breadth-first_search
 * @see https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm
 * @see https://en.wikipedia.org/wiki/Suurballe%27s_algorithm
 *
 * @author Othello
 */
t_paths*	find_paths(t_farm* farm);

/* ************************************************************************** */
/*                                Path Lists                                  */
/* ************************************************************************** */

/**
 * @brief Creates a container holding all active paths in the graph.
 *
 * Traverses the currently opened room connections starting from
 * the start room stored in the rooms container.
 * Each discovered path is stored in the returned paths container.
 *
 * @param rooms Rooms container with access to the graph endpoints
 *
 * @return Newly allocated paths container
 *
 * @author Othello
 */
t_paths*	create_paths(t_rooms* rooms);

/**
 * @brief Appends a path to the path container.
 *
 * @param paths Path container
 * @param last Path to append
 *
 * @author Othello
 */
void		paths_push_back(t_paths* paths, t_path* last);

/**
 * @brief Sorts paths by traversal cost.
 *
 * Shorter and more efficient paths are moved first.
 *
 * @param paths Path container
 *
 * @author Othello
 */
void		paths_sort(t_paths* paths);

/**
 * @brief Prints all computed paths.
 *
 * @param paths Path list head
 *
 * @author Othello
 */
void		print_paths(t_path* paths);

/**
 * @brief Frees all paths in a path container.
 *
 * Releases every path and its internal steps, then clears
 * the container itself.
 *
 * @param paths Path container to free
 *
 * @author Othello
 */
void		delete_paths(t_paths* paths);

/**
 * @brief Frees a single path and its steps.
 *
 * Removes all step nodes linked to the path, then frees
 * the path itself.
 *
 * @param path Path to delete
 *
 * @author Othello
 */
void		delete_path(t_path* path);

/* ************************************************************************** */
/*                                   BFS                                      */
/* ************************************************************************** */

/**
 * @brief Computes BFS depth values for all reachable rooms.
 *
 * Depth values are used to guide path traversal
 * and validate room ordering during search.
 *
 * @param farm Simulation container
 *
 * @author Othello
 */
void		bfs_room_depths(t_farm* farm);

/**
 * @brief Adds a room to the BFS queue.
 *
 * @param queue BFS queue
 * @param room Room to enqueue
 *
 * @author Othello
 */
void		add_room_to_queue(t_bfs_queue* queue, t_room* room);

/**
 * @brief Removes and returns the next BFS entry.
 *
 * @param queue BFS queue
 *
 * @return Next queue entry, or NULL if empty
 *
 * @author Othello
 */
t_bfs*		pop_queue(t_bfs_queue* queue);

/**
 * @brief Clears all remaining BFS queue entries.
 *
 * @param queue BFS queue
 *
 * @author Othello
 */
void		clear_bfs_queue(t_bfs_queue* queue);

/* ************************************************************************** */
/*                              Movement System                               */
/* ************************************************************************** */

/**
 * @brief Moves ants through the farm along computed paths.
 *
 * @param farm Simulation container
 * @param path Path list
 *
 * @author Othello
 */
void	move_ants_through_farm(t_farm* farm, t_path* path);

/**
 * @brief Adds an ant to the movement queue.
 *
 * @param queue Queue head pointer
 * @param ant Ant to enqueue
 *
 * @author Othello
 */
void	add_ant_to_queue(t_queue** queue, t_ant* ant);

/**
 * @brief Clears all queued ants.
 *
 * @param queue Queue head
 *
 * @author Othello
 */
void	clear_queue(t_queue* queue);

# pragma endregion Functions

#endif
