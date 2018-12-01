//#include <dswifi9.h>
#include <nds.h>
#include <maxmod9.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>

#include <stdio.h>
#include <string.h>

#include "image.h"
#include "soundbank.h"
#include "soundbank_bin.h"

static mm_sound_effect notify = { { SFX_NOTIFY }, (int)(1.0f * (1<<10)), 0, 255, 255, };

void OnKeyPressed(int key) {
   if(key > 0) iprintf("%c", key);
}

int main(void) {
	defaultExceptionHandler(); // just to save us from cancer
	
	videoSetMode(MODE_5_2D);
	videoSetModeSub(MODE_0_2D);
	vramSetBankA(VRAM_A_MAIN_BG);
	
	consoleDemoInit();
	
	mmInitDefaultMem((mm_addr)soundbank_bin);
	mmLoadEffect(SFX_NOTIFY);
	
	Keyboard *kbd = keyboardDemoInit();
	kbd->OnKeyPressed = OnKeyPressed;
	
	bgInit(3, BgType_Bmp16, BgSize_B16_256x256, 0,0);
	decompress(imageBitmap, BG_GFX,  LZ77Vram);
	
	while(1) {
		iprintf("DSiRC - Version 1.0.0");
		
	    char name[128]; // I think thats enough.
		char server[128]; // urls can't be longer, can they?
		char channel[128]; // the channel name should be short.
		
		iprintf("\nWhat's your Username?\n");
		scanf("%s", name);
		
		iprintf("\n What IRC server do you want to connect to?\n");
		scanf("%s", server);
		
		iprintf("\nWhat IRC channel do you want to use?\n");
		scanf("%s", channel);
		
		/*if(!Wifi_InitDefault(WFC_CONNECT)) {
			iprintf("Failed to initialize the WiFi connection!");
			return 1;
		} else {
			iprintf("\nConnected to the Internet, time to connect to the IRC server.");
			// Server connection stuff
		}*/
		
		swiWaitForVBlank();
		consoleClear();
	}
	return 0;
}