#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/String.hpp>
#include <map>
#include <vector>

namespace sf
{
class RichText
    : public Drawable
    , public Transformable
{
public:
    RichText();
    RichText(const RichText& other);
    explicit RichText(const String& source, const Font& font, unsigned int characterSize = 30);
    ~RichText();

    enum Style
    {
        Regular    = sf::Text::Regular,
        Bold       = sf::Text::Bold,
        Italic     = sf::Text::Italic,
        Underlined = sf::Text::Underlined,
    };

    String getString() const;
    String getSource() const;
    void   setString(const String& source);
    void   clear();

    unsigned int getCharacterSize() const;
    void         setCharacterSize(unsigned int size);

    const Font* getFont() const;
    void        setFont(const Font& font);

    FloatRect getLocalBounds() const;
    FloatRect getGlobalBounds() const;

    //	Set names for color substitutions (for example, ff0000 would be
    // substituted for "red")
    void addColor(const String& name, const Color& color);
    void addColor(const String& name, unsigned argbHex);

private:
    void draw(RenderTarget& target, RenderStates states) const;

    void  initializeColors();
    Color getColor(const String& source) const;
    Color getColor(unsigned argbHex) const;

    std::map<String, Color> colors;
    std::vector<Text>       texts;

    unsigned int characterSize;
    const Font*  font;

    String    source;
    String    string;
    FloatRect bounds;
};
} // namespace sf
