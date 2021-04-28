#pragma once

#include <map>
#include <memory>

#include <SFML/System/Time.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class Audio
{
public:
    enum Volume
    {
        Min = 0,
        Max = 100
    };

    enum Music
    {
        MAIN_MUSIC,
        A_STAGE_MUSIC,
        B_STAGE_MUSIC,
        C_STAGE_MUSIC
    };

    enum Sound
    {
        SELECTION,
        CLEAN_LINE,
        FALL,
        MOVE,
        GAME_OVER
    };

private:
    static float m_volume_music;
    static float m_volume_fx;
    static sf::Time m_playing_offset;

private:
    static std::map<int16_t, std::unique_ptr<sf::Music>> m_music;
    static std::map<int16_t, std::unique_ptr<sf::Sound>> m_sound;
    static std::map<int16_t, std::unique_ptr<sf::SoundBuffer>> m_sound_buffer;

public:
    Audio();
    ~Audio();

    static void LoadMusic(int16_t id, const std::string &path,
                          bool loop = false, bool play = false);
    static void LoadSound(int16_t id, const std::string &path);

    static std::unique_ptr<sf::Music> &GetMusicPtr(int16_t id);
    static sf::Music &GetMusic(int16_t id);
    static sf::Sound &GetSound(int16_t id);

    static void IncreaseVolumeMusic(float volume);
    static void IncreaseVolumeFX(float volume);
    static void SetPlayingOffset(sf::Time offset);

    static inline float
    GetVolumeMusic() { return m_volume_music; }

    static inline float
    GetVolumeFX() { return m_volume_fx; }

    static inline sf::Time
    GetPlayingOffset() { return m_playing_offset; }
};