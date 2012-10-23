#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_opengl.h"

#include "gfx/sprite.h"
#include "gfx/animatedsprite.h"
#include "util/Utils.h"

#include "InfoSheet.h"

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const char* WINDOW_TITLE = "woop woop pull over that ass too fat [woop woop]";
const std::string FONTS_DIR = "fonts/", SOUND_DIR = "sound/";

const int AUDIO_RATE = 44100;
const Uint16 AUDIO_FORMAT = AUDIO_S16; /* 16-bit stereo */
const int AUDIO_CHAN = 2;
const int AUDIO_BUFFERS = 4096;

const double ROTATION_RATE = 0.5d;
const double SHADOW_SPACING = 1.8d;
const double SCALE_RATE = 0.1d;
const double CENTRE_ADJUST_RATE = 0.1d;
const double UPDATE_RATE = 1000.0d / 30;

const int ALPHA_RATE = 1;
const int ANIM_RATE = 150;
const int SHEET_CHANCE = 5;

SDL_Event event;

Mix_Music *music = NULL;

TTF_Font *font;

double theta = 0, scaleX = 1.0d, scaleY = 1.0d, centreX = 0, centreY = 0;

double timeLastMs, timeCurrentMs, timeDeltaMs, timeAccumulatedMs;
std::vector<float> timeFrames;

bool gameRunning = true;

Colour colour( 255, 255, 255 ), bColour( 64, 64, 64, 200 ), fColour( 255, 255, 255, 200 );

std::vector<InfoSheet*> sheets;

int index = 0;

void musicDone()
{
    Mix_HaltMusic();
    Mix_FreeMusic( music );
    music = NULL;
}

void handleTTFError()
{
    printf( "TTF_Init: %s\n", TTF_GetError() );
    exit( EXIT_FAILURE );
}

void textProcess( GLuint *destSurf, SDL_Surface *text )
{
    GLenum textureFormat;
    GLint colourFormat = text->format->BytesPerPixel;

    // Alpha channel check
    if ( colourFormat == 4 )
    {
        if ( text->format->Rmask == 0x000000ff )
        {
            textureFormat = GL_RGBA;
        }
        else
        {
            textureFormat = GL_BGRA;
        }
    }
    else if ( colourFormat == 3 )
    {
        if ( text->format->Rmask == 0x000000ff )
        {
            textureFormat = GL_RGB;
        }
        else
        {
            textureFormat = GL_BGR;
        }
    }
    else
    {
        printf( "Warning! A text's colourdata is not truecolour." );
    }

    glGenTextures( 1, destSurf );
    glBindTexture( GL_TEXTURE_2D, *destSurf );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, colourFormat, text->w, text->h, 0, textureFormat, GL_UNSIGNED_BYTE, text->pixels );

    if ( text )
    {
        SDL_FreeSurface( text );
    }
}

void drawTextShaded( TTF_Font *font, std::string &text, int dX, int dY, Colour &foregroundColour, Colour &backgroundColour )
{
    SDL_Surface *textSurface;

    if ( !(textSurface = TTF_RenderUTF8_Blended( font, text.c_str(), {255, 255, 255} ) ) )
    {
        handleTTFError();
    }

    int w = textSurface->w, h = textSurface->h;

    GLuint texture;
    textProcess( &texture, textSurface );

    glTranslatef( dX + SHADOW_SPACING, dY + SHADOW_SPACING, 0.0 );

    glBindTexture( GL_TEXTURE_2D, texture );
    glColor4ub( backgroundColour.getRedI(), backgroundColour.getGreenI(), backgroundColour.getBlueI(), backgroundColour.getAlphaI() );
    glEnable( GL_TEXTURE_2D );

    glBegin( GL_QUADS );
    glTexCoord2i( 0, 0 );
    glVertex3f( 0, 0, 0 );
    glTexCoord2i( 1, 0 );
    glVertex3f( w, 0, 0 );
    glTexCoord2i( 1, 1 );
    glVertex3f( w, h, 0 );
    glTexCoord2i( 0, 1 );
    glVertex3f( 0, h, 0 );
    glEnd();

    glDisable( GL_TEXTURE_2D );
    glLoadIdentity();

    //glClear( GL_COLOR_BUFFER_BIT );
    glTranslatef( dX, dY, 0.0 );

    glBindTexture( GL_TEXTURE_2D, texture );
    glColor4ub( foregroundColour.getRedI(), foregroundColour.getGreenI(), foregroundColour.getBlueI(), foregroundColour.getAlphaI() );
    glEnable( GL_TEXTURE_2D );

    glBegin( GL_QUADS );
    glTexCoord2i( 0, 0 );
    glVertex3f( 0, 0, 0 );
    glTexCoord2i( 1, 0 );
    glVertex3f( w, 0, 0 );
    glTexCoord2i( 1, 1 );
    glVertex3f( w, h, 0 );
    glTexCoord2i( 0, 1 );
    glVertex3f( 0, h, 0 );
    glEnd();

    glDisable( GL_TEXTURE_2D );
    glColor4ub( 255, 255, 255, 255 );
    glLoadIdentity();

    glDeleteTextures( 1, &texture );
}

