#pragma once

#include "model.hxx"

#include <string>

class View
{
public:
    /// View dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// View rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;

    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);// Draws game

    Dimensions initial_window_dimensions() const;

    void draw_input(ge211::Sprite_set&, Position mouse_posn);//Movement position of the cursor

    void button_input(ge211::Sprite_set&, Position mouse_posn);//Button inputs for the project

    void target_click(ge211::Sprite_set&, Position mouse_posn);

    double time; //timer

    int lives;//number of lives in the game

    double shrink;//causes the target to get smaller over time

    int score;//score for game

    double click_count;//number of clicks during game

    double hit_count;//number times the player hits the target

    double accuracy;//Text

    double count_down;// timer before game

    bool begin_count;//to start game timer, when player clicks first target

    double differential;//difference between game and shrink

    bool showMainMenu;

    Target target_;



private:
    //Model const& model_;
    Model model_;
    Button button_;
    //Target target_;

    int gamemode = 0;

    //Main menu background
    ge211::Rectangle_sprite menu_sprite;

    //Title text
    ge211::Text_sprite title_text;
    ge211::Font font_info{"GamePlayedOutline-wrX8.ttf",
                          (initial_window_dimensions().height
                          / model_.Dims().height) * 20};

    // Main Button Sprites
    ge211::Rectangle_sprite hard_sprite;
    ge211::Rectangle_sprite medium_sprite;
    ge211::Rectangle_sprite easy_sprite;

    // Button Sprites darken when cursor hovers over them
    ge211::Rectangle_sprite h_hover_sprite;
    ge211::Rectangle_sprite m_hover_sprite;
    ge211::Rectangle_sprite e_hover_sprite;

    // Constant Cursor Sprite for Game
    ge211::Circle_sprite crosshair_sprite;

    // Main Game Background
    ge211::Rectangle_sprite game_board_sprite;

    // Target Sprite
    ge211::Circle_sprite target_sprite;

    //Game timer
    ge211::Text_sprite game_timer;

    ge211::Font font_info2{"GamePlayed-vYL7.ttf",
                          (initial_window_dimensions().height
                           / model_.Dims().height) * 5};

    //Game over Background
    ge211::Rectangle_sprite game_over_screen;

    //Score
    ge211::Text_sprite score_sprite;

    ge211::Font font_info3{"GamePlayed-vYL7.ttf",
                           (initial_window_dimensions().height
                            / model_.Dims().height) * 14};

    //Game over Text
    ge211::sprites::Text_sprite game_over_text;

    //Back to Main Menu button, darkens when hovered
    ge211::Rectangle_sprite back_button;
    ge211::Rectangle_sprite back_hover;

    //shows accuracy
    ge211::Text_sprite accuracy_sprite;

    //countdown
    ge211::Text_sprite count_down_sprite;

    ge211::Font font_info4{"GamePlayedOutline-wrX8.ttf",
                           (initial_window_dimensions().height
                            / model_.Dims().height) * 30};
    //Hearts for lives
    ge211::Image_sprite heart1;
    ge211::Image_sprite heart2;
    ge211::Image_sprite heart3;

    //Back to menu text
    ge211::Text_sprite back_to_menu_text;

    //Game modes text
    ge211::Text_sprite easy_text;
    ge211::Text_sprite med_text;
    ge211::Text_sprite hard_text;

    ge211::Font font_info5{"GamePlayed-vYL7.ttf",
                           (initial_window_dimensions().height
                            / model_.Dims().height) * 5};

    //Show amount of lives
    ge211::Text_sprite lives_text;

    //Statistics for accuracy
    ge211::Text_sprite hits_text;
    ge211::Text_sprite miss_text;

};
