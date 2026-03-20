#include "playlist.h"
#include "globals.h"
#include <iostream>
#include <fstream>
#include <sstream>
bool isEmptyPlaylist(Playlist *p)
{
    return p->front == NULL;
}

void enqueuePlaylist(Playlist *p, int idLagu, bool save)
{
    NodeLagu *newSong = new NodeLagu();
    newSong->id = idLagu;
    newSong->next = NULL;

    if (isEmptyPlaylist(p))
    {
        p->front = newSong;
        p->rear = newSong;
    }
    else
    {
        p->rear->next = newSong;
        p->rear = newSong;
    }

    p->size++;
    if (save)
    {
        savePlaylist();
    }
}

int dequeuePlaylist(Playlist *p)
{
    if (isEmptyPlaylist(p))
        return -1;

    int id = p->front->id;

    NodeLagu *tmp = p->front;
    p->front = p->front->next;
    delete tmp;

    p->size--;

    if (p->front == NULL)
    {
        p->rear = NULL;
    }
    return id;
}

Lagu *findLaguById(int id)
{
    if (head == NULL)
        return NULL;

    Lagu *temp = head;
    do
    {
        if (temp->id == id)
        {
            return temp;
        }
        temp = temp->next;
    } while (temp != head);

    return NULL;
}

void savePlaylist()
{
    ofstream file("playlist.txt");

    Playlist *now = headPlaylist;
    while (now != NULL)
    {
        file << "Playlist: " << now->nama << endl;

        NodeLagu *tmp = now->front;
        while (tmp != NULL)
        {
            file << tmp->id;
            if (tmp->next != NULL)
                file << ",";
            tmp = tmp->next;
        }
        now = now->next;
        file << endl;
    }
}

void tambahPlaylist()
{
    string newPL;
    cout << "Masukkan Nama Playlist Baru: ";
    getline(cin, newPL);

    ifstream fileR("playlist.txt");
    string line;
    while (getline(fileR, line))
    {
        if (line.find("Playlist: ") == 0 && newPL == line.substr(10))
        {
            cout << "Playlist sudah terdaftar!" << endl;
            fileR.close();
            return;
        }
    }

    Playlist *new_pl = new Playlist();
    new_pl->nama = newPL;

    if (headPlaylist == NULL)
    {
        headPlaylist = new_pl;
        new_pl->next = NULL;
    }
    else
    {
        Playlist *now = headPlaylist;
        while (now->next != NULL)
        {
            now = now->next;
        }
        now->next = new_pl;
    }

    cout << "Playlist Baru Ditambahkan." << endl
         << endl;
    savePlaylist();
}

void lihatPlaylist()
{
    ifstream file("playlist.txt");
    string line;
    int counter = 1;

    cout << "========== Daftar Playlist ==========" << endl;
    while (getline(file, line))
    {

        if (line.find("Playlist: ") == 0)
        {
            cout << counter << " | " << line.substr(10) << endl;
            counter++;
        }
    }
    if (counter == 1)
    {
        cout << "Belum Ada Playlist yang Terdaftar." << endl;
    }
    cout << "=====================================" << endl;

    if (counter != 1)
    {
        int input;
        cout << "Pilih Opsi untuk dimainkan (0 = kembali): ";
        cin >> input;
        cin.ignore();

        if (input == 0)
        {
            return;
        }

        Playlist *chosen = headPlaylist;
        for (int i = 1; i < input; i++)
        {
            chosen = chosen->next;
            if (chosen == NULL)
            {
                cout << "Masukkan nomor playlist yang valid" << endl;
                return;
            }
        }

        opsiPlaylist(chosen);
    }
    file.close();
}

void loadPlaylist()
{
    ifstream file("playlist.txt");

    if (!file.is_open())
    {
        cout << "file yang dibuka tidak valid!" << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        if (line.substr(0, 10) == "Playlist: ")
        {
            line = line.substr(10);
            Playlist *pl = new Playlist();
            pl->nama = line;
            pl->next = NULL;
            pl->front = NULL;
            pl->rear = NULL;
            pl->size = 0;

            if (headPlaylist == NULL)
            {
                headPlaylist = pl;
                headPlaylist->next = NULL;
            }
            else
            {
                Playlist *now = headPlaylist;
                while (now->next != NULL)
                {
                    now = now->next;
                }
                now->next = pl;
                pl->next = NULL;
            }

            if (getline(file, line))
            {
                stringstream ss(line);
                string id;
                while (getline(ss, id, ','))
                {
                    if (!id.empty())
                        enqueuePlaylist(pl, stoi(id), false);
                }
            }
        }
    }

    file.close();
}

