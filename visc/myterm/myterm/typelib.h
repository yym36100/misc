#pragma once


#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_LCD_FILTER_H


#include "specialchars.h"

struct typelib {
	FT_Library  library;
	FT_Face     face;
	int error;
	int size;
	unsigned char *surf;
	int ax, ay;
	int gridx, gridy;

	typelib(void){
		error = FT_Init_FreeType( &library );
		ax=ay=0;
	}
	~typelib(void){
		FT_Done_FreeType(library);
	}

	void init(char *fontfile, int sz = 12){
		error = FT_New_Face( library,fontfile,0,&face );

		//todo move this to init?
		error = FT_Library_SetLcdFilter(library,FT_LCD_FILTER_NONE);

		size =sz;
		error = FT_Set_Pixel_Sizes(
			face,   /* handle to face object */
			0,      /* pixel_width           */
			size );   /* pixel_height          */ //10xx18

		int glyph_index;

		FT_GlyphSlot  slot;
		glyph_index = FT_Get_Char_Index( face, 0x2591 );

		error = FT_Load_Glyph(
			face,          /* handle to face object */
			glyph_index,   /* glyph index           */
			FT_LOAD_DEFAULT  );  /* load flags, see below */

		error = FT_Render_Glyph( face->glyph,   /* glyph slot  */
			/*FT_RENDER_MODE_MONO*/ FT_RENDER_MODE_NORMAL/*FT_RENDER_MODE_LCD*/ ); /* render mode */		
		slot = face->glyph;
		gridy = slot->bitmap.rows;
		gridx = slot->bitmap.width;

	}

	void setSurface(unsigned char *_surf){
		surf = _surf;
	}

	void fillRect(int x, int y, int w, int h, int color){
		unsigned char *pp = (unsigned char*)surf;
		pp+= (x + y * www) * 4;

		for(int yy=0;yy<h;yy++){
			for(int xx = 0;xx<w;xx++){
				*(pp + (xx + yy * www)*4 + 0) = color&0xff;
				*(pp + (xx + yy * www)*4 + 1) = color&0xff;
				*(pp + (xx + yy * www)*4 + 2) = color&0xff;
				*(pp + (xx + yy * www)*4 + 3) = color&0xff;
			}
	}
}

void drawChar(int x, int y, wchar_t c) {
	int glyph_index;

	FT_GlyphSlot  slot;
	glyph_index = FT_Get_Char_Index( face, c );

	error = FT_Load_Glyph(
		face,          /* handle to face object */
		glyph_index,   /* glyph index           */
		FT_LOAD_DEFAULT  );  /* load flags, see below */

	error = FT_Render_Glyph( face->glyph,   /* glyph slot  */
		/*FT_RENDER_MODE_MONO*/ FT_RENDER_MODE_NORMAL/*FT_RENDER_MODE_LCD*/ ); /* render mode */

	slot = face->glyph;
	//todo clear char grid first?
	fillRect(x,y+4,gridx,gridy,0xff);
	drawBitmap( &slot->bitmap,x + slot->bitmap_left,16 + y - slot->bitmap_top );
	ax = slot->advance.x >> 6;
	ay = slot->advance.y >> 6;
}

void drawText(int x, int y, wchar_t *text){
	while (*text){
		drawChar(x,y,*text++);
		x+=ax;
		y+=ay;
	}
}

void drawVbar(int x, int y, int val){
	enum {
		start = 0x2581,
		num = 8 };

		val %= num;
		drawChar(x,y,start + val);
}

private:
	void drawBitmap(FT_Bitmap*  bitmap, FT_Int x,FT_Int y) {
		FT_Int  i, j, p, q;
		FT_Int  x_max = x + bitmap->width;
		FT_Int  y_max = y + bitmap->rows;
		unsigned char *pp = (unsigned char*)surf;

		for ( i = x, p = 0; i < x_max; i++, p+=1 )
		{
			for ( j = y, q = 0; j < y_max; j++, q++ )
			{
				if ( i < 0      || j < 0       ||
					i >= www || j >= hhh )
					continue;

				//      image[j][i] |= bitmap->buffer[q * bitmap->width + p];
				*(pp + (i + j * www)*4 + 0) = 255-bitmap->buffer[q * bitmap->pitch + p];
				*(pp + (i + j * www)*4 + 1) = 255-bitmap->buffer[q * bitmap->pitch + p+0];
				*(pp + (i + j * www)*4 + 2) = 255-bitmap->buffer[q * bitmap->pitch + p+0];			
			}
		}
	}

};