#include "pch.h"
#include "ImageTextures.h"

ImageTexture::ImageTexture(SDL_Renderer* sdlRenderer) : SDLTexture(nullptr), SDLRenderer(sdlRenderer), width(0), height(0) {}

ImageTexture::~ImageTexture() {
	//Destroy();
}

bool ImageTexture::Load(const std::string& FileName) {
	//Destroy();
	SDL_Texture* NewSDLTexture = nullptr;
	SDL_Surface* LoadedSurface = IMG_Load(FileName.c_str());
	if (!LoadedSurface) {
		//Debug::Log(EMessageType::ERROR, "Failed to load " + FileName + "  SDL Error: " + SDL_GetError(), __FILE__, __LINE__);
	}
	else {
		if (SDL_SetColorKey(LoadedSurface, SDL_TRUE, SDL_MapRGB(LoadedSurface->format, 0, 0xFF, 0xFF)) < 0) {
			//Debug::Log(EMessageType::WARNING, "Failed to set color key for " + FileName + ".  SDL Error: " + SDL_GetError(), __FILE__, __LINE__);
		}

		NewSDLTexture = SDL_CreateTextureFromSurface(SDLRenderer, LoadedSurface);
		if (!NewSDLTexture) {
			//Debug::Log(EMessageType::ERROR, "Failed to create texture from " + FileName + "!  SDL Error: " + SDL_GetError(), __FILE__, __LINE__);
		}
		else {
			width = LoadedSurface->w;
			height = LoadedSurface->h;
			//Debug::Log(EMessageType::INFO, "Loaded texture " + FileName, __FILE__, __LINE__);
		}

		SDL_FreeSurface(LoadedSurface);
		LoadedSurface = nullptr;
	}

	SDLTexture = NewSDLTexture;
	return SDLTexture != nullptr;
}

void ImageTexture::SetTexture(SDL_Texture& SDLTexture_, const int width_, const int height_) {
	Destroy();
	SDLTexture = &SDLTexture_;
	width = width_;
	height = height_;
}

void ImageTexture::Destroy() {
	SDL_DestroyTexture(SDLTexture);
	SDLTexture = nullptr;
	width = 0;
	height = 0;
}

void ImageTexture::Draw(const DrawParams& Params) const {
	SDL_Rect DrawRect = {
		(int)(Params.x), //+(-width * (Params.scale - 1.0f) * 0.5f)),
		(int)(Params.y), // + (-height * (Params.scale - 1.0f) * 0.5f)),
		(int)(width * Params.scale),
		(int)(height * Params.scale) };

	if (Params.clip) {
		DrawRect.w = Params.clip->w* Params.scale;
		DrawRect.h = Params.clip->h* Params.scale;
	}

	SDL_RenderCopyEx(SDLRenderer, SDLTexture, Params.clip, &DrawRect, Params.angle, Params.center, Params.flip);
}

void ImageTexture::Draw(const int x, const int y, const float scale, SDL_Rect* clip, const double angle,
	SDL_Point* center, const SDL_RendererFlip flip) const {
	DrawParams params = DrawParams{ x, y, scale, clip, angle, center, flip };
	Draw(params);
}

void ImageTexture::SetAlpha(const Uint8 a_) {
	SDL_SetTextureAlphaMod(SDLTexture, a_);
}

void ImageTexture::SetBlendMode(const SDL_BlendMode blendMode_) {
	SDL_SetTextureBlendMode(SDLTexture, blendMode_);
}

void ImageTexture::SetColor(const SDL_Color& SDLColor_) {
	SetColor(SDLColor_.r, SDLColor_.g, SDLColor_.b, SDLColor_.a);
}

void ImageTexture::SetColor(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a) {
	SDL_SetTextureColorMod(SDLTexture, r, g, b);
	SDL_SetTextureAlphaMod(SDLTexture, a);
}

int ImageTexture::GetWidth() const {
	return width;
}

int ImageTexture::GetHeight() const {
	return height;
}
