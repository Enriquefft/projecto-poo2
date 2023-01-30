from numpy.random import shuffle


def printMaze(matrix):
    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            print(matrix[i][j], end=" ")
        print()


class Kruskal:
    def __init__(self, h, w):
        self.h = h
        self.w = w
        self.H = (2 * self.h) + 1
        self.W = (2 * self.w) + 1

    def generate(self):
        """highest-level method that implements the maze-generating algorithm
        Returns:
            np.array: returned matrix
        """

        grid = [["X" for _ in range(self.W)] for _ in range(self.H)]

        forest = []
        for row in range(1, self.H - 1, 2):
            for col in range(1, self.W - 1, 2):
                forest.append([(row, col)])
                grid[row][col] = " "

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
                print("old:")
                print(forest)
                new_tree = forest[tree1] + forest[tree2]
                temp1 = list(forest[tree1])
                temp2 = list(forest[tree2])
                forest = [
                    x for x in forest if x != temp1
                ]  # faster than forest.remove(temp1)
                forest = [x for x in forest if x != temp2]
                forest.append(new_tree)
                grid[ce_row][ce_col] = " "
                print("new:")
                print(forest)
                print()
                print()

        return grid


maze = Kruskal(5, 5).generate()
print("\nFinished Maze:")
for row in maze:
    for elem in row:
        print(elem, end=" ")
    print()
