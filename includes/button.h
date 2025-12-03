/**
 * @file button.h
 * @author Ian Codding II
 * @brief Implementaion of button class
 * @version 0.1
 * @date 2025-10-22
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef BUTTON_H
#define BUTTON_H
#include <iostream>
#include <SFML/Graphics.hpp>

enum buttonState { normalButton,
             hovered,
             clicked };

class Button : public sf::Drawable {
  public:
    Button();
    // Constructor that sets button label to s, button position to the position,  button size to size (given in pixels), and button color to color.
    Button(std::string s, sf::Vector2f position, sf::Vector2f size, sf::Color color);
    ~Button() {};
    // change button position to position (what else needs to be changed?)
    void setPosition(sf::Vector2f position);
    // change button size to size (what else needs to be changed?)
    void setSize(sf::Vector2f size);
    // change button color to color (what else needs to be changed?)
    void setColor(sf::Color btnColor);
    // change button label to s (what else needs to be changed?)
    void setText(std::string s);
    void setColorTextNormal(sf::Color textNormalColor) { mTextNormal = textNormalColor; };
    void setColorTextHover(sf::Color textHoverColor) { mTextHover = textHoverColor; };

    sf::Vector2f getPosition() { return mPosition; };
    sf::Vector2f getDimensions() { return sf::Vector2f(mButton.getGlobalBounds().width, mButton.getGlobalBounds().height); };
    sf::Uint32 getState() { return mBtnState; };
    const sf::Text &getSFMLText() const { return mText; }
    std::string getText() const; // NEW: Returns the label as std::string

    // This function update the button buttonState and/or look
    void update(sf::Event &e, sf::RenderWindow &window);
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

  private:
    sf::Sprite mButton;
    sf::Texture mTexture;
    sf::Color mButtonColor;
    sf::Vector2f mPosition;
    sf::Uint32 mBtnState;

    // text
    sf::Text mText;
    sf::Font mFont;
    sf::Color mTextNormal;
    sf::Color mTextHover;
};
#endif