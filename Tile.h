//
// Created by JOSHUA HADDAD on 2019-04-02.
//

#pragma once
#include <iostream>

using namespace std;

class Tile{
    bool is_mine_;
    int number_bombs_;

public:
    Tile();
    Tile(bool bomb);
    void SetTileMines(Tile& currentTile);
    bool CheckMine();
    void SetMine();

};
