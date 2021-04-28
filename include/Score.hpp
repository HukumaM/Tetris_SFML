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
    public:
        enum PlayerNumber
        {
            First,
            Second
        };

    private:
        static const int16_t m_line_reward[5];

        int16_t m_line_count;

        int32_t m_score_points;

        std::pair<int16_t, bool> m_level;

        int16_t m_number_player;

    private:
        std::map<int32_t, std::string, std::greater<int32_t>> m_ranking_table;

    private:
        sf::Sprite m_sprite_score;
        sf::Sprite m_sprite_lines;
        sf::Sprite m_sprite_line;

        sf::Sprite m_sprite_numbers;

    public:
        Score(int16_t number_player);
        ~Score();

        void Init(const sf::Texture &score,
                  const sf::Texture &lines,
                  const sf::Texture &line,
                  const sf::Texture &number);

        void IncreaseScores(const int16_t value);
        void UpdateScores(const int16_t count_lines);
        void UpdateRankingTable();
        void SaveScores();
        bool LevelChanged();

        inline const int16_t
        GetLevel() const { return m_level.first; }
        //inline int16_t GetScoreLines() const { return m_score_lines; }
        void Draw(sf::RenderWindow &window);
};
