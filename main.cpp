#include <iostream>
#include "globals.h"

// HAPUS COMMENT DI BAWAH JIKA MENGERJAKAN BONUS SFML
#include <SFML/Audio.hpp>

using namespace std;

// HAPUS COMMENT DI BAWAH JIKA MENGERJAKAN BONUS SFML
sf::Music bgm;

// Fungsi bantuan dari Asisten Praktikum (JANGAN DIUBAH)
void putarLagu(string namaFile)
{
    // HAPUS COMMENT DI BAWAH JIKA MENGERJAKAN BONUS SFML
    if (namaFile.empty() || namaFile == "")
    {
        cout << "\n\n[Warning] Tidak ada file audio yang diatur untuk lagu ini!\n";
        bgm.stop();
        return;
    }

    if (!bgm.openFromFile("./music/" + namaFile))
    {
        cout << "[Warning] File audio " << namaFile << " tidak ditemukan!\n";
        return;
    }
    bgm.play();

    cout << "\n[Memutar Audio: " << namaFile << " di latar belakang...]\n";
}

// ==========================================
// AREA PENGERJAAN PRAKTIKAN DIMULAI DARI SINI
// ==========================================

Lagu *head = NULL;
Lagu *tail = NULL;
Playlist *headPlaylist = NULL;

StackLagu *topLagu = NULL;
StackPlaylist *topPlaylist = NULL;

int main()
{
    // TODO: Buat menu utama CLI
    loadPlaylist();
    loadSongs();
    while (true)
    {

        cout << "==== Sigma Music Player ====" << endl;
        cout << "1. Tambah lagu" << endl;
        cout << "2. Lihat daftar lagu" << endl;
        cout << "3. Navigasi Lagu" << endl;
        cout << "4. Tambahkan Playlist" << endl;
        cout << "5. Lihat Daftar Playlist" << endl;
        cout << "6. Restore Lagu" << endl;
        cout << "7. Restore Playlist" << endl;
        cout << "0. Keluar" << endl;

        int input;
        cout << "Pilihan: ";
        cin >> input;
        cin.clear();
        cin.ignore();

        switch (input)
        {
        case 1:
        {
            tambahLagu();
            break;
        }
        case 2:
        {
            lihatDaftarLagu();
            break;
        }
        case 3:
        {
            navigasiLagu();
            break;
        }
        case 4:
            tambahPlaylist();
            break;
        case 5:
            lihatPlaylist();
            break;
        case 6:
            restoreLagu();
            break;
        case 7:
            restorePlaylist();
            break;
        case 0:
            return 0;
        default:
            cout << "ERROR: Masukkan input yang valid! " << endl;
            break;
        }
    }
}
