from numpy.random import shuffle
import numpy as np

import abc


class MazeGenAlgo:
    __metaclass__ = abc.ABCMeta

    def __init__(self, h, w):
        assert w >= 3 and h >= 3, "Mazes cannot be smaller than 3x3."
        self.h = h
        self.w = w
        self.H = (2 * self.h) + 1
        self.W = (2 * self.w) + 1

    @abc.abstractmethod
    def generate(self):
        return None

    """ All of the methods below this are helper methods,
    common to many maze-generating algorithms.
    """

    def _find_neighbors(self, r, c, grid, is_wall=False):
        """Find all the grid neighbors of the current position; visited, or not.
        Args:
            r (int): row of cell of interest
            c (int): column of cell of interest
            grid (np.array): 2D maze grid
            is_wall (bool): Are we looking for neighbors that are walls, or open cells?
        Returns:
            list: all neighboring cells that match our request
        """
        ns = []

        if r > 1 and grid[r - 2][c] == is_wall:
            ns.append((r - 2, c))
        if r < self.H - 2 and grid[r + 2][c] == is_wall:
            ns.append((r + 2, c))
        if c > 1 and grid[r][c - 2] == is_wall:
            ns.append((r, c - 2))
        if c < self.W - 2 and grid[r][c + 2] == is_wall:
            ns.append((r, c + 2))

        shuffle(ns)
        return ns


class Kruskal(MazeGenAlgo):
    def __init__(self, h, w):
        super(Kruskal, self).__init__(h, w)

    def generate(self):
        """highest-level method that implements the maze-generating algorithm
        Returns:
            np.array: returned matrix
        """
        # create empty grid
        grid = np.empty((self.H, self.W), dtype=np.int8)
        grid.fill(1)

        forest = []
        for row in range(1, self.H - 1, 2):
            for col in range(1, self.W - 1, 2):
                forest.append([(row, col)])
                grid[row][col] = 0

        edges = []
        for row in range(2, self.H - 1, 2):
            for col in range(1, self.W - 1, 2):
                edges.append((row, col))
        for row in range(1, self.H - 1, 2):
            for col in range(2, self.W - 1, 2):
                edges.append((row, col))

        shuffle(edges)

        while len(forest) > 1:
            ce_row, ce_col = edges[0]
            edges = edges[1:]

            tree1 = -1
            tree2 = -1

            if ce_row % 2 == 0:  # even-numbered row: vertical wall
                tree1 = sum(
                    [
                        i if (ce_row - 1, ce_col) in j else 0
                        for i, j in enumerate(forest)
                    ]
                )
                tree2 = sum(
                    [
                        i if (ce_row + 1, ce_col) in j else 0
                        for i, j in enumerate(forest)
                    ]
                )
            else:  # odd-numbered row: horizontal wall
                tree1 = sum(
                    [
                        i if (ce_row, ce_col - 1) in j else 0
                        for i, j in enumerate(forest)
                    ]
                )
                tree2 = sum(
                    [
                        i if (ce_row, ce_col + 1) in j else 0
                        for i, j in enumerate(forest)
                    ]
                )

            if tree1 != tree2:
                new_tree = forest[tree1] + forest[tree2]
                temp1 = list(forest[tree1])
                temp2 = list(forest[tree2])
                forest = [
                    x for x in forest if x != temp1
                ]  # faster than forest.remove(temp1)
                forest = [x for x in forest if x != temp2]
                forest.append(new_tree)
                grid[ce_row][ce_col] = 0

        return grid
