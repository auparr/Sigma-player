#pragma once
#include <SFML/Audio.hpp>
#include "lagu.h"
#include "playlist.h"

extern Lagu *head;
extern Lagu *tail;
extern Playlist *headPlaylist;
extern sf::Music bgm;

struct StackLagu
{
    Lagu *data;
    StackLagu *next;
};

struct StackPlaylist
{
    Playlist *data;
    StackPlaylist *next;
};

extern StackLagu *topLagu;
extern StackPlaylist *topPlaylist;

void putarLagu(string namaFile);