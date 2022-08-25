#pragma once

struct PresenceData {
  unsigned int AppId;
  char Status[20];
  char Description[20];
  char LargeImageKey[20];
  char LargeImageText[20];
  char SmallImageKey[20];
  char SmallImageText[20];
  unsigned long time;
};