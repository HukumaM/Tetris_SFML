//-----------------------------------------------------------------------
//  Author      : Nikita Mashtalirov
//  Created     : 01.04.2021
//  Description : A class representing the main menu of the game
//-----------------------------------------------------------------------

#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Tetris.hpp"

namespace Color_Combination
{
    static const sf::Color kakao        = sf::Color(48, 27, 40);
    static const sf::Color chocolate    = sf::Color(82, 54, 52);
    static const sf::Color toffee       = sf::Color(182, 69, 44);
    static const sf::Color glaze        = sf::Color(221, 197, 162);

    // Fresh herbs

    static const sf::Color blue_black   = sf::Color(2, 28, 30);
    static const sf::Color grey_blue    = sf::Color(0, 68, 69);
    static const sf::Color rain         = sf::Color(44, 120, 115);
    static const sf::Color herbs        = sf::Color(111, 185, 143);
}

struct Button
{
    sf::Text text;
    bool selected;
    bool pressed;
    Button(bool want_selected = false, bool want_pressed = false)
        : selected(want_selected), pressed(want_pressed), text(sf::Text())
    {
    }
};

class Menu : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;

private:
    sf::Text m_title;

private:
    Button m_play;
    Button m_exit;

private:
    //  Function for editing text content
    //  @param  text    Variable whose contents will be edited
    //  @param  string  The string to be assigned to the text variable
    //  @param  size    Text character size
    //  @param  color   Text color
    void EditTextContent(sf::Text &text, const sf::String &string, unsigned int size,
                  const sf::Color &color);

    //  Function for editing the position of text on the screen
    //  Defines the middle of the text and moves it to the specified coordinates
    //  @param  text    Variable whose contents will be edited
    //  @param  x       x-axis coordinate
    //  @param  y       y-axis coordinate
    void EditTextPosition(sf::Text &text, float x, float y);

public:
    //  Menu class onstructor
    //  @param  context      
    Menu(std::shared_ptr<Context> &context);
    ~Menu();

public:
    //  Overriding the method for initialization class data
    void Init() override;

    //  Overriding the method for processing keystrokes and mouse clicks
    void ProcessInput() override;

    //  Overriding the method for updating the position of sprites, texts
    //  @param  delta_time  time elapsed since the last function call
    void Update(sf::Time delta_time) override;

    //  Overriding the method for drawing sprites and text
    void Draw() override;
};