#include "Button.h"

Button::Button(SDL_Renderer* ren, std::string filepath, std::function<void ()>& func) : ren(ren), f(func){
	SDL_Surface* s = IMG_Load(filepath.c_str());
	texture = SDL_CreateTextureFromSurface(ren, s);
	pos = SDL_Rect{ 0, 0, 0, 0 };
	clip = SDL_Rect{ 0, 0, 0, 0 };
}

void Button::setDimension(int x, int y, int w, int h) {
	pos = SDL_Rect{ x, y, w, h };
}

void Button::handleEvents(SDL_Event* e) {
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool in = x > pos.x && x < (pos.x + pos.w) && y > pos.y && y < (pos.y + pos.h);
		int tw, th;
		SDL_QueryTexture(texture, nullptr, nullptr, &tw, &th);
		if (!in) {

		}
		if (!in) {
			clip.x = 0;
			clip.y = 0;
			clip.w = tw / 3;
			clip.h = th;
			return;
		}
		if (e->type == SDL_MOUSEMOTION) {
			clip.x = tw / 3;
			clip.y = 0;
			clip.w = tw / 3;
			clip.h = th;
		}
		if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT) {
			clip.x = (2 * tw) / 3;
			clip.y = 0;
			clip.w = tw / 3;
			clip.h = th;
		}
		if (e->type == SDL_MOUSEBUTTONUP && e->button.button == SDL_BUTTON_LEFT) {
			f();
			clip.x = tw / 3;
			clip.y = 0;
			clip.w = tw / 3;
			clip.h = th;
		}
	}

}

void Button::drawButton() {
	SDL_RenderCopy(ren, texture, &clip, &pos);
}