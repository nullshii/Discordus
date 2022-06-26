#include <DiscordRPC.h>
#include <memory.h>
#include <iostream>
#include <time.h>

int main()
{
    DiscordRPC *rpc = new DiscordRPC("990661105124786196");

    rpc->SetLargeImageKey("discordus");
    rpc->SetLargeImageText("discordus");
    rpc->UpdatePresence();

    while (true)
    {
        std::cin.get();
        break;
    }

    delete rpc;
    return 0;
}