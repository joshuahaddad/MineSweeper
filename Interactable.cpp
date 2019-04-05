//
// Created by JOSHUA HADDAD on 2019-04-03.
//

#include "Interactable.h"

//Interactables will handle all the sprite loading

Interactable::Interactable(Texture _texture) {
    texture_ = _texture;
    texture_.setSmooth(true);
    sprite_.setTexture(texture_);
    is_bomb_ = false;
    is_revealed_ = false;
    is_flagged_ = false;
    number_adjacent_mines_ = 0;
}

Sprite Interactable::GetSprite() {
    return sprite_;
}


void Interactable::SetPosition(float x, float y) {
    sprite_.setPosition(x,y);
}

void Interactable::SetTexture(Texture* _texture){
    texture_ = *_texture;
}

bool Interactable::CheckForMine() {
    return is_bomb_;
}

bool Interactable::CheckForReveal() {
    return is_revealed_;
}

void Interactable::SetReveal(bool condition){
    is_revealed_ = condition;
}

void Interactable::SetMine(bool bomb){
    is_bomb_ = bomb;
}

//Sets the rectangle of the digits.png texture to the number provided 0-9, 10 is -.
void Interactable::ShiftDigits(int number) {
    sprite_.setTextureRect(IntRect(number*21,0,21,32));
}

void Interactable::SetAdjacent(Interactable* adjacent) {
    adjacent_tiles_.push_back(adjacent);
}

void Interactable::IncrementMineCount() {
    number_adjacent_mines_++;
}

int Interactable::GetMineCount() {
    return number_adjacent_mines_;
}

void Interactable::RecursiveReveal(int& number_of_mines) {
    is_revealed_ = true;
    if(is_flagged_){
        is_flagged_ = false;
        number_of_mines++;
    }
    for(Interactable* adjacent : adjacent_tiles_){
        if(adjacent == nullptr){
            continue;
        }
        if(adjacent->number_adjacent_mines_ == 0 && !adjacent->is_revealed_){
            adjacent->RecursiveReveal(number_of_mines);
        }
        if(adjacent->number_adjacent_mines_ != 0 && adjacent->IsFlagged()){
            number_of_mines++;
            adjacent->Flag();
        }

        adjacent->is_flagged_ = false;
        adjacent->is_revealed_ = true;

    }
}

bool Interactable::IsFlagged() {
    return is_flagged_;
}

void Interactable::Flag() {
    is_flagged_ = !is_flagged_;
}




