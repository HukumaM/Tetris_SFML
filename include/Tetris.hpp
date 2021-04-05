//-----------------------------------------------------------------------
//  Author      : Nikita Mashtalirov
//  Created     : 01.04.2021
//  Description : The main class of the game
//-----------------------------------------------------------------------

#pragma once

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

#include "AssetManager.hpp"
#include "StateManager.hpp"

//  An enumeration that stores asset IDs
enum AssetID
{
    MAIN_FONT,
    TILES,
    BACKGROUND,
    GAME_OVER
};

//  An enumeration that stores the game window resolution values
enum WINDOW_SIZE
{
    WIDTH_LOW = 540,
    HEIGHT_LOW = 720,
    WIDTH_HIGH = 720,
    HEIGHT_HIGH = 1080
};

//  A structure that stores smart pointers to assets, states, and a window
struct Context
{
    //  Pointer to context assets
    std::unique_ptr<Engine::AssetManager> m_assets;
    //  Pointer to context states
    std::unique_ptr<Engine::StateManager> m_states;
    //  Pointer to render window 
    std::unique_ptr<sf::RenderWindow> m_window;

    Context()
    {
        this->m_assets = std::make_unique<Engine::AssetManager>();
        this->m_states = std::make_unique<Engine::StateManager>();
        this->m_window = std::make_unique<sf::RenderWindow>();
    }
};


class Tetris_Game
{
private:
    //  A common pointer for all states
    std::shared_ptr<Context> m_context;

    //  A variable that stores a time value equal to one frame
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);

public:
    Tetris_Game();
    ~Tetris_Game();

public:
    //  Game launch function
    void Run();
};
