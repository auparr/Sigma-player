#include "lagu.h"
#include "globals.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

void update()
{
    ofstream file("lagu.txt");

    if (head == NULL)
    {
        file.close();
        return;
    }
    Lagu *now = head;
    do
    {
        file << now->id << "|" << now->judul << "|" << now->penyanyi << "|" << now->durasi << "|" << now->genre << "|" << now->fileAudio << endl;
        now = now->next;
    } while (now != head);

    file.close();
}
bool validDuration(string duration)
{
    size_t titik = duration.find('.');

    if (titik == string::npos)
    {
        cout << "ERROR: Format harus menit.detik (contoh: 4.30)!" << endl;
        return false;
    }

    string menit = duration.substr(0, titik);
    string detik = duration.substr(titik + 1);
    if (stoi(detik) >= 60 || (detik.length() > 2))
    {
        cout << "ERROR: Masukkan Input Yang Valid!" << endl;
        return false;
    }

    return true;
}

string FormattedDuration(Lagu *lagu)
{
    stringstream ss;
    int menit = (int)lagu->durasi;
    int detik = (int)((lagu->durasi - menit) * 100);

    ss << setfill('0') << setw(2) << menit << ":" << setfill('0') << setw(2) << detik;

    return ss.str();
}

void loadSongs()
{
    ifstream file("lagu.txt");

    if (file.is_open() == false)
    {
        cout << "File lagu.txt belum ada!" << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string section;

        Lagu *now = new Lagu();

        getline(ss, section, '|');
        now->id = stoi(section);

        getline(ss, section, '|');
        now->judul = section;

        getline(ss, section, '|');
        now->penyanyi = section;

        getline(ss, section, '|');
        now->durasi = stof(section);

        getline(ss, section, '|');
        now->genre = section;

        getline(ss, section);
        now->fileAudio = section;

        if (head == NULL)
        {
            now->next = now;
            now->prev = now;
            head = now;
            tail = now;
        }
        else
        {
            now->prev = tail;
            now->next = head;

            head->prev = now;
            tail->next = now;

            tail = now;
        }
    }
    file.close();
}

void tambahLagu()
{
    // TODO: Implementasi Circular Doubly Linked List
    // TODO: Validasi input durasi float
    // TODO: Simpan ke lagu.txt
    Lagu *laguBaru = new Lagu;

    if (head == NULL)
    {
        laguBaru->id = 1;
    }
    else
    {
        laguBaru->id = tail->id + 1;
    }

    cout << "Masukkan Judul Lagu: ";
    getline(cin, laguBaru->judul);

    cout << "Masukkan Penyanyi: ";
    getline(cin, laguBaru->penyanyi);

    string durasi;
    cout << "Masukkan Durasi (menit.detik): ";
    getline(cin, durasi);

    while (!validDuration(durasi))
    {
        cout << "Masukkan Durasi (menit.detik): ";
        getline(cin, durasi);
    }
    laguBaru->durasi = stof(durasi);

    cout << "Masukkan Genre: ";
    getline(cin, laguBaru->genre);

    cout << "Masukkan Nama File mp3(opsional, kosongkan jika tidak ada): ";
    getline(cin, laguBaru->fileAudio);

    if (head == NULL)
    {
        laguBaru->next = laguBaru;
        laguBaru->prev = laguBaru;

        head = laguBaru;
        tail = laguBaru;
    }
    else
    {
        laguBaru->prev = tail;
        laguBaru->next = head;

        head->prev = laguBaru;
        tail->next = laguBaru;

        tail = laguBaru;
    }

    update();

    cout << "\n[Update]Lagu Baru Berhasil Ditambahkan!\n"
         << endl;
}

void lihatDaftarLagu()
{
    // TODO: Baca dari linked list dan format output durasi menjadi MM:SS

    if (head == NULL)
    {
        cout << "daftar lagu masih kosong, silahkan tambah lagu terlebih dahulu!" << endl;
        return;
    }
    cout << endl
         << endl;
    cout << "================= Sigma Music Player's Playlist ===============" << endl;
    cout << "ID   |    Judul    |    Penyanyi    |    Durasi    |      Genre" << endl;
    cout << "---------------------------------------------------------------" << endl;
    Lagu *now = head;
    do
    {
        cout << now->id << "  |  " << now->judul << "  |  " << now->penyanyi << "  |  " << FormattedDuration(now) << "  |  " << now->genre << endl;
        now = now->next;
    } while (now != head);
    cout << "===============================================================" << endl
         << endl;
}

