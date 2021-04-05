//-----------------------------------------------------------------------
//  Author      : Nikita Mashtalirov
//  Created     : 02.04.2021
//  Description : A class representing the gameplay
//-----------------------------------------------------------------------

#pragma once

#include <memory>

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "Tetris.hpp"
#include "State.hpp"

#include "Tetromino.hpp"
#include "Field.hpp"

class PlayProcess : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    std::unique_ptr<Tetromino> m_tetromino;
    std::unique_ptr<Field> m_field;

private:
    sf::Time m_elapsed_time_fall;
    sf::Time m_elapsed_time_tick;

    sf::Time m_time_fall;
    sf::Time m_time_tick;

private:

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