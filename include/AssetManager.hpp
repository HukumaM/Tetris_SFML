//------------------------------------------------------------------------------------------
//  Author      : Nikita Mashtalirov
//  Created     : 01.04.2021
//  Description : A class that manages all of the app's assets: sprites, text, and textures.
//------------------------------------------------------------------------------------------

#pragma once

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

namespace Engine
{
    class AssetManager
    {
    private:
        //  A member field that stores a map of the texture ID values and a pointer to it
        std::map<int16_t, std::unique_ptr<sf::Texture>> m_textures;
        
        //  A member field that stores a map of the font ID values and a pointer to it
        std::map<int16_t, std::unique_ptr<sf::Font>> m_fonts;

    public:
        AssetManager();
        ~AssetManager();

    public:
        //  Adds a texture to the texture map by its ID
        //  @param id               Texture ID
        //  @param file_path        The path to the specified texture.
        //                          Must be specified relative to the current project folder
        //  @param want_repeated    A flag indicating whether the texture should repeat over the entire specified rectangle
        void
        AddTexture(int16_t id, const std::string &file_path, bool want_repeated = false);

        //  Adds a font to the font map by its ID
        //  @param id               Font ID
        //  @param file_path        The path to the specified font.
        //                          Must be specified relative to the current project folder
        void
        AddFont(int16_t id, const std::string &file_path);

        //  Returns the texture by specified id
        //  @param id               Texture ID
        //  @return                 Constant reference to the texture of the corresponding identifier
        const sf::Texture &
        GetTexture(int16_t id) const;

        //  Returns the font by specified id
        //  @param id               Font ID
        //  @return                 Constant reference to the font of the corresponding identifier
        const sf::Font &
        GetFont(int16_t id) const;
    };

} //namespace Engine