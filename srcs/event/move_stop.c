#include "event.h"

void		check_move(t_data *data)
{
	const Uint8 	*keyboard;

	keyboard = SDL_GetKeyboardState(NULL); 
	
	if (keyboard[SDL_SCANCODE_UP] && keyboard[SDL_SCANCODE_DOWN])
	 	data->walking = MOVE_NONE;
	else if (keyboard[SDL_SCANCODE_LEFT] && keyboard[SDL_SCANCODE_RIGHT]) 
		data->walking = MOVE_NONE;
	else if (keyboard[SDL_SCANCODE_RIGHT]) 
		data->walking = MOVE_RIGHT;
	else if (keyboard[SDL_SCANCODE_DOWN]) 
		data->walking = MOVE_DOWN;
	else if (keyboard[SDL_SCANCODE_UP]) 
		data->walking = MOVE_UP;
	else if (keyboard[SDL_SCANCODE_LEFT]) 
		data->walking = MOVE_LEFT;
}