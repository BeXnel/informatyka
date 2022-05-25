#include <iostream>
#include <SDL.h>
#include <fstream>
#include <string>
#include "drawingOOP.h"
using namespace std;

SDL_Renderer* renderer;
void Triangle::Draw()
{
    cout << "Drawing " << m_name << endl;

    int a_x = m_base/2 + m_x;
    int a_y = m_y;

    int b_x = m_x;
    int b_y = m_y + m_height;

    int c_x = m_x + m_base;
    int c_y = m_y + m_height;

    SDL_SetRenderDrawColor(renderer, m_color.red, m_color.green, m_color.blue, m_color.alpha);
    SDL_RenderDrawLine(renderer, a_x, a_y, b_x, b_y);
    SDL_RenderDrawLine(renderer, a_x, a_y, c_x, c_y);
    SDL_RenderDrawLine(renderer, c_x, c_y, b_x, b_y);

}

void Circle::Draw()
{
    cout << "Drawing " << m_name << endl;

    const float diameter = (m_radius * 2);

    int x = (m_radius - 1);
    int y = 0;
    int tx = 1;
    int ty = 1;
    float error = (tx - diameter);

    SDL_SetRenderDrawColor(renderer, m_color.red, m_color.green, m_color.blue, m_color.alpha);
    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, m_x + x, m_y - y);
        SDL_RenderDrawPoint(renderer, m_x + x, m_y + y);
        SDL_RenderDrawPoint(renderer, m_x - x, m_y - y);
        SDL_RenderDrawPoint(renderer, m_x - x, m_y + y);
        SDL_RenderDrawPoint(renderer, m_x + y, m_y - x);
        SDL_RenderDrawPoint(renderer, m_x + y, m_y + x);
        SDL_RenderDrawPoint(renderer, m_x - y, m_y - x);
        SDL_RenderDrawPoint(renderer, m_x - y, m_y + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void Rectangle::Draw()
{
    cout << "Drawing " << m_name << endl;
    SDL_Rect r;
    r.x = m_x;
    r.y = m_y;
    r.w = m_width;
    r.h = m_height;
    SDL_SetRenderDrawColor(renderer, m_color.red, m_color.green, m_color.blue, m_color.alpha);
    SDL_RenderFillRect(renderer, &r);

}

int main(int argc, char** argv)
{
    bool leftMouseButtonDown = false;
    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("SDL2 Pixel Drawing",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    SDL_Texture* texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 800, 600);
    Uint32* pixels = new Uint32[800 * 600];
    memset(pixels, 0xff000000, 800 * 600 * sizeof(Uint32));
    
    
    
    
    
    while (!quit)
    {
        
        SDL_UpdateTexture(texture, NULL, pixels, 800 * sizeof(Uint32));

        SDL_WaitEvent(&event);

        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT)
                leftMouseButtonDown = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
                leftMouseButtonDown = true;
        case SDL_MOUSEMOTION:
            if (leftMouseButtonDown)
            {
                int mouseX = event.motion.x;
                int mouseY = event.motion.y;
                //pixels[mouseY * 640 + mouseX] = 0;
            }
            break;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // Clear winow
        SDL_RenderClear(renderer);
        Color color = Color{ 1,2,3,4 };
        vector<Shape*> items;
        Rectangle* rect1 = new Rectangle("First Rectangle", 100, 100, 100, 100, Color{123,123,123,255});
        Rectangle* rect2 = new Rectangle("Second Rectangle", 230, 100, 100, 100, Color{ 123,123,123,255 });
        Rectangle* rect3 = new Rectangle("Third Rectangle", 360, 100, 100, 100, Color{ 123,123,123,255 });
        Rectangle* rect4 = new Rectangle("Fourth Rectangle", 490, 100, 100, 100, Color{ 123,123,123,255 });
        Circle* circ1 = new Circle("First Circle", 150, 300, 50, Color{ 123,123,123,255 });
        Circle* circ2 = new Circle("Second Circle", 280, 300, 50, Color{ 123,123,123,255 });
        Circle* circ3 = new Circle("Third Circle", 410, 300, 50, Color{ 123,123,123,255 });
        Circle* circ4 = new Circle("Fourth Circle", 540, 300, 50, Color{ 123,123,123,255 });
        Triangle* tria1 = new Triangle("First Triangle", 100, 400, 100, 100, Color{ 123,123,123,255 });
        Triangle* tria2 = new Triangle("Second Triangle", 230, 400, 100, 100, Color{ 123,123,123,255 });
        Triangle* tria3 = new Triangle("Third Triangle", 360, 400, 100, 100, Color{ 123,255,123,255 });
        Triangle* tria4 = new Triangle("Fourth Triangle", 490, 400, 100, 100, Color{ 123,123,123,255 });
        
        items.push_back(rect1);
        items.push_back(rect2);
        items.push_back(rect3);
        items.push_back(rect4);
        items.push_back(circ1);
        items.push_back(circ2);
        items.push_back(circ3);
        items.push_back(circ4);
        items.push_back(tria1);
        items.push_back(tria2);
        items.push_back(tria3);
        items.push_back(tria4);
        for (Shape* it : items)
        {
            it->Draw();
            delete it;
        }

        items.clear();
        //SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    delete[] pixels;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}