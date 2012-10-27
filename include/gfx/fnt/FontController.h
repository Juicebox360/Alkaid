#ifndef FONTCONTROLLER_H
#define FONTCONTROLLER_H

#include <string>
#include <vector>

#include "gfx/fnt/Font.h"
#include "gfx/fnt/FontController.h"

class FontController
{
    public:
        FontController();
        virtual ~FontController();
        Font *create_font( std::string fontname, int fontsize = 16 );
        void clean_up();
    protected:
    private:
        std::vector<Font*> fonts;
};

#endif // FONTCONTROLLER_H
