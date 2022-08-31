#pragma once

#include "discord_rpc.h"
#include <wx/wx.h>

class MainWindow : public wxFrame {
public:
  MainWindow();

private:
  void CreateMenuBar();
  void InitFields();

  void OnSave(wxCommandEvent &event);
  void OnOpen(wxCommandEvent &event);
  void OnAbout(wxCommandEvent &event);
  void OnExit(wxCommandEvent &event);

  void UpdatePresence(wxCommandEvent &event);
  void ConnectToDiscord(wxCommandEvent &event);

  static void OnDiscordReady(const DiscordUser *connectedUser);

  wxTextCtrl *m_AppIdField;
  wxTextCtrl *m_StateField;
  wxTextCtrl *m_DetailsField;
  wxTextCtrl *m_StartTimestampField;
  wxTextCtrl *m_EndTimestampField;
  wxTextCtrl *m_LargeImageKeyField;
  wxTextCtrl *m_SmallImageKeyField;
  wxTextCtrl *m_LargeImageTextField;
  wxTextCtrl *m_SmallImageTextField;
  wxTextCtrl *m_PartySizeField;
  wxTextCtrl *m_PartyMaxField;

  wxGridSizer *container;

  wxDECLARE_EVENT_TABLE();
};
