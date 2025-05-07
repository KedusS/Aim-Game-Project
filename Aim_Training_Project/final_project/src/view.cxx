#include "view.hxx"
#include <iomanip>

using namespace std;

using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;

// Use this to Make Game Larger
static int const scene_multiplier = 12;

View::View(Model const& model)
        : time(0),
          lives(0),
          shrink(0),
          score(0),
          click_count(0),
          hit_count(0),
          accuracy(0),
          count_down(4),
          begin_count(false),
          differential(0),
          showMainMenu(true),

          target_(0,{620,320},false),

          model_(model),

          button_(model_.Dims().width,model_.Dims().height,
                  {initial_window_dimensions().width / 2,
                   initial_window_dimensions().height / 2}),

          menu_sprite(initial_window_dimensions(),{0,25,51}),

          title_text(),

          hard_sprite(button_.button_dims, {255,0,0}),

          medium_sprite(button_.button_dims, {255,255,0}),

          easy_sprite(button_.button_dims, {0,255,0}),

          h_hover_sprite(button_.button_dims, {153,0,0}),

          m_hover_sprite(button_.button_dims, {153,153,0}),

          e_hover_sprite(button_.button_dims, {0,153,0}),

          crosshair_sprite(scene_multiplier / 2 , {255, 255, 255}),

          game_board_sprite(initial_window_dimensions(),{0,0,0}),

          target_sprite(scene_multiplier * 2, {255,0,0}),

          game_timer(),

          game_over_screen(initial_window_dimensions(),{128,0,0}),

          score_sprite(),

          game_over_text(),

          back_button(button_.button_dims, {240,213,208}),

          back_hover(button_.button_dims, {216,147,134}),

          accuracy_sprite(),

          count_down_sprite(),

          //Heart Sprites using imported image
          heart1("6-pixel-heart-4.png"),

          heart2("6-pixel-heart-4.png"),

          heart3("6-pixel-heart-4.png"),

          back_to_menu_text(),

          easy_text(),

          med_text(),

          hard_text(),

          lives_text(),

          hits_text(),

          miss_text()

{ }

