#include "event.h"

void		check_stand(t_data *data)
{
	const Uint8 	*keyboard;

	keyboard = SDL_GetKeyboardState(NULL); 
	
	if (!keyboard[SDL_SCANCODE_LCTRL] && !keyboard[SDL_SCANCODE_SPACE])
	 	stand(data);
	else if (keyboard[SDL_SCANCODE_LCTRL])
		crouch(data);
	else if (keyboard[SDL_SCANCODE_SPACE])
		jump(data);
}