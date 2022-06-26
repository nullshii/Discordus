#pragma once

#include <discord_rpc.h>

class DiscordRPC
{
public:
    DiscordRPC(const char *appId);
    ~DiscordRPC();

    void SetPresence(DiscordRichPresence &presence);
    void UpdatePresence();
    void ClearPresence();

    void SetInstance(int &instance);
    void SetState(const char *state);
    void SetDetails(const char *details);
    void SetStartTimestamp(int64_t &startTimeStamp);
    void SetEndTimestamp(int64_t &endTimeStamp);
    void SetJoinSecret(const char *joinSecret);
    void SetMatchSecret(const char *matchSecret);
    void SetSpectateSecret(const char *spectateSecret);
    void SetLargeImageKey(const char *largeImageKey);
    void SetLargeImageText(const char *largeImageText);
    void SetSmallImageKey(const char *smallImageKey);
    void SetSmallImageText(const char *smallImageText);
    void SetPartyId(const char *partyId);
    void SetPartySize(int &partySize);
    void SetPartyMax(int &partyMax);
    void SetPartyPrivacy(int &partyPrivacy);

private:
    static void handleDiscordReady(const DiscordUser *connectedUser);
    static void handleDiscordDisconnected(int errcode, const char *message);
    static void handleDiscordError(int errcode, const char *message);
    static void handleDiscordJoin(const char *secret);
    static void handleDiscordSpectate(const char *secret);
    static void handleDiscordJoinRequest(const DiscordUser *request);
    static void internalUpdate();

private:
    DiscordRichPresence m_Presence;
    DiscordEventHandlers m_Handlers;
};
