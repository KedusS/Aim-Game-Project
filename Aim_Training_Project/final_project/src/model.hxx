#pragma once

#include <ge211.hxx>


class Scene
{
public:

    using Dimensions = ge211::Dims<int>;

    using Position = ge211::Posn<int>;

    bool good_position(Position) const;

    void bounds_check(Position) const;

private:

    Dimensions scene_dims;

public:

    explicit Scene(Dimensions dims);

    Dimensions dimensions() const;
};
///--------------------------------------------------------------------------///
class Model
{
public:
    using Dimensions = ge211::Dims<int>;

    using Position = ge211::Posn<int>;

    using Rectangle = ge211::Rect<int>;

    explicit Model(int size = 100);

    Model(int width, int height);

    Dimensions Dims() const;

    Position operator[](Position) const;

    Position random_spot(int radius, Dimensions dims) const;

    bool game_condition (double time, int lives);

private:
    Scene game_scene;
    bool game_over;
};
///--------------------------------------------------------------------------///
class Target
{
public:
    using Dimensions = ge211::Dims<int>;

    using Position = ge211::Posn<int>;

    using Rectangle = ge211::Rect<int>;

    explicit Target (int size = 0, bool cond = false);

    Target(int radius, Position pos, bool cond);

    Position target_pos;
    int target_radius;
    bool target_clicked;

    bool hit_target(Position) const;

private:
};
///--------------------------------------------------------------------------///
class Button
{
public:
    using Dimensions = ge211::Dims<int>;

    using Position = ge211::Posn<int>;

    using Rectangle = ge211::Rect<int>;

    explicit Button (int size = 0);

    Button(int width, int height, Position pos);

    bool button_click(Position, Position) const;

    bool easy_click(Position) const;

    bool med_click(Position) const;

    bool hard_click(Position) const;

    bool back_click(Position) const;

    Position e_button;//position of easy button
    Position m_button;//position of medium button
    Position h_button;//position of hard button
    Position back_button;//position of back button
    Dimensions button_dims;//standard button dimensions

private:
    Dimensions dims;
};