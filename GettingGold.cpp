#include <iostream>
#include <vector>

using namespace std;

void traverseMap (pair<int, int> playerPos, vector<vector<char>>& gameMap);
int gold = 0;


int main() {
    
    int width, height;
    pair<int, int> playerPos; //(Y, X)
    vector<vector<char>> gameMap;

    cin >> width >> height;

    //Fetch input
    for(int i = 0; i < height; i++) {
        vector<char> line;
        for (int j = 0; j < width; j++) {
            char character;
            cin >> character;
            if (character == 'P') {
                playerPos = {i, j};
            }
            line.push_back(character);
        }
        gameMap.push_back(line);
    }

    traverseMap(playerPos, gameMap);
    cout << gold << endl;
    return 0;
}

void traverseMap (pair<int, int> playerPos, vector<vector<char>>& gameMap) {
    int playerY = playerPos.first; //Row index (what Y-value)
    int playerX = playerPos.second; //Column index

    //Out of bounds
    if(playerX < 0 || playerX >= gameMap[0].size() || playerY < 0 || playerY >= gameMap.size()) {
        return;
    }

    //Position already been visited or is a wall.
    if(gameMap[playerY][playerX] == '#') {
        return;
    }

    //If there is gold, increment by 1
    if(gameMap[playerY][playerX] == 'G') {
        gold += 1;
    }
    //Set position as visited
    gameMap[playerY][playerX] = '#';

    //If player senses a draft (T on any adjacent tile), do not continue.
    if ((playerX + 1 < gameMap[0].size() && gameMap[playerY][playerX + 1] == 'T') ||
        (playerX - 1 >= 0 && gameMap[playerY][playerX - 1] == 'T') ||
        (playerY + 1 < gameMap.size() && gameMap[playerY + 1][playerX] == 'T') ||
        (playerY - 1 >= 0 && gameMap[playerY - 1][playerX] == 'T')) {
        return; // A draft is sensed, do not continue
    }

    //If there are no walls to the right and we have not explored it, go right.
    if (playerX + 1 < gameMap[0].size() && gameMap[playerY][playerX + 1] != '#') {
        playerPos = {playerY, playerX + 1};
        traverseMap(playerPos, gameMap);
    }
    //If there are no walls to the left and we have not explored it, go left
    if (playerX - 1 >= 0 && gameMap[playerY][playerX - 1] != '#') {
        playerPos = {playerY, playerX - 1};
        traverseMap(playerPos, gameMap);
    }
    //If there are no walls below and we have not explored it, go down
    if (playerY + 1 < gameMap.size() && gameMap[playerY + 1][playerX] != '#') {
        playerPos = {playerY + 1, playerX};
        traverseMap(playerPos, gameMap);
    }
    //If there are no walls above and we have not explored it, go up
    if (playerY - 1 >= 0 && gameMap[playerY - 1][playerX] != '#') {
        playerPos = {playerY - 1, playerX};
        traverseMap(playerPos, gameMap);
    }
    return;
}