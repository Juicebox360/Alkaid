#include <string>
#include <vector>

#include <SDL2/SDL_ttf.h>

#include "gfx/fnt/FontController.h"
#include "util/Utils.h"
#include "util/Constants.h"

FontController::FontController()
{
}

FontController::~FontController()
{
}

void FontController::clean_up()
{
    for ( std::vector<Font*>::iterator font = fonts.begin(); font < fonts.end(); font++ )
    {
        delete *font;
        *font = NULL;
    }
}

Font *FontController::create_font( std::string fontname, int fontsize )
{
    Font *_font = new Font( TTF_OpenFont( Utils::concat( Constants::FONTS_DIR, fontname ).c_str(), fontsize ) );
    fonts.push_back( _font );
    return _font;
}
