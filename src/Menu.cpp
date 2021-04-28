#include <iostream>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Menu.hpp"
#include "OptionProcess.hpp"
#include "PlayProcess.hpp"
#include "PvP.hpp"

Menu::Menu(std::shared_ptr<Context> &context)
    : m_context(context),
      m_button({{true, false}, {false, false}, {false, false}, {false, false}})
{
}

Menu::~Menu()
{
}

void Menu::Init()
{
    auto x_size = m_context->m_window->getSize().x;
    auto y_size = m_context->m_window->getSize().y;

    m_context->m_assets->AddFont(MAIN_FONT, "assets/fonts/Oswald-Regular.ttf");

    // Title text
    m_title.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_title, "TETRIS", 100, Color_Combination::title);
    EditTextPosition(m_title, x_size / 2, y_size / 8);

    // Audio

    Audio::LoadMusic(Audio::MAIN_MUSIC, "assets/audio/title.ogg", true, true);
    Audio::GetMusic(Audio::MAIN_MUSIC).setVolume(Audio::GetVolumeMusic());

    Audio::LoadSound(Audio::SELECTION, "assets/audio/selection.wav");
    Audio::GetSound(Audio::SELECTION).setVolume(Audio::GetVolumeFX());

    Audio::LoadSound(Audio::GAME_OVER, "assets/audio/game_over.ogg");
    Audio::GetSound(Audio::GAME_OVER).setVolume(Audio::GetVolumeFX());

    m_button.at(ButtonType::Play).text.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_button.at(ButtonType::Play).text, "Play", 50, Color_Combination::button);
    EditTextPosition(m_button.at(ButtonType::Play).text, x_size / 2, y_size / 2);

    m_button.at(ButtonType::PlayerVsPlayer).text.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_button.at(ButtonType::PlayerVsPlayer).text, "PvP", 50, Color_Combination::button);
    EditTextPosition(m_button.at(ButtonType::PlayerVsPlayer).text, x_size / 2, 3 * y_size / 5);

    m_button.at(ButtonType::Option).text.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_button.at(ButtonType::Option).text, "Option", 50, Color_Combination::button);
    EditTextPosition(m_button.at(ButtonType::Option).text, x_size / 2, 7 * y_size / 10);

    m_button.at(ButtonType::Exit).text.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_button.at(ButtonType::Exit).text, "Exit", 50, Color_Combination::button);
    EditTextPosition(m_button.at(ButtonType::Exit).text, x_size / 2, 4 * y_size / 5);
}

void Menu::ProcessInput()
{
    sf::Event event;

    m_button.at(ButtonType::Play).pressed = false;
    m_button.at(ButtonType::PlayerVsPlayer).pressed = false;
    m_button.at(ButtonType::Option).pressed = false;
    m_button.at(ButtonType::Exit).pressed = false;

    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            Audio::GetMusic(Audio::MAIN_MUSIC).stop();
            m_context->m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
            {
                Audio::GetMusic(Audio::MAIN_MUSIC).stop();
                m_context->m_window->close();
                break;
            }
            case sf::Keyboard::Up:
            {
                Audio::GetSound(Audio::SELECTION).play();

                if (m_button.at(ButtonType::Exit).selected)
                {
                    m_button.at(ButtonType::Exit).selected = false;
                    m_button.at(ButtonType::Option).selected = true;
                }
                else if (m_button.at(ButtonType::Option).selected)
                {
                    m_button.at(ButtonType::Option).selected = false;
                    m_button.at(ButtonType::PlayerVsPlayer).selected = true;
                }
                else if (m_button.at(ButtonType::PlayerVsPlayer).selected)
                {
                    m_button.at(ButtonType::PlayerVsPlayer).selected = false;
                    m_button.at(ButtonType::Play).selected = true;
                }
                else
                {
                    m_button.at(ButtonType::Play).selected = true;
                }
                break;
            }
            case sf::Keyboard::Down:
            {
                Audio::GetSound(Audio::SELECTION).play();

                if (m_button.at(ButtonType::Play).selected)
                {
                    m_button.at(ButtonType::Play).selected = false;
                    m_button.at(ButtonType::PlayerVsPlayer).selected = true;
                }
                else if (m_button.at(ButtonType::PlayerVsPlayer).selected)
                {
                    m_button.at(ButtonType::PlayerVsPlayer).selected = false;
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
                Audio::GetSound(Audio::SELECTION).play();

                if (m_button.at(ButtonType::Play).selected)
                {
                    m_button.at(ButtonType::Play).pressed = true;
                }
                else if (m_button.at(ButtonType::PlayerVsPlayer).selected)
                {
                    m_button.at(ButtonType::PlayerVsPlayer).pressed = true;
                }
                else if (m_button.at(ButtonType::Option).selected)
                {
                    m_button.at(ButtonType::Option).pressed = true;
                }
                else if (m_button.at(ButtonType::Exit).selected)
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

void Menu::Update(sf::Time delta_time)
{
    auto x_size = m_context->m_window->getSize().x;
    auto y_size = m_context->m_window->getSize().y;

    Audio::GetMusic(Audio::MAIN_MUSIC).setVolume(Audio::GetVolumeMusic());
    Audio::GetSound(Audio::SELECTION).setVolume(Audio::GetVolumeFX());

    UpdateButton(m_button.at(ButtonType::Play), x_size / 2, y_size / 2);
    UpdateButton(m_button.at(ButtonType::PlayerVsPlayer), x_size / 2, 3 * y_size / 5);
    UpdateButton(m_button.at(ButtonType::Option), x_size / 2, 7 * y_size / 10);
    UpdateButton(m_button.at(ButtonType::Exit), x_size / 2, 4 * y_size / 5);

    if (m_button.at(ButtonType::Play).pressed)
    {
        std::cout << "launch playing" << std::endl;
        Audio::GetMusic(Audio::MAIN_MUSIC).stop();
        m_context->m_states->PushState(
            std::make_unique<PlayProcess>(m_context), true);
    }
    else if (m_button.at(ButtonType::PlayerVsPlayer).pressed)
    {
        std::cout << "launch pvp" << std::endl;
        Audio::GetMusic(Audio::MAIN_MUSIC).stop();
        m_context->m_states->PushState(
            std::make_unique<PvP>(m_context), true);
    }
    else if (m_button.at(ButtonType::Option).pressed)
    {
        std::cout << "launch option" << std::endl;
        m_context->m_states->PushState(
            std::make_unique<OptionProcess>(m_context));
    }
    else if (m_button.at(ButtonType::Exit).pressed)
    {
        std::cout << "launch exit" << std::endl;
        Audio::GetMusic(Audio::MAIN_MUSIC).stop();
        m_context->m_window->close();
    }
}

void Menu::Draw()
{
    m_context->m_window->clear(Color_Combination::background);
    m_context->m_window->draw(m_title);
    m_context->m_window->draw(m_button.at(ButtonType::Play).text);
    m_context->m_window->draw(m_button.at(ButtonType::PlayerVsPlayer).text);
    m_context->m_window->draw(m_button.at(ButtonType::Option).text);
    m_context->m_window->draw(m_button.at(ButtonType::Exit).text);

    m_context->m_window->display();
}