#include "Header.h"

using namespace std;

int Menu(RenderWindow& window, Game& game);
int processingResult(RenderWindow& window, Game& game, int res);

int main()
{
    FreeConsole();
    RenderWindow window(VideoMode(254 + 15, 290), "MineSweeper", Style::Close);
    window.setKeyRepeatEnabled(false);

    Font font;
    font.loadFromFile("Fonts/Calibri.ttf");

    Game game = Game(1);
    Interface interf;
    DownDropMenu DDMenu;

    Clock gameTimeClock;
    int gameTime = 0;

    //Menu(window, game);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == event.KeyReleased) {
                if (event.key.code == Keyboard::F1) {
                    int result = Menu(window, game);
                    if (result == 2) {
                        gameTimeClock.restart();
                        gameTime = 0;
                    }
                    else if (result == 1) {

                    }
                }
                else if (event.key.code == Keyboard::Escape) {
                    window.close();
                }
            }
            else if (event.type == event.MouseButtonPressed) {
                Vector2i mousePos = sf::Mouse::getPosition(window);
                if (event.key.code == Mouse::Left ) {
                    if (!game.stop() && !DDMenu.getDDMenuStatus()) {
                        int px = (mousePos.x - 10) / Cell::size;
                        int py = (mousePos.y - 81) / Cell::size;
                        game.OpenCell(py, px);
                    }
                    DDMenu.setDDMenuStatus(mousePos.x, mousePos.y);
                    int res = DDMenu.selectOption(mousePos.x, mousePos.y);
                    if (processingResult(window, game, res) == 1) {//if new game
                        gameTimeClock.restart();
                        gameTime = 0;
                    }
                }
                else if (event.key.code == Mouse::Right && !game.stop() && !DDMenu.getDDMenuStatus()) {
                    int px = (mousePos.x - 10) / Cell::size;
                    int py = (mousePos.y - 81) / Cell::size;
                    game.SetSelfStatus(py, px);
                }
            }

            interf.setSubMenuStatus(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
            if (DDMenu.getDDMenuStatus())DDMenu.setDDMenuStatus(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
        }
        

        if (game.GetIsGameRun())gameTime = gameTimeClock.getElapsedTime().asSeconds();
        else gameTimeClock.restart();
        if (gameTime > 998)game.losing(2);

        Text timeInGame(to_string(999 - gameTime), font, 18);
        timeInGame.setStyle(Text::Bold);
        timeInGame.setFillColor(Color::Red);
        timeInGame.setPosition(Vector2f(window.getSize().x - 55, 36));

        /*if (Keyboard::isKeyPressed(Keyboard::Key::F2)) {
            window.setSize(Vector2u(274, 224));
            game.newGame(1);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Key::F3)) {
            window.setSize(Vector2u(500, 500));
            game.newGame(2);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Key::F4)) {
            window.setSize(Vector2u(800, 800));
            game.newGame(3);
        }*/
        
        window.clear();
        window.draw(interf);
        window.draw(timeInGame);
        window.draw(game);
        window.draw(DDMenu);
        window.display();
    }

    return 0;
}

int Menu(RenderWindow& window, Game& game) {//0 - nothing have changed, 1 - level was restarted, 2 - level has changed
    Font font;
    font.loadFromFile("Fonts/Calibri.ttf");
    Color TextColor(Color::Red);

    Vector2u WinSize = window.getSize();
    //text New Game
    Text textNewGame(L"����� ����", font, 30);
    textNewGame.setStyle(Text::Bold);
    textNewGame.setOrigin(textNewGame.getLocalBounds().width / 2, textNewGame.getLocalBounds().height / 2);
    textNewGame.setPosition(Vector2f(WinSize.x / 2, WinSize.y / 2 - 50));

    //text Restart Game
    Text textRestart(L"������", font, 30);
    textRestart.setStyle(Text::Bold);
    textRestart.setOrigin(textRestart.getLocalBounds().width / 2, textRestart.getLocalBounds().height / 2);
    textRestart.setPosition(Vector2f(WinSize.x / 2, WinSize.y / 2));

    //text Exit
    Text textExit(L"�����", font, 30);
    textExit.setStyle(Text::Bold);
    textExit.setOrigin(textExit.getLocalBounds().width / 2, textExit.getLocalBounds().height / 2);
    textExit.setPosition(Vector2f(WinSize.x / 2, WinSize.y / 2 + 50));

    int levelMenu = 0;//0 - not level select, 1 - select type of level, custome level options

    while (window.isOpen())
    {
        textNewGame.setFillColor(TextColor);
        textRestart.setFillColor(TextColor);
        textExit.setFillColor(TextColor);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            else if (event.type == event.MouseButtonPressed) {
                if (event.key.code == Mouse::Left) {
                    Vector2i localPosition = sf::Mouse::getPosition(window);
                    int x = localPosition.x;
                    int y = localPosition.y;

                    if (levelMenu == 0) {
                        if (x > 0 && x < 100 && y>0 && y < 100) {//new game

                        }
                        else if (x > 0 && x < 100 && y>0 && y < 100) {//restart

                        }
                        else if (x > 0 && x < 100 && y>0 && y < 100) {//exit

                        }
                    }
                    else if (levelMenu == 1) {//select type of level

                    }
                    else {//custome level options

                    }
                }
            }
            if (event.type == event.KeyReleased) {
                if (event.key.code == Keyboard::F2) {
                    window.create(VideoMode(254 + 15, 290), "MineSweeper", Style::Close);
                    game.newGame(1);
                    return 2;
                }
                else if (event.key.code == Keyboard::F3) {
                    window.create(VideoMode(504 + 15, 415), "MineSweeper", Style::Close);
                    game.newGame(2);
                    return 2;
                }
                else if (event.key.code == Keyboard::F4) {
                    window.create(VideoMode(829 + 15, 590), "MineSweeper", Style::Close);
                    game.newGame(3);
                    return 2;
                }
            }
        }
        // ������ ����� �������� ����
        RectangleShape shape(Vector2f(WinSize.x, WinSize.y));
        shape.setOutlineThickness(-4.f);
        shape.setOutlineColor(Color::Black);
        shape.setFillColor(Color(15, 140, 9));
        window.draw(shape);

        

        window.draw(textNewGame);
        window.draw(textRestart);
        window.draw(textExit);
        window.display();
    }
}

int processingResult(RenderWindow& window, Game& game, int res){
    if (res == 0) {
        return 0;
    }
    else if (res == 1) {
        res = 2 + game.GetLevel();
    }
    else if (res == 2) {
        //Open cells algorinhm
    }
    
    if (res == 3) {
        window.create(VideoMode(254 + 15, 290), "MineSweeper", Style::Close);
        game.newGame(1);
        return 1;
    }
    else if (res == 4) {
        window.create(VideoMode(504 + 15, 415), "MineSweeper", Style::Close);
        game.newGame(2);
        return 1;
    }
    else if (res == 5) {
        window.create(VideoMode(829 + 15, 590), "MineSweeper", Style::Close);
        game.newGame(3);
        return 1;
    }
    else if (res == 6) {
        return Menu(window, game);
    }
    else if (res == 7) {
        return Menu(window, game);
    }
    else if (res == 8) {
        window.close();
        return 0;
    }

}
