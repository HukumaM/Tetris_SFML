
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Menu.hpp"
#include "PlayProcess.hpp"

Menu::Menu(std::shared_ptr<Context> &context)
    : m_context(context),
      m_play(true, false),
      m_exit(false, false)
{
}

Menu::~Menu()
{
}

void Menu::Init()
{
    auto x_window_size = m_context->m_window->getSize().x;
    auto y_window_size = m_context->m_window->getSize().y;

    m_context->m_assets->AddFont(MAIN_FONT, "assets/fonts/Oswald-Regular.ttf");

    // Title text
    m_title.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_title, "TETRIS", 100, Color_Combination::kakao);
    EditTextPosition(m_title, x_window_size / 2, y_window_size / 8);

    //  Text of the play button
    m_play.text.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_play.text, "PLAY", 50, Color_Combination::chocolate);
    EditTextPosition(m_play.text, x_window_size / 2, y_window_size / 2);

    // Text of the exit button
    m_exit.text.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_exit.text, "EXIT", 50, Color_Combination::chocolate);
    EditTextPosition(m_exit.text, x_window_size / 2, 3 * y_window_size / 5);
}

void Menu::ProcessInput()
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
                if (!m_play.selected)
                {
                    m_play.selected = true;
                    m_exit.selected = false;
                }
                break;
            }
            case sf::Keyboard::Down:
            {
                if (!m_exit.selected)
                {
                    m_play.selected = false;
                    m_exit.selected = true;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                m_play.pressed = false;
                m_exit.pressed = false;

                if (m_play.selected)
                {
                    m_play.pressed = true;
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

void Menu::Update(sf::Time delta_time)
{
    auto x_window_size = m_context->m_window->getSize().x;
    auto y_window_size = m_context->m_window->getSize().y;

    if (m_play.selected)
    {
        EditTextContent(m_play.text, m_play.text.getString(), 60,
                        Color_Combination::glaze);
        EditTextPosition(m_play.text, x_window_size / 2, y_window_size / 2);
    }
    else
    {
        EditTextContent(m_play.text, m_play.text.getString(),
                        50, Color_Combination::chocolate);
        EditTextPosition(m_play.text,
                         x_window_size / 2, y_window_size / 2);
    }

    if (m_exit.selected)
    {
        EditTextContent(m_exit.text, m_exit.text.getString(), 60,
                        Color_Combination::glaze);
        EditTextPosition(m_exit.text,
                         x_window_size / 2, 3 * y_window_size / 5);
    }
    else
    {
        EditTextContent(m_exit.text, m_exit.text.getString(), 50,
                        Color_Combination::chocolate);
        EditTextPosition(m_exit.text,
                         x_window_size / 2, 3 * y_window_size / 5);
    }

    if (m_play.pressed)
    {
        m_context->m_states->PushState(
            std::make_unique<PlayProcess>(m_context), true);
    }
    else if (m_exit.pressed)
    {
        m_context->m_window->close();
    }
}

void Menu::Draw()
{
    m_context->m_window->clear(Color_Combination::toffee);
    m_context->m_window->draw(m_title);
    m_context->m_window->draw(m_play.text);
    m_context->m_window->draw(m_exit.text);
    m_context->m_window->display();
}