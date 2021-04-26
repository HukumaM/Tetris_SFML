//-----------------------------------------------------------------------
//  Author      : Nikita Mashtalirov
//  Created     : 02.04.2021
//  Description : A class representing the gameplay
//-----------------------------------------------------------------------

#pragma once

#include <memory>

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "Tetris.hpp"
#include "State.hpp"

#include "Tetromino.hpp"
#include "Field.hpp"
#include "Score.hpp"

class PlayProcess : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;

    std::shared_ptr<Tetromino> m_tetromino;
    std::shared_ptr<Field> m_field;
    std::shared_ptr<Score> m_score;

private:
    sf::Time m_elapsed_time_fall;
    sf::Time m_elapsed_time_tick;

    sf::Time m_time_fall;
    sf::Time m_time_tick;

private:
    sf::Music m_music;

    sf::SoundBuffer m_sound_buffer;
    sf::Sound m_sound;
    
    sf::SoundBuffer m_buffer_clear_line;
    sf::Sound m_sound_clear_line;

    sf::SoundBuffer m_buffer_fall;
    sf::Sound m_sound_fall;

    sf::SoundBuffer m_buffer_move;
    sf::Sound m_sound_move;

private:
    bool m_pause;

public:
    PlayProcess(std::shared_ptr<Context> &context);
    ~PlayProcess();

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

    //   method for pausing the state
    void Pause() override;

    //   method for launching the state
    void Launch() override;
};