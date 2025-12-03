/**
 * @file button.cpp
 * @author Ian Codding II
 * @brief This file implements all of the button functionallity
 * @version 0.1
 * @date 2025-10-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "../includes/button.h"
#include "../includes/errorHandler.h"

/**
 * @brief Construct a new Button:: Button object
 *  Default constructor that loads texture from file “button.png” and font from "Balins_Font.ttf” file.
 *  set texture for mButton, set the origin to the middle of the button (texture),
 *  set color to White, position to {300,100}, set buttonState to normalButton, and scale to 100%
 *  set font for the text, set the size of the text to the half of Button size, set the origin to the middle of the text
 *  and set position at the middle of the button, assign “Push me!” as a string of the button
 * 
 */
Button::Button(): Button("Push ME!", {300, 100}, {1,1}, sf::Color::White){
    mButton.setScale(1,1);
    unsigned int fontSize = mButton.getGlobalBounds().height / 2;
    mText.setCharacterSize(fontSize);
    mText.setOrigin(mText.getGlobalBounds().width / 2, mText.getGlobalBounds().height / 2);
    mText.setPosition(mPosition.x, mPosition.y - fontSize / 4);
}

/**
 * @brief Construct a new Button:: Button object
 *  Constructor that sets button label to s, button position to the position,
 *  button size to size (given in pixels), and button color to color.
 * 
 * @param s 
 * @param position 
 * @param size 
 * @param color 
 */
Button::Button(std::string s, sf::Vector2f position, sf::Vector2f size, sf::Color color) {
    mBtnState = normalButton;  // Initialize enum
    
    if (!mTexture.loadFromFile("assets/sprites/button.png")) {
        throw ResourceError("button.png not found - ensure file is in working directory");
    }
    mButton.setTexture(mTexture);
    
    if (!mFont.loadFromFile("assets/fonts/Balins_Font.ttf")) {
        throw ResourceError("Balins_Font.ttf not found - ensure font file is in working directory");
    }
    mText.setFont(mFont);

    // get size of image
    sf::Vector2u imageSize = mTexture.getSize();

    // change origin to the center of the image (makes rotation easy)
    mButton.setOrigin(imageSize.x / 2, imageSize.y / 2);

    mPosition = position;
    // set position
    mButton.setPosition(mPosition.x, mPosition.y);

    // choose color
    mButtonColor = color;

    mButton.setColor(mButtonColor);

    // set size as a ration of original size
    mButton.setScale(size.x / imageSize.x, size.y / imageSize.y);

    // choose the font size based on button size (I choose half)
    unsigned int fontSize = mButton.getGlobalBounds().height / 2;
    mText.setCharacterSize(fontSize);

    // set label
    mText.setString(s);

    // set origin to the middle
    mText.setOrigin(mText.getGlobalBounds().width / 2, mText.getGlobalBounds().height / 2);

    // set position at the middle of the button
    mText.setPosition(mPosition.x, mPosition.y - fontSize / 4);

    // choose colors
    mTextNormal = sf::Color::Green;
    mTextHover = sf::Color::Red;
    mText.setFillColor(mTextNormal);

    mBtnState = normalButton;
}

/**
 * @brief change button position to position (what else needs to be changed?)
 * 
 * @param position 
 */
void Button::setPosition(sf::Vector2f position) {
    mPosition = position;
    mButton.setPosition(mPosition.x, mPosition.y);

    // mText.setOrigin(mText.getGlobalBounds().width / 2, mText.getGlobalBounds().height / 2);
    unsigned int fontSize = mButton.getGlobalBounds().height / 2;
    mText.setPosition(mPosition.x, mPosition.y - fontSize / 4);
}

/**
 * @brief change button size to size (what else needs to be changed?)
 * 
 * @param size 
 */
void Button::setSize(sf::Vector2f size) {
    sf::Vector2u imageSize = mTexture.getSize();
    mButton.setScale(size.x / imageSize.x, size.y / imageSize.y);

    unsigned int fontSize = mButton.getGlobalBounds().height / 2;
    mText.setCharacterSize(fontSize);
    mText.setOrigin(mText.getGlobalBounds().width / 2, mText.getGlobalBounds().height / 2);
    mText.setPosition(mPosition.x, mPosition.y - fontSize / 4);
}

/**
 * @brief change button color to color (what else needs to be changed?)
 * 
 * @param btnColor 
 */
void Button::setColor(sf::Color btnColor) {
    mButtonColor = btnColor;
    mButton.setColor(mButtonColor);
}

/**
 * @brief change button label to s (what else needs to be changed?)
 * 
 * @param s 
 */
void Button::setText(std::string s) {
    mText.setString(s);
    mText.setOrigin(mText.getGlobalBounds().width / 2, mText.getGlobalBounds().height / 2);
    unsigned int fontSize = mButton.getGlobalBounds().height / 2;
    mText.setPosition(mPosition.x, mPosition.y - fontSize / 4);
}

/**
 * @brief returns the test for the button
 * 
 * @return std::string 
 */
std::string Button::getText() const {
    return mText.getString().toAnsiString();  // Converts sf::String to std::string
}

/**
 * @brief This function update the button state and/or look
 * 
 * @param e 
 * @param window 
 */
void Button::update(sf::Event &e, sf::RenderWindow &window) {
    // get position of the mouse
    // sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2i mPos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosition = window.mapPixelToCoords(mPos, window.getDefaultView());
    bool mouseInButton = mousePosition.x >= mButton.getPosition().x - mButton.getGlobalBounds().width / 2 && mousePosition.x <= mButton.getPosition().x + mButton.getGlobalBounds().width / 2 && mousePosition.y >= mButton.getPosition().y - mButton.getGlobalBounds().height / 2 && mousePosition.y <= mButton.getPosition().y + mButton.getGlobalBounds().height / 2;
    if (e.type == sf::Event::MouseMoved) {
        if (mouseInButton) {
            mBtnState = buttonState::hovered;
        } else {
            mBtnState = buttonState::normalButton;
        }
    }
    if (e.type == sf::Event::MouseButtonPressed) {
        if (e.mouseButton.button == sf::Mouse::Left) {
            if (mouseInButton) {
                mBtnState = buttonState::clicked;
            } else {
                mBtnState = buttonState::normalButton;
            }
        }
    }
    if (e.type == sf::Event::MouseButtonReleased) {
        if (e.mouseButton.button == sf::Mouse::Left) {
            if (mouseInButton) {
                mBtnState = buttonState::hovered;
            } else {
                mBtnState = buttonState::normalButton;
            }
        }
    }
    switch (mBtnState) {
    case normalButton: {
        mButton.setRotation(0);
        mText.setFillColor(mTextNormal);
        break;
    }
    case hovered: {
        mButton.setRotation(0);
        mText.setFillColor(mTextHover);
        break;
    }
    case clicked: {
        mButton.setRotation(180);
        mText.setFillColor(mTextHover);
        break;
    }
    }
}

/**
 * @brief drows to the target
 * 
 * @param target 
 * @param states 
 */
void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(mButton, states);
    target.draw(mText, states);
}