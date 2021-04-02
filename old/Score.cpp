#include "Score.hpp"

namespace Tetris
{
    Score::Score()
        : score(0)
    {
    }
    Score::~Score()
    {
    }
    void Score::EnterPlayersNickname()
    {
    }
    void Score::IncreaseScore(const int16_t number_lines)
    {
        this->score += this->LINE_REWARD[number_lines];
    }
    const int32_t Score::GetScore() const
    {
        return this->score;
    }
    const void Score::GetRanking() const
    {
    }
    void Score::InsertPlayer()
    {
        std::ofstream ranking_file("sys/score_ranking.txt", std::ios_base::out | std::ios_base::app);
        if (ranking_file.is_open())
        {
            ranking_file << "Никита\t" << this->GetScore() << std::endl;
        }
        else
        {
            std::cerr << "Can't open file \"sys/score_ranking.txt\"" << std::endl;
        }
        ranking_file.close();
    }
} // namespace Tetris
