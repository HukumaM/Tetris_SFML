#include "Menu.hpp"
#include "PlayProcess.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

Menu::Menu(std::shared_ptr<Context> &context)
    : m_context(context), m_play(true, false), m_exit(false, false)
{
}

Menu::~Menu()
{
}

void Menu::EditTextContent(sf::Text &text, const sf::String &string, unsigned int size,
                           const sf::Color &color)
{
    text.setString(string);
    text.setCharacterSize(size);
    text.setColor(color);
}

void Menu::EditTextPosition(sf::Text &text, float x, float y)
{
    text.setOrigin(text.getLocalBounds().width / 2,
                   text.getLocalBounds().height / 2);
    text.setPosition(x, y);
}

void Menu::Init()
{
    auto x_window_size = this->m_context->m_window->getSize().x;
    auto y_window_size = this->m_context->m_window->getSize().y;

    this->m_context->m_assets->AddFont(MAIN_FONT, "assets/fonts/Oswald-Regular.ttf");

    // Title text
    this->m_title.setFont(this->m_context->m_assets->GetFont(MAIN_FONT));
    this->EditTextContent(this->m_title, "TETRIS", 100, Color_Combination::kakao);
    this->EditTextPosition(this->m_title, x_window_size / 2, y_window_size / 8);

    //  Text of the play button
    this->m_play.text.setFont(this->m_context->m_assets->GetFont(MAIN_FONT));
    this->EditTextContent(this->m_play.text, "PLAY", 50, Color_Combination::chocolate);
    this->EditTextPosition(this->m_play.text, x_window_size / 2, y_window_size / 2);

    // Text of the exit button
    this->m_exit.text.setFont(this->m_context->m_assets->GetFont(MAIN_FONT));
    this->EditTextContent(this->m_exit.text, "EXIT", 50, Color_Combination::chocolate);
    this->EditTextPosition(this->m_exit.text, x_window_size / 2, 3 * y_window_size / 5);
}

void Menu::ProcessInput()
{
    sf::Event event;
    while (this->m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            this->m_context->m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
            {
                this->m_context->m_window->close();
                break;
            }
            case sf::Keyboard::Up:
            {
                if (!this->m_play.selected)
                {
                    this->m_play.selected = true;
                    this->m_exit.selected = false;
                }
                break;
            }
            case sf::Keyboard::Down:
            {
                if (!this->m_exit.selected)
                {
                    this->m_play.selected = false;
                    this->m_exit.selected = true;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                this->m_play.pressed = false;
                this->m_exit.pressed = false;

                if (this->m_play.selected)
                {
                    this->m_play.pressed = true;
                }
                else
                {
                    this->m_exit.pressed = true;
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
    auto x_window_size = this->m_context->m_window->getSize().x;
    auto y_window_size = this->m_context->m_window->getSize().y;

    if (this->m_play.selected)
    {
        this->EditTextContent(this->m_play.text, this->m_play.text.getString(), 60,
                              Color_Combination::glaze);
        this->EditTextPosition(this->m_play.text, x_window_size / 2, y_window_size / 2);
    }
    else
    {
        this->EditTextContent(this->m_play.text, this->m_play.text.getString(),
                              50, Color_Combination::chocolate);
        this->EditTextPosition(this->m_play.text,
                               x_window_size / 2, y_window_size / 2);
    }

    if (this->m_exit.selected)
    {
        this->EditTextContent(this->m_exit.text, this->m_exit.text.getString(), 60,
                              Color_Combination::glaze);
        this->EditTextPosition(this->m_exit.text,
                               x_window_size / 2, 3 * y_window_size / 5);
    }
    else
    {
        this->EditTextContent(this->m_exit.text, this->m_exit.text.getString(), 50,
                              Color_Combination::chocolate);
        this->EditTextPosition(this->m_exit.text,
                               x_window_size / 2, 3 * y_window_size / 5);
    }

    if (this->m_play.pressed)
    {
        this->m_context->m_states->PushState(
            std::make_unique<PlayProcess>(this->m_context), true);
    }
    else if (this->m_exit.pressed)
    {
        this->m_context->m_window->close();
    }
}

void Menu::Draw()
{
    this->m_context->m_window->clear(Color_Combination::toffee);
    this->m_context->m_window->draw(this->m_title);
    this->m_context->m_window->draw(this->m_play.text);
    this->m_context->m_window->draw(this->m_exit.text);
    this->m_context->m_window->display();
}