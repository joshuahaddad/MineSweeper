//
// Created by JOSHUA HADDAD on 2019-04-02.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "Interactable.h"
#include "Board.h"

using namespace std;
using namespace sf;

//This class will handle all the levels, win conditions, events, etc.
//This class will not handle drawing the sprites.  It will load all sprites then Interactable will handle drawing sprites

class GameObject{
    map<string,Texture> textures_;
    map<string,Board> all_levels_;

    bool win_;
    bool lose_;

public:
    vector<vector<Interactable*>> game_interactables_;
    vector<vector<Interactable*>> board_tiles_;
    Board current_board_;
    bool board_revealed_;

    GameObject();

    //Board functionality
    void LoadBoards(vector<string>);
    void SetBoard(Board board);
    Board* GetCurrentBoard();
    Board RetrieveBoard(string key);
    void GetDigitCodes(vector<int> &);
    void SetSurroundings();
    void RevealMines();
    bool IsRevealed();

    //Game functionality
    void ResetGame();
    void SetLoss();
    void CheckWin();
    bool GetLoss();
    bool Win();

    //Texture handling
    void LoadTextures();
    Texture* GetTexture(string key);
    void GenerateBoard(Interactable&);



};