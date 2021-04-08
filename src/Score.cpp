#include <fstream>

#include "Score.hpp"
#include "Support.hpp"

Score::Score()
    : m_score(0),
      m_score_lines(0),
      m_level(1, 1)
{
}

Score::~Score()
{
}

void Score::Init(const sf::Texture &texture, const sf::Font &font)
{
    m_sprite.setTexture(texture);

    m_text_score.setFont(font);

    EditTextContent(m_text_score, "0", 30, Color_Combination::herbs);
    EditTextPosition(m_text_score, 450, 68);
}

void Score::UpdateScores(const int16_t count_lines)
{
    m_score += LINE_REWARD[count_lines];
    m_score_lines += count_lines;
    if (m_score_lines >= 10)
    {
        m_score_lines -= 10;
        m_level.first = m_level.second;
        ++m_level.second;
    }
    else
    {
        m_level.first = m_level.second;
    }
    EditTextContent(m_text_score, std::to_string(m_score), 30,
                    Color_Combination::herbs);
    EditTextPosition(m_text_score, 450, 68);
}

void Score::IncreaseScores(const int16_t value)
{
    m_score += value;
}

void Score::SaveScores()
{
    std::ofstream ranking_file("sys/score_ranking.txt", std::ios_base::out | std::ios_base::app);
    if (ranking_file.is_open())
    {
        ranking_file << std::endl << "Никита\t" << m_score << std::flush;
    }
    else
    {
        //  std::cerr << "Can't open file \"sys/score_ranking.txt\"" << std::endl;
    }
    ranking_file.close();
}

bool Score::LevelChanged()
{
    return m_level.second != m_level.first++;
}

void Score::Draw(sf::RenderWindow &window)
{
    for (size_t y{0}; y < 40; ++y)
    {
        for (size_t x{0}; x < 10; ++x)
        {
            if (y == 0 || y == 39 || x == 0 || x == 9 || y == 2 || y == 5)
            {
                m_sprite.setTextureRect(sf::IntRect(36, 0, 18, 18));
                m_sprite.setPosition(360 + x * 18, y * 18);
            }
            else
            {
                m_sprite.setTextureRect(sf::IntRect(0, 0, 18, 18));
                m_sprite.setPosition(360 + x * 18, y * 18);
            }
            window.draw(m_sprite);
        }
    }
    window.draw(m_text_score);
}