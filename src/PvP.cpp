#include "PvP.hpp"
#include "PauseProcess.hpp"
#include "GameOver.hpp"

#include <iostream>

#include <SFML/Window/Event.hpp>

Player::Player(std::shared_ptr<Tetromino> tetromino,
               std::shared_ptr<Field> field,
               std::shared_ptr<Score> score)
    : m_tetromino(tetromino),
      m_field(field),
      m_score(score),
      elapsed_time_fall(sf::Time::Zero),
      elapsed_time_tick(sf::Time::Zero),
      time_fall(sf::seconds(0.3f)),
      time_tick(sf::seconds(0.7f)),
      game_over(false)
{
}

PvP::PvP(std::shared_ptr<Context> &context)
    : m_context(context),
      m_music(std::make_unique<sf::Music>()),
      m_player_1(std::make_shared<Tetromino>(Score::PlayerNumber::First),
                 std::make_shared<Field>(Score::PlayerNumber::First),
                 std::make_shared<Score>(Score::PlayerNumber::First)),
      m_player_2(std::make_shared<Tetromino>(Score::PlayerNumber::Second),
                 std::make_shared<Field>(Score::PlayerNumber::Second),
                 std::make_shared<Score>(Score::PlayerNumber::Second))
{
}

PvP::~PvP()
{
}

