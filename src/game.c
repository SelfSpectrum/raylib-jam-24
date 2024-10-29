StateData StartState(void) // Necesario para cargar todas las cosas que utilizaremos en el juego
{
    StateData state;
    state.textures[0].tex = LoadTexture("resources/room.png");
    return state;
}
void EndState(StateData *state) // Necesario para descargar todas las cosas que fueron cargadas
{
    UnloadTexture(state->textures[0].tex);
}
void ChangeScreen(StateData *state, GameScreen screen);
{
    state->screen = screen;
    switch (state->screen) {
        default:
            state->bg = (Sprite) { 0, (Rectangle) { 0.0f, 0.0f, 1.0f, 1.0f }, (Rectangle) { 0.0f, 0.0f, 800.0f, 450.0f }, (Vector2) { 0.0f, 0.0f }, 0.0f, false };
    }
}
