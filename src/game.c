#include "game.h"

StateData LoadState(void) // Necesario para cargar todas las cosas que utilizaremos en el juego
{
    int i = 0;
    StateData state = { 0 };
    state.screen = SCREEN_LOGOBLINK; 
    state.logoPositionX = GetScreenWidth()/2 - 128;
    state.logoPositionY = GetScreenHeight()/2 - 128;
    state.framesCounter = 0;
    state.letterCount = 0;
    state.sideRect = (Rectangle){ 16.0f, 16.0f, 16.0f, 16.0f };
    state.textures[0] = LoadTexture("resources/gfx/room.png");
    for ( ; i < OBJ_SIZE; i++) state.interactuable[i].isValid = false;
    state.onMachine = false;
    return state;
}
void UnloadState(StateData *state) // Necesario para descargar todas las cosas que fueron cargadas
{
    UnloadTexture(state->textures[0]);
}
void Menu(StateData *state)
{
    if (IsKeyPressed(KEY_RIGHT) && !state->lookCeil)
    {
        state->wall++;
        ChangeSelection(state);
    }
    if (IsKeyPressed(KEY_LEFT) && !state->lookCeil)
    {
        state->wall--;
        ChangeSelection(state);
    }
    if (IsKeyPressed(KEY_DOWN))
    {
        ChangeScreen(state, SCREEN_ROOM);
    }
    if (IsKeyPressed(KEY_UP))
    {
        ChangeScreen(state, SCREEN_CEILING);
    }
}
void ChangeSelection(StateData *state)
{
    if (state->wall < 0) state->wall += 4;
    else if (state->wall > 3) state->wall -= 4;
    int i = 0;
    for ( ; i < OBJ_SIZE; i++) state->interactuable[i].isValid = false;
    switch (state->wall)
    {
        case 0:
        {
            state->bg = (Sprite){ 0, (Rectangle) { 0.0f, 0.0f, 800.0f, 450.0f }, (Rectangle){ 0.0f, 0.0f, 800.0f, 450.0f }, (Vector2){ 0.0f, 0.0f }, 0.0f };
            state->interactuable[0].sprite = (Sprite){ 0, (Rectangle){ 1600.0f, 450.0f, 128.0f, 142.0f }, (Rectangle){ 235.0f, 200.0f, 128.0f, 142.0f }, (Vector2){ 0.0f, 0.0f }, 0.0f };
            state->interactuable[0].spriteOn = (Sprite){ 0, (Rectangle){ 1728.0f, 450.0f, 128.0f, 142.0f }, (Rectangle){ 235.0f, 200.0f, 128.0f, 142.0f }, (Vector2){ 0.0f, 0.0f }, 0.0f };
            state->interactuable[0].isHover = false;
            state->interactuable[0].isValid = true;
        } break;
        case 1:
        {
            state->bg = (Sprite){ 0, (Rectangle) { 0.0f, 450.0f, 800.0f, 450.0f }, (Rectangle){ 0.0f, 0.0f, 800.0f, 450.0f }, (Vector2){ 0.0f, 0.0f }, 0.0f };
        } break;
        case 2:
        {
            state->bg = (Sprite){ 0, (Rectangle) { 0.0f, 900.0f, 800.0f, 450.0f }, (Rectangle){ 0.0f, 0.0f, 800.0f, 450.0f }, (Vector2){ 0.0f, 0.0f }, 0.0f };
        } break;
        case 3:
        {
            state->bg = (Sprite){ 0, (Rectangle) { 800.0f, 0.0f, 800.0f, 450.0f }, (Rectangle){ 0.0f, 0.0f, 800.0f, 450.0f }, (Vector2){ 0.0f, 0.0f }, 0.0f};
        } break;
        default:
        {
            state->bg = (Sprite){ 0, (Rectangle){ 800.0f, 450.0f, 800.0f, 450.0f }, (Rectangle){ 0.0f, 0.0f, 800.0f, 450.0f }, (Vector2){ 0.0f, 0.0f }, 0.0f };
        }
    }
}
void ChangeScreen(StateData *state, GameScreen screen)
{
    state->screen = screen;
    switch (state->screen)
    {
        case SCREEN_LOGOLEFTTOP:
        {
            state->framesCounter = 0; // Reinicio el contador para reutilizarlo
        } break;
        case SCREEN_ROOM:
        {
            ChangeSelection(state);
        } break;
        case SCREEN_CEILING:
        {
            int i = 0;
            for ( ; i < OBJ_SIZE; i++) state->interactuable[i].isValid = false;
            state->bg = (Sprite){ 0, (Rectangle){ 800.0f, 450.0f, 800.0f, 450.0f }, (Rectangle){ 0.0f, 0.0f, 800.0f, 450.0f }, (Vector2){ 0.0f, 0.0f }, 0.0f };
        } break;
        default:
        {
        } break;
    }
}
void UpdateState(StateData *state)
{
    switch (state->screen)
    {
        case SCREEN_LOGOBLINK:
        {
            state->framesCounter++;
            if (state->framesCounter >= 120) ChangeScreen(state, SCREEN_LOGOLEFTTOP);
        } break;
        case SCREEN_LOGOLEFTTOP:
        {
            state->sideRect.width += 4;
            state->sideRect.height += 4;
            if (state->sideRect.width >= 256) ChangeScreen(state, SCREEN_LOGORIGHTBOT);
        } break;
        case SCREEN_LOGORIGHTBOT:
        {
            state->sideRect.x += 4;
            state->sideRect.y += 4;
            if (state->sideRect.x >= 256) ChangeScreen(state, SCREEN_LOGOLETTER);
        } break;
        case SCREEN_LOGOLETTER:
        {
            state->framesCounter++;
            if (state->letterCount < 10 && state->framesCounter/12)       // Every 12 frames, one more letter!
            {
                state->letterCount++;
                state->framesCounter = 0;
            }
            if (state->framesCounter >= 60) ChangeScreen(state, SCREEN_ROOM);
        } break;
        case SCREEN_ROOM:
        case SCREEN_CEILING:
        {
            state->mousePos = GetMousePosition();
            Menu(state);
            UpdateInteractuable(state);
        } break;
        default:
        {
        } break;
    }
}
void UpdateInteractuable(StateData *state)
{
    int i = 0;
    for ( ; i < OBJ_SIZE; i++)
    {
        if (CheckCollisionPointRec(state->mousePos, state->interactuable[i].sprite.dest))
        {
            state->interactuable[i].isHover = true;
        }
        else state->interactuable[i].isHover = false;
    }
}
void DrawState(StateData *state)
{
    switch (state->screen)
    {
        case SCREEN_LOGOBLINK:
        {
            if ((state->framesCounter/15)%2) DrawRectangle(state->logoPositionX, state->logoPositionY, 16, 16, COLOR_7);
        } break;
        case SCREEN_LOGOLEFTTOP:
        {
            DrawRectangle(state->logoPositionX, state->logoPositionY, state->sideRect.width, 16, COLOR_7);
            DrawRectangle(state->logoPositionX, state->logoPositionY, 16, state->sideRect.height, COLOR_7);
        } break;
        case SCREEN_LOGORIGHTBOT:
        {
            DrawRectangle(state->logoPositionX, state->logoPositionY, state->sideRect.width, 16, COLOR_7);
            DrawRectangle(state->logoPositionX, state->logoPositionY, 16, state->sideRect.height, COLOR_7);
            DrawRectangle(state->logoPositionX + 240, state->logoPositionY, 16, state->sideRect.y, COLOR_7);
            DrawRectangle(state->logoPositionX, state->logoPositionY + 240, state->sideRect.x, 16, COLOR_7);
        } break;
        case SCREEN_LOGOLETTER:
        {
            DrawRectangle(state->logoPositionX, state->logoPositionY, state->sideRect.width, 16, COLOR_7);
            DrawRectangle(state->logoPositionX, state->logoPositionY + 16, 16, state->sideRect.height - 32, COLOR_7);
        
            DrawRectangle(state->logoPositionX + 240, state->logoPositionY + 16, 16, state->sideRect.y - 32, COLOR_7);
            DrawRectangle(state->logoPositionX, state->logoPositionY + 240, state->sideRect.x, 16, COLOR_7);
        
            DrawRectangle(GetScreenWidth()/2 - 112, GetScreenHeight()/2 - 112, 224, 224, COLOR_1);
        
            DrawText(TextSubtext("raylib", 0, state->letterCount), GetScreenWidth()/2 - 44, GetScreenHeight()/2 + 48, 50, COLOR_7);
        } break;
        case SCREEN_ROOM:
        case SCREEN_CEILING:
        {
            DrawTexturePro(state->textures[state->bg.textureIndex], state->bg.source, state->bg.dest, state->bg.origin, state->bg.rotation, WHITE);
            // Aquí se dibujan los accesorios interactuables, podría ser mejor, pero que paja, no me da el cuerpo
            DrawInteractuable(state);
        } break;
        default:
        {
        } break;
    }
}
void DrawInteractuable(StateData *state)
{
    int i = 0;
    bool isValid = false;
    bool isHover = false;
    Sprite sprite = { 0 };
    for ( ; i < OBJ_SIZE; i++)
    {
        isValid = state->interactuable[i].isValid;
        isHover = state->interactuable[i].isHover;
        sprite = state->interactuable[i].sprite;
        if (isValid && !isHover)
        {
            sprite = state->interactuable[i].sprite;
            DrawTexturePro(state->textures[sprite.textureIndex], sprite.source, sprite.dest, sprite.origin, sprite.rotation, WHITE);
        }
        if (isValid && isHover)
        {
            sprite = state->interactuable[i].spriteOn;
            DrawTexturePro(state->textures[sprite.textureIndex], sprite.source, sprite.dest, sprite.origin, sprite.rotation, WHITE);
        }
    }
}
float HeavisideEasing(float value, float step)
{
    return (float) (atan(((double) (value) - .5) * step) / PI + .5);
}
