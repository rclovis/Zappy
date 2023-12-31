/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** TileGui
*/

#include "TileGui.hpp"

TileGui::TileGui(sf::Sprite *tile, int x, int y, int id, sf::Texture *texture, sf::IntRect rect, int rotate, Data *data)
{
    _data = data;
    _x = x;
    _y = y;
    _spriteTile = tile;
    _spriteRessource.setTexture(*texture);
    _spriteRessource.setOrigin(16, 16);
    _spriteRessource.setScale(0.5, 0.5);
    _rect = rect;
    _id = id;
    _nbFrame = (rect.top == 16 * 6 || id == 0) ? 4 : 0;
    _frame = 0;
    _rotate = rotate;
    _ressourcesPos = std::vector<std::vector<sf::Vector2f>>(8);
}

TileGui::~TileGui()
{
}

void TileGui::update()
{
    if (_id == -1) return;
    for (int i = 0; i < 7; i++) {
        int nb = _data->getMap()[_y / 16][_x / 16]->getRessources()[i];
        if (nb > _ressourcesPos[i].size()) {
            while (_ressourcesPos[i].size() < nb) {
                sf::Vector2f pos = sf::Vector2f(_x + rand() % 8, _y + rand() % 8);
                _ressourcesPos[i].push_back(pos);
            }
        } else if (nb < _ressourcesPos[i].size()) {
            while (_ressourcesPos[i].size() > nb) {
                _ressourcesPos[i].erase(_ressourcesPos[i].begin() + nb, _ressourcesPos[i].end());
            }
        }
    }
}

void TileGui::animate(int timeUnit)
{
    if (_nbFrame > 0) {
        if (_clock.getElapsedTime().asMilliseconds() > 1000 / timeUnit) {
            _frame++;
            if (_frame >= _nbFrame)
                _frame = 0;
            _rect.left = _frame * 16;
            _clock.restart();
        }
    }
}

void TileGui::display(sf::RenderWindow *window)
{
    _spriteTile->setPosition(_x, _y);
    _spriteTile->setTextureRect(_rect);
    _spriteTile->setRotation(_rotate);
    window->draw(*_spriteTile);
}

void TileGui::displayRessources(sf::RenderWindow *window)
{
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < _ressourcesPos[i].size(); j++) {
            sf::Vector2f pos = _ressourcesPos[i][j];
            sf::IntRect rect = sf::IntRect(i * 16, 7 * 16, 16, 16);
            _spriteRessource.setTextureRect(rect);
            _spriteRessource.setPosition(pos);
            window->draw(_spriteRessource);
        }
    }
}
