//
// Created by JOSHUA HADDAD on 2019-04-02.
//

#include "Tile.h"
Tile::Tile() {
    is_mine_ = false;
}

Tile::Tile(bool bomb) {
    is_mine_ = bomb;
}
void Tile::SetTileMines(Tile &currentTile) {
     currentTile.is_mine_ = true;
}

bool Tile::CheckMine() {
    return is_mine_;
}


