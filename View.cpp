#include "View.h"

View get_player_coordinate_for_view(float x, float y, View& view) {
    view.setCenter(x+50,y+50);
	return view;
}

void change_view(View& view) {
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		view.zoom(1.0500f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		view.zoom(0.9500f);
	}
}
