//-----------------------------------------------------------------------
//  Author      : Nikita Mashtalirov
//  Created     : 06.04.2021
//  Description : A class representing the game over
//-----------------------------------------------------------------------

#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "State.hpp"
#include "Tetris.hpp"
#include "Support.hpp"

class PauseProcess : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;

private:
    sf::Text m_stat;
    sf::Text m_pause;

private:
    Button m_continue;
    Button m_restart;
    Button m_option;
    Button m_exit;

private:
    sf::SoundBuffer m_sound_buffer;
    sf::Sound m_sound_selection;
    sf::Music m_music;

private:
    void UpdateButton(Button &button, float x_pos, float y_pos);

public:
    //  Menu class onstructor
    //  @param  context
    PauseProcess(std::shared_ptr<Context> &context);
    ~PauseProcess();

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