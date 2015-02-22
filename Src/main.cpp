 /*
    Project SDL
    Copyright (C) 2015  Isabelle Delmas-Lenertz

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include "sdl.h"
#include "SDL_image.h"

using namespace std;
int main(int argc, char* argv[])
{
    SDL_Surface* pDisplaySurface = NULL; //display surface
    SDL_Event event; //event structure

    //initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO)==-1) {
        cerr << "Could not initialize SDL!" << endl;
        exit(1);
    } else {
        //report success
        cout << "SDL initialized properly!" << endl;
        }
        //create the window
        pDisplaySurface = SDL_SetVideoMode(1024,768,0,SDL_ANYFORMAT);
        //error check
        if (pDisplaySurface == NULL) {
        //report error on the creation of video display
        cerr << "Could not set up display surface!" << endl;
        exit(1);
    }
    // Read in the image
    SDL_Surface* pJpegimage = IMG_Load("C:\\tmp\\goat.jpg");
    if (pJpegimage == NULL) {
        // report error trying to read in image file
        cerr << "Could not read image file" << endl;
        exit(1);
    }
    // Get image ready for display on the screen
    SDL_Surface* pDisplayFormat = SDL_DisplayFormat(pJpegimage);
    // show on display screen
    SDL_Rect DestR;
    DestR.x = 0;
    DestR.y = 0;
    SDL_BlitSurface(pDisplayFormat, NULL, pDisplaySurface, &DestR);

    // process events until user closes the window
    for(;;) {
        //wait for an event
        if(SDL_WaitEvent(&event)==0) {
            cerr << "Error while waiting for an event!" << endl;
            exit(1);
        }

        //check for a quit event
        if(event.type==SDL_QUIT) break;

        //update the screen
        SDL_UpdateRect(pDisplaySurface,0,0,0,0);
    }
    // unload the dynamically loaded image libraries
    SDL_FreeSurface(pJpegimage);

    IMG_Quit();

    // close SDL
    SDL_Quit();
    // we are done
    cout << "Terminating normally." << endl;
    //return 0
    return(0);
}
