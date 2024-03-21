#include <iostream>
#include <string>

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
                 << "Enchantment: " << grid[row][col]->enchantment << endl
                 << "Weight: " << grid[row][col]->weight << endl
                 << "Cost: " << grid[row][col]->cost << endl;
        } else {
            cout << "No item at this position or invalid position\n";
        }
    }

    // Move an item from one position to another
    void moveItem(int row, int col, int secondRow, int secondCol) {
        while(true){
            display();
            if (isValidPosition(row, col) && isValidPosition(secondRow, secondCol)) {
                swap(grid[row][col], grid[secondRow][secondCol]);
            } else {
                cout << "Invalid position\n";
            }
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
    // Check if the given position is valid
    bool isValidPosition(int row, int col) {
        return row >= 0 && row < rows && col >= 0 && col < cols;
    }
};

class Player {
public:
    int HP;
    int gold;
    Item* mainHand;
    Item* armor;
    Item* boots;
    Item* pants;
    Item* secondHand;
    Equipment* eq;


    Player() {
        HP = 100;
        gold = 1000;
        mainHand = nullptr;
        armor = nullptr;
        boots = nullptr;
        pants = nullptr;
        secondHand = nullptr;
        eq = new Equipment();
    }
    void setMainWeapon(int i, int j) {
        Item* temp = mainHand;
        if(eq->grid[i][j]->type == "Weapon"){
            mainHand = eq->grid[i][j];
            eq->grid[i][j] = temp;
        }else{
            cout<<"Invalid type of item"<<endl;
        }

    }
    void setMainArmor(int i, int j) {
        Item* temp = armor;
        if(eq->grid[i][j]->type == "Armor"){
            armor = eq->grid[i][j];
            eq->grid[i][j] = temp;
        }else{
            cout<<"Invalid type of item"<<endl;
        }
    }
    void setMainBoots(int i, int j) {
        Item* temp = boots;
        if(eq->grid[i][j]->type == "Boots"){
            boots = eq->grid[i][j];
            eq->grid[i][j] = temp;
        }else{
            cout<<"Invalid type of item"<<endl;
        }
    }
    void setMainPants(int i, int j) {
        Item* temp = pants;
        if(eq->grid[i][j]->type == "Pants"){
            pants = eq->grid[i][j];
            eq->grid[i][j] = temp;
        }else{
            cout<<"Invalid type of item"<<endl;
        }
    }
    void setMainSecondHand(int i, int j) {
        Item* temp = secondHand;
        if(eq->grid[i][j]->type == "Shield"){
            secondHand = eq->grid[i][j];
            eq->grid[i][j] = temp;
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
    void buyItemFromShop(int i, int j){

    }
    ~Player() {
        delete eq;
    }
};

class Game {
    Item* mainHand;
    Item* armor;
    Player* player;
public:
    Game(Player* player) {
        // Initialize eq pointer
        this->player = player;
        player->eq = new Equipment();
        mainHand = nullptr;
        armor = nullptr;
    }

    ~Game() {
        delete player->eq; // Delete eq pointer in the destructor
    }

    void menuLoop() {
        char x;
        bool IsGameRunning = true;
        while (IsGameRunning) {

            player->displayPlayerStats();
            cout << endl;
            cout << "Choose Your Action: " << endl;
            cout << "Move Your Item (M)" << endl;
            cout << "Delete Item (D)" << endl;
            cout << "Equip Item (E)" << endl;
            cout << "Show Details (Y)" << endl;
            cout << "Exit (X)" << endl;
            cout << "Choose Option: ";
            cin >> x;
            switch (x) {
            case 'E':
                int z;
                int xx;
                int yy;
                cout<<"chhose you item: "<<endl;
                cin>>xx>>yy;
                cout<<"Where Do you wanna Put this item: Armor(1), Weapon(2), SecondHand(3), Boots(4), Pants(5)"<<endl;
                cin>>z;
                if(z == 1){
                    player->setMainArmor(xx,yy);
                }
                else if(z == 2){
                    player->setMainWeapon(xx,yy);
                }
                else if(z == 3){
                    player->setMainSecondHand(xx,yy);
                }
                else if(z == 4){
                    player->setMainBoots(xx,yy);
                }
                else if(z == 5){
                    player->setMainPants(xx,yy);
                }
                else{
                    cout<<"Wrong option"<<endl;

                }
                player->displayPlayerStats();
                break;
            case 'Y':
                int detailX;
                int detailY;
                cout << "Choose desired item: ";
                cin >> detailX;
                cin >> detailY;
                if(player->eq->grid[detailX][detailY] !=nullptr){
                    cout << "Name: " << player->eq->grid[detailX][detailY]->name << " Level: " << player->eq->grid[detailX][detailY]->level << " Durability: " << player->eq->grid[detailX][detailY]->durability << " Enchantment: " << player->eq->grid[detailX][detailY]->enchantment << " Weight: " << player->eq->grid[detailX][detailY]->weight << " Cost: " << player->eq->grid[detailX][detailY]->cost << "Type: " <<player->eq->grid[detailX][detailY]->type;
                    for (const auto& enchant : player->eq->grid[detailX][detailY]->enchantment) {
                        cout << enchant << " ";
                    }
                    cout << endl;
                }else{
                    cout<<"You Choosed Empty Space/Unexisting Index"<<endl;
                }
                break;

            case 'D':
                int deleteX, deleteY;
                cout << "Enter the coordinates of the item you want to delete (x y): ";
                cin >> deleteX;
                cin >> deleteY;
                if(player->eq->grid[deleteX][deleteY] !=nullptr){
                    try {
                        player->eq->deleteItem(deleteX, deleteY);
                        cout << "Item deleted." << endl;
                    }
                    catch(const std::exception& e) {
                        cout << "try again: " << e.what() << endl;
                    }

                }
                else{
                    cout<<"You Choosed Empty Space/Unexisting Index"<<endl;
                }
                player->eq->display();
                break;
            case 'M':
                int I;
                int J;
                int K;
                int L;
                cout<<"What item do you want to move? "<<endl;
                cin>>I>>J;
                cout<<"Where do you want to move this item? "<<endl;
                cin>>K>>L;
                player->eq->moveItem(I,J,K,L);
                break;

            case 'X':
                IsGameRunning = false;
                break;
            }
        }
    }
};
class Shop : public Equipment{
public:
    Shop(int rows = 5, int cols = 10) : Equipment(rows, cols){
        grid = new Item**[rows];
        for (int i = 0; i < rows; i++) {
            grid[i] = new Item*[cols]();
        }
    }
    ~Shop() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                delete grid[i][j];
            }
            delete[] grid[i];
        }
        delete[] grid;
    }
};

int main() {
    Player P;
    Equipment E;
    Shop S;
    Game G(&P);
    Item* item1 = new Item("Sword", 1, 3, "Sharpness", 10.2, 100, "Weapon");
    Item* item2 = new Item("Armor", 1, 4, "Protection", 5.2, 100, "Armor");

    P.eq->addItem(item1,0,0);
    P.eq->addItem(item2,0,1);
    G.menuLoop();
    delete item1;
    delete item2;
    return 0;
}
