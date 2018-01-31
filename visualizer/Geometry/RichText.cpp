#include "RichText.hpp"
#include <SFML/Graphics.hpp>
#include <sstream>

#ifndef nullptr
#define nullptr NULL
#endif

namespace
{
	struct chunk
	{
		chunk()
		{
			style = sf::Text::Regular;
			color = sf::Color::White;
			endsInNewline = false;
		}

		sf::String
		text;

		int
		style;

		sf::Color
		color;

		bool
		endsInNewline;
	};

	void newChunk(std::vector<chunk>& chunks, chunk*& currentChunk, chunk& lastChunk)
	{
		chunks.push_back(chunk());
		currentChunk = &(chunks[chunks.size() - 1]);

		//	only carry information over if currentChunk and lastChunk aren't the same
		//	this only happens for the first chunk, but it causes random errors
		if (chunks.size() > 2)
		{
			currentChunk->style = lastChunk.style;
			currentChunk->color = lastChunk.color;
		}
	};
}

namespace sf
{
	RichText::RichText()
	{
		characterSize = 30;
		font = nullptr;

		initializeColors();
	}

	RichText::RichText(const String& source, const Font& font, unsigned int characterSize)
	{
		initializeColors();

		this->characterSize = characterSize;
		this->font = &font;

		setString(source);

		initializeColors();
	}

	RichText::RichText(const RichText& other)
	{
		this->characterSize = other.characterSize;
		this->font = other.font;

		for (unsigned i = 0; i < other.texts.size(); ++i)
		{
			texts.push_back(other.texts[i]);
		}

		for (std::map<String, Color>::const_iterator it = other.colors.begin(); it != other.colors.end(); ++it)
		{
			colors[it->first] = it->second;
		}
	}

	RichText::~RichText()
	{
	}

	String RichText::getString() const
	{
		return string;
	}

	String RichText::getSource() const
	{
		return source;
	}

	void RichText::setString(const String& source)
	{
		this->source = source;

		if (font == nullptr)
		{
			return;
		}

		clear();

		std::vector<chunk> chunks;
		chunks.push_back(chunk());

		chunk* currentChunk = &(chunks[0]);
		bool escaped = false;

		for (unsigned i = 0; i < source.getSize(); ++i)
		{
			chunk& lastChunk = *currentChunk;

			switch (source[i])
			{
				case '~': //	italics
				{
					if (escaped)
					{
						currentChunk->text += source[i];
						escaped = false;
						break;
					}

					newChunk(chunks, currentChunk, lastChunk);

					if ((lastChunk.style & Text::Italic) >= 0)
					{
						currentChunk->style ^= Text::Italic;
					}
					else
					{
						currentChunk->style |= Text::Italic;
					}

					currentChunk->color = lastChunk.color;
					break;
				}
				case '*': //	bold
				{
					if (escaped)
					{
						currentChunk->text += source[i];
						escaped = false;
						break;
					}

					newChunk(chunks, currentChunk, lastChunk);

					if ((lastChunk.style & Text::Bold) >= 0)
					{
						currentChunk->style ^= Text::Bold;
					}
					else
					{
						currentChunk->style |= Text::Bold;
					}

					currentChunk->color = lastChunk.color;
					break;
				}
				case '_': 	//	underline
				{
					if (escaped)
					{
						currentChunk->text += source[i];
						escaped = false;
						break;
					}

					newChunk(chunks, currentChunk, lastChunk);

					if ((lastChunk.style & Text::Underlined) >= 0)
					{
						currentChunk->style ^= Text::Underlined;
					}
					else
					{
						currentChunk->style |= Text::Underlined;
					}

					currentChunk->color = lastChunk.color;
					break;
				}
				case '#':	//	color
				{
					if (escaped)
					{
						currentChunk->text += source[i];
						escaped = false;
						break;
					}

					int length = 0;
					int start = i + 1;

					//	seek forward until the next whitespace
					while (!isspace(source[++i]))
					{
						++length;
					}

					newChunk(chunks, currentChunk, lastChunk);
					currentChunk->color = getColor(source.toWideString().substr(start, length));;
					break;

				}
				case '\\':	//	escape sequence for escaping formatting characters
				{
					if (i < source.getSize())
					{
						switch (source[i + 1])
						{
							case '~':
							case '*':
							case '_':
							case '#':
							{
								escaped = true;
								break;
							}
							default:
								break;
						}
					}

					if (!escaped)
					{
						currentChunk->text += source[i];
					}

					break;
				}
				case '\n':	// make a new chunk in the case of a newline
				{
					currentChunk->endsInNewline = true;
					newChunk(chunks, currentChunk, lastChunk);
					break;
				}
				default:
				{
					escaped = false;
					currentChunk->text += source[i];
					break;
				}
			}
		}

		string = "";
		for (unsigned i = 0; i < chunks.size(); ++i)
		{
			if (!chunks[i].endsInNewline && chunks[i].text.getSize() == 0)
			{
				continue;
			}

			string += chunks[i].text + (chunks[i].endsInNewline ? "\n" : "");
		}

		Text text;
		text.setString(string);
		text.setCharacterSize(characterSize);

		if (font != nullptr)
		{
			text.setFont(*font);
		}

		bounds = text.getLocalBounds();

		int cursor = 0;
		chunk* lastChunk = nullptr;
		for (unsigned i = 0; i < chunks.size(); ++i)
		{
			Text t;
			t.setFillColor(chunks[i].color);
			t.setString(chunks[i].text);
			t.setStyle(chunks[i].style);
			t.setCharacterSize(characterSize);

			if (font != nullptr)
			{
				t.setFont(*font);
			}

			t.setPosition(text.findCharacterPos(cursor));

			if (lastChunk != nullptr && lastChunk->endsInNewline)
			{
				t.setPosition(0, t.getPosition().y + font->getLineSpacing(characterSize));
				++cursor;
			}

			texts.push_back(t);
			cursor += chunks[i].text.getSize();
			lastChunk = &chunks[i];
		}
	}