void processKey( SDL_KeyboardEvent key, Sprite &sprite )
{
    switch ( key.keysym.sym )
    {
        case SDLK_t:
            if ( key.state == SDL_PRESSED )
            {
                if ( index < sprite.getCount() )
                {
                    index++;
                    printf( "Index now at %i\n", index );
                }
            }
            break;
        case SDLK_g:
            if ( key.state == SDL_PRESSED )
            {
                if ( index > 0 )
                {
                    index--;
                    printf( "Index now at %i\n", index );
                }
            }
            break;
    }
}

void processInput( Sprite &sprite )
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
                processKey( event.key, sprite );
                break;
        }
    }

    Uint8 *keystate = SDL_GetKeyState( NULL );

    if ( keystate[SDLK_LEFT] )
    {
        theta += ROTATION_RATE;
        if ( theta >= 360.0d )
        {
            theta -= 360.0d;
        }
        printf( "Theta: %d\n", theta );
    }
    if ( keystate[SDLK_RIGHT] )
    {
        theta -= ROTATION_RATE;
        if ( theta < 0.0d )
        {
            theta += 360.0d;
        }
        printf( "Theta: %d\n", theta );
    }
    if ( keystate[SDLK_UP] )
    {
        colour.addAlpha( ALPHA_RATE );
    }
    if ( keystate[SDLK_DOWN] )
    {
        colour.addAlpha( -ALPHA_RATE );
    }
    if ( keystate[SDLK_q] )
    {
        scaleY += SCALE_RATE;
    }
    if ( keystate[SDLK_a] )
    {
        scaleY -= SCALE_RATE;
    }
    if ( keystate[SDLK_w] )
    {
        scaleX += SCALE_RATE;
    }
    if ( keystate[SDLK_s] )
    {
        scaleX -= SCALE_RATE;
    }
    if ( keystate[SDLK_e] )
    {
        centreX += CENTRE_ADJUST_RATE;
        sprite.setCentreX( centreX );
    }
    if ( keystate[SDLK_d] )
    {
        centreX -= CENTRE_ADJUST_RATE;
        sprite.setCentreX( centreX );
    }
    if ( keystate[SDLK_r] )
    {
        centreY += CENTRE_ADJUST_RATE;
        sprite.setCentreY( centreY );
    }
    if ( keystate[SDLK_f] )
    {
        centreY -= CENTRE_ADJUST_RATE;
        sprite.setCentreY( centreY );
    }
}

void initGL()
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

void cleanUp()
{
    Mix_CloseAudio();

    TTF_CloseFont( font );
    TTF_Quit();

    SDL_Quit();
}

// The parameter list is temporary; the actual version will be handled by a SpriteManager or the like.
void render( SDL_Surface *screen, Sprite &sprite, AnimatedSprite &anim, AnimatedSprite *paper )
{
    glClear( GL_COLOR_BUFFER_BIT );

    sprite.render( screen, (SDL_GetVideoInfo()->current_w) / 2, (SDL_GetVideoInfo()->current_h) / 2, index, scaleX, scaleY, &colour, theta );
    anim.render( screen, SDL_GetVideoInfo()->current_w - 70.0d, SDL_GetVideoInfo()->current_h - 70.0d, 2.0d, 2.0d, &Colour::WHITE, 0.0d );
    paper->render( screen, 70.0d, SDL_GetVideoInfo()->current_h - 70.0d, 2.0d, 2.0d, &Colour::WHITE, 0.0d );

    for ( int i = 0; i < sheets.size(); i++ )
    {
        (sheets[i])->render( screen );
    }

    std::string temp = Utils::concat( "Left / Right Arrow: Rotation (t = ", theta, ")" );
    drawTextShaded( font, temp, 10, 10, fColour, bColour );

    temp = Utils::concat( "Up / Down Arrow: Alpha transparency (a = ", double( colour.getAlphaI() ), ")" );
    drawTextShaded( font, temp, 10, 30, fColour, bColour );

    temp = Utils::concat( "Q / A: Y-scale (scaleY = ", scaleY, ")" );
    drawTextShaded( font, temp, 10, 50, fColour, bColour );

    temp = Utils::concat( "W / S: X-scale (scaleX = ", scaleX, ")" );
    drawTextShaded( font, temp, 10, 70, fColour, bColour );

    temp = Utils::concat( "E / D: X-centre (centreX = ", centreX, ")" );
    drawTextShaded( font, temp, 10, 90, fColour, bColour );

    temp = Utils::concat( "R / F: Y-centre (centreY = ", centreY, ")" );
    drawTextShaded( font, temp, 10, 110, fColour, bColour );

    temp = Utils::concat( "T / G: Sprite index (index = ", index, ")" );
    drawTextShaded( font, temp, 10, 130, fColour, bColour );

    temp = Utils::concat( "fps (smooth/realtickratio): ",
                          1000.0/(timeFrames.back()-timeFrames.front()) * (timeFrames.size()-1), "/",
                          1/(timeFrames.back()-timeFrames[timeFrames.size() - 2]) * UPDATE_RATE );
    drawTextShaded( font, temp, 10, 150, fColour, bColour );

    temp = Utils::concat( "timeFrames stats: ",
                          "back:", timeFrames.back(), " ",
                          "front:", timeFrames.front(), " ",
                          "length:", timeFrames.back()-timeFrames.front(), " ",
                          "size:", timeFrames.size() );
    drawTextShaded( font, temp, 10, 170, fColour, bColour );

    glDisable( GL_TEXTURE_2D );
    glColor4ub( 255, 0, 0, 100 );
    glLineWidth( 1.0f );

    glBegin( GL_LINES );
    glVertex2i( (SDL_GetVideoInfo()->current_w) / 2, 0 );
    glVertex2i( (SDL_GetVideoInfo()->current_w) / 2, SDL_GetVideoInfo()->current_h );
    glEnd();

    glBegin( GL_LINES );
    glVertex2i( 0, (SDL_GetVideoInfo()->current_h) / 2 );
    glVertex2i( SDL_GetVideoInfo()->current_w, (SDL_GetVideoInfo()->current_h) / 2 );
    glEnd();

    glColor4ub( 255, 255, 255, 255 );

    glEnable( GL_TEXTURE_2D );

    // Refresh
    SDL_GL_SwapBuffers();
}

