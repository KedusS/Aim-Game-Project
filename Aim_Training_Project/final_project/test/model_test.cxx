#include "model.hxx"
#include <catch.hxx>

//Tests whether mouse clicks on easy button,
// in which it updates the game to the easy game mode.
TEST_CASE("Easy Mode Test")
{
    Model model_(100,100);
    Button button_(10,5,{50,50});

    ge211::Posn<int> mouse_pos = {0,0};

    int game_mode = 0;
    int lives = 0;
    int time = 0;
    int shrink = 0;

    if (button_.easy_click(mouse_pos)) {
        game_mode = 3;
        lives = 3;
        time = 30;
        shrink = 1;
    } else if (button_.med_click(mouse_pos)) {
        game_mode = 2;
        lives = 3;
        time = 30;
        shrink = 2;
    } else if (button_.hard_click(mouse_pos)) {
        game_mode = 1;
        lives = 3;
        time = 30;
        shrink = 3;
    }

    CHECK(lives == 0);
    CHECK(time == 0);
    CHECK(shrink == 0);
    CHECK(game_mode == 0);

    CHECK(model_.game_condition(time,lives));

    mouse_pos = {10, 56};

    if (button_.easy_click(mouse_pos)) {
        game_mode = 3;
        lives = 3;
        time = 30;
        shrink = 1;
    } else if (button_.med_click(mouse_pos)) {
        game_mode = 2;
        lives = 3;
        time = 30;
        shrink = 2;
    } else if (button_.hard_click(mouse_pos)) {
        game_mode = 1;
        lives = 3;
        time = 30;
        shrink = 3;
    }

    CHECK(lives == 0);
    CHECK(time == 0);
    CHECK(shrink == 0);
    CHECK(game_mode == 0);

    CHECK(model_.game_condition(time,lives));

    mouse_pos = {38, 54};

    if (button_.easy_click(mouse_pos)) {
        game_mode = 3;
        lives = 3;
        time = 30;
        shrink = 1;
    } else if (button_.med_click(mouse_pos)) {
        game_mode = 2;
        lives = 3;
        time = 30;
        shrink = 2;
    } else if (button_.hard_click(mouse_pos)) {
        game_mode = 1;
        lives = 3;
        time = 30;
        shrink = 3;
    }

    CHECK(lives == 3);
    CHECK(time == 30);
    CHECK(shrink == 1);
    CHECK(game_mode == 3);

    CHECK_FALSE(model_.game_condition(time,lives));
}

//Tests whether mouse clicks on medium button,
// in which it updates the game to the medium game mode.
TEST_CASE("Medium Mode Test")
{
    Model model_(100,100);
    Button button_(10,5,{50,50});

    ge211::Posn<int> mouse_pos = {0,0};

    int game_mode = 0;
    int lives = 0;
    int time = 0;
    int shrink = 0;

    if (button_.easy_click(mouse_pos)) {
        game_mode = 3;
        lives = 3;
        time = 30;
        shrink = 1;
    } else if (button_.med_click(mouse_pos)) {
        game_mode = 2;
        lives = 3;
        time = 30;
        shrink = 2;
    } else if (button_.hard_click(mouse_pos)) {
        game_mode = 1;
        lives = 3;
        time = 30;
        shrink = 3;
    }

    CHECK(lives == 0);
    CHECK(time == 0);
    CHECK(shrink == 0);
    CHECK(game_mode == 0);

    CHECK(model_.game_condition(time,lives));

    mouse_pos = {10, 56};

    if (button_.easy_click(mouse_pos)) {
        game_mode = 3;
        lives = 3;
        time = 30;
        shrink = 1;
    } else if (button_.med_click(mouse_pos)) {
        game_mode = 2;
        lives = 3;
        time = 30;
        shrink = 2;
    } else if (button_.hard_click(mouse_pos)) {
        game_mode = 1;
        lives = 3;
        time = 30;
        shrink = 3;
    }

    CHECK(lives == 0);
    CHECK(time == 0);
    CHECK(shrink == 0);
    CHECK(game_mode == 0);

    CHECK(model_.game_condition(time,lives));

    mouse_pos = {38, 56};

    if (button_.easy_click(mouse_pos)) {
        game_mode = 3;
        lives = 3;
        time = 30;
        shrink = 1;
    } else if (button_.med_click(mouse_pos)) {
        game_mode = 2;
        lives = 3;
        time = 30;
        shrink = 2;
    } else if (button_.hard_click(mouse_pos)) {
        game_mode = 1;
        lives = 3;
        time = 30;
        shrink = 3;
    }

    CHECK(lives == 3);
    CHECK(time == 30);
    CHECK(shrink == 2);
    CHECK(game_mode == 2);

    CHECK_FALSE(model_.game_condition(time,lives));
}

