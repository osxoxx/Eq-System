#include <iostream>
#include <string>

using namespace std;

class Item {
public:
    string name;
    int level;
    int durability;
    float critChance;
    string enchantment;
    float weight;
    int cost;

    // Constructor
    Item(string name, int level, int durability, float critChance, string enchantment, float weight, int cost)
        : name(name), level(level), durability(durability), critChance(critChance), enchantment(enchantment), weight(weight), cost(cost) {}
};

class Equipment {
    Item*** grid;
    int rows;
    int cols;

public:
    // Constructor
    Equipment(int rows = 5, int cols = 5) : rows(rows), cols(cols) {
        grid = new Item**[rows];
        for (int i = 0; i < rows; i++) {
            grid[i] = new Item*[cols]();
        }
    }

    // Destructor
    ~Equipment() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                delete grid[i][j];
            }
            delete[] grid[i];
        }
        delete[] grid;
    }

    // Display the equipment grid
    void display() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j]) {
                    cout << "[" << grid[i][j]->name << "]\t";
                } else {
                    cout << "[]\t";
                }
            }
            cout << endl;
        }
    }

    // Add an item to the equipment grid
    void addItem(Item* item, int row, int col) {
        if (isValidPosition(row, col)) {
            delete grid[row][col];
            grid[row][col] = item;
        } else {
            cout << "Invalid position\n";
        }
    }

    // Show details of an item at a specific position
    void showDetails(int row, int col) {
        if (isValidPosition(row, col) && grid[row][col]) {
            cout << "Details: " << endl;
            cout << "Name: " << grid[row][col]->name << endl
                 << "Durability: " << grid[row][col]->durability << endl
                 << "Level: " << grid[row][col]->level << endl
                 << "CritChance: " << grid[row][col]->critChance << endl
                 << "Enchantment: " << grid[row][col]->enchantment << endl
                 << "Weight: " << grid[row][col]->weight << endl
                 << "Cost: " << grid[row][col]->cost << endl;
        } else {
            cout << "No item at this position or invalid position\n";
        }
    }

    // Move an item from one position to another
    void moveItem(int row, int col, int secondRow, int secondCol) {
        if (isValidPosition(row, col) && isValidPosition(secondRow, secondCol)) {
            swap(grid[row][col], grid[secondRow][secondCol]);
        } else {
            cout << "Invalid position\n";
        }
    }

    // Delete an item from a specific position
    void deleteItem(int row, int col) {
        if (isValidPosition(row, col)) {
            delete grid[row][col];
            grid[row][col] = nullptr;
        } else {
            cout << "Invalid position\n";
        }
    }

private:
    // Check if the given position is valid
    bool isValidPosition(int row, int col) {
        return row >= 0 && row < rows && col >= 0 && col < cols;
    }
};

void game() {
    Equipment E;
    Item* item1 = new Item("Sword", 1, 3, 2.0, "Sharpness", 10.2, 100);
    Item* item2 = new Item("Shield", 1, 4, 0.0, "Protection", 5.2, 100);

    E.addItem(item1, 0, 0);
    E.addItem(item2, 0, 1);

    E.display();
    cout << endl;
    E.moveItem(0, 0, 0, 3);
    E.display();
    E.deleteItem(0, 1);
    E.display();

    delete item1;
    delete item2;
}

int main() {
    game();
    return 0;
}


