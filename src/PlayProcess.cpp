#include "PlayProcess.hpp"
#include "PauseProcess.hpp"
#include "GameOver.hpp"

#include <SFML/Window/Event.hpp>

PlayProcess::PlayProcess(std::shared_ptr<Context> &context)
    : m_context(context),
      m_tetromino(std::make_shared<Tetromino>()),
      m_field(std::make_shared<Field>()),
      m_score(std::make_shared<Score>()),
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
    m_context->m_assets->AddTexture(SIDE_VIEW,
                                    "assets/textures/tiles.png", true);

    m_tetromino->Init(m_context->m_assets->GetTexture(TILES));
    m_field->Init(m_context->m_assets->GetTexture(TILES));
    m_score->Init(m_context->m_assets->GetTexture(TILES),
                  m_context->m_assets->GetFont(MAIN_FONT));
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
                m_context->m_states->PushState(std::make_unique<PauseProcess>(m_context));
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
                    m_score->IncreaseScores(7);
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
            case sf::Keyboard::Space:
            {
                while (m_field->PermissibilityMovement(
                    m_tetromino->GetFigure(), 0, DOWN))
                {
                    m_tetromino->Move(0, DOWN);
                    m_score->IncreaseScores(7);
                    m_elapsed_time_tick = sf::Time::Zero;
                }
                break;
            }
            default:
                break;
            }
        }
    }
}

void PlayProcess::Update(sf::Time delta_time)
{
    if (!m_pause)
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
                m_tetromino->Create();
                if (m_field->FigureOnCells(m_tetromino->GetFigure()))
                {
                    m_context->m_states->PushState(std::make_unique<GameOver>(m_context), true);
                    m_score->SaveScores();
                }
                m_field->ClearLines(*m_score);
                if (m_score->LevelChanged())
                {
                    m_time_fall -= sf::seconds(0.015f);
                    m_time_tick -= sf::seconds(0.025f);
                }
            }
            m_elapsed_time_fall = sf::Time::Zero;
            m_elapsed_time_tick = sf::Time::Zero;
        }

        m_tetromino->ShadowDisplay(*m_field);
    }
}

void PlayProcess::Draw()
{
    m_context->m_window->clear();
    m_field->Draw(*m_context->m_window);
    m_tetromino->Draw(*m_context->m_window);
    m_score->Draw(*m_context->m_window);

    m_context->m_window->display();
}

void PlayProcess::Pause()
{
    m_pause = true;
}

void PlayProcess::Launch()
{
    m_pause = false;
}