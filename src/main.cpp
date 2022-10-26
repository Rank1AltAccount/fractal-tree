#include <SDL.h> 
#include <cmath>
 
class Application {
public: 
	void init() {
		// Do not initialize SDL more than once
		if (SDL_WasInit(SDL_INIT_VIDEO) == 0) { 
			SDL_Init(SDL_INIT_VIDEO); 
		}

		window = SDL_CreateWindow(
			"Fractal Tree (control with arrow keys)",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			windowWidth,
			windowHeight,
			SDL_WINDOW_OPENGL
		);

		renderer = SDL_CreateRenderer(
			window,
			-1,
			SDL_RENDERER_ACCELERATED
		); 
	}

	// Cool startup animation
	void initAnimation() {
		int iBranchLength = branchLength; // Store the initial value
 
		for (branchLength = 0; branchLength < iBranchLength; branchLength++) {
			renderFrame(); 
			SDL_Delay(10);
		} 
	}

	void quit() { 
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		exit(0);
	}

	// Branch properties controlled by arrow keys
	void processInput() { 
		switch (event.key.keysym.scancode) {
		case SDL_SCANCODE_UP:
			branchLength += 5;
			break; 

		case SDL_SCANCODE_DOWN:
			if (branchLength >= 6) {
				branchLength -= 5; 
			}
			break;

		case SDL_SCANCODE_LEFT:
			branchSpread += 1;
			break;

		case SDL_SCANCODE_RIGHT:
			branchSpread -= 1;
			break;
		}

		renderFrame();
	}
	
	void renderFractalTree(int startX, int startY, double bLength, double bAngle) {
		double angleInRad = (bAngle * M_PI) / 180.0;
		
		int endX = startX - bLength * cos(angleInRad);
		int endY = startY - bLength * sin(angleInRad);
		
		SDL_RenderDrawLine(renderer, startX, startY, endX, endY);
		
		if (bLength > branchMinLength) {
			bLength *= branchLengthMul;

			renderFractalTree(endX, endY, bLength, bAngle + branchSpread);
			renderFractalTree(endX, endY, bLength, bAngle - branchSpread);
		}
	}

	// This function is outside the event loop because there is no point in redrawing static frames
	void renderFrame() { 
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
		SDL_RenderClear(renderer); // Fill the window with black

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
		renderFractalTree(windowWidth / 2, windowHeight, branchLength, 90); // 90 degrees for the initial tree trunk

		SDL_RenderPresent(renderer); 
	}
	
	void eventLoop() {
		while (true) {
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT:
					quit();

				case SDL_KEYDOWN:
					processInput();
				}
			}

			SDL_Delay(50); // Unless you want to cook on your CPU
		}
	}
 
	void run() {
		init();
		initAnimation();
		eventLoop();
	}

	Application(int wWidth, int wHeight) { 
		windowWidth = wWidth;
		windowHeight = wHeight;
	}

private:
	int windowWidth;
	int windowHeight; 

	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Event event; 
 
	int branchLength = 125; // Initial length that gets lesser with each branch
	int branchMinLength = 15; // Branches shorter than this value are not rendered
	int branchSpread = 35; // Branch angle from point

	double branchLengthMul = 0.8; // Each consequent branch gets shorter by getting multiplied by this value
};
 
// Parameters specified so SDL could see the entry point
int main(int argc, char* argv[]) { 
	Application app(800, 600);
	app.run();

	return 0;
}
