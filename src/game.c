#include "game.h"

StateData LoadState(void) // Necesario para cargar todas las cosas que utilizaremos en el juego
{
    int i = 0;
    StateData state = { 0 };
    state.screen = SCREEN_LOGO_BLINK; 
    state.logoPositionX = GetScreenWidth()/2 - 128;
    state.logoPositionY = GetScreenHeight()/2 - 128;
    state.framesCounter = 0;
    state.letterCount = 0;
    state.sideRect = (Rectangle){ 16.0f, 16.0f, 16.0f, 16.0f };
    state.textures[0] = LoadTexture("resources/gfx/room.png");
    state.textures[1] = LoadTexture("resources/gfx/details.png");
    for ( ; i < OBJ_SIZE; i++) state.interactuable[i].state = BUTTONSTATE_INVALID;
    return state;
}
void UnloadState(StateData *state) // Necesario para descargar todas las cosas que fueron cargadas
{
    UnloadTexture(state->textures[0]);
    UnloadTexture(state->textures[1]);
}
void ChangeSelection(StateData *state)
{
    if (state->wall < 0) state->wall += 4;
    else if (state->wall > 3) state->wall -= 4;
    int i = 0;
    for ( ; i < OBJ_SIZE; i++) state->interactuable[i].state = BUTTONSTATE_INVALID;
    switch (state->wall)
    {
        case 0:
        {
            state->bg = (Sprite){ 0, (Rectangle) { 0.0f, 0.0f, 800.0f, 450.0f }, (Rectangle){ 0.0f, 0.0f, 800.0f, 450.0f }, (Vector2){ 0.0f, 0.0f }, 0.0f };
            state->interactuable[0].sprite = (Sprite){ 0, (Rectangle){ 1600.0f, 450.0f, 128.0f, 142.0f }, (Rectangle){ 235.0f, 200.0f, 128.0f, 142.0f }, (Vector2){ 0.0f, 0.0f }, 0.0f };
            state->interactuable[0].spriteOn = (Sprite){ 0, (Rectangle){ 1728.0f, 450.0f, 128.0f, 142.0f }, (Rectangle){ 235.0f, 200.0f, 128.0f, 142.0f }, (Vector2){ 0.0f, 0.0f }, 0.0f };
            state->interactuable[0].state = BUTTONSTATE_OFF;
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
    sprintf(state->screenId, "Scene index %d", (int)state->screen);
    switch (state->screen)
    {
        case SCREEN_LOGO_BLINK:
        {
            state->bgColor = COLOR_1;
        } break;
        case SCREEN_LOGO_LEFT_TOP:
        {
            state->framesCounter = 0; // Reinicio el contador para reutilizarlo
        } break;
        case SCREEN_LOGO_CROMABER:
        {
            state->framesCounter = 0;
            state->bgColor = COLOR_8;
        } break;
        case SCREEN_TITLE:
        {
            state->bg = (Sprite){ 0, (Rectangle){ 800.0f, 450.0f, 800.0f, 450.0f }, (Rectangle){ 0.0f, 0.0f, 800.0f, 450.0f }, (Vector2){ 0.0f, 0.0f }, 0.0f };
        } break;
        case SCREEN_ROOM:
        {
            ChangeSelection(state);
        } break;
        case SCREEN_CEILING:
        {
            int i = 0;
            for ( ; i < OBJ_SIZE; i++) state->interactuable[i].state = BUTTONSTATE_INVALID;
            state->bg = (Sprite){ 0, (Rectangle){ 800.0f, 450.0f, 800.0f, 450.0f }, (Rectangle){ 0.0f, 0.0f, 800.0f, 450.0f }, (Vector2){ 0.0f, 0.0f }, 0.0f };
        } break;
        case SCREEN_RADIO:
        {
            int i = 0;
            for ( ; i < OBJ_SIZE; i++) state->interactuable[i].state = BUTTONSTATE_INVALID;
            state->bg = (Sprite){ 0, (Rectangle){ 1600.0f, 0.0f, 800.0f, 450.0f }, (Rectangle){ 0.0f, 0.0f, 800.0f, 450.0f }, (Vector2){ 0.0f, 0.0f }, 0.0f };
            state->interactuable[0].sprite = (Sprite){ 0, (Rectangle){ 1600.0f, 592.0f, 112.0f, 96.0f }, (Rectangle){ 32.0f, 32.0f, 112.0f, 96.0f }, (Vector2){ 0.0f, 0.0f }, 0.0f };
            state->interactuable[0].spriteOn = (Sprite){ 0, (Rectangle){ 1712.0f, 592.0f, 112.0f, 96.0f }, (Rectangle){ 32.0f, 32.0f, 112.0f, 96.0f }, (Vector2){ 0.0f, 0.0f }, 0.0f };
            state->interactuable[0].state = BUTTONSTATE_OFF;
        } break;
        default:
        {
            state->bg = (Sprite){ 0, (Rectangle){ 800.0f, 450.0f, 800.0f, 450.0f }, (Rectangle){ 0.0f, 0.0f, 0.0f, 0.0f }, (Vector2){ 0.0f, 0.0f }, 0.0f };
        } break;
    }
}
void UpdateState(StateData *state)
{
    switch (state->screen)
    {
        case SCREEN_LOGO_BLINK:
        {
            state->framesCounter++;
            if (state->framesCounter >= 120) ChangeScreen(state, SCREEN_LOGO_LEFT_TOP);
        } break;
        case SCREEN_LOGO_LEFT_TOP:
        {
            state->sideRect.width += 4;
            state->sideRect.height += 4;
            if (state->sideRect.width >= 256) ChangeScreen(state, SCREEN_LOGO_RIGHT_BOTTOM);
        } break;
        case SCREEN_LOGO_RIGHT_BOTTOM:
        {
            state->sideRect.x += 4;
            state->sideRect.y += 4;
            if (state->sideRect.x >= 256) ChangeScreen(state, SCREEN_LOGO_LETTER);
        } break;
        case SCREEN_LOGO_LETTER:
        {
            state->framesCounter++;
            if (state->letterCount < 10 && state->framesCounter/12)       // Every 12 frames, one more letter!
            {
                state->letterCount++;
                state->framesCounter = 0;
            }
            if (state->framesCounter >= 60) ChangeScreen(state, SCREEN_LOGO_CROMABER);
        } break;
        case SCREEN_LOGO_CROMABER:
        {
            state->framesCounter++;
            if (state->framesCounter >= 360) ChangeScreen(state, SCREEN_ROOM);
        } break;
        case SCREEN_ROOM:
        {
            state->mousePos = GetMousePosition();
            UpdateInteractuable(state);
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
            if (IsKeyPressed(KEY_UP))
            {
                ChangeScreen(state, SCREEN_CEILING);
            }
        } break;
        case SCREEN_CEILING:
        {
            state->mousePos = GetMousePosition();
            UpdateInteractuable(state);
            if (IsKeyPressed(KEY_DOWN))
            {
                ChangeScreen(state, SCREEN_ROOM);
            }
        } break;
        case SCREEN_RADIO:
        {
            state->mousePos = GetMousePosition();
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
        if (state->interactuable[i].state == BUTTONSTATE_INVALID) continue;
        if (CheckCollisionPointRec(state->mousePos, state->interactuable[i].sprite.dest))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) state->interactuable[i].state = BUTTONSTATE_PRESS;
            else state->interactuable[i].state = BUTTONSTATE_HOVER;
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                switch (state->screen)
                {
                    case SCREEN_ROOM:
                    {
                        if ((i == 0) && (state->wall == 0)) ChangeScreen(state, SCREEN_RADIO);
                    } break;
                    case SCREEN_RADIO:
                    {
                        if (i == 0) ChangeScreen(state, SCREEN_ROOM);
                    } break;
                    default:
                    {
                    } break;
                }
            ChangeScreen(state, SCREEN_RADIO);
            }
        }
        else state->interactuable[i].state = BUTTONSTATE_OFF;
    }
}
void DrawState(StateData *state)
{
    switch (state->screen)
    {
        case SCREEN_LOGO_BLINK:
        {
            if ((state->framesCounter/15)%2) DrawRectangle(state->logoPositionX, state->logoPositionY, 16, 16, COLOR_7);
        } break;
        case SCREEN_LOGO_LEFT_TOP:
        {
            DrawRectangle(state->logoPositionX, state->logoPositionY, state->sideRect.width, 16, COLOR_7);
            DrawRectangle(state->logoPositionX, state->logoPositionY, 16, state->sideRect.height, COLOR_7);
        } break;
        case SCREEN_LOGO_RIGHT_BOTTOM:
        {
            DrawRectangle(state->logoPositionX, state->logoPositionY, state->sideRect.width, 16, COLOR_7);
            DrawRectangle(state->logoPositionX, state->logoPositionY, 16, state->sideRect.height, COLOR_7);
            DrawRectangle(state->logoPositionX + 240, state->logoPositionY, 16, state->sideRect.y, COLOR_7);
            DrawRectangle(state->logoPositionX, state->logoPositionY + 240, state->sideRect.x, 16, COLOR_7);
        } break;
        case SCREEN_LOGO_LETTER:
        {
            DrawRectangle(state->logoPositionX, state->logoPositionY, state->sideRect.width, 16, COLOR_7);
            DrawRectangle(state->logoPositionX, state->logoPositionY + 16, 16, state->sideRect.height - 32, COLOR_7);
        
            DrawRectangle(state->logoPositionX + 240, state->logoPositionY + 16, 16, state->sideRect.y - 32, COLOR_7);
            DrawRectangle(state->logoPositionX, state->logoPositionY + 240, state->sideRect.x, 16, COLOR_7);
        
            DrawRectangle(GetScreenWidth()/2 - 112, GetScreenHeight()/2 - 112, 224, 224, COLOR_1);
        
            DrawText(TextSubtext("raylib", 0, state->letterCount), GetScreenWidth()/2 - 44, GetScreenHeight()/2 + 48, 50, COLOR_7);
        } break;
        case SCREEN_LOGO_CROMABER:
        {
            DrawTexturePro(state->textures[1], (Rectangle){ 0.0f, 0.0f, 416.0f, 368.0f }, (Rectangle){ 32.0f, 225.0f - 184.0f*HeavisideEasing(10.0, (state->framesCounter - 120)/6.0f) , 416.0f, 368.0f*HeavisideEasing(10.0, (state->framesCounter - 120)/6.0f) }, (Vector2){ 0.0f, 0.0f }, 0, WHITE);
        } break;
        case SCREEN_ROOM:
        case SCREEN_CEILING:
        case SCREEN_RADIO:
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
    bool isPress = false;
    Sprite sprite = { 0 };
    for ( ; i < OBJ_SIZE; i++)
    {
        isValid = state->interactuable[i].state != BUTTONSTATE_INVALID;
        isHover = state->interactuable[i].state == BUTTONSTATE_HOVER;
        isPress = state->interactuable[i].state == BUTTONSTATE_PRESS;
        sprite = state->interactuable[i].sprite;
        DrawRectangleLinesEx(sprite.dest, 1, WHITE);
        if (isValid)
        {
            sprite = state->interactuable[i].sprite;
            DrawTexturePro(state->textures[sprite.textureIndex], sprite.source, sprite.dest, sprite.origin, sprite.rotation, WHITE);
            if (isHover || isPress)
            {
                sprite = state->interactuable[i].spriteOn;
                DrawTexturePro(state->textures[sprite.textureIndex], sprite.source, sprite.dest, sprite.origin, sprite.rotation, (isPress)? COLOR_2 : COLOR_5);
            }
        }
    }
}
float HeavisideEasing(float value, float step)
{
    return (float) (atan(((double) (value) - .5) * step) / PI + .5);
}