void PvP::Init()
{
    if (m_context->m_window->getSize() != sf::Vector2u(1080, 720))
    {
        m_context->m_window->close();
        m_context->m_window->create(sf::VideoMode(WIDTH_LOW + WIDTH_LOW, HEIGHT_LOW), "Tetris",
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

    m_player_1.m_tetromino->Init(m_context->m_assets->GetTexture(TILES_SEA),
                                 m_context->m_assets->GetTexture(TILES_SEA_SHADOW));

    m_player_1.m_field->Init(m_context->m_assets->GetTexture(TILES_SEA));

    m_player_1.m_score->Init(m_context->m_assets->GetTexture(SCORE_TABLE),
                             m_context->m_assets->GetTexture(LINES_TABLE),
                             m_context->m_assets->GetTexture(LINE_TABLE),
                             m_context->m_assets->GetTexture(NUMBERS));

    m_player_2.m_tetromino->Init(m_context->m_assets->GetTexture(TILES_SEA),
                                 m_context->m_assets->GetTexture(TILES_SEA_SHADOW));

    m_player_2.m_field->Init(m_context->m_assets->GetTexture(TILES_SEA));

    m_player_2.m_score->Init(m_context->m_assets->GetTexture(SCORE_TABLE),
                             m_context->m_assets->GetTexture(LINES_TABLE),
                             m_context->m_assets->GetTexture(LINE_TABLE),
                             m_context->m_assets->GetTexture(NUMBERS));

    Audio::LoadMusic(Audio::A_STAGE_MUSIC, "assets/audio/a_type_music.ogg", true, true);
    Audio::LoadMusic(Audio::B_STAGE_MUSIC, "assets/audio/b_type_music.ogg", true);
    Audio::LoadMusic(Audio::C_STAGE_MUSIC, "assets/audio/c_type_music.ogg", true);

    m_music = std::move(Audio::GetMusicPtr(Audio::A_STAGE_MUSIC));
    m_music->setVolume(Audio::GetVolumeMusic());

    Audio::LoadSound(Audio::CLEAN_LINE, "assets/audio/line.wav");
    Audio::GetSound(Audio::CLEAN_LINE).setVolume(Audio::GetVolumeFX());

    Audio::LoadSound(Audio::FALL, "assets/audio/fall.wav");
    Audio::GetSound(Audio::FALL).setVolume(Audio::GetVolumeFX());

    Audio::LoadSound(Audio::MOVE, "assets/audio/selection.wav");
    Audio::GetSound(Audio::MOVE).setVolume(Audio::GetVolumeFX());
    Audio::GetSound(Audio::MOVE).setPitch(1.4f);
}

void PvP::ProcessInput()
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
            }
            if (!m_player_1.game_over)
            {
                switch (event.key.code)
                {
                    // First
                case sf::Keyboard::R:
                {
                    if (m_player_1.m_tetromino->Rotate(*m_player_1.m_field))
                    {
                        m_player_1.elapsed_time_tick = sf::Time::Zero;
                        Audio::GetSound(Audio::MOVE).play();
                    }
                    break;
                }
                case sf::Keyboard::F:
                {
                    if (m_player_1.m_field->PermissibilityMovement(
                            m_player_1.m_tetromino->GetCurrentFigure(), 0, DOWN))
                    {
                        m_player_1.m_tetromino->Move(0, DOWN);
                        m_player_1.m_score->IncreaseScores(7);
                        m_player_1.elapsed_time_tick = sf::Time::Zero;
                    }
                    break;
                }
                case sf::Keyboard::D:
                {
                    if (m_player_1.m_field->PermissibilityMovement(
                            m_player_1.m_tetromino->GetCurrentFigure(), LEFT, 0))
                    {
                        m_player_1.m_tetromino->Move(LEFT, 0);
                        m_player_1.elapsed_time_tick = sf::Time::Zero;
                    }
                    break;
                }
                case sf::Keyboard::G:
                {
                    if (m_player_1.m_field->PermissibilityMovement(
                            m_player_1.m_tetromino->GetCurrentFigure(), RIGTH, 0))
                    {
                        m_player_1.m_tetromino->Move(RIGTH, 0);
                        m_player_1.elapsed_time_tick = sf::Time::Zero;
                    }
                    break;
                }
                case sf::Keyboard::LShift:
                {

                    while (m_player_1.m_field->PermissibilityMovement(
                        m_player_1.m_tetromino->GetCurrentFigure(), 0, DOWN))
                    {
                        m_player_1.m_tetromino->Move(0, DOWN);
                        m_player_1.m_score->IncreaseScores(7);
                        m_player_1.elapsed_time_tick = sf::Time::Zero;
                        Audio::GetSound(Audio::FALL).play();
                    }
                    break;
                }
                }
            }
            if (!m_player_2.game_over)
            {
                switch (event.key.code)
                {
                    // Second
                case sf::Keyboard::Up:
                {
                    if (m_player_2.m_tetromino->Rotate(*m_player_2.m_field))
                    {
                        m_player_2.elapsed_time_tick = sf::Time::Zero;
                        Audio::GetSound(Audio::MOVE).play();
                    }
                    break;
                }
                case sf::Keyboard::Down:
                {
                    if (m_player_2.m_field->PermissibilityMovement(
                            m_player_2.m_tetromino->GetCurrentFigure(), 0, DOWN))
                    {
                        m_player_2.m_tetromino->Move(0, DOWN);
                        m_player_2.m_score->IncreaseScores(7);
                        m_player_2.elapsed_time_tick = sf::Time::Zero;
                    }
                    break;
                }
                case sf::Keyboard::Left:
                {
                    if (m_player_2.m_field->PermissibilityMovement(
                            m_player_2.m_tetromino->GetCurrentFigure(), LEFT, 0))
                    {
                        m_player_2.m_tetromino->Move(LEFT, 0);
                        m_player_2.elapsed_time_tick = sf::Time::Zero;
                    }
                    break;
                }
                case sf::Keyboard::Right:
                {
                    if (m_player_2.m_field->PermissibilityMovement(
                            m_player_2.m_tetromino->GetCurrentFigure(), RIGTH, 0))
                    {
                        m_player_2.m_tetromino->Move(RIGTH, 0);
                        m_player_2.elapsed_time_tick = sf::Time::Zero;
                    }
                    break;
                }
                case sf::Keyboard::RControl:
                {
                    while (m_player_2.m_field->PermissibilityMovement(
                        m_player_2.m_tetromino->GetCurrentFigure(), 0, DOWN))
                    {
                        m_player_2.m_tetromino->Move(0, DOWN);
                        m_player_2.m_score->IncreaseScores(7);
                        m_player_2.elapsed_time_tick = sf::Time::Zero;
                        Audio::GetSound(Audio::FALL).play();
                    }
                    break;
                }
                }
            }
        }
    }
}

