#include "PlayProcess.hpp"
#include "Menu.hpp"

#include <SFML/Window/Event.hpp>

PlayProcess::PlayProcess(std::shared_ptr<Context> &context)
    : m_context(context),
      m_tetromino(std::make_unique<Tetromino>()),
      m_field(std::make_unique<Field>()),
      m_time_fall(sf::seconds(0.3f)),
      m_time_tick(sf::seconds(0.7f))
{
}

PlayProcess::~PlayProcess()
{
}

void PlayProcess::Init()
{
    m_context->m_assets->AddTexture(TILES,
                                    "assets/textures/tiles.png");
    m_context->m_assets->AddTexture(GAME_OVER,
                                    "assets/textures/game_over.png");

    m_tetromino->Init(m_context->m_assets->GetTexture(TILES));
    m_field->Init(m_context->m_assets->GetTexture(TILES));
}

void PlayProcess::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_context->m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
            {
                Pause();
                m_context->m_states->PushState(
                    std::make_unique<Menu>(m_context));
                break;
            }
            case sf::Keyboard::Up:
            {
                if (m_tetromino->Rotate(*m_field))
                {
                    m_elapsed_time_tick = sf::Time::Zero;
                }
                break;
            }
            case sf::Keyboard::Down:
            {
                if (m_field->PermissibilityMovement(
                        m_tetromino->GetFigure(), 0, DOWN))
                {
                    m_tetromino->Move(0, DOWN);
                    m_elapsed_time_tick = sf::Time::Zero;
                }
                break;
            }
            case sf::Keyboard::Left:
            {
                if (m_field->PermissibilityMovement(
                        m_tetromino->GetFigure(), LEFT, 0))
                {
                    m_tetromino->Move(LEFT, 0);
                    m_elapsed_time_tick = sf::Time::Zero;
                }
                break;
            }
            case sf::Keyboard::Right:
            {
                if (m_field->PermissibilityMovement(
                        m_tetromino->GetFigure(), RIGTH, 0))
                {
                    m_tetromino->Move(RIGTH, 0);
                    m_elapsed_time_tick = sf::Time::Zero;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                // m_play.pressed = false;
                // m_exit.pressed = false;

                // if (m_play.selected)
                // {
                //     m_play.pressed = true;
                // }
                // else
                // {
                //     m_exit.pressed = true;
                // }
                break;
            }
            case sf::Keyboard::Space:
            {
                while (m_field->PermissibilityMovement(
                    m_tetromino->GetFigure(), 0, DOWN))
                {
                    m_tetromino->Move(0, DOWN);
                    m_elapsed_time_tick = sf::Time::Zero;
                }
                break;
            }
            default:
                break;
            }
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Space)
            {
            }
        }
    }
}

void PlayProcess::Update(sf::Time delta_time)
{
    m_elapsed_time_fall += delta_time;
    m_elapsed_time_tick += delta_time;

    if (m_elapsed_time_fall >= m_time_fall &&
        m_elapsed_time_tick < m_time_tick)
    {
        if (m_field->PermissibilityMovement(m_tetromino->GetFigure(), 0, DOWN))
        {
            m_tetromino->Move(0, DOWN);
            m_elapsed_time_fall = sf::Time::Zero;
            m_elapsed_time_tick = sf::Time::Zero;
        }
    }
    else if (m_elapsed_time_fall >= m_time_fall &&
             m_elapsed_time_tick >= m_time_tick)
    {
        if (!m_field->PermissibilityMovement(m_tetromino->GetFigure(), 0, DOWN))
        {
            m_field->PlaceFigureOnField(m_tetromino->GetFigure(), m_tetromino->GetColor());
            if (!m_tetromino->Create())
            {
            }
            m_field->ClearLines();
            //score.InsertPlayer();
        }
        m_elapsed_time_fall = sf::Time::Zero;
        m_elapsed_time_tick = sf::Time::Zero;
    }

    m_tetromino->ShadowDisplay(*m_field);
}

void PlayProcess::Draw()
{
    m_context->m_window->clear();
    m_field->Draw(*m_context->m_window);
    m_tetromino->Draw(*m_context->m_window);

    m_context->m_window->display();
}

void PlayProcess::Pause()
{
}

void PlayProcess::Launch()
{
}