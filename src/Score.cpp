#include <fstream>

#include "Score.hpp"
#include "Support.hpp"

const int16_t Score::m_line_reward[5] = {0, 100, 300, 500, 800};

Score::Score(int16_t number_player)
    : m_line_count(0),
      m_score_points(0),
      m_level(0, false),
      m_number_player(number_player)
{
}

Score::~Score()
{
}

void Score::Init(const sf::Texture &score,
                 const sf::Texture &lines,
                 const sf::Texture &line,
                 const sf::Texture &number)
{
    m_sprite_score.setTexture(score);
    m_sprite_lines.setTexture(lines);
    m_sprite_line.setTexture(line);
    m_sprite_numbers.setTexture(number);

    m_sprite_score.setTextureRect(sf::IntRect(0, 0, 180, 360));
    m_sprite_score.setPosition(m_number_player ? 900.f : 360.f, 0.f);
    m_sprite_lines.setTextureRect(sf::IntRect(0, 0, 180, 90));
    m_sprite_lines.setPosition(m_number_player ? 900.f : 360.f, 306.f);
    m_sprite_line.setTextureRect(sf::IntRect(0, 0, 180, 324));
    m_sprite_line.setPosition(m_number_player ? 900.f : 360.f, 396.f);

    //     switch (m_number_player)
    //     {
    //     case PlayerNumber::First:
    //         break;
    //     case PlayerNumber::Second:
    //         m_sprite_score.setTextureRect(sf::IntRect(0, 0, 180, 360));
    //         m_sprite_score.setPosition(900.f, 0.f);
    //         m_sprite_lines.setTextureRect(sf::IntRect(0, 0, 180, 90));
    //         m_sprite_lines.setPosition(900.f, 306.f);
    //         m_sprite_line.setTextureRect(sf::IntRect(0, 0, 180, 324));
    //         m_sprite_line.setPosition(900.f, 396.f);

    //         break;
    // }
}

void Score::UpdateScores(const int16_t count_lines)
{
    m_line_count += count_lines;

    if (m_line_count >= 10)
    {
        m_line_count -= 10;
        m_level.first++;
        m_level.second = true;
    }
    else
    {
        m_level.second = false;
    }

    m_score_points += m_line_reward[count_lines] * m_level.first;
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
    m_score_points += value;
}

void Score::SaveScores()
{
    std::ofstream ranking_file("sys/score_ranking.txt", std::ios_base::out | std::ios_base::app);
    if (ranking_file.is_open())
    {
        ranking_file << std::endl
                     << (m_number_player ? "Nikita\t" : "Lera\t") << m_score_points << std::flush;
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
    window.draw(m_sprite_score);
    std::string score(std::to_string(m_score_points));
    score.insert(0, 6 - score.size(), '0');
    for (size_t i{0}; i < 6; ++i)
    {
        m_sprite_numbers.setTextureRect(sf::IntRect((score.at(i) - 48) * 10, 0, 10, 18));
        m_sprite_numbers.setPosition((m_number_player ? 540 : 0) + 399 + i * 18, 62);
        window.draw(m_sprite_numbers);
    }

    std::string level(std::to_string(m_level.first));
    level.insert(0, 2 - level.size(), '0');
    for (size_t i{0}; i < 2; ++i)
    {
        m_sprite_numbers.setTextureRect(sf::IntRect((level.at(i) - 48) * 10, 0, 10, 18));
        m_sprite_numbers.setPosition((m_number_player ? 540 : 0) + 437 + i * 15, 258);
        window.draw(m_sprite_numbers);
    }

    window.draw(m_sprite_lines);
    window.draw(m_sprite_line);

    std::string lines(std::to_string(m_line_count + (m_level.first) * 10));
    lines.insert(0, 3 - lines.size(), '0');
    for (size_t i{0}; i < 3; ++i)
    {
        m_sprite_numbers.setTextureRect(sf::IntRect((lines.at(i) - 48) * 10, 0, 10, 18));
        m_sprite_numbers.setPosition((m_number_player ? 540 : 0) + 430 + i * 15, 348);
        window.draw(m_sprite_numbers);
    }

    // switch (m_number)
    // {
    // case PlayerNumber::First:
    //     window.draw(m_sprite_score);
    //     std::string score(std::to_string(m_score_points));
    //     score.insert(0, 6 - score.size(), '0');
    //     for (size_t i{0}; i < 6; ++i)
    //     {
    //         m_sprite_numbers.setTextureRect(sf::IntRect((score.at(i) - 48) * 10, 0, 10, 18));
    //         m_sprite_numbers.setPosition(399 + i * 18, 62);
    //         window.draw(m_sprite_numbers);
    //     }

    //     std::string level(std::to_string(m_level.first));
    //     level.insert(0, 2 - level.size(), '0');
    //     for (size_t i{0}; i < 2; ++i)
    //     {
    //         m_sprite_numbers.setTextureRect(sf::IntRect((level.at(i) - 48) * 10, 0, 10, 18));
    //         m_sprite_numbers.setPosition(437 + i * 15, 258);
    //         window.draw(m_sprite_numbers);
    //     }

    //     window.draw(m_sprite_lines);
    //     window.draw(m_sprite_line);

    //     std::string lines(std::to_string(m_line_count + (m_level.first) * 10));
    //     lines.insert(0, 3 - lines.size(), '0');
    //     for (size_t i{0}; i < 3; ++i)
    //     {
    //         m_sprite_numbers.setTextureRect(sf::IntRect((lines.at(i) - 48) * 10, 0, 10, 18));
    //         m_sprite_numbers.setPosition(430 + i * 15, 348);
    //         window.draw(m_sprite_numbers);
    //     }
    //     break;
    // case PlayerNumber::Second:
    //     window.draw(m_sprite_score);
    //     std::string score(std::to_string(m_score_points));
    //     score.insert(0, 6 - score.size(), '0');
    //     for (size_t i{0}; i < 6; ++i)
    //     {
    //         m_sprite_numbers.setTextureRect(sf::IntRect((score.at(i) - 48) * 10, 0, 10, 18));
    //         m_sprite_numbers.setPosition(1119 + i * 18, 62);
    //         window.draw(m_sprite_numbers);
    //     }

    //     std::string level(std::to_string(m_level.first));
    //     level.insert(0, 2 - level.size(), '0');
    //     for (size_t i{0}; i < 2; ++i)
    //     {
    //         m_sprite_numbers.setTextureRect(sf::IntRect((level.at(i) - 48) * 10, 0, 10, 18));
    //         m_sprite_numbers.setPosition(1157 + i * 15, 258);
    //         window.draw(m_sprite_numbers);
    //     }

    //     window.draw(m_sprite_lines);
    //     window.draw(m_sprite_line);

    //     std::string lines(std::to_string(m_line_count + (m_level.first) * 10));
    //     lines.insert(0, 3 - lines.size(), '0');
    //     for (size_t i{0}; i < 3; ++i)
    //     {
    //         m_sprite_numbers.setTextureRect(sf::IntRect((lines.at(i) - 48) * 10, 0, 10, 18));
    //         m_sprite_numbers.setPosition(1150 + i * 15, 348);
    //         window.draw(m_sprite_numbers);
    //     }
    //     break;
    // }
}