void opsiPlaylist(Playlist *p)
{
    while (true)
    {
        cout << "=============================================" << endl;
        cout << "Playlist: " << p->nama << endl;

        cout << "Daftar Antrean: " << endl;
        cout << "---------------------------------------------" << endl;
        NodeLagu *tmp = p->front;
        for (int i = 0; i < p->size; i++)
        {
            Lagu *lagu = findLaguById(tmp->id);
            cout << i + 1 << "  |  [ID:" << tmp->id << "]" << "  |  " << lagu->judul << endl;
            tmp = tmp->next;
        }

        if (p->size == 0)
        {
            cout << "Belum ada lagu pada playlist ini" << endl;
        }

        char input;
        cout << "---------------------------------------------" << endl;
        cout << "[P]Play | [F]Remove Front | [R]Remove by Id | [D]Delete Playlist | [Q]quit" << endl
             << ">>";
        cin >> input;
        cin.ignore();
        input = toupper(input);

        switch (input)
        {
        case 'P':
        {
            NodeLagu *tmp = p->front;
            while (tmp != NULL)
            {
                Lagu *lagu = findLaguById(tmp->id);
                putarLagu(lagu->fileAudio);
                cout << "-------------------------------------------------" << endl;
                cout << "Lagu diputar: " << lagu->judul << endl;
                cout << "Durasi: " << FormattedDuration(lagu) << endl;
                if (tmp->next != NULL)
                {
                    Lagu *next = findLaguById(tmp->next->id);
                    cout << "Lagu selanjutnya: " << next->judul << endl;
                }
                cout << "-------------------------------------------------" << endl;

                char input;
                cout << "[N]Next | [Quit] >> ";
                cin >> input;
                cin.ignore();

                input = toupper(input);

                if (input == 'Q')
                {
                    bgm.stop();
                    break;
                }
                if (input == 'N')
                {
                    tmp = tmp->next;

                    if (tmp == NULL)
                    {
                        cout << "playlist sudah berakhir" << endl
                             << endl;
                        bgm.stop();
                        break;
                    }
                }

                if (tmp->next != NULL)
                {
                    Lagu *next = findLaguById(tmp->next->id);
                    cout << "Lagu selanjutnya: " << next->judul << endl;
                }
            }
            break;
        }
        case 'R':
        {
            bool deleted = false;
            int input;
            cout << "Hapus Lagu dengan ID: ";
            cin >> input;
            cin.ignore();
            NodeLagu *prev = NULL;
            NodeLagu *tmp = p->front;
            while (tmp != NULL)
            {
                if (tmp->id == input)
                {

                    if (prev == NULL)
                        p->front = tmp->next;
                    else
                        prev->next = tmp->next;

                    if (tmp == p->rear)
                        p->rear = prev;

                    delete tmp;
                    p->size--;
                    savePlaylist();
                    deleted = true;
                    cout << "Lagu berhasil dihapus!" << endl;
                    break;
                }
                prev = tmp;
                tmp = tmp->next;
            }
            if (!deleted)
                cout << "Tidak ada lagu dengan ID tersebut" << endl;
            break;
        }
        case 'F':
        {
            int id = dequeuePlaylist(p);
            Lagu *lagu = findLaguById(id);
            if (lagu)
            {
                cout << "Lagu " << lagu->judul << " Berhasil Dihapus dari Antrean!" << endl;
            }

            savePlaylist();
            break;
        }
        case 'D':
        {
            if (headPlaylist == p)
            {
                headPlaylist = p->next;
            }
            else
            {
                Playlist *tmp = headPlaylist;
                while (tmp->next != p)
                    tmp = tmp->next;
                tmp->next = p->next;
            }
            delete p;
            cout << "Playlist berhasil dihapus!" << endl
                 << endl;
            savePlaylist();
            return;
        }

        case 'Q':
            return;
        default:
            break;
        }
    }
}