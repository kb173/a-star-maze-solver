#include <iostream>
#include <climits>
#include <vector>
#include <map>
#include <algorithm>

struct Maze {
    char data[41][41];
};

struct MazeNode {
    MazeNode(std::vector<uint> v, uint priority) : v(v), priority(priority) {}
    std::vector<uint> v;
    uint priority;
};

Maze solve_maze(const Maze &maze) {
    Maze result;

    result = maze;
    
    std::vector<MazeNode> nodes;
    std::make_heap(nodes.begin(), nodes.end(), [](MazeNode n1, MazeNode n2){return n1.priority > n2.priority;});

    nodes.push_back(MazeNode(std::vector<uint>{1, 1}, 0));
    std::push_heap(nodes.begin(), nodes.end(), [](MazeNode n1, MazeNode n2){return n1.priority > n2.priority;});

    std::map<std::vector<uint>, uint> costs;
    std::map<std::vector<uint>, std::vector<uint>> parents;

    costs[std::vector<uint>{1, 1}] = 1;

    while(true) {
        // Get the best node
        MazeNode best = nodes.front();
        std::pop_heap(nodes.begin(), nodes.end(), [](MazeNode n1, MazeNode n2){return n1.priority > n2.priority;});
        nodes.pop_back();

        uint current_x = best.v[0];
        uint current_y = best.v[1];
        std::vector<uint> here = std::vector<uint>{current_x, current_y};

        // Are we done?
        if (current_x == 39 && current_y == 39) {
            std::vector<uint> parent = here;

            while (true) {
                result.data[parent[1]][parent[0]] = 'o';

                if (parents.find(parent) == parents.end()) break;
                parent = parents[parent];
            }
            return result;
        }

        for (int kernel_y = -1; kernel_y <= 1; kernel_y++) {
            for (int kernel_x = -1; kernel_x <= 1; kernel_x++) {
                // Ignore the current position
                if (kernel_x == 0 && kernel_y == 0) continue;

                uint x = current_x + kernel_x;
                uint y = current_y + kernel_y;

                // Can we go here?
                if (maze.data[y][x] == '#') continue;

                std::vector<uint> next = std::vector<uint>{x, y};

                // The cost is the travelled distance to the next node
                uint cost = costs[here] + abs(kernel_y) + abs(kernel_x);

                // If this node hasn't been added yet or its costs are better, add it!
                if (costs.find(next) == costs.end() || cost < costs[next]) {
                    costs[next] = cost;
                    uint priority = cost + (39 - x) + (39 - y);

                    // Add this node
                    nodes.push_back(MazeNode(next, priority));
                    std::push_heap(nodes.begin(), nodes.end(), [](MazeNode n1, MazeNode n2){return n1.priority > n2.priority;});

                    parents[next] = here;
                }
            }
        }
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
