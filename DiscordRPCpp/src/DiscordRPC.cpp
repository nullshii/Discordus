#include "DiscordRPC.h"

#include <stdio.h>
#include <memory.h>
#include <time.h>

DiscordRPC::DiscordRPC(const char *appId)
{
    memset(&m_Presence, 0, sizeof(m_Presence));
    m_Presence.instance = 0;

    m_Presence.state = "State";
    m_Presence.details = "Details";

    m_Presence.startTimestamp = time(0);
    m_Presence.endTimestamp = time(0) + 5 * 60;

    m_Presence.joinSecret = "Join";
    m_Presence.matchSecret = "Match";
    m_Presence.spectateSecret = "Look";

    m_Presence.largeImageKey = "Discordus";
    m_Presence.largeImageText = "Discordus";
    m_Presence.smallImageKey = "Discordus";
    m_Presence.smallImageText = "Discordus";

    m_Presence.partyId = "SomeParty";
    m_Presence.partySize = 2;
    m_Presence.partyMax = 6;
    m_Presence.partyPrivacy = DISCORD_PARTY_PUBLIC;

    memset(&m_Handlers, 0, sizeof(m_Handlers));
    m_Handlers.ready = handleDiscordReady;
    m_Handlers.disconnected = handleDiscordDisconnected;
    m_Handlers.errored = handleDiscordError;
    m_Handlers.joinGame = handleDiscordJoin;
    m_Handlers.spectateGame = handleDiscordSpectate;
    m_Handlers.joinRequest = handleDiscordJoinRequest;
    Discord_Initialize(appId, &m_Handlers, 1, nullptr);
}

DiscordRPC::~DiscordRPC() = default;

void DiscordRPC::SetPresence(DiscordRichPresence &presence)
{
    m_Presence = presence;
}

void DiscordRPC::UpdatePresence()
{
    Discord_UpdatePresence(&m_Presence);
    internalUpdate();
}

void DiscordRPC::ClearPresence()
{
    Discord_ClearPresence();
    internalUpdate();
}

#pragma region Setters

void DiscordRPC::SetInstance(int &instance)
{
    m_Presence.instance = instance;
}

void DiscordRPC::SetState(const char *state)
{
    m_Presence.state = state;
}

void DiscordRPC::SetDetails(const char *details)
{
    m_Presence.details = details;
}

void DiscordRPC::SetStartTimestamp(int64_t &startTimeStamp)
{
    m_Presence.startTimestamp = startTimeStamp;
}

void DiscordRPC::SetEndTimestamp(int64_t &endTimeStamp)
{
    m_Presence.endTimestamp = endTimeStamp;
}

void DiscordRPC::SetJoinSecret(const char *joinSecret)
{
    m_Presence.joinSecret = joinSecret;
}

void DiscordRPC::SetMatchSecret(const char *matchSecret)
{
    m_Presence.matchSecret = matchSecret;
}

void DiscordRPC::SetSpectateSecret(const char *spectateSecret)
{
    m_Presence.spectateSecret = spectateSecret;
}

void DiscordRPC::SetLargeImageKey(const char *largeImageKey)
{
    m_Presence.largeImageKey = largeImageKey;
}

void DiscordRPC::SetLargeImageText(const char *largeImageText)
{
    m_Presence.largeImageText = largeImageText;
}

void DiscordRPC::SetSmallImageKey(const char *smallImageKey)
{
    m_Presence.smallImageKey = smallImageKey;
}

void DiscordRPC::SetSmallImageText(const char *smallImageText)
{
    m_Presence.smallImageText = smallImageText;
}

void DiscordRPC::SetPartyId(const char *partyId)
{
    m_Presence.partyId = partyId;
}

void DiscordRPC::SetPartySize(int &partySize)
{
    m_Presence.partySize = partySize;
}

void DiscordRPC::SetPartyMax(int &partyMax)
{
    m_Presence.partyMax = partyMax;
}

void DiscordRPC::SetPartyPrivacy(int &partyPrivacy)
{
    m_Presence.partyPrivacy = partyPrivacy;
}

#pragma endregion // Setters

#pragma region Internal

void DiscordRPC::handleDiscordReady(const DiscordUser *connectedUser)
{
    printf("Discord: connected to user %s#%s - %s\n",
           connectedUser->username,
           connectedUser->discriminator,
           connectedUser->userId);
}

void DiscordRPC::handleDiscordDisconnected(int errcode, const char *message)
{
    printf("Discord: disconnected (%d: %s)\n", errcode, message);
}

void DiscordRPC::handleDiscordError(int errcode, const char *message)
{
    printf("Discord: error (%d: %s)\n", errcode, message);
}

void DiscordRPC::handleDiscordJoin(const char *secret)
{
    printf("Discord: join (%s)\n", secret);
}

void DiscordRPC::handleDiscordSpectate(const char *secret)
{
    printf("Discord: spectate (%s)\n", secret);
}

void DiscordRPC::handleDiscordJoinRequest(const DiscordUser *request)
{
    printf("\nDiscord: join request from %s#%s - %s\n",
           request->username,
           request->discriminator,
           request->userId);

    Discord_Respond(request->userId, DISCORD_REPLY_YES);
}

void DiscordRPC::internalUpdate()
{
#ifdef DISCORD_DISABLE_IO_THREAD
    Discord_UpdateConnection();
#endif
    Discord_RunCallbacks();
}

#pragma endregion // Internal