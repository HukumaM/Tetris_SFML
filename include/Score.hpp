//-----------------------------------------------------------------------
//  Author      : Nikita Mashtalirov
//  Created     : 06.04.2021
//  Description : A class representing the score
//-----------------------------------------------------------------------

#pragma once

#include <fstream>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Score
{
private:
    const int16_t LINE_REWARD[5]{0, 100, 300, 500, 800};
    int32_t m_score;
    int16_t m_score_lines;
    std::pair<int16_t, int16_t> m_level;

private:
    sf::Sprite m_sprite;
    sf::Text m_text_score;

public:
    Score();
    ~Score();

    void Init(const sf::Texture &texture, const sf::Font &font);

    void IncreaseScores(const int16_t value);
    void UpdateScores(const int16_t count_lines);
    void SaveScores();
    bool LevelChanged();
    inline int16_t GetScoreLines() const { return m_score_lines; }
    void Draw(sf::RenderWindow &window);
};