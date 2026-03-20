#pragma once
#include <string>
#include "lagu.h"

struct NodeLagu
{
    int id;
    NodeLagu *next;
};

struct Playlist
{
    string nama;
    int size;
    NodeLagu *front;
    NodeLagu *rear;

    Playlist *next;
};

void tambahPlaylist();
void lihatPlaylist();
void loadPlaylist();
bool isEmptyPlaylist(Playlist *p);
void enqueuePlaylist(Playlist *p, int idLagu, bool save = true);
int dequeuePlaylist(Playlist *p);
Lagu *findLaguById(int id);
void savePlaylist();
void opsiPlaylist(Playlist *p);

void pushPlaylist(Playlist *pl);
Playlist *popPlaylist();
bool isEmptyStackPlaylist();
void restorePlaylist();