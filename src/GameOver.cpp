#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "GameOver.hpp"
#include "PlayProcess.hpp"

GameOver::GameOver(std::shared_ptr<Context> &context)
    : m_context(context),
      m_restart(true, false),
      m_option(false, false),
      m_exit(false, false)
{
}

GameOver::~GameOver()
{
}

void GameOver::Init()
{
    auto x_window_size = m_context->m_window->getSize().x;
    auto y_window_size = m_context->m_window->getSize().y;

    m_context->m_assets->AddFont(MAIN_FONT, "assets/fonts/Oswald-Regular.ttf");

    // Title text
    m_gm_title.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_gm_title, "GAME OVER", 54, Color_Combination::title);
    EditTextPosition(m_gm_title, x_window_size / 2, y_window_size / 8);

    //  Text of the play button
    m_restart.text.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_restart.text, "RESTART", 50, Color_Combination::button);
    EditTextPosition(m_restart.text, x_window_size / 2, y_window_size / 2);

    // Text of the menu button
    m_exit.text.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_exit.text, "EXIT", 50, Color_Combination::button);
    EditTextPosition(m_exit.text, x_window_size / 2, 3 * y_window_size / 5);

    // Text of the exit button
    m_exit.text.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_exit.text, "EXIT", 50, Color_Combination::button);
    EditTextPosition(m_exit.text, x_window_size / 2, 3 * y_window_size / 5);

    // Audio
    if (m_sound_buffer.loadFromFile("assets/audio/selection.wav"))
    {
        m_sound_selection.setBuffer(m_sound_buffer);
        m_sound_selection.setVolume(50.f);
    }
    if (m_music.openFromFile("assets/audio/game_over.ogg"))
    {
        m_music.setVolume(100.f);
        m_music.play();
    }
}

void GameOver::ProcessInput()
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
                m_context->m_window->close();
                break;
            }
            case sf::Keyboard::Up:
            {
                m_sound_selection.play();
                if (!m_restart.selected)
                {
                    m_restart.selected = true;
                    m_exit.selected = false;
                }
                break;
            }
            case sf::Keyboard::Down:
            {
                m_sound_selection.play();
                if (!m_exit.selected)
                {
                    m_restart.selected = false;
                    m_exit.selected = true;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                m_sound_selection.play();
                m_restart.pressed = false;
                m_exit.pressed = false;

                if (m_restart.selected)
                {
                    m_restart.pressed = true;
                }
                else
                {
                    m_exit.pressed = true;
                }
                break;
            }
            default:
                break;
            }
        }
    }
}

void GameOver::Update(sf::Time delta_time)
{
    auto x_window_size = m_context->m_window->getSize().x;
    auto y_window_size = m_context->m_window->getSize().y;

    if (m_restart.selected)
    {
        EditTextContent(m_restart.text, m_restart.text.getString(), 60,
                        Color_Combination::button_pressed);
        EditTextPosition(m_restart.text, x_window_size / 2, y_window_size / 2);
    }
    else
    {
        EditTextContent(m_restart.text, m_restart.text.getString(),
                        50, Color_Combination::button);
        EditTextPosition(m_restart.text,
                         x_window_size / 2, y_window_size / 2);
    }

    if (m_exit.selected)
    {
        EditTextContent(m_exit.text, m_exit.text.getString(), 60,
                        Color_Combination::button_pressed);
        EditTextPosition(m_exit.text,
                         x_window_size / 2, 3 * y_window_size / 5);
    }
    else
    {
        EditTextContent(m_exit.text, m_exit.text.getString(), 50,
                        Color_Combination::button);
        EditTextPosition(m_exit.text,
                         x_window_size / 2, 3 * y_window_size / 5);
    }

    if (m_restart.pressed)
    {
        m_context->m_states->PushState(
            std::make_unique<PlayProcess>(m_context), true);
    }
    else if (m_exit.pressed)
    {
        m_context->m_window->close();
    }
}

void GameOver::Draw()
{
    m_context->m_window->clear(Color_Combination::background);
    m_context->m_window->draw(m_gm_title);
    m_context->m_window->draw(m_restart.text);
    m_context->m_window->draw(m_exit.text);
    m_context->m_window->display();
}