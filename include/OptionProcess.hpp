//-----------------------------------------------------------------------
//  Author      : Nikita Mashtalirov
//  Created     : 26.04.2021
//  Description : A class representing the 
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

class OptionProcess : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;

private:
    float m_music_volume;
    float m_fx_volume;

private:
    enum ButtonType
    {
        Music,
        FX,
        Back
    };
    std::vector<Button> m_button;

public:
    //  Menu class onstructor
    //  @param  context
    OptionProcess(std::shared_ptr<Context> &context);
    ~OptionProcess();

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