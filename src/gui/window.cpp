#include <cstdlib>
#include <iostream>
#include <sstream>
#include <memory>
#include <SDL2/SDL.h>
#include "../cpu/interpreter/err.hpp"
#include "window.hpp"

namespace {
    // Initialize SDL subsystem.
    void init() {
#if DEBUG
        static bool inited = false;
        assert(!inited);
        inited = true;
#endif
        if (SDL_Init(SDL_INIT_VIDEO)) {
            stringstream ss;
            ss << "Failed to initialize SDL:" << SDL_GetError() << endl;
            throw err(ss.str());
        }
        atexit(SDL_Quit); // Destroys everything SDL has initialized at program exit.
    }

    // Creates a window in a desktop window system.
    class Window {
    public:
        Window(const char *title, const uint width, const uint height);
        void draw16(const u16 fb[]);
        ~Window();
        Window(const Window&)         = delete;
        void operator=(const Window&) = delete;
    private:
        void blit();
        SDL_Window *w;
        SDL_Surface *s;
    };

    unique_ptr<Window> win;

    void fb16_to_fb32(const u16 fb16[], u32 fb32[]) {
        for (int x = 0; x < 320; x++) {
            for (int y = 0; y < 240; y++) {
                // Red.
                fb32[x + (y * 320)] |= (((fb16[x + (y * 320)] >> 11) & 0xf800) * 65535) << 16;
                // Green.
                fb32[x + (y * 320)] |= (((fb16[x + (y * 320)] >> 6) & 0x7c0) * 65535) << 8;
                // Blue.
                fb32[x + (y * 320)] |= ((fb16[x + (y * 320)] >> 1) & 0x3e) * 65535;
            }
        }
    }
}

// Draw in 5/5/5/1 16-bit RGBA pixel format.
void draw16(const u16 fb[]) {
    win->draw16(fb);
}

void Window::blit() {
    SDL_BlitSurface(s, nullptr, SDL_GetWindowSurface(w), nullptr);
    SDL_UpdateWindowSurface(w);
}

// Draw in 5/5/5/1 16-bit RGBA pixel format.
void Window::draw16(const u16 fb[]) {
    // Convert from 16-bit to 32-bit.
    //memset((u32*)s->pixels, 0x00, 320*240*sizeof(u32));
    fb16_to_fb32(fb, (u32*)s->pixels);
    // Blit to window surface.
    blit();
}

Window::Window(const char title[], const uint width, const uint height)
{
    init();
    w = SDL_CreateWindow(title, 
                         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         width, height,
                         SDL_WINDOW_SHOWN);
    if (!w) {
        stringstream ss;
        ss << "Failed to create a window: " << SDL_GetError() << '\n';
        throw err(ss.str());
    }
    // ARGB 8/8/8/8.
    s = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    if (!s) {
        stringstream ss;
        ss << "Failed to create a surface: " << SDL_GetError() << '\n';
        throw err(ss.str());
    }
    SDL_FillRect(s, nullptr, SDL_MapRGB(s->format, 0, 0, 0));
    blit();
}

Window::~Window() {
    SDL_FreeSurface(s);
    SDL_DestroyWindow(w);
}

void create_window(const char title[], const int width, const int height) {
    win = unique_ptr<Window>(new Window(title, width, height));
}
