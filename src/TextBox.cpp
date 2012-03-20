#include "../include/TextBox.h"

TextBox::TextBox(float posx, float posy, std::string text)
{
    this->posx = posx;
    this->posy = posy;
    this->text = text;
    image.LoadFromFile("images/TextBox.png");
    image.SetSmooth(false);
    sprite.SetImage(image);
    sprite.SetPosition(this->posx, this->posy);
    timer.Reset();
}

TextBox::~TextBox()
{

}

void TextBox::Draw(sf::RenderWindow &window)
{
    sf::Font textFont;
    textFont.LoadFromFile("Treamd.ttf");
    sf::String textString(text, textFont, 22);

    sf::FloatRect rect = textString.GetRect();

    textString.SetColor(sf::Color(0, 0, 0, 255));
    textString.SetPosition((sprite.GetSize().x - rect.GetWidth()) / 2, (sprite.GetSize().y - rect.GetHeight()) / 2);

    window.Draw(sprite);
    window.Draw(textString);
}
