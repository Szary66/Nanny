#include "TextInput.h"
using namespace Engine;
using namespace Text;

CInput::CInput (SDL_Renderer* rend, std::string file, unsigned size, unsigned width, unsigned height)
: renderer (rend), CFont (file, size), mWidth (width), mHeight (height)
{
	color = { 0, 0, 0, 0xFF };
	loadFromRenderedText ("Enter Text:", color);
	
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}


CInput::~CInput ()
{
	//Deallocate
	free ();
}


bool CInput::loadFromFile (std::string path)
{
	//Get rid of preexisting texture
	free ();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load (path.c_str ());
	if ( loadedSurface == NULL )
	{
		printf ("Unable to load image %s! SDL_image Error: %s\n", path.c_str (), IMG_GetError ());
	}
	else
	{
		//Color key image
		SDL_SetColorKey (loadedSurface, SDL_TRUE, SDL_MapRGB (loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface (renderer, loadedSurface);
		if ( newTexture == NULL )
		{
			printf ("Unable to create texture from %s! SDL Error: %s\n", path.c_str (), SDL_GetError ());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface (loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}



bool CInput::loadFromRenderedText (std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free ();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid (getFont(), textureText.c_str (), textColor);
	if ( textSurface != NULL )
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface (renderer, textSurface);
		if ( mTexture == NULL )
		{
			printf ("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError ());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface (textSurface);
	}
	else
	{
		printf ("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError ());
	}


	//Return success
	return mTexture != NULL;
}


void CInput::free ()
{
	if ( mTexture != NULL )
	{
		SDL_DestroyTexture (mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}


void CInput::setColor (Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod (mTexture, red, green, blue);
}


void CInput::setBlendMode (SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode (mTexture, blending);
}


void CInput::setAlpha (Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod (mTexture, alpha);
}


void CInput::render (int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if ( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx (renderer, mTexture, clip, &renderQuad, angle, center, flip);
}


int CInput::getWidth ()const
{
	return mWidth;
}


int CInput::getHeight ()const
{
	return mHeight;
}


#include "Event.h"
std::string CInput::enter (std::string oldText)
{
	CKeyboard keyboard;
	CKeyboard newKeyboard;

	std::string newText;

	SDL_StartTextInput ();

	keyboard.pressed = false;
	bool quit = false;
	while ( !quit )
	{
		bool renderText = false;
		while ( keyboard.pollEvent () != 0 )
		{
			keyboard.pollEvent ();
			if ( keyboard.isPressed () && keyboard.pressed == false)
			{
				if ( keyboard.getEvent ()->key.keysym.sym == SDL_SCANCODE_KP_ENTER )
					return newText;
				else if ( keyboard.getEvent ()->key.keysym.sym == SDLK_ESCAPE )
					return oldText;
				else if ( keyboard.getEvent ()->key.keysym.sym == SDLK_SPACE )
					quit = true;

				else if ( keyboard.getEvent ()->key.keysym.sym == SDLK_BACKSPACE && newText.length () > 0 )
					newText.pop_back ();

				newKeyboard = keyboard;
			}
			else if ( keyboard.getEvent ()->type == SDL_TEXTINPUT )
			{
				newText += keyboard.getEvent ()->text.text;
			}
			
			if ( newText != "" )
				loadFromRenderedText (newText, color);
			else
				loadFromRenderedText (" ", color);

			//Clear screen
			SDL_SetRenderDrawColor (renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear (renderer);

			//Render text textures
			render (500, 20);//( wScreen * 0.2 / 2, mHeight);

			//Update screen
			SDL_RenderPresent (renderer);
		}
	}
	//Disable text input
	SDL_StopTextInput ();
	
	return newText;
}


