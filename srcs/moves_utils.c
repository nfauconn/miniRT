#include "moves.h"

bool	is_rotate(int keycode)
{
	return (keycode == W_KEY
		|| keycode == A_KEY || keycode == S_KEY || keycode == D_KEY);
}

bool	is_dir_key(int keycode)
{
	return ((keycode >= LEFT_ARROW && keycode <= DOWN_ARROW) || keycode == W_KEY
		|| keycode == A_KEY || keycode == S_KEY || keycode == D_KEY
		|| keycode == '+' || keycode == '-');
}
