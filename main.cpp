#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "GameObject.h"
#include "Interactable.h"


using namespace std;
using namespace sf;

int main()
{
    vector<string> board_paths;
    board_paths.emplace_back("./boards/testboard1.brd");
    board_paths.emplace_back("./boards/testboard2.brd");
    board_paths.emplace_back("./boards/testboard3.brd");

    RenderWindow window(VideoMode(800, 600), "Minesweeper");

    GameObject game = GameObject();
    game.LoadTextures();
    game.LoadBoards(board_paths);
    game.SetBoard(game.RetrieveBoard("testboard2"));

    Interactable debug_button = Interactable(*game.GetTexture("debug"));
    Interactable test_one = Interactable(*game.GetTexture("test_1"));
    Interactable test_two = Interactable(*game.GetTexture("test_2"));
    Interactable test_three = Interactable(*game.GetTexture("Test_3"));
    Interactable game_status = Interactable(*game.GetTexture("face_happy"));
    Interactable mine_counter_digit_one = Interactable(*game.GetTexture("digits"));
    Interactable mine_counter_digit_two = Interactable(*game.GetTexture("digits"));
    Interactable mine_counter_digit_three = Interactable(*game.GetTexture("digits"));
    debug_button.SetPosition(512, 512);
    test_one.SetPosition(576, 512);
    test_two.SetPosition(640, 512);
    test_three.SetPosition(704, 512);
    game_status.SetPosition(352,512);
    mine_counter_digit_one.SetPosition(42,512);
    mine_counter_digit_two.SetPosition(21,512);
    mine_counter_digit_three.SetPosition(0,512);

    game.GenerateBoard(game_status);


    //sprite.setTextureRect(sf::IntRect(10,10,32,32));

    //Get number of bombs

    Event event;

    int frame = 0;
    vector<int> bomb_numbers{game.GetCurrentBoard()->GetNumberMines(),-1,-1,-1};

    while(window.isOpen()){
        bomb_numbers.at(0) = game.GetCurrentBoard()->GetNumberMines();
        game.GetDigitCodes(bomb_numbers);
        mine_counter_digit_one.ShiftDigits(bomb_numbers.at(1));
        mine_counter_digit_two.ShiftDigits(bomb_numbers.at(2));
        mine_counter_digit_three.ShiftDigits(bomb_numbers.at(3));

        int row = -1;
        int column = -1;
        bool right_click = false;
        bool left_click = false;

        while(window.pollEvent(event)){
            switch(event.type){
                case Event::Closed:
                    window.close();
                    break;

                //floor(x/width) is the horizontal component floor(y/height) is the vertical component
                case Event::MouseButtonPressed:
                    column = floor(event.mouseButton.x/32);
                    row = floor(event.mouseButton.y/32);
                    frame = 0;
                    if(event.mouseButton.button == sf::Mouse::Right){
                        right_click = true;
                    }
                    else{
                        left_click = true;
                    }
                    break;

                default:
                    break;
            }
        }


        if(frame < 30){
            if(row == 16 || row == 17){
                if(column == 11 || column == 12) {
                    cout << "Face!" << endl;
                    game.ResetGame();
                    game.GenerateBoard(game_status);
                    bomb_numbers.at(0) = game.GetCurrentBoard()->GetNumberMines();
                }

                if(column == 16 || column == 17){
                    game.RevealMines();
                }

                if(column == 18 || column == 19){
                    game.SetBoard(game.RetrieveBoard("testboard1"));
                    cout << "Test1" << endl;
                    game.GenerateBoard(game_status);
                    bomb_numbers.at(0) = game.GetCurrentBoard()->GetNumberMines();
                }
                if(column == 20 || column == 21){
                    cout << "Test2" << endl;
                    game.SetBoard(game.RetrieveBoard("testboard2"));
                    game.GenerateBoard(game_status);
                    bomb_numbers.at(0) = game.GetCurrentBoard()->GetNumberMines();
                }
                if(column == 22 || column == 23){
                    cout << "Test3" << endl;
                    game.SetBoard(game.RetrieveBoard("testboard3"));
                    game.GenerateBoard(game_status);
                    bomb_numbers.at(0) = game.GetCurrentBoard()->GetNumberMines();
                }
            }
            if(row < 16 && left_click && !game.GetLoss()){
                Interactable* clicked_tile = game.game_interactables_.at(row).at(column);

                if(clicked_tile->CheckForMine() && !clicked_tile->IsFlagged()){
                    game.SetLoss();
                    game_status.SetTexture(game.GetTexture("face_lose"));
                    if(!game.IsRevealed())
                        game.RevealMines();
                } else if (!clicked_tile->IsFlagged()) {
                    clicked_tile->SetReveal(true);
                    if(clicked_tile->GetMineCount() == 0){
                        clicked_tile->RecursiveReveal(*game.GetCurrentBoard()->GetNumberMinesPtr());
                    }
                    else if(clicked_tile->IsFlagged()){
                        clicked_tile->Flag();
                        game.GetCurrentBoard()->SetNumberMines(1);
                    }
                }
            }

            if(row < 16 && right_click && !game.GetLoss()){
                Interactable* clicked_tile = game.game_interactables_.at(row).at(column);
                if(!clicked_tile->CheckForReveal() && !clicked_tile->IsFlagged()){
                    game.GetCurrentBoard()->SetNumberMines(-1);
                    clicked_tile->Flag();
                }
                else if(clicked_tile->IsFlagged()){
                    game.GetCurrentBoard()->SetNumberMines(1);
                    clicked_tile->Flag();
                }
            }

            window.clear(Color(255,255,255));
            window.draw(debug_button.GetSprite());
            window.draw(test_one.GetSprite());
            window.draw(test_two.GetSprite());
            window.draw(test_three.GetSprite());
            window.draw(game_status.GetSprite());
            window.draw(mine_counter_digit_one.GetSprite());
            window.draw(mine_counter_digit_two.GetSprite());
            window.draw(mine_counter_digit_three.GetSprite());

            for(unsigned i = 0; i < game.game_interactables_.size(); i++){
                for (unsigned int j = 0; j < game.game_interactables_.at(i).size(); j++) {
                    window.draw(game.board_tiles_.at(i).at(j)->GetSprite());
                    Interactable* current_tile = game.game_interactables_.at(i).at(j);

                    if(current_tile->CheckForMine() && game.board_revealed_){
                        current_tile->SetReveal(true);
                        current_tile->SetTexture(game.GetTexture("mine"));
                    }
                    if(current_tile->CheckForMine() && !game.board_revealed_){
                        current_tile->SetReveal(false);
                    }

                    if(!current_tile->CheckForReveal()){
                        current_tile->SetTexture(game.GetTexture("tile_hidden"));
                    } else {
                        if(!current_tile->CheckForMine() && current_tile->GetMineCount() == 0)
                            current_tile->SetTexture(game.GetTexture("tile_revealed"));
                        if(!current_tile->CheckForMine() && current_tile->GetMineCount() != 0){
                            int number_mines = current_tile->GetMineCount();
                            string digit_name = "number_" + to_string(number_mines);
                            current_tile->SetTexture(game.GetTexture(digit_name));
                        }
                    }

                    window.draw(current_tile->GetSprite());

                    if(current_tile->IsFlagged() && !current_tile->CheckForReveal()){
                        current_tile->SetTexture(game.GetTexture("flag"));
                        window.draw(current_tile->GetSprite());
                    }


                }
            }
        }

        if(!game.Win())
            game.CheckWin();

        if(game.Win()){
            game_status.SetTexture(game.GetTexture("face_win"));
        }
        window.display();
        frame++;

    }

    return 0;
}