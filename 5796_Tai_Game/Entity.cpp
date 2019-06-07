#include "Entity.h"

//constructor
Entity::Entity()
{
	object = NULL;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
}

//destructor
Entity::~Entity()
{
	free();
}
bool Entity::loadImage(std::string path, SDL_Renderer* screen)
{
    free();//improve fast.
	SDL_Texture* newTexture = NULL;
	//return surface
	SDL_Surface* loadSurface = IMG_Load(path.c_str());
	//check if surface !=null
	if (loadSurface != NULL)
	{
		//color key																R	G	B
		SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface->format, 167, 175, 180));
		//set texture from surface
		newTexture = SDL_CreateTextureFromSurface(screen, loadSurface);
		//check texture.
		if (newTexture != NULL)
		{
			rect.w = loadSurface->w;
			rect.h = loadSurface->h;
		}
		//free sureface
		SDL_FreeSurface(loadSurface);
	}
	object = newTexture;
	return object != NULL; //==null return 0 false

}
void Entity::render(SDL_Renderer* des, const SDL_Rect* clip)//clip==null
{
	SDL_Rect rect_ = 
	{ 
		rect.x, 
		rect.y, 
		rect.w, 
		rect.h
	};
	//push objct to des with size
	SDL_RenderCopy(des, object, clip, &rect_);
}
void Entity::free(){
	//good for memory
	if (object != NULL)
	{
		SDL_DestroyTexture(object);
		object = NULL;
		rect.w = 0;
		rect.h = 0;

	}
}
