#include "GameEngine.h"
#include "ImageTextures.h"

int main(int argc, char* argv[])
{
	GameEngine* NewGame = new GameEngine();
	NewGame->Window->WindowSetup(new char[3] {'L','S','B'}, 1280, 720);
	ImageTexture* Logo = new ImageTexture(NewGame->Window->GetRenderer());
	Logo->Load("Images/Test.png");
	//NewGame->GameLoop();
	//delete NewGame;
	NewGame = nullptr;
	while (true)
	{
		Logo->Draw();
		if (getchar()) {
			break;
		}
	}
	//getchar();
	return 0;
}