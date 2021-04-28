#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "PauseProcess.hpp"
#include "OptionProcess.hpp"
#include "PlayProcess.hpp"

PauseProcess::PauseProcess(std::shared_ptr<Context> &context)
    : m_context(context),
      m_button({{true, false}, {false, false}, {false, false}, {false, false}})
{
}

PauseProcess::~PauseProcess()
{
}

void PauseProcess::Init()
{
    auto x_size = m_context->m_window->getSize().x;
    auto y_size = m_context->m_window->getSize().y;

    // PauseProcess text
    m_pause.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_pause, "PAUSE", 100, Color_Combination::title);
    EditTextPosition(m_pause, x_size / 2, y_size / 8);

    //  Text of the continue button
    m_button.at(ButtonType::Continue).text.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_button.at(ButtonType::Continue).text, "CONTINUE", 50, Color_Combination::button);
    EditTextPosition(m_button.at(ButtonType::Continue).text, x_size / 2, y_size / 2);

    //  Text of the restart button
    m_button.at(ButtonType::Restart).text.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_button.at(ButtonType::Restart).text, "RESTART", 50, Color_Combination::button);
    EditTextPosition(m_button.at(ButtonType::Restart).text, x_size / 2, 3 * y_size / 5);

    // Text of the option button
    m_button.at(ButtonType::Option).text.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_button.at(ButtonType::Option).text, "OPTION", 50, Color_Combination::button);
    EditTextPosition(m_button.at(ButtonType::Option).text, x_size / 2, 7 * y_size / 10);

    // Text of the exit button
    m_button.at(ButtonType::Exit).text.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_button.at(ButtonType::Exit).text, "EXIT", 50, Color_Combination::button);
    EditTextPosition(m_button.at(ButtonType::Exit).text, x_size / 2, 4 * y_size / 5);

    Audio::GetSound(Audio::Sound::SELECTION).setVolume(Audio::GetVolumeFX());
    Audio::GetMusic(Audio::Music::MAIN_MUSIC).setVolume(Audio::GetVolumeMusic());
    Audio::GetMusic(Audio::Music::MAIN_MUSIC).play();
}

void PauseProcess::ProcessInput()
{
    sf::Event event;

    m_button.at(ButtonType::Continue).pressed = false;
    m_button.at(ButtonType::Restart).pressed = false;
    m_button.at(ButtonType::Option).pressed = false;
    m_button.at(ButtonType::Exit).pressed = false;

    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            Audio::GetMusic(Audio::Music::MAIN_MUSIC).stop();
            m_context->m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
            {
                Audio::GetMusic(Audio::Music::MAIN_MUSIC).stop();
                m_context->m_states->PopState();
                break;
            }
            case sf::Keyboard::Up:
            {
                Audio::GetSound(Audio::Sound::SELECTION).play();

                if (m_button.at(ButtonType::Exit).selected)
                {
                    m_button.at(ButtonType::Exit).selected = false;
                    m_button.at(ButtonType::Option).selected = true;
                }
                else if (m_button.at(ButtonType::Option).selected)
                {
                    m_button.at(ButtonType::Option).selected = false;
                    m_button.at(ButtonType::Restart).selected = true;
                }
                else if (m_button.at(ButtonType::Restart).selected)
                {
                    m_button.at(ButtonType::Restart).selected = false;
                    m_button.at(ButtonType::Continue).selected = true;
                }
                else
                {
                    m_button.at(ButtonType::Continue).selected = true;
                }
                break;
            }
            case sf::Keyboard::Down:
            {
                Audio::GetSound(Audio::Sound::SELECTION).play();
                
                if (m_button.at(ButtonType::Continue).selected)
                {
                    m_button.at(ButtonType::Continue).selected = false;
                    m_button.at(ButtonType::Restart).selected = true;
                }
                else if (m_button.at(ButtonType::Restart).selected)
                {
                    m_button.at(ButtonType::Restart).selected = false;
                    m_button.at(ButtonType::Option).selected = true;
                }
                else if (m_button.at(ButtonType::Option).selected)
                {
                    m_button.at(ButtonType::Option).selected = false;
                    m_button.at(ButtonType::Exit).selected = true;
                }
                else
                {
                    m_button.at(ButtonType::Exit).selected = true;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                Audio::GetSound(Audio::Sound::SELECTION).play();

                if (m_button.at(ButtonType::Continue).selected)
                {
                    m_button.at(ButtonType::Continue).pressed = true;
                }
                else if (m_button.at(ButtonType::Restart).selected)
                {
                    m_button.at(ButtonType::Restart).pressed = true;
                }
                else if (m_button.at(ButtonType::Option).selected)
                {
                    m_button.at(ButtonType::Option).pressed = true;
                }
                else
                {
                    m_button.at(ButtonType::Exit).pressed = true;
                }
                break;
            }
            default:
                break;
            }
        }
    }
}

void PauseProcess::Update(sf::Time delta_time)
{
    auto x_size = m_context->m_window->getSize().x;
    auto y_size = m_context->m_window->getSize().y;

    UpdateButton(m_button.at(ButtonType::Continue), x_size / 2, y_size / 2);
    UpdateButton(m_button.at(ButtonType::Restart), x_size / 2, 3 * y_size / 5);
    UpdateButton(m_button.at(ButtonType::Option), x_size / 2, 7 * y_size / 10);
    UpdateButton(m_button.at(ButtonType::Exit), x_size / 2, 4 * y_size / 5);

    Audio::GetSound(Audio::SELECTION).setVolume(Audio::GetVolumeFX());
    Audio::GetMusic(Audio::MAIN_MUSIC).setVolume(Audio::GetVolumeMusic());

    if (m_button.at(ButtonType::Continue).pressed)
    {
        Audio::GetMusic(Audio::MAIN_MUSIC).stop();
        m_context->m_states->PopState();
    }
    else if (m_button.at(ButtonType::Restart).pressed)
    {
        Audio::GetMusic(Audio::MAIN_MUSIC).stop();
        m_context->m_states->PushState(
            std::make_unique<PlayProcess>(m_context), true);
    }
    else if (m_button.at(ButtonType::Option).pressed)
    {
        m_context->m_states->PushState(
            std::make_unique<OptionProcess>(m_context));
    }
    else if (m_button.at(ButtonType::Exit).pressed)
    {
        Audio::GetMusic(Audio::MAIN_MUSIC).stop();
        m_context->m_window->close();
    }
}

void PauseProcess::Draw()
{
    m_context->m_window->clear(Color_Combination::background);
    m_context->m_window->draw(m_pause);
    m_context->m_window->draw(m_button.at(ButtonType::Continue).text);
    m_context->m_window->draw(m_button.at(ButtonType::Restart).text);
    m_context->m_window->draw(m_button.at(ButtonType::Option).text);
    m_context->m_window->draw(m_button.at(ButtonType::Exit).text);
    m_context->m_window->display();
}