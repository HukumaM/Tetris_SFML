#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "PauseProcess.hpp"
#include "PlayProcess.hpp"

PauseProcess::PauseProcess(std::shared_ptr<Context> &context)
    : m_context(context),
      m_continue(true, false),
      m_restart(false, false),
      m_option(false, false),
      m_exit(false, false)
{
}

PauseProcess::~PauseProcess()
{
}

void PauseProcess::Init()
{
    auto x_window_size = m_context->m_window->getSize().x;
    auto y_window_size = m_context->m_window->getSize().y;

    // PauseProcess text
    m_pause.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_pause, "PAUSE", 100, Color_Combination::title);
    EditTextPosition(m_pause, x_window_size / 2, y_window_size / 8);

    //  Text of the continue button
    m_continue.text.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_continue.text, "CONTINUE", 50, Color_Combination::button);
    EditTextPosition(m_continue.text, x_window_size / 4, y_window_size / 2);

    //  Text of the restart button
    m_restart.text.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_restart.text, "RESTART", 50, Color_Combination::button);
    EditTextPosition(m_restart.text, x_window_size / 4, 3 * y_window_size / 5);

    // Text of the option button
    m_option.text.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_option.text, "OPTION", 50, Color_Combination::button);
    EditTextPosition(m_option.text, x_window_size / 4, 7 * y_window_size / 10);

    // Text of the exit button
    m_exit.text.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_exit.text, "EXIT", 50, Color_Combination::button);
    EditTextPosition(m_exit.text, x_window_size / 4, 4 * y_window_size / 5);

    // Audio
    if (m_sound_buffer.loadFromFile("assets/audio/selection.wav"))
    {
        m_sound_selection.setBuffer(m_sound_buffer);
        m_sound_selection.setVolume(50.f);
    }
    if (m_music.openFromFile("assets/audio/title.ogg"))
    {
        m_music.setLoop(true);
        m_music.setVolume(50.f);
        m_music.play();
    }
}

void PauseProcess::ProcessInput()
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
                m_music.stop();
                m_context->m_states->PopState();
                break;
            }
            case sf::Keyboard::Up:
            {
                m_sound_selection.play();

                if (m_exit.selected)
                {
                    m_exit.selected = false;
                    m_option.selected = true;
                }
                else if (m_option.selected)
                {
                    m_option.selected = false;
                    m_restart.selected = true;
                }
                else if (m_restart.selected)
                {
                    m_restart.selected = false;
                    m_continue.selected = true;
                }
                else
                {
                    m_continue.selected = true;
                }
                break;
            }
            case sf::Keyboard::Down:
            {
                m_sound_selection.play();

                if (m_continue.selected)
                {
                    m_continue.selected = false;
                    m_restart.selected = true;
                }
                else if (m_restart.selected)
                {
                    m_restart.selected = false;
                    m_option.selected = true;
                }
                else if (m_option.selected)
                {
                    m_option.selected = false;
                    m_exit.selected = true;
                }
                else
                {
                    m_exit.selected = true;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                m_sound_selection.play();
                m_continue.pressed = m_restart.pressed = false;
                m_option.pressed = m_exit.pressed = false;

                if (m_continue.selected)
                {
                    m_continue.pressed = true;
                }
                else if (m_restart.selected)
                {
                    m_restart.pressed = true;
                }
                else if (m_option.selected)
                {
                    m_option.pressed = true;
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

void PauseProcess::UpdateButton(Button &button, float x_pos, float y_pos)
{
    if (button.selected)
    {
        EditTextContent(button.text, button.text.getString(),
                        60, Color_Combination::button_pressed);
        EditTextPosition(button.text, x_pos, y_pos);
    }
    else
    {
        EditTextContent(button.text, button.text.getString(),
                        50, Color_Combination::button);
        EditTextPosition(button.text, x_pos, y_pos);
    }
}

void PauseProcess::Update(sf::Time delta_time)
{
    auto x_window_size = m_context->m_window->getSize().x;
    auto y_window_size = m_context->m_window->getSize().y;

    UpdateButton(m_continue, x_window_size / 4, y_window_size / 2);
    UpdateButton(m_restart, x_window_size / 4, 3 * y_window_size / 5);
    UpdateButton(m_option, x_window_size / 4, 7 * y_window_size / 10);
    UpdateButton(m_exit, x_window_size / 4, 4 * y_window_size / 5);

    if (m_continue.pressed)
    {
        m_music.stop();
        m_context->m_states->PopState();
    }
    else if (m_restart.pressed)
    {
        m_music.stop();
        m_context->m_states->PushState(
            std::make_unique<PlayProcess>(m_context), true);
    }
    else if (m_option.pressed)
    {
    }
    else if (m_exit.pressed)
    {
        m_music.stop();
        m_context->m_window->close();
    }
}

void PauseProcess::Draw()
{
    m_context->m_window->clear(Color_Combination::background);
    m_context->m_window->draw(m_pause);
    m_context->m_window->draw(m_continue.text);
    m_context->m_window->draw(m_restart.text);
    m_context->m_window->draw(m_option.text);
    m_context->m_window->draw(m_exit.text);
    m_context->m_window->display();
}