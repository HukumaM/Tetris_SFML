#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "GameOver.hpp"
#include "Menu.hpp"

GameOver::GameOver(std::shared_ptr<Context> &context)
    : m_context(context),
      m_button{{true, false}, {false, false}}
{
}

GameOver::~GameOver()
{
}

void GameOver::Init()
{
    auto x_size = m_context->m_window->getSize().x;
    auto y_size = m_context->m_window->getSize().y;

    m_context->m_assets->AddFont(MAIN_FONT, "assets/fonts/Oswald-Regular.ttf");

    // Title text
    m_gm_title.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_gm_title, "GAME OVER", 54, Color_Combination::title);
    EditTextPosition(m_gm_title, x_size / 2, y_size / 8);

    //  Text of the play button
    m_button.at(ButtonType::MENU).text.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_button.at(ButtonType::MENU).text, "Menu", 50, Color_Combination::button);
    EditTextPosition(m_button.at(ButtonType::MENU).text, x_size / 2, y_size / 2);

    // Text of the menu button
    m_button.at(ButtonType::EXIT).text.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_button.at(ButtonType::EXIT).text, "Exit", 50, Color_Combination::button);
    EditTextPosition(m_button.at(ButtonType::EXIT).text, x_size / 2, 3 * y_size / 5);

    // Audio
    Audio::GetSound(Audio::GAME_OVER).play();
}

void GameOver::ProcessInput()
{
    sf::Event event;

    m_button.at(ButtonType::MENU).pressed = false;
    m_button.at(ButtonType::EXIT).pressed = false;

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
                Audio::GetSound(Audio::SELECTION).play();
                if (m_button.at(ButtonType::EXIT).selected)
                {
                    m_button.at(ButtonType::MENU).selected = true;
                    m_button.at(ButtonType::EXIT).selected = false;
                }
                break;
            }
            case sf::Keyboard::Down:
            {
                Audio::GetSound(Audio::SELECTION).play();
                if (m_button.at(ButtonType::MENU).selected)
                {
                    m_button.at(ButtonType::MENU).selected = false;
                    m_button.at(ButtonType::EXIT).selected = true;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                Audio::GetSound(Audio::SELECTION).play();
                
                if (m_button.at(ButtonType::MENU).selected)
                {
                    m_button.at(ButtonType::MENU).pressed = true;
                }
                else
                {
                    m_button.at(ButtonType::EXIT).pressed = true;
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
    auto x_size = m_context->m_window->getSize().x;
    auto y_size = m_context->m_window->getSize().y;

    Audio::GetSound(Audio::SELECTION).setVolume(Audio::GetVolumeFX());
    
    
    UpdateButton(m_button.at(ButtonType::MENU), x_size / 2, y_size / 2);
    UpdateButton(m_button.at(ButtonType::EXIT), x_size / 2, 3 * y_size / 5);

    if (m_button.at(ButtonType::MENU).pressed)
    {
        m_context->m_states->PushState(
            std::make_unique<Menu>(m_context), true);
    }
    else if (m_button.at(ButtonType::EXIT).pressed)
    {
        m_context->m_window->close();
    }
}

void GameOver::Draw()
{
    m_context->m_window->clear(Color_Combination::background);
    m_context->m_window->draw(m_gm_title);
    m_context->m_window->draw(m_button.at(ButtonType::MENU).text);
    m_context->m_window->draw(m_button.at(ButtonType::EXIT).text);
    m_context->m_window->display();
}