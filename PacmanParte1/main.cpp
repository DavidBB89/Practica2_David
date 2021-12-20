#include "Map.h"
#include "Enemy.h"
#include "TimeManager.h"
#include <vector>
#include "CustomList.h"
#include "CustomVector.h"

/// <summary>
/// Sets the needed variables
/// </summary>
void Setup();
/// <summary>
/// Handles the inputs
/// </summary>
void Input();
/// <summary>
/// Handles the logic of the game
/// </summary>
void Logic();
/// <summary>
/// Draws the screen
/// </summary>
void Draw();

enum USER_INPUTS { NONE, UP, DOWN, RIGHT, LEFT, QUIT };
Map pacman_map = Map();
std::vector<Enemy> enemies;
char player_char = 'O';
int player_x = 1;
int player_y = 1;
int player_points = 0;
USER_INPUTS input = USER_INPUTS::NONE;
bool run = true;
bool win = false;

int main()
{
    //CustomList lista = CustomList();
   /*CustomVector lista;
    for (size_t i = 0; i < 20; i++)
    {
        lista.Add(i);
    }
    for (size_t i = 0; i < lista.Length(); i++)
    {
        std::cout << lista.At(i) << std::endl;
    }*/

    Setup();
    while (run)
    {
        Input();
        Logic();
        Draw();
    }
}
void Setup()
{
    std::cout.sync_with_stdio(false);
    srand(time(NULL));
    player_x = pacman_map.spawn_player.X;
    player_y = pacman_map.spawn_player.Y;

    int totalEnemies = 0;
    std::cout << "¿Cuantos enemigos quieres?";
    std::cin >> totalEnemies;
    if (totalEnemies < 1) totalEnemies = 1;
    for (size_t i = 0; i < totalEnemies; i++)
    {
        enemies.push_back(Enemy(pacman_map.spawn_enemy, 5.0f * i));
    }
}
void Input()
{
    input = USER_INPUTS::NONE;
    if (ConsoleUtils::KeyPressed(VK_UP) || ConsoleUtils::KeyPressed('W'))
    {
        input = USER_INPUTS::UP;
    }
    if (ConsoleUtils::KeyPressed(VK_DOWN) || ConsoleUtils::KeyPressed('S'))
    {
        input = USER_INPUTS::DOWN;
    }
    if (ConsoleUtils::KeyPressed(VK_RIGHT) || ConsoleUtils::KeyPressed('D'))
    {
        input = USER_INPUTS::RIGHT;
    }
    if (ConsoleUtils::KeyPressed(VK_LEFT) || ConsoleUtils::KeyPressed('A'))
    {
        input = USER_INPUTS::LEFT;
    }
    if (ConsoleUtils::KeyPressed(VK_ESCAPE) || ConsoleUtils::KeyPressed('Q'))
    {
        input = USER_INPUTS::QUIT;
    }
}
void Logic()
{
    if (win)
    {
        switch (input)
        {
        case QUIT:
            run = false;
            break;
        }
    }
    else
    {
        int player_y_new = player_y;
        int player_x_new = player_x;
        switch (input)
        {
        case UP:
            player_y_new--;
            break;
        case DOWN:
            player_y_new++;
            break;
        case RIGHT:
            player_x_new++;
            break;
        case LEFT:
            player_x_new--;
            break;
        case QUIT:
            run = false;
            break;
        }
        if (player_x_new < 0)
        {
            player_x_new = pacman_map.Width - 1;
        }
        player_x_new %= pacman_map.Width;
        if (player_y_new < 0)
        {
            player_y_new = pacman_map.Height - 1;
        }
        player_y_new %= pacman_map.Height;

        switch (pacman_map.GetTile(player_x_new, player_y_new))
        {
        case Map::MAP_TILES::MAP_WALL:
            player_y_new = player_y;
            player_x_new = player_x;
            break;
        case Map::MAP_TILES::MAP_POINT:
            pacman_map.points--;
            player_points++;
            pacman_map.SetTile(player_x_new, player_y_new, Map::MAP_TILES::MAP_EMPTY);
            break;
        case Map::MAP_TILES::MAP_POWERUP:
            player_points += 100;
            pacman_map.SetTile(player_x_new, player_y_new, Map::MAP_TILES::MAP_EMPTY);
            for (size_t i = 0; i < enemies.size(); i++)
            {
                enemies[i].PowerUpPicked();
            }
            break;
        }

        player_y = player_y_new;
        player_x = player_x_new;
        if (pacman_map.points <= 0)
        {
            win = true;
        }
        for (size_t i = 0; i < enemies.size(); i++)
        {
            switch (enemies[i].Update(&pacman_map, { (short)player_x , (short)player_y }))
            {
            case Enemy::ENEMY_STATE::ENEMY_EATED:
                player_x = pacman_map.spawn_player.X;
                player_y = pacman_map.spawn_player.Y;
                break;
            case Enemy::ENEMY_STATE::ENEMY_KILLED:
                enemies[i].Kill();
                player_points += 50;
                break;
            default:
                break;
            }
        }
    }
}
void Draw()
{
    ConsoleUtils::Console_SetPos(0,0);
    pacman_map.Draw();
    ConsoleUtils::Console_SetPos(player_x, player_y);
    ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::DARK_YELLOW);
    std::cout << player_char;
    for (size_t i = 0; i < enemies.size(); i++)
    {
        enemies[i].Draw();
    }
    ConsoleUtils::Console_ClearCharacter({ 0,(short)pacman_map.Height });
    ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::CYAN);
    std::cout << "Puntuacion actual: " << player_points << " Puntuacion pendiente: " << pacman_map.points << std::endl;
    if (win)
    {
        ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::GREEN);
        std::cout << "Has ganado!" << std::endl;
    }
    std::cout << TimeManager::getInstance().frameCount << std::endl;
    std::cout << TimeManager::getInstance().deltaTime << std::endl;
    std::cout << TimeManager::getInstance().time << std::endl;

    TimeManager::getInstance().NextFrame();
}