	void RichText::clear()
	{
		texts.clear();
		bounds = FloatRect();
	}

	unsigned int RichText::getCharacterSize() const
	{
		return characterSize;
	}

	void RichText::setCharacterSize(unsigned int size)
	{
		characterSize = std::max<unsigned int>(size, 1);
		setString(source);
	}

	const Font* RichText::getFont() const
	{
		return font;
	}

	void RichText::setFont(const Font& font)
	{
		this->font = &font;

		setString(source);
	}

	FloatRect RichText::getLocalBounds() const
	{
		return bounds;
	}


	FloatRect RichText::getGlobalBounds() const
	{
		return getTransform().transformRect(getLocalBounds());
	}

	void
	RichText::addColor(const String& name, const Color& color)
	{
		colors[name] = color;
	}

	void
	RichText::addColor(const String& name, unsigned argbHex)
	{
		colors[name] = getColor(argbHex);
	}

	void RichText::draw(RenderTarget& target, RenderStates states) const
	{
		states.transform *= getTransform();

		// Draw
		for(unsigned i = 0; i < texts.size(); ++i)
		{
			// Draw text
			target.draw(texts[i], states);
		}
	}

	void
	RichText::initializeColors()
	{
		colors["default"] = Color::White;
		colors["black"] = Color::Black;
		colors["blue"] = Color::Blue;
		colors["cyan"] = Color::Cyan;
		colors["green"] = Color::Green;
		colors["magenta"] = Color::Magenta;
		colors["red"] = Color::Red;
		colors["white"] = Color::White;
		colors["yellow"] = Color::Yellow;
	}

	Color
	RichText::getColor(const String& source) const
	{
		std::map<String, Color>::const_iterator result = colors.find(source);
		if (result == colors.end())
		{
			unsigned hex = 0x0;
			if (!(std::stringstream(source) >> std::hex >> hex))
			{
				//	Error parsing; return default
				return Color::White;
			};

			return getColor(hex);
		}

		return result->second;
	}

	Color
	RichText::getColor(unsigned argbHex) const
	{
		argbHex |= 0xff000000;
		return Color(argbHex >> 16 & 0xFF, argbHex >> 8 & 0xFF, argbHex >> 0 & 0xFF, argbHex >> 24 & 0xFF);
	}

}