void navigasiLagu()
{
    // TODO: Implementasi navigasi Next (N), Prev (P), Edit (E), Delete (D), Quit (Q)
    // Hint: Panggil putarLagu(nodeSaatIni->fileAudio) saat berpindah lagu!

    if (head == NULL)
    {
        cout << "Daftar musik masih kosong!" << endl;
        return;
    }

    Lagu *now = head;
    putarLagu(now->fileAudio);

    while (true)
    {
        cout << "========== Navigasi Lagu ==========" << endl;
        cout << "ID       |  " << now->id << endl;
        cout << "Judul    |  " << now->judul << endl;
        cout << "Penyanyi |  " << now->penyanyi << endl;
        cout << "Durasi   |  " << FormattedDuration(now) << endl;
        cout << "Genre    |  " << now->genre << endl;

        char input;
        cout << "[P]Previous | [N]Next | [E]Edit | | [A]Add to Playlist [D]Delete | [Q]Quit" << endl;
        cout << ">> ";
        cin >> input;
        cin.ignore();

        input = toupper(input);

        string inputBaru;
        switch (input)
        {
        case 'P':

            now = now->prev;
            putarLagu(now->fileAudio);
            continue;

        case 'N':
            now = now->next;
            putarLagu(now->fileAudio);
            continue;

        case 'E':
        {

            cout << "Judul (" << now->judul << "): ";
            getline(cin, inputBaru);

            if (!inputBaru.empty())
            {
                now->judul = inputBaru;
            }

            cout << "Penyanyi (" << now->penyanyi << "): ";
            getline(cin, inputBaru);

            if (!inputBaru.empty())
            {
                now->penyanyi = inputBaru;
            }

            cout << "Durasi (" << FormattedDuration(now) << "): ";
            getline(cin, inputBaru);

            if (!inputBaru.empty() && validDuration(inputBaru))
            {
                now->durasi = stof(inputBaru);
            }

            cout << "Genre (" << now->genre << "): ";
            getline(cin, inputBaru);

            if (!inputBaru.empty())
            {
                now->genre = inputBaru;
            }

            update();

            cout << "\nData Musik Berhasil Diupdate!\n";
            continue;
        }
        case 'A':
        {
            if (headPlaylist == NULL)
            {
                cout << "Belum ada playlist" << endl;
                continue;
            }

            cout << "======== Daftar Playlist ========" << endl;
            Playlist *tmp = headPlaylist;
            int index = 1;
            while (tmp != NULL)
            {
                cout << index << ". " << tmp->nama << endl;
                tmp = tmp->next;
                index++;
            }
            cout << "==================================" << endl;

            int input;
            cout << "Silahkan pilih playlist: ";
            cin >> input;
            cin.ignore();

            tmp = headPlaylist;

            for (int i = 1; i < input; i++)
            {
                tmp = tmp->next;
            }

            if (tmp == NULL)
            {
                cout << "Playlist tidak valid" << endl;
                continue;
            }

            enqueuePlaylist(tmp, now->id);
            cout << "Lagu \"" << now->judul
                 << "\" berhasil ditambahkan ke \""
                 << tmp->nama << "\"!\n";
            break;
        }
        case 'D':
        {

            char confirm;
            cout << "Apakah anda yakin ingin menghapus lagu ini? (y/n): ";
            cin >> confirm;
            cin.ignore();

            confirm = toupper(confirm);

            if (confirm != 'Y')
            {
                cout << "Penghapusan dibatalkan." << endl;
                continue;
            }

            pushLagu(now);

            if (now->next == now)
            {
                delete now;
                head = NULL;
                tail = NULL;
                now = NULL;

                bgm.stop();
                update();
                cout << "\nMusik Terakhir Dihapus!\n";
                return;
            }

            Lagu *nextSong = now->next;

            now->prev->next = now->next;
            now->next->prev = now->prev;

            if (now == head)
            {
                head = now->next;
            }

            if (now == tail)
            {
                tail = now->prev;
            }

            delete now;
            now = nextSong;

            bgm.stop();
            update();
            putarLagu(now->fileAudio);

            cout << "\nMusik Berhasil Dihapus!\n";
            continue;
        }

        case 'Q':
            bgm.stop();
            return;

        default:
            cout << "\n[Warning]Masukkan Input Yang Valid!\n";
            break;
        }
    }
}

void pushLagu(Lagu *lagu)
{

    StackLagu *newNode = new StackLagu();

    newNode->data = new Lagu();
    newNode->data->id = lagu->id;
    newNode->data->judul = lagu->judul;
    newNode->data->penyanyi = lagu->penyanyi;
    newNode->data->durasi = lagu->durasi;
    newNode->data->genre = lagu->genre;
    newNode->data->fileAudio = lagu->fileAudio;
    newNode->data->next = NULL;
    newNode->data->prev = NULL;

    newNode->next = topLagu;
    topLagu = newNode;
}

Lagu *popLagu()
{
    if (topLagu == NULL)
    {
        return NULL;
    }

    StackLagu *temp = topLagu;
    Lagu *lagu = temp->data;

    topLagu = topLagu->next;
    delete temp;

    return lagu;
}

bool isEmptyStackLagu()
{
    return topLagu == NULL;
}

void restoreLagu()
{
    if (isEmptyStackLagu())
    {
        cout << "Tidak ada lagu yang bisa di restore" << endl;
        return;
    }

    Lagu *lagu = popLagu();

    if (head == NULL)
    {
        lagu->next = lagu;
        lagu->prev = lagu;
        head = lagu;
        tail = lagu;
    }
    else
    {
        lagu->prev = tail;
        lagu->next = head;

        head->prev = lagu;
        tail->next = lagu;

        tail = lagu;
    }

    update();

    cout << "Lagu \"" << lagu->judul << "\" berhasil dipulihkan!" << endl;
}