#include "controller.hxx"

//Zero constructor
Controller::Controller(int size)
        : Controller(size,size)
{ }
//Main constructor
Controller::Controller(int width, int height)
        : model_(width, height),
          view_(model_),
          cursor(0,0),
          click(0,0)
{}

//Draws the view functions all together
void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
    view_.draw_input(set,cursor);
    view_.button_input(set,click);

    if (!model_.game_condition(view_.time,view_.lives)){
        view_.target_click(set,click);
    }
}

View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

//Cursor follows the mouse
void Controller::on_mouse_move(ge211::Posn<int> pos)
{
    cursor = pos;
}

//When clicking
void
Controller::on_mouse_up(ge211::Mouse_button, ge211::Posn<int> pos)
{
    click = pos;

    //count clicks
    if (!model_.game_condition(view_.time,view_.lives)
    && !view_.showMainMenu && (view_.count_down <= 0)){
        view_.click_count += 1;
    }

    //initialize game to 30 seconds and 3 lives and start game
    if (!view_.target_.target_clicked) {
        view_.time = 30;
        view_.lives = 3;
    }

    if (view_.target_.hit_target(click)) {//if target clicked
        view_.target_.target_clicked = true;

        // Updates amount of hits
        view_.hit_count += 1;
    }

}

void
Controller::on_frame(double dt)
{
    if (view_.begin_count) {//beginning count down timer
        view_.count_down -= dt * 0.85;
    }

    //game timer update
    if (!model_.game_condition(view_.time,view_.lives)
    && view_.target_.target_clicked) {
        view_.time -= dt;
    }

    //target shrink timer
    if (view_.target_.target_clicked && !view_.target_.hit_target(click)) {
        view_.shrink += dt;
    }
}