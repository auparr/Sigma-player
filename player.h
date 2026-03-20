#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "lagu.h"

enum PlayerAction
{
    NONE,
    NEXT,
    PREV,
    STOP
};

PlayerAction showPlayerGUI(Lagu *song, sf::Music &bgm);