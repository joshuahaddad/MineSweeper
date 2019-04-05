//
// Created by JOSHUA HADDAD on 2019-04-03.
//

#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <iterator>
#include <string>

using namespace sf;
using namespace std;

class Interactable{
    Texture texture_;
    Sprite sprite_;
    bool is_revealed_;
    bool is_bomb_;
    bool is_flagged_;
    vector<Interactable*> adjacent_tiles_;


public:
    int number_adjacent_mines_;
    Interactable() = default;
    Interactable(Texture);
    Sprite GetSprite();
    void SetPosition(float x, float y);
    void SetTexture(Texture*);
    bool CheckForMine();
    bool CheckForReveal();
    void SetReveal(bool);
    void SetMine(bool bomb);
    void ShiftDigits(int shift);
    void SetAdjacent(Interactable*);
    void IncrementMineCount();
    int GetMineCount();
    void RecursiveReveal(int &);
    bool IsFlagged();
    void Flag();

};