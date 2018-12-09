//#include <dswifi9.h>
#include <fat.h>
#include <maxmod9.h>
#include <nds.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "libircclient.h"
#include "gl2d.h"
#include "image.h"
#include "soundbank.h"
#include "soundbank_bin.h"

static mm_sound_effect notify = { { SFX_NOTIFY }, (int)(1.0f * (1<<10)), 0, 255, 255, };

struct Settings {
	char* Name; // The Username for the User, of course.
	char* Server; // We need something which can get our IP in the end.
	char* Channel; // Just so we don't feel lonely.
};

void OnKeyPressed(int key) {
	if(key > 0) iprintf("%c", key);
}

void OpenBrowser(char* url) {
	// soon:tm:
}

// how to handle errors 101
void Error(char* message) {
	int keyPressed;
	swiWaitForVBlank();
	consoleClear();
	iprintf("An error occurred: %s\n(A) Reload (B) Exit");
	do {
		scanKeys();
		keyPressed = keysDown();
		if (keyPressed & KEY_A ) main();
		if (keyPressed & KEY_B) exit(0);
	} while(1);
}

void Save(struct Settings settings) {
	iprintf("FAT not working yet :(");
	return;
	/*if(!fatInitDefault()) Error("Failed to initialize SD Card.");	
	else {
		iprintf("\nInitialized SD Card. Saving data...");
		// nothing yet :(
		iprintf("\nDone.");
		return;
	}*/
}

void ConnectIRC(struct Settings settings) {
	iprintf("WiFi not working yet :(");
	return;
    /*if(!Wifi_InitDefault(true)) Error("Failed to initialize the WiFi connection!");
	else {
		iprintf("\nConnected to the Internet, time to connect to the IRC server.");
		// nothing yet :(
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
		
		// So lemme spy on you for a short time
		iprintf("\nWhat's your Username?\n");
		scanf("%s", settings.Name);
		iprintf("\n What IRC server do you want to connect to?\n");
		scanf("%s", settings.Server);
		iprintf("\nWhat IRC channel do you want to use?\n");
		scanf("%s", settings.Channel);

		// Good clean fun:tm:
		swiWaitForVBlank();
		consoleClear();
		
		// Is this actually better?
		int keyPressed;

		// Let the user choose something.
		iprintf("Current settings:\nName: %s\nServer: %s\nChannel: %s\n\nWould you like to save your settings?\n(A) Yes  (B) No  (START) Return", settings.Name, settings.Server, settings.Channel);
		do {
			swiWaitForVBlank();
			scanKeys();

			keyPressed = keysDown();
			if (keyPressed & KEY_A ) {
				Save(settings);
				ConnectIRC(settings);
			}
			if (keyPressed & KEY_B) ConnectIRC(settings);
			if (keyPressed & KEY_START) break;
		} while(1);

		// Just to clean after pressing X.
		swiWaitForVBlank();
		consoleClear();
	}
	return 0;
}