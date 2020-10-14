#include <iostream>
#include <climits>
#include <vector>
#include <map>
#include <algorithm>

struct Maze {
    char data[41][41];
};

struct MazeNode {
    MazeNode(uint x, uint y, uint cost, uint travelled) : x(x), y(y), cost(cost), travelled(travelled) {}
    uint x;
    uint y;
    uint cost;
    uint travelled;
};

Maze solve_maze(const Maze &maze) {
    Maze result;

    result = maze;
    
    std::vector<MazeNode> nodes;
    std::make_heap(nodes.begin(), nodes.end(), [](MazeNode n1, MazeNode n2){return n1.cost > n2.cost;});

    nodes.push_back(MazeNode(1, 1));
    std::push_heap(nodes.begin(), nodes.end(), [](MazeNode n1, MazeNode n2){return n1.cost > n2.cost;});

    std::map<MazeNode, uint> costs;
    std::map<MazeNode, MazeNode> parents;

    for (int i = 0; i < 5000; i++) {
        // Get the best node
        MazeNode best = nodes.front();
        std::pop_heap(nodes.begin(), nodes.end(), [](MazeNode n1, MazeNode n2){return n1.cost > n2.cost;});
        nodes.pop_back();

        int current_x = best.x;
        int current_y = best.y;

        result.data[current_y][current_x] = 'P';

        std::cout << i << ": " << current_x << ", " << current_y << " with " << best.travelled << " travelled" << " and cost " << best.cost << std::endl;

        for (int kernel_y = -1; kernel_y <= 1; kernel_y++) {
            for (int kernel_x = -1; kernel_x <= 1; kernel_x++) {
                // Ignore the current position
                if (kernel_x == 0 && kernel_y == 0) continue;

                int x = current_x + kernel_x;
                int y = current_y + kernel_y;

                // Can we go here?
                if (maze.data[y][x] == '#') continue;

                // The cost is the already travelled distance together with the optimal
                //   distance from here to the target
                uint cost = best.travelled + 1 + (39 - x) + (39 - y);

                // Add this node
                nodes.push_back(MazeNode(x, y, cost, best.travelled + 1));
                std::push_heap(nodes.begin(), nodes.end(), [](MazeNode n1, MazeNode n2){return n1.cost > n2.cost;});
            }
        }

        std::cout << nodes.size() << std::endl;
    }
    
    return result;
}

int main() {
    // Read in the maze
    Maze maze;

    for (int line = 0; line < 41; line++) {
        for (int col = 0; col < 41; col++) {
            maze.data[line][col] = getchar();
        }

        // Read the newline char
        getchar();
    }

    Maze result = solve_maze(maze);

    // Print the result
    for (int line = 0; line < 41; line++) {
        for (int col = 0; col < 41; col++) {
            std::cout << result.data[line][col];
        }

        std::cout << '\n';
    }

    return 0;
}
