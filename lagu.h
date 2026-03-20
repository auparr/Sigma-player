#pragma once
#include <string>
using namespace std;

struct Lagu
{
    int id;
    string judul;
    string penyanyi;
    float durasi;
    string genre;
    string fileAudio;
    Lagu *next;
    Lagu *prev;
};

void update();
bool validDuration(string duration);
string FormattedDuration(Lagu *lagu);
void loadSongs();
void tambahLagu();
void lihatDaftarLagu();
void navigasiLagu();
