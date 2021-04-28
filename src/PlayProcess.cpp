#include "PlayProcess.hpp"
#include "PauseProcess.hpp"
#include "GameOver.hpp"

#include <SFML/Window/Event.hpp>

PlayProcess::PlayProcess(std::shared_ptr<Context> &context)
    : m_context(context),
      m_tetromino(std::make_shared<Tetromino>(Score::PlayerNumber::First)),
      m_field(std::make_shared<Field>(Score::PlayerNumber::First)),
      m_score(std::make_shared<Score>(Score::PlayerNumber::First)),
      m_music(std::make_unique<sf::Music>()),
      m_time_fall(sf::seconds(0.3f)),
      m_time_tick(sf::seconds(0.7f))
{
}

PlayProcess::~PlayProcess()
{
}

void PlayProcess::Init()
{
    if (m_context->m_window->getSize() != sf::Vector2u(540, 720))
    {
        m_context->m_window->close();
        m_context->m_window->create(sf::VideoMode(WIDTH_LOW, HEIGHT_LOW), "Tetris",
                                    sf::Style::Titlebar | sf::Style::Close);
    }
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
                  m_context->m_assets->GetTexture(NUMBERS));

    Audio::LoadMusic(Audio::A_STAGE_MUSIC, "assets/audio/a_type_music.ogg", true, true);
    Audio::LoadMusic(Audio::B_STAGE_MUSIC, "assets/audio/b_type_music.ogg", true);
    Audio::LoadMusic(Audio::C_STAGE_MUSIC, "assets/audio/c_type_music.ogg", true);

    m_music = std::move(Audio::GetMusicPtr(Audio::A_STAGE_MUSIC));
    m_music->setVolume(Audio::GetVolumeMusic());
    m_music->setLoopPoints(sf::Music::TimeSpan(sf::Time::Zero, sf::seconds(170)));

    Audio::LoadSound(Audio::CLEAN_LINE, "assets/audio/line.wav");
    Audio::GetSound(Audio::CLEAN_LINE).setVolume(Audio::GetVolumeFX());

    Audio::LoadSound(Audio::FALL, "assets/audio/fall.wav");
    Audio::GetSound(Audio::FALL).setVolume(Audio::GetVolumeFX());

    Audio::LoadSound(Audio::MOVE, "assets/audio/selection.wav");
    Audio::GetSound(Audio::MOVE).setVolume(Audio::GetVolumeFX());
    Audio::GetSound(Audio::MOVE).setPitch(1.4f);
}

void PlayProcess::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_music->stop();
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
                    Audio::GetSound(Audio::MOVE).play();
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
                    Audio::GetSound(Audio::FALL).play();
                }
                break;
            }
            case sf::Keyboard::RControl:
            {
                m_score->UpdateScores(1);
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
        Audio::GetSound(Audio::FALL).setVolume(Audio::GetVolumeFX());
        Audio::GetSound(Audio::MOVE).setVolume(Audio::GetVolumeFX());
        Audio::GetSound(Audio::CLEAN_LINE).setVolume(Audio::GetVolumeFX());

        m_music->setVolume(Audio::GetVolumeMusic());

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
                    m_music->stop();
                    m_context->m_states->PushState(std::make_unique<GameOver>(m_context), true);
                    m_score->SaveScores();
                    m_score->UpdateRankingTable();
                }
                if (m_field->ClearLines(*m_score))
                {
                    Audio::GetSound(Audio::CLEAN_LINE).play();
                }
                if (m_score->LevelChanged())
                {
                    m_time_fall -= sf::seconds(0.015f);
                    m_time_tick -= sf::seconds(0.025f);

                    auto level = m_score->GetLevel();
                    if (level == 6)
                    {
                        m_music->stop();
                        m_music = std::move(Audio::GetMusicPtr(Audio::B_STAGE_MUSIC));
                        m_music->play();
                    }
                    else if (level == 11)
                    {
                        m_music->stop();
                        m_music = std::move(Audio::GetMusicPtr(Audio::C_STAGE_MUSIC));
                        m_music->play();
                    }

                    m_music->setPitch(static_cast<float>(level) / 40.f + 1.f);
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
    m_field->Draw(*m_context->m_window.get());
    m_score->Draw(*m_context->m_window.get());
    m_tetromino->Draw(*m_context->m_window.get());
    m_context->m_window->display();
}

void PlayProcess::Pause()
{
    m_pause = true;
    m_music->pause();
}

void PlayProcess::Launch()
{
    m_pause = false;
    m_music->play();
}