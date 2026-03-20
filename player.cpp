#include "player.h"
#include <sstream>
#include <iomanip>
#include <iostream>

extern string FormattedDuration(Lagu *lagu);

PlayerAction showPlayerGUI(Lagu *song, sf::Music &bgm)
{

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1024, 640), "Sigma Music Player", sf::Style::Default, settings);

    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"))
    {
        if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
        {
            std::cout << "Warning: Font tidak ditemukan! Pastikan path font benar.\n";
        }
    }

    bool isPaused = false;
    PlayerAction action = NONE;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                bgm.stop();
                action = STOP;
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {

                if (event.key.code == sf::Keyboard::Space)
                {
                    if (isPaused)
                    {
                        bgm.play();
                        isPaused = false;
                    }
                    else
                    {
                        bgm.pause();
                        isPaused = true;
                    }
                }

                if (event.key.code == sf::Keyboard::N)
                {
                    action = NEXT;
                    bgm.stop();
                    window.close();
                }

                if (event.key.code == sf::Keyboard::P)
                {
                    action = PREV;
                    bgm.stop();
                    window.close();
                }

                if (event.key.code == sf::Keyboard::Escape)
                {
                    action = STOP;
                    bgm.stop();
                    window.close();
                }
            }
        }

        if (bgm.getStatus() == sf::Music::Stopped && !isPaused && action == NONE)
        {
            action = NEXT;
            window.close();
        }

        window.clear(sf::Color(18, 18, 24));

        sf::RectangleShape headerBg(sf::Vector2f(1024, 80));
        headerBg.setFillColor(sf::Color(25, 25, 35));
        window.draw(headerBg);

        sf::Text headerText("NOW PLAYING", font, 22);
        headerText.setPosition(40, 25);
        headerText.setFillColor(sf::Color(150, 150, 160));
        headerText.setStyle(sf::Text::Bold);
        window.draw(headerText);

        sf::RectangleShape headerLine(sf::Vector2f(1024, 2));
        headerLine.setPosition(0, 80);
        headerLine.setFillColor(sf::Color(40, 40, 60));
        window.draw(headerLine);

        sf::CircleShape albumArt(140);
        albumArt.setPosition(80, 140);
        albumArt.setFillColor(sf::Color(45, 45, 60));

        albumArt.setOutlineThickness(4);
        albumArt.setOutlineColor(sf::Color(65, 65, 85));
        window.draw(albumArt);

        sf::Text noteIcon("", font, 120);
        noteIcon.setPosition(165, 160);
        noteIcon.setFillColor(sf::Color(80, 80, 100));
        window.draw(noteIcon);

        sf::Text title(song->judul, font, 48);
        title.setPosition(420, 160);
        title.setFillColor(sf::Color::White);
        title.setStyle(sf::Text::Bold);
        window.draw(title);

        sf::Text artist(song->penyanyi, font, 32);
        artist.setPosition(420, 230);
        artist.setFillColor(sf::Color(180, 180, 200));
        window.draw(artist);

        stringstream info;
        info << song->genre << "    " << FormattedDuration(song);
        sf::Text details(info.str(), font, 24);
        details.setPosition(420, 290);
        details.setFillColor(sf::Color(120, 120, 140));
        window.draw(details);

        float progressBarWidth = 864.0f;

        sf::RectangleShape barBg(sf::Vector2f(progressBarWidth, 16));
        barBg.setPosition(80, 480);
        barBg.setFillColor(sf::Color(40, 40, 55));
        window.draw(barBg);

        float totalSeconds = (int)song->durasi * 60.0f + ((song->durasi - (int)song->durasi) * 100.0f);
        float progress = 0.0f;

        if (totalSeconds > 0)
        {
            progress = bgm.getPlayingOffset().asSeconds() / totalSeconds;
        }
        if (progress > 1.0f)
            progress = 1.0f;

        sf::RectangleShape barFill(sf::Vector2f(progressBarWidth * progress, 16));
        barFill.setPosition(80, 480);
        barFill.setFillColor(isPaused ? sf::Color(255, 180, 80) : sf::Color(30, 215, 96));
        window.draw(barFill);

        int elapsed = (int)bgm.getPlayingOffset().asSeconds();
        int eMin = elapsed / 60;
        int eSec = elapsed % 60;

        stringstream elapsedStr;
        elapsedStr << setfill('0') << setw(2) << eMin << ":" << setfill('0') << setw(2) << eSec;

        sf::Text elapsedText(elapsedStr.str(), font, 18);
        elapsedText.setPosition(80, 510);
        elapsedText.setFillColor(sf::Color(180, 180, 200));
        window.draw(elapsedText);

        sf::Text totalText(FormattedDuration(song), font, 18);
        totalText.setPosition(890, 510);
        totalText.setFillColor(sf::Color(180, 180, 200));
        window.draw(totalText);

        sf::RectangleShape controlBg(sf::Vector2f(1024, 90));
        controlBg.setPosition(0, 550);
        controlBg.setFillColor(sf::Color(25, 25, 35));
        window.draw(controlBg);

        string status = isPaused ? "PAUSED" : "PLAYING";
        sf::Text statusText(status, font, 24);
        statusText.setPosition(40, 580);
        statusText.setFillColor(isPaused ? sf::Color(255, 180, 80) : sf::Color(30, 215, 96));
        statusText.setStyle(sf::Text::Bold);
        window.draw(statusText);

        sf::Text controlsMenu("[P] Prev    [SPACE] Play/Pause    [N] Next    [ESC] Exit", font, 18);
        controlsMenu.setPosition(480, 582);
        controlsMenu.setFillColor(sf::Color(200, 200, 220));
        window.draw(controlsMenu);

        window.display();
    }

    return action;
}
