#include "Tetris.hpp"

int main()
{
    Tetris_Game tetris;
    tetris.Run();

    return 0;

    // using namespace Tetris;
    // Tetris::Engine eng;
    // sf::RenderWindow window(sf::VideoMode(WIDTH_FIELD_PIXELS + 100, HEIGHT_FIELD_PIXELS), "Tetris", sf::Style::Close | sf::Style::Titlebar);
    // window.setFramerateLimit(60);

    // while (window.isOpen())
    // {
    //     sf::Event window_event;
    //     while (window.pollEvent(window_event))
    //     {
    //         if (window_event.type == sf::Event::Closed)
    //         {
    //             window.close();
    //         }
    //         if (window_event.type == sf::Event::KeyPressed)
    //         {
    //             if (window_event.key.code == sf::Keyboard::Up)
    //             {
    //                 eng.Move(StateMovement::Rotate, 0, 0);
    //             }
    //             else if (window_event.key.code == sf::Keyboard::Down)
    //             {
    //                 eng.Move(StateMovement::Move, 0, 1);
    //             }
    //             else if (window_event.key.code == sf::Keyboard::Space)
    //             {
    //                 eng.SetTimeFall(TIME_FALL_SPACE);
    //             }
    //             else if (window_event.key.code == sf::Keyboard::Left)
    //             {
    //                 eng.Move(StateMovement::Move, -1, 0);
    //             }
    //             else if (window_event.key.code == sf::Keyboard::Right)
    //             {
    //                 eng.Move(StateMovement::Move, 1, 0);
    //             }
    //             else if (window_event.key.code == sf::Keyboard::Escape)
    //             {
    //                 window.close();
    //             }
    //         }
    //         else if (window_event.type == sf::Event::KeyReleased)
    //         {
    //             if (window_event.key.code == sf::Keyboard::Space)
    //             {
    //                 eng.SetTimeFall(TIME_FALL);
    //             }
    //         }
    //         else
    //         {
    //         }
    //     }
    //     window.clear(sf::Color::White);
    //     eng.Render(window);
    //     eng.Update();
    //     window.display();
    // }
    // return 0;
}