void PvP::Update(sf::Time delta_time)
{
    if (!m_pause)
    {
        Audio::GetSound(Audio::FALL).setVolume(Audio::GetVolumeFX());
        Audio::GetSound(Audio::MOVE).setVolume(Audio::GetVolumeFX());
        Audio::GetSound(Audio::CLEAN_LINE).setVolume(Audio::GetVolumeFX());

        m_music->setVolume(Audio::GetVolumeMusic());
        if (!m_player_1.game_over)
        {
            m_player_1.elapsed_time_fall += delta_time;
            m_player_1.elapsed_time_tick += delta_time;

            if (m_player_1.elapsed_time_fall >= m_player_1.time_fall &&
                m_player_1.elapsed_time_tick < m_player_1.time_tick)
            {
                if (m_player_1.m_field->PermissibilityMovement(
                        m_player_1.m_tetromino->GetCurrentFigure(), 0, DOWN))
                {
                    m_player_1.m_tetromino->Move(0, DOWN);
                    m_player_1.elapsed_time_fall = sf::Time::Zero;
                    m_player_1.elapsed_time_tick = sf::Time::Zero;
                }
            }
            else if (m_player_1.elapsed_time_fall >= m_player_1.time_fall &&
                     m_player_1.elapsed_time_tick >= m_player_1.time_tick)
            {
                if (!m_player_1.m_field->PermissibilityMovement(
                        m_player_1.m_tetromino->GetCurrentFigure(), 0, DOWN))
                {
                    m_player_1.m_field->PlaceFigureOnField(
                        m_player_1.m_tetromino->GetCurrentFigure(),
                        m_player_1.m_tetromino->GetColor());
                    m_player_1.m_tetromino->CreateNextFigure();
                    m_player_1.m_tetromino->Create();
                    if (m_player_1.m_field->FigureOnCells(m_player_1.m_tetromino->GetCurrentFigure()))
                    {
                        Audio::GetSound(Audio::GAME_OVER).play();
                        m_player_1.game_over = true;
                        m_player_1.m_score->SaveScores();
                        m_player_1.m_score->UpdateRankingTable();
                    }
                    if (m_player_1.m_field->ClearLines(*m_player_1.m_score))
                    {
                        Audio::GetSound(Audio::CLEAN_LINE).play();
                    }
                    if (m_player_1.m_score->LevelChanged())
                    {
                        m_player_1.time_fall -= sf::seconds(0.015f);
                        m_player_1.time_tick -= sf::seconds(0.025f);

                        auto level_p1 = m_player_1.m_score->GetLevel();
                        auto level_p2 = m_player_2.m_score->GetLevel();

                        if ((level_p1 == 11 && level_p2 < 11) || (level_p1 < 11 && level_p2 == 11))
                        {
                            std::cout << "Change music" << std::endl;

                            m_music->stop();
                            m_music = std::move(Audio::GetMusicPtr(Audio::C_STAGE_MUSIC));
                            m_music->play();
                        }
                        else if ((level_p1 == 6 && level_p2 < 6) || (level_p1 < 6 && level_p2 == 6))
                        {
                            std::cout << "Change music" << std::endl;
                            m_music->stop();
                            m_music = std::move(Audio::GetMusicPtr(Audio::B_STAGE_MUSIC));
                            m_music->play();
                        }

                        auto max_lvl = std::max(level_p1, level_p2);
                        m_music->setPitch(static_cast<float>(max_lvl) / 40.f + 1.f);

                        std::cout << "Pitch\t" << m_music->getPitch() << std::endl;
                        std::cout << "Time fall\t" << m_player_1.time_fall.asSeconds() << std::endl;
                        std::cout << "Time tick\t" << m_player_1.time_tick.asSeconds() << std::endl;
                    }
                }
                m_player_1.elapsed_time_fall = sf::Time::Zero;
                m_player_1.elapsed_time_tick = sf::Time::Zero;
            }

            m_player_1.m_tetromino->ShadowDisplay(*m_player_1.m_field);
        }

        // Second
        if (!m_player_2.game_over)
        {
            m_player_2.elapsed_time_fall += delta_time;
            m_player_2.elapsed_time_tick += delta_time;

            if (m_player_2.elapsed_time_fall >= m_player_2.time_fall &&
                m_player_2.elapsed_time_tick < m_player_2.time_tick)
            {
                if (m_player_2.m_field->PermissibilityMovement(m_player_2.m_tetromino->GetCurrentFigure(), 0, DOWN))
                {
                    m_player_2.m_tetromino->Move(0, DOWN);
                    m_player_2.elapsed_time_fall = sf::Time::Zero;
                    m_player_2.elapsed_time_tick = sf::Time::Zero;
                }
            }
            else if (m_player_2.elapsed_time_fall >= m_player_2.time_fall &&
                     m_player_2.elapsed_time_tick >= m_player_2.time_tick)
            {
                if (!m_player_2.m_field->PermissibilityMovement(m_player_2.m_tetromino->GetCurrentFigure(), 0, DOWN))
                {
                    m_player_2.m_field->PlaceFigureOnField(
                        m_player_2.m_tetromino->GetCurrentFigure(),
                        m_player_2.m_tetromino->GetColor());
                    m_player_2.m_tetromino->CreateNextFigure();
                    m_player_2.m_tetromino->Create();
                    if (m_player_2.m_field->FigureOnCells(m_player_2.m_tetromino->GetCurrentFigure()))
                    {
                        Audio::GetSound(Audio::GAME_OVER).play();
                        m_player_2.game_over = true;
                        m_player_2.m_score->SaveScores();
                        m_player_2.m_score->UpdateRankingTable();
                    }
                    if (m_player_2.m_field->ClearLines(*m_player_2.m_score))
                    {
                        Audio::GetSound(Audio::CLEAN_LINE).play();
                    }
                    if (m_player_2.m_score->LevelChanged())
                    {
                        m_player_2.time_fall -= sf::seconds(0.015f);
                        m_player_2.time_tick -= sf::seconds(0.025f);

                        auto level_p1 = m_player_1.m_score->GetLevel();
                        auto level_p2 = m_player_2.m_score->GetLevel();

                        if ((level_p1 == 11 && level_p2 < 11) || (level_p1 < 11 && level_p2 == 11))
                        {
                            std::cout << "Change music" << std::endl;

                            m_music->stop();
                            m_music = std::move(Audio::GetMusicPtr(Audio::C_STAGE_MUSIC));
                            m_music->play();
                        }
                        else if ((level_p1 == 6 && level_p2 < 6) || (level_p1 < 6 && level_p2 == 6))
                        {
                            std::cout << "Change music" << std::endl;
                            m_music->stop();
                            m_music = std::move(Audio::GetMusicPtr(Audio::B_STAGE_MUSIC));
                            m_music->play();
                        }

                        auto max_lvl = std::max(level_p1, level_p2);
                        m_music->setPitch(static_cast<float>(max_lvl) / 40.f + 1.f);

                        std::cout << "Pitch\t" << m_music->getPitch() << std::endl;
                        std::cout << "Time fall\t" << m_player_2.time_fall.asSeconds() << std::endl;
                        std::cout << "Time tick\t" << m_player_2.time_tick.asSeconds() << std::endl;
                    }
                }
                m_player_2.elapsed_time_fall = sf::Time::Zero;
                m_player_2.elapsed_time_tick = sf::Time::Zero;
            }

            m_player_2.m_tetromino->ShadowDisplay(*m_player_2.m_field);
        }

        if (m_player_1.game_over && m_player_2.game_over)
        {
            m_context->m_states->PushState(std::make_unique<GameOver>(m_context), true);
        }
    }
}

void PvP::Draw()
{
    m_context->m_window->clear();

    m_player_1.m_field->Draw(*m_context->m_window.get());
    m_player_1.m_score->Draw(*m_context->m_window.get());
    if (!m_player_1.game_over)
    {
        m_player_1.m_tetromino->Draw(*m_context->m_window.get());
    }

    m_player_2.m_field->Draw(*m_context->m_window.get());
    m_player_2.m_score->Draw(*m_context->m_window.get());
    if (!m_player_2.game_over)
    {
        m_player_2.m_tetromino->Draw(*m_context->m_window.get());
    }

    m_context->m_window->display();
}

void PvP::Pause()
{
    m_pause = true;
    m_music->pause();
}

void PvP::Launch()
{
    m_pause = false;
    m_music->play();
}