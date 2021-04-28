#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "OptionProcess.hpp"
#include "PauseProcess.hpp"

OptionProcess::OptionProcess(std::shared_ptr<Context> &context)
    : m_context(context),
      m_button({{false, false}, {false, false}, {true, false}})
{
}

OptionProcess::~OptionProcess()
{
}

void OptionProcess::Init()
{
    auto x_window_size = m_context->m_window->getSize().x;
    auto y_window_size = m_context->m_window->getSize().y;

    // Button music
    m_button.at(ButtonType::Music).text.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_button.at(ButtonType::Music).text,
                    "Music Volume\t" +
                        std::to_string(static_cast<int16_t>(Audio::GetVolumeMusic())),
                    50, Color_Combination::button);
    EditTextPosition(m_button.at(ButtonType::Music).text,
                     x_window_size / 2,
                     2 * y_window_size / 5);

    // Button FX
    m_button.at(ButtonType::FX).text.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_button.at(ButtonType::FX).text,
                    "FX Volume\t" +
                        std::to_string(static_cast<int16_t>(Audio::GetVolumeFX())),
                    50, Color_Combination::button);
    EditTextPosition(m_button.at(ButtonType::FX).text,
                     x_window_size / 2,
                     y_window_size / 2);

    // Button back
    m_button.at(ButtonType::Back).text.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    EditTextContent(m_button.at(ButtonType::Back).text,
                    "BACK", 50, Color_Combination::button);
    EditTextPosition(m_button.at(ButtonType::Back).text,
                     x_window_size / 2,
                     7 * y_window_size / 10);
}

void OptionProcess::ProcessInput()
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
                m_context->m_states->PopState();
                break;
            }
            case sf::Keyboard::Up:
            {
                Audio::GetSound(Audio::SELECTION).play();

                if (m_button.at(ButtonType::Back).selected)
                {
                    m_button.at(ButtonType::Back).selected = false;
                    m_button.at(ButtonType::FX).selected = true;
                }
                else if (m_button.at(ButtonType::FX).selected)
                {
                    m_button.at(ButtonType::FX).selected = false;
                    m_button.at(ButtonType::Music).selected = true;
                }
                else
                {
                    m_button.at(ButtonType::Music).selected = true;
                }
                break;
            }
            case sf::Keyboard::Down:
            {
                Audio::GetSound(Audio::SELECTION).play();

                if (m_button.at(ButtonType::Music).selected)
                {
                    m_button.at(ButtonType::Music).selected = false;
                    m_button.at(ButtonType::FX).selected = true;
                }
                else if (m_button.at(ButtonType::FX).selected)
                {
                    m_button.at(ButtonType::FX).selected = false;
                    m_button.at(ButtonType::Back).selected = true;
                }
                else
                {
                    m_button.at(ButtonType::Back).selected = true;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                Audio::GetSound(Audio::SELECTION).play();

                m_button.at(ButtonType::Back).pressed = false;

                if (m_button.at(ButtonType::Back).selected)
                {
                    m_button.at(ButtonType::Back).pressed = true;
                }
                break;
            }
            case sf::Keyboard::Left:
            {
                Audio::GetSound(Audio::SELECTION).play();

                if (m_button.at(ButtonType::Music).selected && Audio::GetVolumeMusic() > Audio::Volume::Min)
                {
                    Audio::IncreaseVolumeMusic(-10.f);
                }
                if (m_button.at(ButtonType::FX).selected && Audio::GetVolumeFX() > Audio::Volume::Min)
                {
                    Audio::IncreaseVolumeFX(-10.f);
                }
                break;
            }
            case sf::Keyboard::Right:
            {
                Audio::GetSound(Audio::SELECTION).play();
                if (m_button.at(ButtonType::Music).selected && Audio::GetVolumeMusic() < Audio::Volume::Max)
                {
                    Audio::IncreaseVolumeMusic(10.f);
                }
                if (m_button.at(ButtonType::FX).selected && Audio::GetVolumeFX() < Audio::Volume::Max)
                {
                    Audio::IncreaseVolumeFX(10.f);
                }
                break;
            }
            default:
                break;
            }
        }
    }
}

void OptionProcess::Update(sf::Time delta_time)
{
    auto x_window_size = m_context->m_window->getSize().x;
    auto y_window_size = m_context->m_window->getSize().y;

    m_button.at(ButtonType::Music).text.setString("Music Volume\t" + std::to_string(static_cast<int16_t>(Audio::GetVolumeMusic())));
    m_button.at(ButtonType::FX).text.setString("FX Volume\t" + std::to_string(static_cast<int16_t>(Audio::GetVolumeFX())));

    UpdateButton(m_button.at(ButtonType::Music), x_window_size / 2, 2 * y_window_size / 5);
    UpdateButton(m_button.at(ButtonType::FX), x_window_size / 2, y_window_size / 2);
    UpdateButton(m_button.at(ButtonType::Back), x_window_size / 2, 7 * y_window_size / 10);

    Audio::GetSound(Audio::SELECTION).setVolume(Audio::GetVolumeFX());
    Audio::GetMusic(Audio::MAIN_MUSIC).setVolume(Audio::GetVolumeMusic());

    if (m_button.at(ButtonType::Back).pressed)
    {
        m_context->m_states->PopState();
    }
}

void OptionProcess::Draw()
{
    m_context->m_window->clear(Color_Combination::background);
    m_context->m_window->draw(m_button.at(ButtonType::Back).text);
    m_context->m_window->draw(m_button.at(ButtonType::FX).text);
    m_context->m_window->draw(m_button.at(ButtonType::Music).text);
    m_context->m_window->display();
}