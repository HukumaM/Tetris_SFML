#include "Audio.hpp"

float Audio::m_volume_music = Volume::Max;
float Audio::m_volume_fx = Volume::Max;
sf::Time Audio::m_playing_offset = sf::Time::Zero;

std::map<int16_t, std::unique_ptr<sf::Music>> Audio::m_music =
    std::map<int16_t, std::unique_ptr<sf::Music>>();

std::map<int16_t, std::unique_ptr<sf::Sound>> Audio::m_sound =
    std::map<int16_t, std::unique_ptr<sf::Sound>>();

std::map<int16_t, std::unique_ptr<sf::SoundBuffer>> Audio::m_sound_buffer =
    std::map<int16_t, std::unique_ptr<sf::SoundBuffer>>();

Audio::Audio()
{
}

Audio::~Audio()
{
}

void Audio::LoadMusic(int16_t id, const std::string &path, bool loop, bool play)
{
    auto music = std::make_unique<sf::Music>();

    if (music->openFromFile(path))
    {
        m_music[id] = std::move(music);
        m_music[id]->setLoop(loop);
        if (play)
        {
            m_music[id]->play();
        }
    }
}

void Audio::LoadSound(int16_t id, const std::string &path)
{
    auto sound_buffer = std::make_unique<sf::SoundBuffer>();
    auto sound = std::make_unique<sf::Sound>();

    if (sound_buffer->loadFromFile(path))
    {
        m_sound_buffer[id] = std::move(sound_buffer);
        sound->setBuffer(*(m_sound_buffer.at(id).get()));
        m_sound[id] = std::move(sound);
    }
}

std::unique_ptr<sf::Music> &Audio::GetMusicPtr(int16_t id)
{
    return m_music.at(id);
}

sf::Music &Audio::GetMusic(int16_t id)
{
    return *(m_music.at(id).get());
}

sf::Sound &Audio::GetSound(int16_t id)
{
    return *(m_sound.at(id).get());
}

void Audio::IncreaseVolumeMusic(float volume)
{
    m_volume_music += volume;
}

void Audio::IncreaseVolumeFX(float volume)
{
    m_volume_fx += volume;
}

void Audio::SetPlayingOffset(sf::Time offset)
{
    m_playing_offset = offset;
}