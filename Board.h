//
// Created by JOSHUA HADDAD on 2019-04-02.
//

#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include "Tile.h"

class Board{
    vector<vector<Tile>> board_tiles_;
    int number_of_mines_;

public:
    int height_;
    int length_;
    Board(int _length, int _height);
    Board();
    void LoadFromFile(string path);
    void PrintBoard();
    void StoreLines(const vector<string>& lines);
    int GetHeight();
    int GetLength();
    int GetNumberMines();
    int* GetNumberMinesPtr();
    bool IsMine(int row, int column);
    void RandomBoard();
    void SetNumberMines(int shift);
};