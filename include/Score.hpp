//-----------------------------------------------------------------------
//  Author      : Nikita Mashtalirov
//  Created     : 06.04.2021
//  Description : A class representing the score
//-----------------------------------------------------------------------

#pragma once

#include <map>
#include <string>
#include <fstream>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Score
{
private:
    const int16_t m_line_reward[5]{0, 100, 300, 500, 800};
    std::pair<int16_t, bool> m_level;
    int32_t m_score;
    int16_t m_score_lines;

private:
    std::map<int32_t, std::string, std::greater<int32_t>> m_ranking_table;
    sf::Text m_text_line;

private:
    sf::Sprite m_sprite;
    sf::Text m_text_score;

public:
    Score();
    ~Score();

    void Init(const sf::Texture &texture, const sf::Font &font);

    void IncreaseScores(const int16_t value);
    void UpdateScores(const int16_t count_lines);
    void UpdateRankingTable();
    void SaveScores();
    bool LevelChanged();
    inline int16_t GetScoreLines() const { return m_score_lines; }
    void Draw(sf::RenderWindow &window);
};