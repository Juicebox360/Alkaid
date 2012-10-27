#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <vector>
#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
//#include "SDL_mixer.h"
#include "SDL_opengl.h"

#include "world/ent/EntityController.h"
#include "world/ent/EntityEnums.h"
#include "world/World.h"
#include "util/Utils.h"
#include "util/Constants.h"
#include "gfx/fnt/FontController.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const char *WINDOW_TITLE = "Alkaid Engine Demonstration";

SDL_Event event;

double time_last_ms, time_current_ms, time_delta_ms, time_delta;
std::vector<float> timeFrames;

bool gameRunning = true;

World world;
FontController fonts;

SDL_Surface *screen;

Font *font;
Colour bColour( 64, 64, 64, 200 ), fColour( 255, 255, 255, 200 );

void processKey( SDL_KeyboardEvent key )
{
    switch ( key.keysym.sym )
    {
        case SDLK_1:
            if ( key.state == SDL_PRESSED )
            {
                printf( "Making a Runner\n" );

                world.get_entity_controller()->entity_create( ENTITY_RUNNER, &world, new Vector2d( Utils::random_int( 0, SDL_GetVideoInfo()->current_w ), Utils::random_int( 0, SDL_GetVideoInfo()->current_h ) ) );
            }
            break;
        case SDLK_2:
            if ( key.state == SDL_PRESSED )
            {
                printf( "Making a Rocketman\n" );

                world.get_entity_controller()->entity_create( ENTITY_ROCKETMAN, &world, new Vector2d( Utils::random_int( 0, SDL_GetVideoInfo()->current_w ), Utils::random_int( 0, SDL_GetVideoInfo()->current_h ) ) );
            }
            break;
        case SDLK_3:
            if ( key.state == SDL_PRESSED )
            {
                printf( "Making a Healer\n" );

                world.get_entity_controller()->entity_create( ENTITY_HEALER, &world, new Vector2d( Utils::random_int( 0, SDL_GetVideoInfo()->current_w ), Utils::random_int( 0, SDL_GetVideoInfo()->current_h ) ) );
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
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) != 0 )
    {
        printf( "Unable to initialise SDL: %s\n", SDL_GetError() );
        exit( EXIT_FAILURE );
    }
    printf( "Init: SDL_TTF...\n" );
    if ( TTF_Init() != 0 )
    {
        printf( "Unable to initialise SDL_TTF: %s\n", TTF_GetError() );
        exit( EXIT_FAILURE );
    }
    printf( "Completed library inits.\n" );

    EntityController::pre_init();
    Utils::pre_init();

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, true );

    screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_OPENGL | SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER );

    // GL bullshit
    init_gl();

    SDL_WM_SetCaption( WINDOW_TITLE, 0 );
}

void cleanUp()
{
    //Mix_CloseAudio();

    fonts.clean_up();
    TTF_Quit();

    SDL_Quit();
}

void render( SDL_Surface *screen )
{
    glClear( GL_COLOR_BUFFER_BIT );

    world.render( screen );

    // Text
    font->draw_text_shaded( "Press 1 to make a Runner, 2 to make a Rocketman, and 3 to make a Healer.", 5.0d, 5.0d, 1.8d, fColour, bColour );

    // Refresh
    SDL_GL_SwapBuffers();
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

        world.update( screen, time_delta_ms );

        // Render everything if the updating for this tick is done
        render( screen );
    }
    printf( "Exiting game loop.\n" );

    cleanUp();

    printf( "Exiting regularly." );

    exit( EXIT_SUCCESS );
}
