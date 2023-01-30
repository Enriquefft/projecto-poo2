from random import choice, randrange
import numpy as np

# https://github.com/john-science/mazelib/blob/main/mazelib/generate/MazeGenAlgo.py

RANDOM = 1
SERPENTINE = 2

_hunt_order = RANDOM

h = 3
w = 3


def generate():
    H = (2 * h) + 1
    W = (2 * w) + 1
    # create empty grid
    grid = np.empty((H, W), dtype=np.int8)
    grid.fill(1)

    # find an arbitrary starting position
    # 1 3 5 7 9  11

    # 1 2 3 4 5  6
    # 2 4 6 8 10 12
    # 1 3 5 7 9  11
    grid[randrange(1, H, 2)][randrange(1, W, 2)] = 0
    num_visited = 1
    row, col = _hunt(grid, num_visited)

    # perform many random walks, to fill the maze
    while row != -1 and col != -1:
        walk = _generate_random_walk(grid, (row, col))
        num_visited += _solve_random_walk(grid, walk, (row, col))
        (row, col) = _hunt(grid, num_visited)

    return grid


def _hunt(grid, count):
    """Based on how this algorithm was configured, choose hunt for the next starting point.

    Args:
        grid (np.array): maze array
        count (int): max number of times to iterate
    Returns:
        tuple: next cell
    """
    if _hunt_order == SERPENTINE:
        return _hunt_serpentine(grid, count)
    else:
        return _hunt_random(grid, count)


def _hunt_random(grid, count):
    if count >= (h * w):
        return (-1, -1)

    H = (2 * h) + 1
    W = (2 * w) + 1

    return (randrange(1, H, 2), randrange(1, W, 2))


def _hunt_serpentine(grid, count):

    cell = (1, -1)
    found = False

    H = (2 * h) + 1
    W = (2 * w) + 1

    while not found:
        cell = (cell[0], cell[1] + 2)
        if cell[1] > (W - 2):
            cell = (cell[0] + 2, 1)
            if cell[0] > (H - 2):
                return (-1, -1)

        if grid[cell[0]][cell[1]] != 0:
            found = True

    return cell


def _generate_random_walk(grid, start):
    direction = _random_dir(start)
    walk = {}
    walk[start] = direction
    current = _move(start, direction)

    for row in grid:
        for elem in row:
            if elem == 1:
                print("██", end="")
            elif elem == 0:
                print("  ", end="")
        print()
    # error
    raise Exception("error")
    while grid[current[0]][current[1]] == 1:
        direction = _random_dir(current)
        walk[current] = direction
        current = _move(current, direction)

    return walk


def _random_dir(current):
    H = (2 * h) + 1
    W = (2 * w) + 1
    r, c = current
    options = []
    if r > 1:
        options.append(0)  # North
    if r < (H - 2):
        options.append(1)  # South
    if c > 1:
        options.append(2)  # East
    if c < (W - 2):
        options.append(3)  # West

    direction = choice(options)
    if direction == 0:
        return (-2, 0)  # North
    elif direction == 1:
        return (2, 0)  # South
    elif direction == 2:
        return (0, -2)  # East
    else:
        return (0, 2)  # West


def _move(start, direction):
    """Convolve a position tuple with a direction tuple to generate a new position.

    Args:
        start (tuple): position to start from
        direction (tuple): vector direction to travel to
    Returns:
        tuple: position of next cell to travel to
    """
    return (start[0] + direction[0], start[1] + direction[1])


def _solve_random_walk(grid, walk, start):
    """Move through the random walk, visiting all the cells you touch,
    and breaking down the walls you cross.

    Args:
        grid (np.array): maze array
        walk (dict): random walk directions, from each cell
        start (tuple): position of cell to star the process at
    Returns:
        int: number of steps taken to complete the process
    """
    visits = 0
    current = start

    while grid[current[0]][current[1]] != 0:
        grid[current] = 0
        next1 = _move(current, walk[current])

        new_x = (next1[0] + current[0]) // 2
        new_y = (next1[1] + current[1]) // 2

        # print(f"current: {current}, next: {next1}, new: {new_x, new_y}")
        # print()

        grid[(next1[0] + current[0]) // 2, (next1[1] + current[1]) // 2] = 0
        visits += 1
        current = next1

    return visits


x = generate()

# for row in x:
#     for elem in row:
#         if elem == 1:
#             print("██", end="")
#         elif elem == 0:
#             print("  ", end="")
#     print()
