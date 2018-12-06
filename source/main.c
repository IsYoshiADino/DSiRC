// devkitARM and libnds includes
//#include <dswifi9.h>
#include <nds.h>
#include <maxmod9.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>

// Custom includes
#include "libircclient.h"
#include "gl2d.h"

// System includes
#include <stdio.h>
#include <string.h>

// Build-only includes
#include "image.h"
#include "soundbank.h"
#include "soundbank_bin.h"

static mm_sound_effect notify = { { SFX_NOTIFY }, (int)(1.0f * (1<<10)), 0, 255, 255, };

struct Settings {
	char[128] Name; // The Username for the User, of course.
	char[128] Server; // We need something which can get our IP in the end.
	char[128] Channel; // Just so we don't feel lonely.
};

void OnKeyPressed(int key) {
	if(key > 0) iprintf("%c", key);
}

void OpenBrowser(char* url) {
	// soon:tm:
}

void Save(Settings settings) {
	// soon:tm:
}

void Connect(Settings settings) {
	/* soon:tm:
	At least there some weirdo code

    if(!Wifi_InitDefault(WFC_CONNECT)) {
		iprintf("Failed to initialize the WiFi connection!");
		return 1;
	} else {
		iprintf("\nConnected to the Internet, time to connect to the IRC server.");
		// Server connection stuff
	}*/
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
		
		// At least you can set something.
		struct Settings settings;
	    char name[128]; // I think that's enough.
		char server[128]; // urls can't be longer, can they?
		char channel[128]; // the channel name should be short.
		
		// So lemme spy on you for a short time
		iprintf("\nWhat's your Username?\n");
		scanf("%s", name);
		iprintf("\n What IRC server do you want to connect to?\n");
		scanf("%s", server);
		iprintf("\nWhat IRC channel do you want to use?\n");
		scanf("%s", channel);
		
		// So let's create the actual settings object.
		strcpy(settings.Name, name);
		strcpy(settings.Server, server);
		strcpy(settings.Channel, channel);

		// Good clean fun:tm:
		swiWaitForVBlank();
		consoleClear();
		
		// Let the user choose something.
		int keyPressed = keysDown();
		iprintf("Current settings:\nName: %s\nServer: %s\nChannel: %s\n\nWould you like to save your settings?\n(A) Yes  (B) No  (X) Return", settings.Name, settings.Server, settings.Channel);
		if (keyPressed & KEY_A ) {
			Save(settings);
			Connect(settings);
		}
		if (keyPressed & KEY_B) {
			Connect(settings);
		} 
		if (keyPressed & KEY_X) {
			continue;
		} 
	}
	return 0;
}