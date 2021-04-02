#pragma once 

#include "config.hpp"

#include <fstream>

namespace Tetris
{
    class Score
    {
    private:
        const int16_t LINE_REWARD[5]{0, 100, 300, 500, 800};

        int32_t score;
    private:
        void EnterPlayersNickname();

    public:
        Score();
        ~Score();
        void IncreaseScore(const int16_t number_lines);
        const int32_t GetScore() const;
        const void GetRanking() const;
        void InsertPlayer();
        
    };
}