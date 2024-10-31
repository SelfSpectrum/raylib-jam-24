#include "game.h"

StateData LoadState(void) // Necesario para cargar todas las cosas que utilizaremos en el juego
{
    StateData state;
    state.screen = SCREEN_LOGO; 
    state.textures[0].tex = LoadTexture("resources/gfx/room.png");
    state.onMachine = false;
    return state;
}
void UnloadState(StateData *state) // Necesario para descargar todas las cosas que fueron cargadas
{
    UnloadTexture(state->textures[0].tex);
}
void Menu(StateData *state)
{
    if (!state->onMachine)
    {
        if (IsKeyPressed(KEY_RIGHT))
        {
            state->wall++;
            ChangeSelection(state);
        }
        if (IsKeyPressed(KEY_LEFT))
        {
            state->wall--;
            ChangeSelection(state);
        }
        if (IsKeyPressed(KEY_DOWN))
        {
            state->lookCeil = false;
            ChangeSelection(state);
        }
        if (IsKeyPressed(KEY_UP))
        {
            state->lookCeil = true;
            ChangeSelection(state);
        }
    }
}
void ChangeSelection(StateData *state)
{
    if (state->wall < 0) state->wall += 4;
    else if (state->wall > 3) state->wall -= 4;
    if (state->lookCeil)
        state->bg = (Sprite) { 0, (Rectangle) { 800.0f, 450.0f, 800.0f, 450.0f }, (Rectangle) { 0.0f, 0.0f, 800.0f, 450.0f }, (Vector2) { 0.0f, 0.0f }, 0.0f, false };
    else
    {
        switch (state->wall)
        {
            case 0:
            {
                state->bg = (Sprite) { 0, (Rectangle) { 0.0f, 0.0f, 800.0f, 450.0f }, (Rectangle) { 0.0f, 0.0f, 800.0f, 450.0f }, (Vector2) { 0.0f, 0.0f }, 0.0f, false };
            } break;
            case 1:
            {
                state->bg = (Sprite) { 0, (Rectangle) { 0.0f, 450.0f, 800.0f, 450.0f }, (Rectangle) { 0.0f, 0.0f, 800.0f, 450.0f }, (Vector2) { 0.0f, 0.0f }, 0.0f, false };
            } break;
            case 2:
            {
                state->bg = (Sprite) { 0, (Rectangle) { 0.0f, 900.0f, 800.0f, 450.0f }, (Rectangle) { 0.0f, 0.0f, 800.0f, 450.0f }, (Vector2) { 0.0f, 0.0f }, 0.0f, false };
            } break;
            case 3:
            {
                state->bg = (Sprite) { 0, (Rectangle) { 800.0f, 0.0f, 800.0f, 450.0f }, (Rectangle) { 0.0f, 0.0f, 800.0f, 450.0f }, (Vector2) { 0.0f, 0.0f }, 0.0f, false };
            } break;
            default:
            {
                    state->bg = (Sprite) { 0, (Rectangle) { 800.0f, 450.0f, 800.0f, 450.0f }, (Rectangle) { 0.0f, 0.0f, 800.0f, 450.0f }, (Vector2) { 0.0f, 0.0f }, 0.0f, false };
            }
        }
    }
}
void ChangeScreen(StateData *state, GameScreen screen)
{
    state->screen = screen;
    switch (state->screen)
    {
        default:
            state->bg = (Sprite) { 0, (Rectangle) { 0.0f, 0.0f, 800.0f, 450.0f }, (Rectangle) { 0.0f, 0.0f, 800.0f, 450.0f }, (Vector2) { 0.0f, 0.0f }, 0.0f, false };
    }
}