// Renders sprite that require no direct user interaction
void
View::draw(ge211::Sprite_set& set)
{
    // Title Builder
    ge211::Text_sprite::Builder name_builder(font_info);

    // Set Title color
    name_builder.color({0,255,250}) << "HITS";

    // Updates the title_text sprite
    title_text.reconfigure(name_builder);

    // Finds approximate center
    int x = initial_window_dimensions().width / 2;
    int y = initial_window_dimensions().height / 2;
    Position center = {x,y};

    // Updates Easy Button Text
    ge211::Text_sprite::Builder easy_build(font_info5);
    easy_build.color({0,0,0}) << "EASY";
    easy_text.reconfigure(easy_build);

    // Updates Medium Button Text
    ge211::Text_sprite::Builder med_build(font_info5);
    med_build.color({0,0,0}) << "MEDIUM";
    med_text.reconfigure(med_build);

    // Updates Hard Button Text
    ge211::Text_sprite::Builder hard_build(font_info5);
    hard_build.color({0,0,0}) << "HARD";
    hard_text.reconfigure(hard_build);

    // Checks that Main Menu is Active
    if (showMainMenu) {

        // Adds Main Menu Sprite
        set.add_sprite(menu_sprite, {0, 0});

        // Adds Title Text near approximate center
        set.add_sprite(title_text,
                       {center.left_by(model_.Dims().width * 2.25)
                              .up_by(model_.Dims().height * 6)}, 2);

        // Adds Easy Button and Easy Text
        set.add_sprite(easy_sprite, button_.e_button, 2);
        set.add_sprite(easy_text,button_.e_button.right_by(100),5);

        // Adds Medium Button and Medium Text
        set.add_sprite(medium_sprite,button_.m_button, 2);
        set.add_sprite(med_text,button_.m_button.right_by(60),5);

        // Adds Hard Button and Hard Text
        set.add_sprite(hard_sprite,button_.h_button, 2);
        set.add_sprite(hard_text, button_.h_button.right_by(100),5);
    }

    // Checks that Main Menu is off and Game is Over
    if (!showMainMenu && model_.game_condition(time,lives)) {

        // Adds Game Over Background
        set.add_sprite(game_over_screen,{0,0},7);

        // Checks if Hits are Greater that Clicks which occur
        // from occasional double render
        if (hit_count > click_count) {
            click_count = hit_count;
        }

        // Calculates final Accuracy
        accuracy = (hit_count / click_count) * 100;

        // Sets final score
        double final_score = score - (click_count - hit_count) * 25;

        // Name Builders for Game Over Text Sprites
        ge211::Text_sprite::Builder name_builder1(font_info2);
        ge211::Text_sprite::Builder name_builder2(font_info3);
        ge211::Text_sprite::Builder name_builder3(font_info2);
        ge211::Text_sprite::Builder name_builder4(font_info2);
        ge211::Text_sprite::Builder name_builder5(font_info2);
        ge211::Text_sprite::Builder name_builder6(font_info2);

        // Configures all the Name Builders
        name_builder1.color({238,232,170}) << "Score: " <<  final_score;

        name_builder2.color({240,213,208}) << "Game Over";

        name_builder3.color({238,232,170}) << "Accuracy: " << setprecision(3)
        << accuracy << "%";

        name_builder4.color({238,232,170}) << "Lives: "  << lives;

        name_builder5.color({238,232,170}) << "Hits: " << hit_count;

        name_builder6.color({238,232,170}) << "Misses: "
        << (click_count - hit_count);


        // Updates all Game Over text sprite
        score_sprite.reconfigure(name_builder1);
        game_over_text.reconfigure(name_builder2);
        accuracy_sprite.reconfigure(name_builder3);
        lives_text.reconfigure(name_builder4);
        hits_text.reconfigure(name_builder5);
        miss_text.reconfigure(name_builder6);

        // Updates Back to Main Menu button text
        ge211::Text_sprite::Builder menu_build(font_info5);
        menu_build.color({0,0,0}) << "MAIN MENU";
        back_to_menu_text.reconfigure(menu_build);

        // Adds the Score Text
        set.add_sprite(score_sprite,
                       {center.left_by(model_.Dims().width * 2)
                                .up_by(model_.Dims().height * 2.5)}, 8);

        // Adds the Accuracy Text
        set.add_sprite(accuracy_sprite,
                       {center.left_by(model_.Dims().width * 2)
                                .up_by(model_.Dims().height * 1.5)}, 8);

        // Adds the Lives Text
        set.add_sprite(lives_text,
                       {center.left_by(model_.Dims().width * 2)
                                .up_by(model_.Dims().height * 0.5)}, 8);

        // Adds the Hits Text
        set.add_sprite(hits_text,
                       {center.left_by(model_.Dims().width * 2)
                                .down_by(model_.Dims().height * 0.5)}, 8);

        // Adds the Misses Text
        set.add_sprite(miss_text,
                       {center.left_by(model_.Dims().width * 2)
                                .down_by(model_.Dims().height * 1.5)}, 8);

        // Adds Game Over Title text
        set.add_sprite(game_over_text,
                       {center.left_by(model_.Dims().width * 4.25)
                                .up_by(model_.Dims().height * 6)}, 8);

        // Creates a Back to Main Menu button
        set.add_sprite(back_button,button_.back_button, 8);

        // Adds Back to Main Menu text
        set.add_sprite(back_to_menu_text,button_.back_button.right_by(15),9);
    }

    // Checks that counter is started and not zero
    if (begin_count && count_down > 0) {

        // Count Down Text Builder
        ge211::Text_sprite::Builder name_builder4(font_info4);

        // Converts double value "count" to int value "count_down"
        int count = count_down;

        // Set Count Down color
        name_builder4.color({255,255,255}) << count;

        // Updates the count_down sprite
        count_down_sprite.reconfigure(name_builder4);

        // Adds Count Down in approximate center
        set.add_sprite(count_down_sprite,
                       center.left_by(model_.Dims().width)
                       .up_by(model_.Dims().height * 4) , 6);
    }

    // Checks that Main Menu is off and Count Down ended
    if (!showMainMenu && count_down <= 0) {

        // Sets standard transformation for Target
        ge211::Transform target = ge211::Transform{}
                .set_scale_x(gamemode)
                .set_scale_y(gamemode);

        // Checks which game mode is selected and that the game is not over
        if (gamemode == 3 && !model_.game_condition(time,lives)) {

            // Updates the differential to cause the target to shrink
            differential = gamemode - shrink * 0.5;

            // Cause the transformation to shrink target on every frame
            target = ge211::Transform{}
                    .set_scale_x(differential)
                    .set_scale_y(differential);

            // Updates corresponding hit box of target
            target_.target_radius = target_sprite
                    .dimensions().width * (differential) * 2;

        } else if (gamemode == 2 && !model_.game_condition(time,lives)) {

            differential = gamemode - shrink * 0.75;

            target = ge211::Transform{}
                    .set_scale_x(differential)
                    .set_scale_y(differential);

            target_.target_radius = target_sprite
                    .dimensions().width * (differential) * 2;

        } else if (gamemode == 1 && !model_.game_condition(time,lives)) {

            differential = gamemode - shrink;

            target = ge211::Transform{}
                    .set_scale_x(differential)
                    .set_scale_y(differential);

            target_.target_radius = target_sprite
                    .dimensions().width * (differential) * 2;
        }

        // Checks that target disappears and game is not over to subtract a life
        if (differential <= 0 && !model_.game_condition(time,lives)) {
            lives -= 1;
        }

        // Sets the standard transformation for the heart sprites
        ge211::Transform heart = ge211::Transform{}
        .set_scale_y(0.03)
        .set_scale_x(0.03);

        // Updates how many hearts show up depending on how many lives remain
        // If there is no lives, end the game
        if (lives == 0) {
            time = 0;
        } else if (lives == 1) {
            set.add_sprite(heart1,{0,0},5,heart);
        } else if (lives == 2) {
            set.add_sprite(heart1,{0,0},5,heart);
            set.add_sprite(heart2,{50,0},5,heart);
        } else if (lives == 3) {
            set.add_sprite(heart1,{0,0},5,heart);
            set.add_sprite(heart2,{50,0},5,heart);
            set.add_sprite(heart3,{100,0},5,heart);
        }

        // Render the target sprite which shrinks at target_pos
        set.add_sprite(target_sprite, target_.target_pos, 6, target);
    }
}

