#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <vector>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
//#include "SDL_mixer.h"
#include <SDL2/SDL_opengl.h>

#include "world/ent/Supervisor.h"
#include "world/ent/EntityEnums.h"
#include "world/World.h"
#include "util/Utils.h"
#include "util/Constants.h"
#include "gfx/fnt/FontController.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const char *WINDOW_TITLE = "Benetnasch";

SDL_Event event;

double time_last_ms, time_current_ms, time_delta_ms, time_delta;
std::vector<float> timeFrames;

bool gameRunning = true;

World world;
FontController fonts;

SDL_Surface *surface;
SDL_Window *primaryWindow;
SDL_GLContext buff;

//SDL_Renderer *renderer;
//SDL_Texture *screen;

Font *font;
Colour bColour( 64, 64, 64, 200 ), fColour( 255, 255, 255, 200 );

void processKey( SDL_KeyboardEvent key )
{
    int w, h;
    SDL_GetWindowSize( primaryWindow, &w, &h );

    switch ( key.keysym.sym )
    {
        case SDLK_1:
            if ( key.state == SDL_PRESSED )
            {
                printf( "Making a Runner\n" );

                world.get_entity_supervisor()->entity_create( ENTITY_RUNNER, &world, new Vector2d( Utils::random_int( 0, w ), Utils::random_int( 0, h ) ) );
            }
            break;
        case SDLK_2:
            if ( key.state == SDL_PRESSED )
            {
                printf( "Making a Rocketman\n" );

                world.get_entity_supervisor()->entity_create( ENTITY_ROCKETMAN, &world, new Vector2d( Utils::random_int( 0, w), Utils::random_int( 0, h ) ) );
            }
            break;
        case SDLK_3:
            if ( key.state == SDL_PRESSED )
            {
                printf( "Making a Healer\n" );

                world.get_entity_supervisor()->entity_create( ENTITY_HEALER, &world, new Vector2d( Utils::random_int( 0, w ), Utils::random_int( 0, h ) ) );
            }
            break;
        case SDLK_0:
            if ( key.state == SDL_PRESSED )
            {
                printf( "Clearing all entities\n" );

                world.get_entity_supervisor()->reset();
            }
            break;
        case SDLK_8:
            if ( key.state == SDL_PRESSED )
            {
                if ( world.get_entity_supervisor()->entity_count() > 0 )
                {
                    printf( "Clearing the first entity\n" );

                    world.get_entity_supervisor()->entity_kill( &(world.get_entity_supervisor()->entity_list()->at( 0 )) );
                }
            }
            break;
    }
}

void processInput()
{
    if ( SDL_PollEvent( &event ) )
    {
         switch( event.type )
         {
            case SDL_QUIT:
                gameRunning = false;
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                processKey( event.key );
                break;
        }
    }

    /*
    Uint8 *keystate = SDL_GetKeyState( NULL );

    if ( keystate[SDLK_LEFT] )
    {
    }
    */
}

