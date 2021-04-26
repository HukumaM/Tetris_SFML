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
    m_context->m_assets->AddTexture(TILES_SEA,
                                    "assets/textures/tiles_seas.png");
    m_context->m_assets->AddTexture(TILES_SEA_SHADOW,
                                    "assets/textures/tiles_seas_shadow.png");
    m_context->m_assets->AddTexture(NUMBERS,
                                    "assets/textures/numbers.png");

    m_context->m_assets->AddTexture(SCORE_TABLE, "assets/textures/score_table.png");
    m_context->m_assets->AddTexture(LINES_TABLE, "assets/textures/lines_table.png");
    m_context->m_assets->AddTexture(LINE_TABLE, "assets/textures/line_table.png", true);

    // m_context->m_assets->AddTexture(TILES_RAINBOW,
    //                                 "assets/textures/tiles_rainbow.png");
    // m_context->m_assets->AddTexture(TILES_RAINBOW_SHADOW,
    //                                 "assets/textures/tiles_rainbow_shadow.png");

    m_context->m_assets->AddTexture(SIDE_VIEW,
                                    "assets/textures/tiles.png", true);

    m_tetromino->Init(m_context->m_assets->GetTexture(TILES_SEA),
                      m_context->m_assets->GetTexture(TILES_SEA_SHADOW));

    m_field->Init(m_context->m_assets->GetTexture(TILES_SEA));

    m_score->Init(m_context->m_assets->GetTexture(SCORE_TABLE),
                  m_context->m_assets->GetTexture(LINES_TABLE),
                  m_context->m_assets->GetTexture(LINE_TABLE),
                  m_context->m_assets->GetTexture(NUMBERS),
                  m_context->m_assets->GetFont(MAIN_FONT));

    // m_score->Init(m_context->m_assets->GetTexture(SCORE_TABLE),
    //               m_context->m_assets->GetTexture(NUMBERS),
    //               m_context->m_assets->GetFont(MAIN_FONT));
    // m_tetromino->Init(m_context->m_assets->GetTexture(TILES_RAINBOW),
    //                   m_context->m_assets->GetTexture(TILES_RAINBOW_SHADOW));
    // m_field->Init(m_context->m_assets->GetTexture(TILES_RAINBOW));
    // m_score->Init(m_context->m_assets->GetTexture(TILES_RAINBOW),
    //               m_context->m_assets->GetFont(MAIN_FONT));

    if (m_music.openFromFile("assets/audio/a_type_music.ogg"))
    {
        m_music.play();
        m_music.setLoop(true);
        m_music.setVolume(50.f);
    }

    if (m_buffer_clear_line.loadFromFile("assets/audio/line.wav"))
    {
        m_sound_clear_line.setBuffer(m_buffer_clear_line);
    }
    if (m_buffer_fall.loadFromFile("assets/audio/fall.wav"))
    {
        m_sound_fall.setBuffer(m_buffer_fall);
    }
    if (m_buffer_move.loadFromFile("assets/audio/selection.wav"))
    {
        m_sound_move.setBuffer(m_buffer_move);
        m_sound_move.setPitch(1.f);
        m_sound_move.setVolume(50.f);
    }
}

void PlayProcess::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_music.stop();
            m_context->m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
            {
                m_music.pause();
                m_context->m_states->PushState(std::make_unique<PauseProcess>(m_context));
                break;
            }
            case sf::Keyboard::Up:
            {
                if (m_tetromino->Rotate(*m_field))
                {
                    m_elapsed_time_tick = sf::Time::Zero;
                    m_sound_move.play();
                }
                break;
            }
            case sf::Keyboard::Down:
            {
                if (m_field->PermissibilityMovement(
                        m_tetromino->GetCurrentFigure(), 0, DOWN))
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
                        m_tetromino->GetCurrentFigure(), LEFT, 0))
                {
                    m_tetromino->Move(LEFT, 0);
                    m_elapsed_time_tick = sf::Time::Zero;
                }
                break;
            }
            case sf::Keyboard::Right:
            {
                if (m_field->PermissibilityMovement(
                        m_tetromino->GetCurrentFigure(), RIGTH, 0))
                {
                    m_tetromino->Move(RIGTH, 0);
                    m_elapsed_time_tick = sf::Time::Zero;
                }
                break;
            }
            case sf::Keyboard::Space:
            {
                while (m_field->PermissibilityMovement(
                    m_tetromino->GetCurrentFigure(), 0, DOWN))
                {
                    m_tetromino->Move(0, DOWN);
                    m_score->IncreaseScores(7);
                    m_elapsed_time_tick = sf::Time::Zero;
                    m_sound_fall.play();
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
            if (m_field->PermissibilityMovement(m_tetromino->GetCurrentFigure(), 0, DOWN))
            {
                m_tetromino->Move(0, DOWN);
                m_elapsed_time_fall = sf::Time::Zero;
                m_elapsed_time_tick = sf::Time::Zero;
            }
        }
        else if (m_elapsed_time_fall >= m_time_fall &&
                 m_elapsed_time_tick >= m_time_tick)
        {
            if (!m_field->PermissibilityMovement(m_tetromino->GetCurrentFigure(), 0, DOWN))
            {
                m_field->PlaceFigureOnField(m_tetromino->GetCurrentFigure(), m_tetromino->GetColor());
                m_tetromino->CreateNextFigure();
                m_tetromino->Create();
                if (m_field->FigureOnCells(m_tetromino->GetCurrentFigure()))
                {
                    m_music.stop();
                    m_context->m_states->PushState(std::make_unique<GameOver>(m_context), true);
                    m_score->SaveScores();
                    m_score->UpdateRankingTable();
                }
                if (m_field->ClearLines(*m_score))
                {
                    m_sound_clear_line.play();
                }
                if (m_score->LevelChanged()) 
                {
                    m_time_fall -= sf::seconds(0.015f);
                    m_time_tick -= sf::seconds(0.025f);
                }
                if (m_score->LevelChanged() && m_score->GetLevel() == 6)
                {
                    m_music.stop();
                    if (m_music.openFromFile("assets/audio/b_type_music.ogg"))
                    {
                        m_music.play();
                    }
                }
                else if (m_score->LevelChanged() && m_score->GetLevel() == 11)
                {
                    m_music.stop();
                    if (m_music.openFromFile("assets/audio/c_type_music.ogg"))
                    {
                        m_music.play();
                    }
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
    m_score->Draw(*m_context->m_window);
    m_tetromino->Draw(*m_context->m_window);
    m_context->m_window->display();
}

void PlayProcess::Pause()
{
    m_pause = true;
    if (m_music.getStatus() == sf::Sound::Paused)
    {
        m_music.pause();
    }
}

void PlayProcess::Launch()
{
    m_pause = false;
    if (m_music.getStatus() == sf::Sound::Paused)
    {
        m_music.play();
    }
}