// Creates the initial window dimensions of the game
View::Dimensions
View::initial_window_dimensions() const
{
    return scene_multiplier * model_.Dims();
}

// Renders sprite that require mouse motion
void
View::draw_input(ge211::Sprite_set& set, ge211::Posn<int> mouse_posn)
{
    // Render the cross-hair sprite wherever mouse moves
    set.add_sprite(crosshair_sprite,
                   mouse_posn.left_by(scene_multiplier / 2)
                             .up_by(scene_multiplier / 2), 10);

    // Checks that Main Menu is on
    if (showMainMenu) {

        // If mouse moves over Easy Button, create hovering effect
        if (button_.easy_click(mouse_posn)) {
            set.add_sprite(e_hover_sprite,button_.e_button, 3);
        } else {
            set.add_sprite(easy_sprite,button_.e_button, 2);
        }

        // If mouse moves over Medium Button, create hovering effect
        if (button_.med_click(mouse_posn)) {
            set.add_sprite(m_hover_sprite,button_.m_button, 3);
        } else {
            set.add_sprite(medium_sprite,button_.m_button, 2);
        }

        // If mouse moves over Hard Button, create hovering effect
        if (button_.hard_click(mouse_posn)) {
            set.add_sprite(h_hover_sprite,button_.h_button, 3);
        } else {
            set.add_sprite(hard_sprite,button_.h_button, 2);
        }
    }


    // If Game is Over and Main Menu is off, create hovering effect
    // for Back to Main Menu Button
    if (!showMainMenu && model_.game_condition(time,lives)) {
        if (button_.back_click(mouse_posn)) {
            set.add_sprite(back_hover, button_.back_button, 9);
        } else {
            set.add_sprite(back_button,button_.back_button, 8);
        }
    }

}

// Performs button operations when mouse position from click is received
void
View::button_input(ge211::Sprite_set& set, View::Position mouse_posn)
{

    if (showMainMenu) {

        // Checks that Easy Button is clicked
        if (button_.easy_click(mouse_posn)) {

            // Renders Game Background
            set.add_sprite(game_board_sprite, {0, 0}, 4);

            // Turn off Main Menu
            showMainMenu = false;

            // Set Game Mode to Easy (3)
            gamemode = 3;

            // Begin Counter
            begin_count = true;
        }

        if (button_.med_click(mouse_posn)) {
            set.add_sprite(game_board_sprite, {0, 0}, 4);
            showMainMenu = false;

            // Set Game Mode to Medium (2)
            gamemode = 2;

            begin_count = true;
        }

        if (button_.hard_click(mouse_posn)) {
            set.add_sprite(game_board_sprite, {0, 0}, 4);
            showMainMenu = false;

            // Set Game Mode to Hard (1)
            gamemode = 1;

            begin_count = true;
        }
    }

    // Checks that the game is over
    if (!showMainMenu && model_.game_condition(time,lives)) {
        // If Back to Main Menu is clicked, reset all conditions
        if (button_.back_click(mouse_posn)) {
            showMainMenu = true;
            gamemode = 0;
            target_.target_clicked = false;
            score = 0;
            click_count = 0;
            hit_count = 0;
            accuracy = 0;
            count_down = 4;
            begin_count = false;
            shrink = 0;
        }
    }
}

// Performs operations on the targets when click position is received
void
View::target_click(ge211::Sprite_set& set, View::Position mouse_posn)
{

    // Creates Text Builder for Timer
    ge211::Text_sprite::Builder timer(font_info2);

    // Checks that Main Menu is off and Count Down Finished
    if (!showMainMenu && count_down <= 0) {

        // Checks that the first target is clicked to start game
        if (target_.target_clicked) {

            // Checks that the target is hit, or that the target completely disappears
            if (target_.hit_target(mouse_posn) || (differential <= 0)) {

                // Sets Target Pos to a random position on the game board
                target_.target_pos = model_.random_spot
                        (target_.target_radius, initial_window_dimensions());

                // Set Target Click to true
                target_.target_clicked = true;

                // Resets the shrink timer
                shrink = 0;

                // No score is added if the target disappears
                if (differential <= 0) {
                    ;
                } else {
                    score += 100;
                }

            }
        }

        int count = time;

        // Updates the value of the timer
        timer.color({0,255,250}) << count;

        // Updates the timer sprite
        game_timer.reconfigure(timer);

        // Displays the timer which counts down in the corner of the screen
        set.add_sprite(game_timer,
                       {initial_window_dimensions().width - 100, 0}, 5);

    }

}








