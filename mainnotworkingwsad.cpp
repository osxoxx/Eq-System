#include <iostream>
#include <string>
#include <thread>

using namespace std;

class Item {
public:
    string name;
    int level;
    int durability;
    string enchantment;
    float weight;
    int cost;
    string type;

    // Constructor
    Item(string name = "item", int level = 1, int durability = 1, string enchantment = " ", float weight = 0.0, int cost = 0.0, string type = "")
        : name(name), level(level), durability(durability),  enchantment(enchantment), weight(weight), cost(cost), type(type) {}
};

class Equipment {
public:
    Item*** grid;
    int rows;
    int cols;
    int currentRow;
    int currentCol;

    // Constructor
    Equipment(int rows = 5, int cols = 5) : rows(rows), cols(cols), currentRow(0), currentCol(0) {
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
                if (i == currentRow && j == currentCol) {
                    cout << "[X]\t";
                } else if (grid[i][j]) {
                    cout << "[" << grid[i][j]->name << "]\t";
                } else {
                    cout << "[]\t";
                }
            }
            cout << endl;
        }
    }

    // Move the cursor position based on user input
    void moveCursor(char direction) {
        switch (direction) {
        case 'W':
            if (currentRow > 0) currentRow--;
            break;
        case 'A':
            if (currentCol > 0) currentCol--;
            break;
        case 'S':
            if (currentRow < rows - 1) currentRow++;
            break;
        case 'D':
            if (currentCol < cols - 1) currentCol++;
            break;
        default:
            cout << "Invalid direction\n";
        }
    }

    // Add an item to the equipment grid at cursor position
    void addItem(Item* item) {
        if (grid[currentRow][currentCol]) {
            delete grid[currentRow][currentCol];
        }
        grid[currentRow][currentCol] = item;
    }
};

class Player {
public:
    int HP;
    Item* mainHand;
    Item* armor;
    Item* boots;
    Item* pants;
    Item* secondHand;
    Equipment* eq;


    Player() {
        HP = 100;
        mainHand = nullptr;
        armor = nullptr;
        boots = nullptr;
        pants = nullptr;
        secondHand = nullptr;
        eq = new Equipment();
    }
    void setMainWeapon() {
        Item* temp = mainHand;
        if(eq->grid[eq->currentRow][eq->currentCol]->type == "Weapon"){
            mainHand = eq->grid[eq->currentRow][eq->currentCol];
            eq->grid[eq->currentRow][eq->currentCol] = temp;
        }else{
            cout<<"Invalid type of item"<<endl;
        }

    }
    void setMainArmor() {
        Item* temp = armor;
        if(eq->grid[eq->currentRow][eq->currentCol]->type == "Armor"){
            armor = eq->grid[eq->currentRow][eq->currentCol];
            eq->grid[eq->currentRow][eq->currentCol] = temp;
        }else{
            cout<<"Invalid type of item"<<endl;
        }
    }
    void setMainBoots() {
        Item* temp = boots;
        if(eq->grid[eq->currentRow][eq->currentCol]->type == "Boots"){
            boots = eq->grid[eq->currentRow][eq->currentCol];
            eq->grid[eq->currentRow][eq->currentCol] = temp;
        }else{
            cout<<"Invalid type of item"<<endl;
        }
    }
    void setMainPants() {
        Item* temp = pants;
        if(eq->grid[eq->currentRow][eq->currentCol]->type == "Pants"){
            pants = eq->grid[eq->currentRow][eq->currentCol];
            eq->grid[eq->currentRow][eq->currentCol] = temp;
        }else{
            cout<<"Invalid type of item"<<endl;
        }
    }
    void setMainSecondHand() {
        Item* temp = secondHand;
        if(eq->grid[eq->currentRow][eq->currentCol]->type == "Shield"){
            secondHand = eq->grid[eq->currentRow][eq->currentCol];
            eq->grid[eq->currentRow][eq->currentCol] = temp;
        }else{
            cout<<"Invalid type of item"<<endl;
        }
    }
    void showEq() {
        eq->display();
    }
    void displayPlayerStats() {
        cout << "HP: " << HP << endl;
        cout << (mainHand != nullptr ? mainHand->name : "none") << endl;
        cout << (armor != nullptr ? armor->name : "none") << endl;
        eq->display();
    }
    ~Player() {
        delete eq;
    }
};

void game() {
    Player P;
    char input;
        // Display the equipment grid
        P.showEq();

        // User input
        cout << "Enter movement direction (W/A/S/D) to move cursor, Q to quit, E to equip item: ";
        cin >> input;

        // Process user input
        switch (input) {
        case 'W':
        case 'A':
        case 'S':
        case 'D':
            // Move cursor
            if (P.eq != nullptr) {
                P.eq->moveCursor(input);
            } else {
                cout << "No equipment to move cursor on.\n";
            }
            break;
        case 'E':
            // Equip item
            P.setMainWeapon(); // For example, equip weapon
            break;

        default:
            cout << "Invalid input\n";
        }
}

int main() {
    bool running = true;
    while (running) {
        game();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    return 0;
}
