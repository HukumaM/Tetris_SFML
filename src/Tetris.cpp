#include "Tetris.hpp"
#include "Menu.hpp"


Tetris_Game::Tetris_Game()
    : m_context(std::make_shared<Context>())
{
    m_context->m_window->create(sf::VideoMode(WIDTH_LOW, HEIGHT_LOW), "Tetris",
                                      sf::Style::Titlebar | sf::Style::Close);

    m_context->m_states->PushState(std::make_unique<Menu>(m_context));

    m_context->m_window->setPosition(sf::Vector2i(660, 180));
}

Tetris_Game::~Tetris_Game()
{
}

void Tetris_Game::Run()
{
    //  The clock variable required to determine the elapsed time per cycle
    sf::Clock clock;
    //  A variable required to store the time elapsed since the last frame
    sf::Time time_since_last_frame{sf::Time::Zero};

    while (this->m_context->m_window->isOpen())
    {
        time_since_last_frame += clock.restart();
        while (time_since_last_frame > this->TIME_PER_FRAME)
        {
            time_since_last_frame -= this->TIME_PER_FRAME;

            this->m_context->m_states->ProcessStateChange();
            this->m_context->m_states->GetState()->ProcessInput();
            this->m_context->m_states->GetState()->Update(this->TIME_PER_FRAME);
            this->m_context->m_states->GetState()->Draw();
        }
    }
}
