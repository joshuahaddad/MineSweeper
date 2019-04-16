//
// Created by JOSHUA HADDAD on 2019-04-02.
//

#include "Board.h"

Board::Board(int _length, int _height){
    number_of_mines_ = 0;
    height_ = _height;
    length_ = _length;
}


void Board::LoadFromFile(string path) {
    ifstream board_reader(path);
    string value;
    vector<string> lines;

    if(board_reader.is_open()){
        while(board_reader >> value){
            lines.push_back(value);
        }
    }

    length_ = lines.at(0).length();
    height_ = 0;
    StoreLines(lines);

    PrintBoard();

}

void Board::StoreLines(const vector<string>& lines){
    for(string line: lines){
        vector<Tile> tile_lines;

        for(int j = 0; j < length_; j++){
            if(line.substr(j, 1) == "1"){
                number_of_mines_++;
                Tile current_tile = Tile(true);
                tile_lines.push_back(current_tile);
            }
            else{
                Tile current_tile = Tile();
                tile_lines.push_back(current_tile);
            }
        }

        board_tiles_.push_back(tile_lines);
        height_++;
    }
}
//Helper method for debugging the board if needed
void Board::PrintBoard(){
    for(int i = 0; i < height_; i++){
        for(int j = 0; j < length_; j++){
            cout << board_tiles_.at(i).at(j).CheckMine() << " ";
        }
        cout << endl;
    }
}

int Board::GetHeight() {
    return height_;
}

int Board::GetLength() {
    return length_;
}

bool Board::IsMine(int row, int column) {
    if(row > board_tiles_.size()-1 || row < 0 || column > board_tiles_.at(0).size()-1 || column < 0)
        return false;
    return board_tiles_.at(row).at(column).CheckMine();
}

int Board::GetNumberMines() {
    return number_of_mines_;
}

Board::Board() {
    height_ = 0;
    length_ = 0;
    number_of_mines_ = 0;
}

void Board::RandomBoard() {
    number_of_mines_ = 50;

    for(int i = 0; i < height_; i++){
        vector<Tile> tile_lines;
        for(int j = 0; j < length_; j++){
            Tile current_tile = Tile(false);
            tile_lines.push_back(current_tile);
        }
        board_tiles_.push_back(tile_lines);
    }

    for(int i = 0; i < 50; i++){
        int x = rand() % 16;
        int y = rand() % 25;

        board_tiles_.at(x).at(y).SetMine();
    }
}

void Board::SetNumberMines(int shift) {
    number_of_mines_ += shift;
}

int* Board::GetNumberMinesPtr() {
    int* ptr = &number_of_mines_;
    return ptr;
}




