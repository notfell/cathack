#include "../all.h"

static int64_t eptime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

void Discord::Initialize()
{
	DiscordEventHandlers Handle;
	memset(&Handle, 0, sizeof(Handle));
	Discord_Initialize("1062110098589225052", &Handle, 1, NULL); //Your Api Key
}

void Discord::Update()
{
	//Copy Your Api Pre-Visualize
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.state = "";
	discordPresence.details = "me0wing on </ac_cli3nt>";
	discordPresence.startTimestamp = eptime;
	discordPresence.largeImageKey = "image";
	discordPresence.largeImageText = "cathack";
	Discord_UpdatePresence(&discordPresence);
}

void Discord::Shutdown()
{
	Discord_ClearPresence();
	Discord_Shutdown();
}