//Tests whether mouse clicks on hard button,
//in which it updates the game to the hard game mode.
TEST_CASE("Hard Mode Test")
{
    Model model_(100,100);
    Button button_(10,5,{50,50});

    ge211::Posn<int> mouse_pos = {0,0};

    int game_mode = 0;
    int lives = 0;
    int time = 0;
    int shrink = 0;

    if (button_.easy_click(mouse_pos)) {
        game_mode = 3;
        lives = 3;
        time = 30;
        shrink = 1;
    } else if (button_.med_click(mouse_pos)) {
        game_mode = 2;
        lives = 3;
        time = 30;
        shrink = 2;
    } else if (button_.hard_click(mouse_pos)) {
        game_mode = 1;
        lives = 3;
        time = 30;
        shrink = 3;
    }

    CHECK(lives == 0);
    CHECK(time == 0);
    CHECK(shrink == 0);
    CHECK(game_mode == 0);

    CHECK(model_.game_condition(time,lives));

    mouse_pos = {10, 56};

    if (button_.easy_click(mouse_pos)) {
        game_mode = 3;
        lives = 3;
        time = 30;
        shrink = 1;
    } else if (button_.med_click(mouse_pos)) {
        game_mode = 2;
        lives = 3;
        time = 30;
        shrink = 2;
    } else if (button_.hard_click(mouse_pos)) {
        game_mode = 1;
        lives = 3;
        time = 30;
        shrink = 3;
    }

    CHECK(lives == 0);
    CHECK(time == 0);
    CHECK(shrink == 0);
    CHECK(game_mode == 0);

    CHECK(model_.game_condition(time,lives));

    mouse_pos = {38, 64};

    if (button_.easy_click(mouse_pos)) {
        game_mode = 3;
        lives = 3;
        time = 30;
        shrink = 1;
    } else if (button_.med_click(mouse_pos)) {
        game_mode = 2;
        lives = 3;
        time = 30;
        shrink = 2;
    } else if (button_.hard_click(mouse_pos)) {
        game_mode = 1;
        lives = 3;
        time = 30;
        shrink = 3;
    }

    CHECK(lives == 3);
    CHECK(time == 30);
    CHECK(shrink == 3);
    CHECK(game_mode == 1);

    CHECK_FALSE(model_.game_condition(time,lives));
}

//Creates a target and mouse position that are not equal,
// then move mouse position to target position, so hit_target
// is true, then the target position becomes random
// using random function. Repeat.
TEST_CASE("Hit Recognition Test")
{
    Model model_(100,100);
    Target target_(5,{32,40},false);

    ge211::Posn<int> mouse_pos = {0,0};

    CHECK_FALSE(target_.hit_target(mouse_pos));
    CHECK_FALSE(target_.target_clicked);

    mouse_pos = {10,10};

    Target expected_target = target_;

    if (target_.hit_target(mouse_pos)) {
        target_.target_clicked = true;
        expected_target.target_pos = model_.random_spot
                (target_.target_radius,model_.Dims());
    }

    CHECK_FALSE(target_.hit_target(mouse_pos));
    CHECK_FALSE(target_.target_clicked);

    CHECK(target_.target_pos == expected_target.target_pos);

    mouse_pos = {36,36};

    if (target_.hit_target(mouse_pos)) {
        target_.target_clicked = true;
        expected_target.target_pos = model_.random_spot
                (target_.target_radius,model_.Dims());
    }

    CHECK(target_.hit_target(mouse_pos));
    CHECK(target_.target_clicked);

    CHECK_FALSE(target_.target_pos == expected_target.target_pos);

    target_.target_pos = expected_target.target_pos;

    mouse_pos = {target_.target_pos.x - 10, target_.target_pos.y};

    if (target_.hit_target(mouse_pos)) {
        expected_target.target_pos = model_.random_spot
                (target_.target_radius,model_.Dims());
    }

    CHECK_FALSE(target_.hit_target(mouse_pos));
    CHECK(target_.target_clicked);

    CHECK(target_.target_pos == expected_target.target_pos);

    mouse_pos = {mouse_pos.x + 14, mouse_pos.y - 2};

    if (target_.hit_target(mouse_pos)) {
        expected_target.target_pos = model_.random_spot
                (target_.target_radius,model_.Dims());
    }

    CHECK(target_.hit_target(mouse_pos));
    CHECK(target_.target_clicked);

    CHECK_FALSE(target_.target_pos == expected_target.target_pos);
}

//Checks if game is over if time runs out or lives run out
TEST_CASE("Game Over Test 1")
{
    Model model_(100,100);
    Target target_(5,{32,40},false);

    int lives = 0;
    int time = 0;

    CHECK(model_.game_condition(time,lives));

    ge211::Posn<int> mouse_pos = {0,0};

    if (target_.hit_target(mouse_pos)) {
        target_.target_clicked = true;
        lives = 3;
        time = 10;
    }

    CHECK_FALSE(target_.hit_target(mouse_pos));

    mouse_pos = {36,36};

    if (target_.hit_target(mouse_pos)) {
        target_.target_clicked = true;
        target_.target_pos = model_.random_spot
                (target_.target_radius,model_.Dims());
        lives = 3;
        time = 10;
    }

    CHECK(lives == 3);
    CHECK(time == 10);
    CHECK_FALSE(model_.game_condition(time,lives));

    if (target_.target_clicked) {
        time -= 5;
    }

    CHECK(time == 5);
    CHECK_FALSE(model_.game_condition(time,lives));

    if (target_.target_clicked) {
        time -= 5;
        target_.target_clicked = false;
    }

    CHECK(time == 0);
    CHECK(lives == 3);
    CHECK(model_.game_condition(time,lives));

    /// ---------------------------------------------- ///

    lives = 3;
    time = 10;

    CHECK_FALSE(model_.game_condition(time,lives));

    if (!target_.target_clicked) {
        lives -= 1;
        time -= 1;
    }

    CHECK_FALSE(model_.game_condition(time,lives));
    CHECK(lives == 2);

    if (!target_.target_clicked) {
        lives -= 1;
        time -= 1;
    }

    CHECK_FALSE(model_.game_condition(time,lives));
    CHECK(lives == 1);

    if (!target_.target_clicked) {
        lives -= 1;
        time -= 1;
    }

    CHECK(model_.game_condition(time,lives));
    CHECK(lives == 0);
    CHECK(time == 7);

}

