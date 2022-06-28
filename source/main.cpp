//Drawing test program 
//made with libnds and help from examples and documentation

#include <nds.h>
#include <stdio.h>
#include <nds/arm9/input.h>
#include <nds/arm9/video.h>
#include <nds/touch.h>



const int white = RGB5(255,255,255);
const int black = RGB5(0,0,0);
const int gray = RGB5(156,156,156);



int i = 0;
u16 currentX;
u16 currentY;

void init();
void OAMDraw(int index, u16 posX, u16 posY);

touchPosition touch;
u16* gfxSub;

bool clicking;

int main(void)
{

	init();
	
	//Initialise OAM 
	oamInit(&oamSub, SpriteMapping_1D_32, false);
	gfxSub = oamAllocateGfx(&oamSub, SpriteSize_16x16, SpriteColorFormat_256Color);
	
	for(i = 0; i < 16 * 16 / 2; i++)
	{
		gfxSub[i] = 1 | (1 << 8);
	}

	BG_PALETTE_SUB[0] = white;
	SPRITE_PALETTE_SUB[0] = black;
	SPRITE_PALETTE_SUB[2] = gray;
	
	
	
	
	while(1)
	{
		
		
		//Input checking
		scanKeys();
	
		int btnDown = keysDown();
		int btnHeld = keysHeld();
		//int btnUp = keysUp();
		
		
		if (btnHeld & KEY_TOUCH)
		{
			clicking = true;
			
			touchRead(&touch);
			
		}
	
			
		if (clicking == true)
		{
			OAMDraw(0, touch.px, touch.py);
			
		
		}
	
		//For loop for drawing more?
				/*for (u16 j = 0; j < 16 * 4; j++)
				{
						OAMDraw(2 + j, currentX - j, currentY - j);
						
						
				}*/
			
		if (btnHeld & KEY_R)
		{
			//Sort of the center
			touch.px = 115;
			touch.py = 88;
		}
		
		if (btnDown & KEY_L)
		{
			//Clears the sprite? Might have to look into memory
			clicking = false;
			oamClearSprite(&oamSub,0);
			oamClearSprite(&oamSub,2);
			//Is this freeing said memory?
			oamAllocReset(&oamSub);
		}
		
		iprintf("\x1b[0;0H(%d,%d)     ",touch.px, touch.py);
		
		
		
		oamUpdate(&oamSub);
        swiWaitForVBlank();
		
	}

}

void init()
{
	
	//lcdMainOnBottom();
	
	videoSetMode(MODE_0_2D /*| DISPLAY_SPR_ACTIVE | DISPLAY_BG0_ACTIVE | DISPLAY_SPR_1D*/);
	//videoSetModeSub(MODE_0_2D | DISPLAY_SPR_ACTIVE | DISPLAY_BG0_ACTIVE | DISPLAY_SPR_1D);
	videoSetModeSub(MODE_0_2D);
	
	vramSetBankA(VRAM_A_MAIN_BG);
	vramSetBankD(VRAM_D_SUB_SPRITE);
	
	
	
	consoleInit(0, 0,BgType_Text4bpp, BgSize_T_256x256, 31,0, true, true); 
	iprintf("\nFeel free to draw!\n");
	
}

void OAMDraw(int index, u16 posX, u16 posY)
{
	oamSet(&oamSub, 
			index, 
			posX, 
			posY, 
			0, 
			0,
			SpriteSize_16x16, 
			SpriteColorFormat_256Color, 
			gfxSub, 
			-1, 
			false, 
			false,			
			false, false, 
			false	
			);  
	
}

