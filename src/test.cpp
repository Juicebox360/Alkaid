/*
void drawTextShaded( SDL_Surface *surface, TTF_Font *font, std::string *text, int dX, int dY, Colour &foregroundColour, Colour &backgroundColour )
{
    SDL_Surface *textSurfaceFrnt, *textSurfaceBack;

    if ( !(textSurfaceFrnt = TTF_RenderUTF8_Blended( font, text->c_str(), foregroundColour.toEngineFormat() ) ) )
    {
        handleTTFError();
    }
    if ( !(textSurfaceBack = TTF_RenderUTF8_Blended( font, text->c_str(), backgroundColour.toEngineFormat() ) ) )
    {
        handleTTFError();
    }

    int w = textSurfaceFrnt->w, h = textSurfaceFrnt->h;

    GLuint textureFrnt, textureBack;
    textProcess( &textureFrnt, textSurfaceFrnt );
    textProcess( &textureBack, textSurfaceBack );

    //glClear( GL_COLOR_BUFFER_BIT );
    /*
    glTranslatef( dX + SHADOW_SPACING, dY + SHADOW_SPACING, 0.0 );

    glBindTexture( GL_TEXTURE_2D, textureBack );

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

    glBindTexture( GL_TEXTURE_2D, textureFrnt );

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

    glDeleteTextures( 1, &textureFrnt );
    glDeleteTextures( 1, &textureBack );
}
*/
