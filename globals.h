#pragma once
#include <SFML/Audio.hpp>
#include "lagu.h"
#include "playlist.h"

extern Lagu *head;
extern Lagu *tail;
extern Playlist *headPlaylist;
extern sf::Music bgm;

void putarLagu(string namaFile);