int main( int argc, char **argv )
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
    printf( "Init: SDL_Mixer...\n" );
    if ( Mix_OpenAudio( AUDIO_RATE, AUDIO_FORMAT, AUDIO_CHAN, AUDIO_BUFFERS ) != 0 )
    {
        printf( "Unable to initialise SDL_Mixer: %s\n", Mix_GetError() );
        exit( EXIT_FAILURE );
    }

    printf( "Completed library inits.\n" );

    InfoSheet::preInit();

    Utils::init();

    std::string fontDir;
    fontDir.append( FONTS_DIR );
    fontDir.append( "sauce8bit.ttf" );
    font = TTF_OpenFont( fontDir.c_str(), 32 );

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, true );

    SDL_Surface *screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_OPENGL | SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER );

    // GL bullshit
    initGL();

    SDL_WM_SetCaption( WINDOW_TITLE, 0 );

    Sprite sprite( "csstrip.png", 32, 32, centreX, centreY );
    AnimatedSprite anim( "csstrip.png", ANIM_RATE, 2, 3, true, 32, 32, 16, 16 );
    AnimatedSprite *paper = new AnimatedSprite( "sheets.png", 100, 0, 4, true, 10, 10, 5, 5 );

    printf( "Entering game loop.\n" );
    while ( gameRunning )
    {
        timeLastMs = timeCurrentMs;
        timeCurrentMs = SDL_GetTicks();
        timeDeltaMs = timeCurrentMs - timeLastMs;
        timeAccumulatedMs += timeDeltaMs;

        //this is a while just in case the FPS goes below the update rate
        while ( timeAccumulatedMs >= UPDATE_RATE )
        {
            timeFrames.push_back(timeCurrentMs);
            while( timeFrames[0]+1000 < timeCurrentMs )
                timeFrames.erase( timeFrames.begin() );

            // Update. Physics. Inputs. AI.
            processInput( sprite );

            anim.update( screen, timeAccumulatedMs );
            paper->update( screen, timeAccumulatedMs );

            if ( Utils::randomInt( 1, 100 ) <= SHEET_CHANCE )
            {
                sheets.push_back( new InfoSheet( SDL_GetVideoInfo()->current_w - 73.0d + (Utils::randomInt( 0, 6 ) - 3.0d), SDL_GetVideoInfo()->current_h - 70.0d + (Utils::randomInt( 0, 6 ) - 3.0d), (Utils::randomInt( 0, 8 ) - 8.0d), (Utils::randomInt( 0, 20 ) - 10) / 10.0d ) );
                //printf( "Creating a new sheet. There are now %i sheets.\n", sheets.size() );
            }
            if ( sheets.size() > 0 )
            {
                for ( int i = 0; i < sheets.size(); i++ )
                {
                    (sheets[i])->update( screen, timeAccumulatedMs );
                }

                // You only really need to check the first item, it's the "oldest"
                if ( !((sheets[0])->isVisible()) )
                {
                    //printf( "Deleting a sheet. There are now %i sheets.\n", sheets.size() );
                    delete sheets[0];
                    sheets.erase( sheets.begin() );
                }
            }

            timeAccumulatedMs -= UPDATE_RATE;

            // Render everything if the updating for this tick is done
            if( timeAccumulatedMs < UPDATE_RATE )
                render( screen, sprite, anim, paper );
        }
    }

    printf( "Exiting game loop.\n" );

    delete paper;
    cleanUp();

    printf( "Exiting regularly." );

    exit( EXIT_SUCCESS );
}
