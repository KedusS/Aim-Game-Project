#include "model.hxx"
#include <stdlib.h>

using namespace ge211;


Scene::Scene(Dimensions dims)
    : scene_dims(dims)
{
    if (dims.width < 2 || dims.height < 2) {
        throw Client_logic_error("Scene::Scene: dimensions too small");
    }

    if (dims.width > 120 || dims.height > 120) {
        throw Client_logic_error("Scene::Scene: dimensions too large");
    }
}

Scene::Dimensions
Scene::dimensions() const
{
    return scene_dims;
}

//In bounds of the screen
bool
Scene::good_position(Position pos) const
{
    return 0 <= pos.x && pos.x < scene_dims.width &&
           0 <= pos.y && pos.y < scene_dims.height;
}

void
Scene::bounds_check(Position pos) const
{//if not in good position, cause error
    if (!good_position(pos)) {
        throw Client_logic_error("Scene: position out of bounds");
    }
}

///--------------------------------------------------------------------------///

static int const scene_multiplier = 12;

//Zero Constructor
Model::Model(int size)
        : Model(size,size)

{}

//Main Constructor
Model::Model(int width, int height)
        : game_scene({width,height}),
          game_over(true)
{}

Model::Dimensions
Model::Dims() const
{
    return game_scene.dimensions();
}

Model::Position
Model::operator[](Position pos) const
{
    game_scene.bounds_check(pos);
    return pos;
}

//Find random position on screen
Model::Position
Model::random_spot(int radius, Dimensions dims) const
{//https://stackoverflow.com/questions/26086128/generate-different-random-coordinates
    // for random position
    int x = rand() % (dims.width - radius);//also makes sure the target position is not set out of bounds
    int y = rand() % (dims.height - radius);

    return {x,y};
}

//Tells whether game ends or not based on lives and time
bool
Model::game_condition(double time, int lives)
{
    // If time or lives are 0 game over
    if (time <= 0 || lives == 0) {
        game_over = true;
    } else {
        game_over = false;
    }

    return game_over;
}

///--------------------------------------------------------------------------///

Target::Target(int size, bool cond)
        :Target(size,{size,size},cond)
{}

Target::Target(int radius, Position pos, bool cond)
        : target_pos(pos),
          target_radius(radius),
          target_clicked(cond)
{}

//Tells us whether the player clicks on the target
bool Target::hit_target(Position pos) const
{
    bool result;

    Rectangle target(target_pos.x, target_pos.y,
                     target_radius / 2, target_radius / 2);

    // Cursor edges
    int r_cursor = pos.x + (scene_multiplier / 2);
    int l_cursor = pos.x - (scene_multiplier / 2);
    int t_cursor = pos.y - (scene_multiplier / 2);
    int b_cursor = pos.y + (scene_multiplier / 2);

    // Easy Button Edges
    int r_easy = target_pos.x + target.width;
    int l_easy = target_pos.x;
    int t_easy = target_pos.y;
    int b_easy = target_pos.y + target.height;

    // Conditions to check if hits target
    bool cond1 = r_cursor < l_easy;
    bool cond2 = l_cursor > r_easy;
    bool cond3 = t_cursor > b_easy;
    bool cond4 = b_cursor < t_easy;

    if (cond1 || cond2 || cond3 || cond4){
        result = false;
    } else {
        result = true;
    }

    return result;
}

///--------------------------------------------------------------------------///
//Zero Constructor
Button::Button(int size)
        : Button(size,size,{size,size})
{}
//Main Constructor
Button::Button(int width, int height, Position pos)
        : e_button{pos.left_by(width * 1.5).up_by(height * 1.25)},
          m_button{pos.left_by(width * 1.5)},
          h_button{pos.left_by(width * 1.5).down_by(height * 1.25)},
          back_button(pos.right_by(width * 2.75).down_by(height * 4.5)),
          button_dims(width * 3,height),
          dims(width,height)
{};

//Tells us whether the player clicks on the buttons
bool
Button::button_click(Position pos, Position button_pos) const
{

    bool result;

    Rectangle button(button_pos.x, button_pos.y,
                       button_dims.width, button_dims.height);

    // Cursor edges
    int r_cursor = pos.x + (scene_multiplier / 2);
    int l_cursor = pos.x - (scene_multiplier / 2);
    int t_cursor = pos.y - (scene_multiplier / 2);
    int b_cursor = pos.y + (scene_multiplier / 2);

    // Easy Button Edges
    int r_easy = button_pos.x + button.width;
    int l_easy = button_pos.x;
    int t_easy = button_pos.y;
    int b_easy = button_pos.y + button.height;

    // Conditions to check if hits button
    bool cond1 = r_cursor < l_easy;
    bool cond2 = l_cursor > r_easy;
    bool cond3 = t_cursor > b_easy;
    bool cond4 = b_cursor < t_easy;

    if (cond1 || cond2 || cond3 || cond4){
        result = false;
    } else {
        result = true;
    }

    return result;
}

//Easy button
bool
Button::easy_click(Position pos) const
{
    return (button_click(pos,e_button));
}

//Medium button
bool
Button::med_click(Position pos) const
{
    return (button_click(pos,m_button));
}

//Hard button
bool
Button::hard_click(Position pos) const
{
    return (button_click(pos,h_button));
}

//Back to main menu button
bool
Button::back_click(Position pos) const
{
    return (button_click(pos,back_button));
}