void init_gl()
{
    glClearColor( 0.1f, 0.1f, 0.3f, 0.0f );
    glViewport( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );
    glClear( GL_COLOR_BUFFER_BIT );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

void pre_init()
{
    printf( "Initialising.\n" );

    freopen( "CON", "w", stdout );
    freopen( "CON", "w", stderr );

    printf( "Init: SDL...\n" );
    if ( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
    {
        printf( "Unable to initialise SDL: %s\n", SDL_GetError() );
        exit( EXIT_FAILURE );
    }
    printf( "Creating window...\n" );
    primaryWindow = SDL_CreateWindow( WINDOW_TITLE, 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );
    if ( primaryWindow == nullptr )
    {
        printf( "Unable to create window: %s\n", SDL_GetError() );
        exit( EXIT_FAILURE );
    }
    printf( "Creating drawing buffer...\n" );
    buff = SDL_GL_CreateContext( primaryWindow );
    if ( buff == nullptr )
    {
        printf( "Unable to create drawing buffer: %s\n", SDL_GetError() );
        exit( EXIT_FAILURE );
    }

/*
    printf( "Creating renderer...\n" );
    renderer = SDL_CreateRenderer( primaryWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if ( renderer == nullptr )
    {
        printf( "Unable to create renderer: %s\n", SDL_GetError() );
        exit( EXIT_FAILURE );
    }
    printf( "Creating drawing surface...\n" );
    screen = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, WINDOW_WIDTH, WINDOW_HEIGHT );
    if ( screen == nullptr )
    {
        printf( "Unable to create drawing surface: %s\n", SDL_GetError() );
        exit( EXIT_FAILURE );
    }

    Uint32 rMask, gMask, bMask, aMask;
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rMsk = 0xff000000;
        gMask = 0x00ff0000;
        bMask = 0x0000ff00;
        aMask = 0x000000ff;
    #else
        rMask = 0x000000ff;
        gMask = 0x0000ff00;
        bMask = 0x00ff0000;
        aMask = 0xff000000;
    #endif

    printf( "Creating drawing buffer...\n" );
    buff = SDL_CreateRGBSurface( 0, WINDOW_WIDTH, WINDOW_HEIGHT, 32, rMask, gMask, bMask, aMask );
    if ( buff == nullptr )
    {
        printf( "Unable to create drawing buffer: %s\n", SDL_GetError() );
        exit( EXIT_FAILURE );
    }
    */

    printf( "Init: SDL_TTF...\n" );
    if ( TTF_Init() != 0 )
    {
        printf( "Unable to initialise SDL_TTF: %s\n", TTF_GetError() );
        exit( EXIT_FAILURE );
    }
    printf( "Completed library inits.\n" );

    printf( "Pre-initialisation of Supervisor.\n" );
    Supervisor::pre_init();
    printf( "Pre-initialisation of Utils.\n" );
    Utils::pre_init();

    printf( "Setting Double-buffer.\n" );
    //SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, true );
    SDL_GL_SetSwapInterval( 1 );

    //printf( "Setting video mode.\n" );
    //screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_OPENGL | SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER );

    // GL bullshit
    printf( "Initialising OpenGL.\n" );
    init_gl();

    //SDL_WM_SetCaption( WINDOW_TITLE, 0 );

    printf( "Initialisation completed!\n" );
}

void cleanUp()
{
    //Mix_CloseAudio();

    //SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( primaryWindow );
    //SDL_DestroyTexture( screen );
    //SDL_FreeSurface( surface );

    fonts.clean_up();
    TTF_Quit();

    SDL_Quit();
}

void render( SDL_Window *window )
{
    glClear( GL_COLOR_BUFFER_BIT );

    //SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    //SDL_RenderClear( renderer );
    //SDL_RenderPresent( renderer );

    world.render( window );

    // Text
    font->draw_text_shaded( "Press 1 to make a Runner, 2 to make a Rocketman, and 3 to make a Healer.", 5.0d, 5.0d, 1.8d, fColour, bColour );
    font->draw_text_shaded( "Press 0 to destroy all entities.", 5.0d, 500.0d, 1.8d, fColour, bColour );

    // Refresh
    //SDL_GL_SwapBuffers();
    SDL_GL_SwapWindow( window );

/*
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderClear( renderer );
    glClear( GL_COLOR_BUFFER_BIT );

    world.render( buffer );

    font->draw_text_shaded( "Press 1 to make a Runner, 2 to make a Rocketman, and 3 to make a Healer.", 5.0d, 5.0d, 1.8d, fColour, bColour );
    font->draw_text_shaded( "Press 0 to destroy all entities.", 5.0d, 500.0d, 1.8d, fColour, bColour );

    screen = SDL_CreateTextureFromSurface( renderer, buffer );
    SDL_RenderCopy( renderer, screen, NULL, NULL );
    SDL_RenderPresent( renderer );

    SDL_GL_SwapWindow( window );
*/
}

int main( int argc, char **argv )
{
    pre_init();

    font = fonts.create_font( "sauce8bit.ttf", 32 );

    printf( "Entering game loop.\n" );
    while ( gameRunning )
    {
        time_last_ms = time_current_ms;
        time_current_ms = SDL_GetTicks();
        time_delta_ms = time_current_ms - time_last_ms;
        time_delta = time_delta_ms / 1000.0d;

        timeFrames.push_back( time_current_ms );
        while ( timeFrames[0] + 1000 < time_current_ms )
        {
            timeFrames.erase( timeFrames.begin() );
        }

        //printf( "Apparently, FPS is %f.\n", 1000.0 / (timeFrames.back() - timeFrames.front()) * (timeFrames.size() - 1) );

        // Update. Physics. Inputs. AI.
        processInput();

        world.update( primaryWindow, time_delta_ms );

        // Render everything if the updating for this tick is done
        render( primaryWindow );
    }
    printf( "Exiting game loop.\n" );

    cleanUp();

    printf( "Exiting regularly." );

    exit( EXIT_SUCCESS );
}
