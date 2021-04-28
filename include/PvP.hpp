//-----------------------------------------------------------------------
//  Author      : Nikita Mashtalirov
//  Created     : 27.04.2021
//  Description : A class representing the gameplay PvP
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

struct Player
{
public:
    std::shared_ptr<Tetromino> m_tetromino;
    std::shared_ptr<Field> m_field;
    std::shared_ptr<Score> m_score;

public:
    sf::Time elapsed_time_fall;
    sf::Time elapsed_time_tick;

    sf::Time time_fall;
    sf::Time time_tick;

    bool game_over;

public:
    Player(
        std::shared_ptr<Tetromino> tetromino,
        std::shared_ptr<Field> field,
        std::shared_ptr<Score> score);
};

class PvP : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;

private:
    Player m_player_1;
    Player m_player_2;

private:
    std::unique_ptr<sf::Music> m_music;

private:
    bool m_pause;

public:
    PvP(std::shared_ptr<Context> &context);
    ~PvP();

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