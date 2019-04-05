//
// Created by JOSHUA HADDAD on 2019-04-02.
//

#include "GameObject.h"
GameObject::GameObject() {
    win_ = false;
    lose_ = false;
    board_revealed_ = false;

}
void GameObject::LoadTextures() {
    Texture texture;
    string imagePaths[] = {"./images/debug.png", "./images/digits.png", "./images/face_happy.png","./images/face_lose.png",
                           "./images/face_win.png", "./images/flag.png", "./images/mine.png", "./images/number_1.png",
                           "./images/number_2.png","./images/number_3.png","./images/number_4.png","./images/number_5.png",
                           "./images/number_5.png","./images/number_6.png", "./images/number_7.png","./images/number_8.png",
                           "./images/test_1.png","./images/test_2.png","./images/Test_3.png", "./images/tile_hidden.png","./images/tile_revealed.png"};

    for(string paths: imagePaths){
        Texture texture;
        texture.loadFromFile(paths);
        texture.setSmooth(true);

        long begin =paths.find("s/")+2;
        long end = paths.find(".png",2);

        string name = paths.substr(begin, end-begin);
        textures_.emplace(name, texture);
    }
}

Texture* GameObject::GetTexture(string key){
    return &textures_[key];
}

void GameObject::LoadBoards(vector<string> paths){
    map<string, Board> boards;
    for(int i = 0; i < paths.size(); i++){
        Board currentBoard;
        currentBoard.LoadFromFile(paths.at(i));
        string path = paths.at(i);
        long begin = path.find("s/")+2;
        long end = path.find(".brd",2);
        string name = path.substr(begin, end-begin);
        all_levels_.emplace(name, currentBoard);
    }

}

void GameObject::SetBoard(Board board) {
    current_board_ = board;
}

void GameObject::GenerateBoard(Interactable &game_status) {
    game_status.SetTexture(GetTexture("face_happy"));
    lose_ = false;
    win_ = false;

    game_interactables_.clear();
    for(int i = 0; i < current_board_.GetHeight(); i ++){
        vector<Interactable*> row;
        vector<Interactable*> background_row;
        for(int j = 0; j < current_board_.GetLength(); j ++){
            Interactable* background_piece = new Interactable(*GetTexture("tile_revealed"));
            Interactable* piece = new Interactable(*GetTexture("tile_hidden"));

            if(current_board_.IsMine(i,j))
                piece->SetMine(true);
            if(!current_board_.IsMine(i,j))
                piece->SetMine(false);

            background_piece -> SetPosition(j*32,i*32);
            piece -> SetPosition(j*32,i*32);
            row.push_back(piece);
            background_row.push_back(background_piece);
        }
        game_interactables_.push_back(row);
        board_tiles_.push_back(background_row);
    }
    SetSurroundings();
}

Board GameObject::RetrieveBoard(string key) {
    return all_levels_[key];
}

void GameObject::GetDigitCodes(vector<int> &in_data) {
    bool negative = false;

    if(in_data.at(0) < 0){
        negative = true;
        in_data.at(0) *= -1;
    }

    string number = to_string(in_data.at(0));
    if(number.length() == 1){
        in_data.at(1) = stoi(number);
        in_data.at(2) = 0;
        negative ?  in_data.at(3) = 10 : in_data.at(3) = 0;
    }
    if(number.length() == 2){
        in_data.at(1) = stoi(number.substr(1,1));
        in_data.at(2) = stoi(number.substr(0,1));
        negative ?  in_data.at(3) = 10 : in_data.at(3) = 0;
    }
    if(number.length() == 3){
        in_data.at(1) = stoi(number.substr(2,1));
        in_data.at(2) = stoi(number.substr(1,1));
        in_data.at(3) = stoi(number.substr(0,1));
    }

}

Board* GameObject::GetCurrentBoard() {
    Board* ptr = &current_board_;
    return ptr;
}

void GameObject::ResetGame() {

    //Generate new board
    current_board_ = Board(25,16);

    //Populate board with random stuff!
    current_board_.RandomBoard();

}

void GameObject::SetSurroundings() {
    for(int c = 0; c < game_interactables_.size(); c++){
        for(int r = 0; r < game_interactables_.at(0).size(); r++){
            if(r == 1 && c == 1){
                int x = 5;
            }
            Interactable* current_inspected_interactable = game_interactables_.at(c).at(r);
            for (int row = -1; row <= 1; row++) {
                for (int column = -1; column <= 1; column++) {
                    try{
                        Interactable* adjacent_tile = game_interactables_.at(c+column).at(r+row);
                        if(adjacent_tile->CheckForMine()){
                            current_inspected_interactable->IncrementMineCount();
                        }
                        current_inspected_interactable->SetAdjacent(adjacent_tile);
                    }
                    catch(const out_of_range &e){
                        current_inspected_interactable->SetAdjacent(nullptr);
                    }
                }
            }
        }
    }
    cout << "Got out" << endl;
}

void GameObject::SetLoss() {
    lose_ = true;
}

void GameObject::CheckWin() {
    win_ = true;
    for(int i = 0; i < game_interactables_.size(); i++){
        for(int j = 0; j < game_interactables_.at(0).size(); j++){
            if(game_interactables_.at(i).at(j)->CheckForMine())
                continue;
            if(!game_interactables_.at(i).at(j)->CheckForReveal())
                win_ = false;
        }
    }
}

bool GameObject::GetLoss() {
    return lose_;
}

bool GameObject::Win() {
    return win_;
}

void GameObject::RevealMines() {
    board_revealed_ = !board_revealed_;
}

bool GameObject::IsRevealed() {
    return board_revealed_;
}







