//-----------------------------------------------------------------------
//  Author      : Nikita Mashtalirov
//  Created     : 01.04.2021
//  Description : A class representing the main menu of the game
//-----------------------------------------------------------------------

#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics/Text.hpp>

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "State.hpp"
#include "Tetris.hpp"
#include "Support.hpp"

class Menu : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;

private:
    sf::Text m_title;

private:
    enum ButtonType
    {
        Play,
        PlayerVsPlayer,
        Option,
        Exit
    };
    std::vector<Button> m_button;

private:
    sf::Music m_music;
    sf::SoundBuffer m_sound_buffer;
    sf::Sound m_sound_selection;

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