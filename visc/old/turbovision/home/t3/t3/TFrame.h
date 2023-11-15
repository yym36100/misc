#pragma once

#define funky "-O|ooO  "
#define funky2 "\xb2\xb2\xb2\xb2\xb2\xb2  "
#define funky21 "\xb1\xb1\xb1\xb1\xb1\xb1  "
#define funky22 "\xb0\xb0\xb0\xb0\xb0\xb0  "
#define funky3 "-O|ooO  "
#define basic "xxxxxx  "
#define simple "\xc4\xbf\xb3\xd9\xc0\xda  "
#define doublel "\xcd\xbb\xba\xbc\xc8\xc9  "

struct TFrame : public TWidget {
	char *title;
	char *border;
	char attr;
	TFrame(uint8_t x, uint8_t y,uint8_t w, uint8_t h, char *_title = 0, char *_art = simple,char _attr = 0x07) : title(_title), border(_art),attr(_attr) {
		s.x = x; s.y = y;
		e.x = x + w - 1;
		e.y = y + h - 1;
	}

	void Draw(){
		uint16_t w = GetWidth();
		uint16_t h = GetHeight();
		uint16_t x = s.x, y = s.y;
		char *linebuff = new char[w+1];
		con->SetCurosrPos(lx + s.x, ly + s.y);
		con->SetColor(attr);

		for (int i = 1; i < w - 1; i++) { linebuff[i] = border[0]; }
		linebuff[0] = border[5]; linebuff[w - 1] = border[1]; linebuff[w] = 0;
		char *linebuff_a = new char[w+1];
		memset(linebuff_a,7,w+1);
		if (title) {

			int tl = strlen(title);
			char  *pt = title;
			if (tl > w - 4) tl = w - 4;			
						
			int offs = ((w - 4) - tl) / 2;
			for (int i = 0; i < tl; i++) {
				linebuff[2 + offs + i] = *pt++;
				linebuff_a[2 + offs + i] = 0x70;
			}
			linebuff[2 + offs - 1] = border[6];
			linebuff[2 + offs + tl] = border[7];
		}
		con->Write(linebuff,linebuff_a);
		if(linebuff_a) delete[] linebuff_a;
		
		con->SetCurosrPos(lx + x, ly + y + h -1);
		for (int i = 1; i < w - 1; i++) { linebuff[i] = border[0]; }
		linebuff[0] = border[4]; linebuff[w - 1] = border[3]; linebuff[w] = 0;
		con->Write(linebuff);

		linebuff[1] = 0;
		for (int i = 1; i < h - 1; i++) {
			linebuff[0] = border[2];
			con->SetCurosrPos(lx+x, ly+y + i);			
			con->Write(linebuff);
			con->SetCurosrPos(lx+x + w - 1, ly+y + i);			
			con->Write(linebuff);
		}

		delete[] linebuff;
	}
};


