# Lem-in
Lem-in is a pathfinding and flow optimization program which calculates optimal paths through a graph network, depending on the number of units that need to be sent.

The program simulates the problem by sending a number of ants from a starting room, through a network of interconnected rooms, to an end room. Each room, except for the start and end, has a capacity of 1 ant.

Paths are found using the Edmonds-Karp algorithm, modified for a node capacity of 1 and with edge capacities discarded, creating a max-flow graph. Additionally, every generated flow state during this process is evaluated for efficiency, resulting in the most efficient path set for traversing the required number of units.

---

# Table of Contents
- [Implementation](#implementation)
  - [Path Discovery](#path-discovery)
  - [Path Traversal](#path-traversal)
- [Setup](#setup)
  - [Dependencies](#dependencies)
  - [Configuration](#configuration)
  - [Build](#build)
- [Usage](#usage)
- [References](#references)
- [Credits](#credits)
- [License](#license)

---

# Implementation
The map input (detailed [below](#usage)) is first parsed through a [common parser](src/common_functions.c#L18), generating the [graph system](hdr/common.h#L211) used by both `lem-in` and `visu-hex` executables.

The map describes the number of units ([ants](hdr/common.h#L108)) traversing the graph network, the nodes ([rooms](hdr/common.h#L176)) and their coordinates, and the edges ([links](hdr/common.h#L251)) connecting them. Any lines not recognised by the common parser are placed into a [storage list](hdr/common.h#L231) for later interpretation by the target executable. This mechanism is [primarily used by the visualiser](src/visualizer.c#L27) to process solver-specific output. Any remaining lines are [emitted](src/farm/destroy_farm.c#L23) as comments (#!) when execution completes.

The [Solver](src/main.c#L33) (lem-in) implements a [modified version](src/path/find_paths.c#L94) of the Edmonds-Karp algorithm. Edmonds-Karp is designed to compute the maximum flow through a network between an input node and an output node. In its traditional form, the amount of flow is constrained by the capacity of the edges connecting the nodes.

<div style="background:white; display:inline-block; padding:10px; border-radius:6px;">
  <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/3/3e/Edmonds-Karp_flow_example_0.svg/3840px-Edmonds-Karp_flow_example_0.svg.png" style="max-width:423px; height:auto;" />
</div>

The Lem-in network, however, is not constrained by edge capacity. Instead, each room, with the exception of the start and end rooms, has a node capacity of one unit. This capacity is represented during the Path Discovery phase through the [in and out pointers](hdr/common.h#L183) of a node, and during the Path Traversal phase through the node's [ant pointer](hdr/common.h#L190).

---

## Path Discovery
Path discovery operates in three alternating stages: BFS, flow-network augmentation, and flow-state evaluation.

The first stage performs a [BFS (Breadth First Search)](src/path/find_paths.c#L101) from the start node to the end node in the current graph. Traversal is [permitted](src/path/find_paths.c#L187) over unused edges and in reverse direction over edges belonging to previously established paths (counter-current traversal). During traversal, each visited node stores a reference to the node from which it was reached in its [parent pointer](hdr/common.h#L186). When the end node is reached, the chain of parent pointers, starting from the end node, forms the shortest available path, known as the augmenting path. If the end node cannot be reached, the flow state has reached maximum flow and no further augmenting paths exist.

The second stage follows the augmenting path and updates the current flow state by [modifying](src/path/find_paths.c#L103) the [in and out pointers](hdr/common.h#L183) for each node along the path. This either creates a new path when traversing unused edges, or splits and reroutes existing paths when traversing counter-current edges of already established flows.

In the third stage, the [set of available paths](src/path/find_paths.c#L105) in the current flow state is generated. This flow state is then [evaluated](src/path/find_paths.c#L106) by computing the projected number of turns required for all units to traverse the network under that configuration. The resulting cost is [compared](src/path/find_paths.c#L109) against the previously best known flow state, and the best-performing path set is stored.

When no further augmenting paths can be found, the flow state with the lowest evaluated cost remains as the optimal solution.
<div style="background:white; display:inline-block; padding:10px; border-radius:6px;">
  <img src="https://github.com/OthelloPlusPlus/lem-in/blob/img/EdmondsKarp.gif" alt="EdmondsKarp" width="69%"/>
</div>

---

## Path Traversal
During Path Discovery, each path in the path set already has a number of units assigned to it. During Path Traversal, a list of ants is [created](src/main.c#L42) and prepared for movement.

Each turn, represented by a line in the output, the ants currently traversing the network are [moved sequentially](src/ant/move_ants_through_farm.c#L31) according to their assigned paths. Each node contains an [ant pointer](hdr/common.h#L186) which indicates a room’s occupancy and is used by ants to verify availability during movement. Movement of active ants is emitted using the standard `L[ant_id]-[room]` format.

After all active ants have attempted their movement for the current turn, new ants are [introduced](src/ant/move_ants_through_farm.c#L32) into the network where their starting nodes are unoccupied and the path has not yet reached its assigned unit capacity.

Additional protection is implemented to avoid invalid movements. If an ant is scheduled to move during its turn but its destination node is occupied, the ant is placed into a [retry queue](src/ant/move_ants_through_farm.c#L77) and [re-attempts](src/ant/move_ants_through_farm.c#L74) its movement later within the same turn.

While it should be impossible given a correct path set, if an ant cannot complete its movement after the full turn cycle, it is [removed from the retry queue](src/ant/queue.c) and will retry during the next turn as normal. This stalled movement is indicated by emitting the `X[ant_id]-[room]` format.

---

# Setup

## Dependencies
This project depends on:
- [libft](https://github.com/OthelloPlusPlus/Libft) (42 standard library)
- [MLX42](https://github.com/codam-coding-college/MLX42) (for visualisation mode)

These dependencies are expected to be installed in standard user or system prefixes.

---

## Configuration
Before building the project, generate the Makefile using the configure script.
```sh
# Default
./configure
# If dependencies (such as libft and MLX42) are installed in non-standard locations
./configure --with-lib=[path/to/libs] --with-include=[path/to/includes]
```

---

## Build
This project builds two executables, lem-in and visu-hex, from a shared codebase.
The two targets share parsing and core data structures, with separate execution layers for solving and visualisation.

```sh
make            # Build all targets
make lem-in     # Build solver
make visu-hex   # Build visualiser
```

---

# Usage
The solver reads a map from STDIN describing the number of ants traversing the nest, the rooms in the nest, and how those rooms are interconnected. The format is as follows:
- First line: an unsigned integer representing the number of ants
- Room definitions: `[name] [x] [y]`
- Link definitions: `[name]-[name]`
The following rules must be adhered to:
- Room names must be alphanumeric or `_`
- Room names must not start with `L` (reserved for output formatting)
- Commands can be added starting with `##`. Unknown commands are ignored. Two commands are mandatory:
  - `##start` marks the next room as the starting room
  - `##end` marks the next room as the ending room
- Lines starting with `#` are treated as comments and ignored

```sh
6

##start
start 1 0
4 2 4
3 0 4
2 2 2
1 0 2
##end
end 1 6

start-1
start-2
1-3
2-4
3-end
4-end
```

The solver first repeats the parsed input, adding comments that describe the internal graph structure and selected paths. It then outputs the calculated ant movements in the following format:
`L[ant_id]-[room] [L[ant_id]-[room] ...]`
Each line represents a single turn, wherein each active ant only moves once.

```sh
6

# Rooms 6
##start
start 1 0
4 2 4
3 0 4
2 2 2
1 0 2
##end
end 1 6

# Links 6
start-1
start-2
1-3
2-4
3-end
4-end

# Paths 2
#  3 ants > start > 1 > 3 > end
#  3 ants > start > 2 > 4 > end

# Moves 
L1-1 L2-2 
L1-3 L2-4 L3-1 L4-2 
L1-end L2-end L3-3 L4-4 L5-1 L6-2 
L3-end L4-end L5-3 L6-4 
L5-end L6-end 
# Number of lines: 5
```

The visualiser reads the solver output from STDIN and and generates a visual representation of the ans moving through their nest.

A HUD is displayed in the top-left corner with available control modes.

The following commands can be used to run the solver and visualiser:

```sh
# Run a series of valid and invalid maps
make demo
./demo.sh
# Run solver
./lem-in < file.map
# Run solver with visualisation
./lem-in < file.map | ./visu-hex
```

---

# References

[Flow network](https://en.wikipedia.org/wiki/Flow_network)

[Edmonds–Karp algorithm](https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm)

[BFS - Breadth-first search](https://en.wikipedia.org/wiki/Breadth-first_search)

---

# Credits
Othello<br>
[<img alt="LinkedIn" height="32px" src="https://github.githubassets.com/images/modules/logos_page/GitHub-Mark.png" target="_blank" />](https://github.com/OthelloPlusPlus)
[<img alt="LinkedIn" height="32px" src="https://upload.wikimedia.org/wikipedia/commons/c/ca/LinkedIn_logo_initials.png" target="_blank" />](https://nl.linkedin.com/in/orlando-hengelmolen)

# License
Copyright (c) 2026 Othello

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

1. The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

2. The Software may not be modified, adapted, merged, or used to create
   derivative works. It may not be incorporated into other software projects,
   libraries, or products in modified or unmodified form without prior written
   permission from the author.

3. Any use of the Software in a public project, website, application, or
   distributed product must include clear attribution to the author (Othello),
   such as in a credits file, documentation, or an “About” section.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
