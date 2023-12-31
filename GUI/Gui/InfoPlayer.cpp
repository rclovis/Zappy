/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** InfoPlayer
*/

#include "InfoPlayer.hpp"

InfoPlayer::InfoPlayer(Data *data)
{
    _data = data;
    _button.setSize(sf::Vector2f(32, 32));
    _button.setFillColor(sf::Color::Black);
    _button.setOrigin(_button.getSize().x, 0);
    _texture.loadFromFile("GUI/sprites/icons.png");
    _view.setSize(720, 480);
    for (int i = 0;i < _data->getTeams().size();i++) {
        _teams.push_back(new InfoTeam(_data, _texture, _data->getTeams()[i]->getName(), i));
    }
}

InfoPlayer::~InfoPlayer()
{
    for (int i = 0;i < _teams.size();i++) {
        delete _teams[i];
    }
}

void InfoPlayer::setMouse(sf::RenderWindow &window, sf::Event event, sf::View view)
{
    if (event.type == sf::Event::MouseButtonReleased) {
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorld = window.mapPixelToCoords(mouse, _view);
        if (_button.getGlobalBounds().contains(mouseWorld)) {
            if (_display == 0)
                _display = 1;
            else
                _display = 0;
        }
    }
    int i = 0;
    for (;i < _teams.size();i++) {
        if (_teams[i]->setMouse(window, event, view))
            break;
    }
    if (i != _teams.size()) {
        for (int j = 0;j < _teams.size();j++) {
            if (j != i)
                _teams[j]->unToggle();
        }
    }
}

void InfoPlayer::update()
{
    for (int i = 0;i < _teams.size();i++) {
        _teams[i]->update();
    }
}

void InfoPlayer::draw(sf::RenderWindow &window)
{
    _view.setCenter(window.getView().getCenter());
    _button.setPosition(window.getView().getCenter().x + 720 / 2 - 10, window.getView().getCenter().y - 480 / 2 + 10);
    sf::View view = window.getView();
    for (int i = 0;i < _teams.size();i++) {
        window.setView(view);
        _teams[i]->draw(window, _display);
    }
    window.setView(_view);
    window.draw(_button);
}

sf::View InfoPlayer::getView(sf::View globalView, std::vector<PlayerGui *> player)
{
    for (int i = 0;i < _teams.size();i++) {
        if (_teams[i]->getClicked() == 1) {
            return (_teams[i]->getView(player));
        }
    }
    return (globalView);
}

