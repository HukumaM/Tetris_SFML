#include <fstream>

#include "Score.hpp"
#include "Support.hpp"

Score::Score()
    : m_score(0),
      m_score_lines(0),
      m_level(1, false)
{
}

Score::~Score()
{
}

void Score::Init(const sf::Texture &texture, const sf::Font &font)
{
    m_sprite.setTexture(texture);

    m_text_score.setFont(font);
    m_text_line.setFont(font);

    UpdateRankingTable();

    EditTextContent(m_text_score, "0", 30, Color_Combination::herbs);
    EditTextPosition(m_text_score, 450, 68);
}

void Score::UpdateScores(const int16_t count_lines)
{
    m_score_lines += count_lines;

    if (m_score_lines >= 10)
    {
        m_score_lines -= 10;
        m_level.first++;
        m_level.second = true;
    }
    else
    {
        m_level.second = false;
    }

    m_score += m_line_reward[count_lines] * m_level.first;

    EditTextContent(m_text_score, std::to_string(m_score), 30,
                    Color_Combination::herbs);
    EditTextPosition(m_text_score, 450, 68);
}

void Score::UpdateRankingTable()
{
    std::ifstream ranking_file("sys/score_ranking.txt", std::ios::in);
    if (ranking_file.is_open())
    {
        while (!ranking_file.eof())
        {
            std::pair<int32_t, std::string> line;
            ranking_file >> line.second;
            ranking_file >> line.first;
            m_ranking_table.emplace(line);
        }
    }
    ranking_file.close();
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
        ranking_file << std::endl
                     << "Nikita\t" << m_score << std::flush;
    }
    else
    {
        //  std::cerr << "Can't open file \"sys/score_ranking.txt\"" << std::endl;
    }
    ranking_file.close();
}

bool Score::LevelChanged()
{
    return m_level.second;
}

void Score::Draw(sf::RenderWindow &window)
{

    for (size_t y{0}; y < 40; ++y)
    {
        for (size_t x{0}; x < 10; ++x)
        {
            if (y == 0 || y == 39 || x == 0 || x == 9 || y == 2 || y == 5)
            {
                m_sprite.setTextureRect(sf::IntRect(126, 0, 18, 18));
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

    int16_t line_number{1};
    for (auto line{m_ranking_table.begin()};
         line_number <= 10 && line != m_ranking_table.end();
         line++, ++line_number)
    {
        EditTextContent(m_text_line, line->second + " " + std::to_string(line->first),
                        25, Color_Combination::herbs);
        EditTextPosition(m_text_line, 450, 108 + line_number * 36);
        window.draw(m_text_line);
    }

    window.draw(m_text_score);
}