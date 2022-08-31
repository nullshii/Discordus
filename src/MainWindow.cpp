#include "MainWindow.hpp"
#include "NumberValidator.hpp"
#include "discord_rpc.h"
#include "wx/wxcrt.h"

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <functional>
#include <memory>
#include <string>

#define TEXT_CTRL_COUNT 8

enum ID {
  ButtonConnect,
  ButtonUpdate,
};

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame) EVT_BUTTON(ButtonConnect, MainWindow::ConnectToDiscord)
    EVT_BUTTON(ButtonUpdate, MainWindow::UpdatePresence) wxEND_EVENT_TABLE();

MainWindow::MainWindow() : wxFrame(NULL, wxID_ANY, "Discordus") {
  this->CreateMenuBar();
  this->SetMinSize(wxSize(400, 310));
  this->CreateStatusBar();

  container = new wxGridSizer(2);
  this->SetSizer(container);
  container->Layout();

  InitFields();

  wxButton *LaunchButton = new wxButton(this, ID::ButtonConnect, "Connect");
  wxButton *UpdateButton = new wxButton(this, ID::ButtonUpdate, "Update");

  container->Add(LaunchButton, 1, wxALL | wxEXPAND, 5);
  container->Add(UpdateButton, 1, wxALL | wxEXPAND, 5);

  this->Bind(wxEVT_MENU, &MainWindow::OnSave, this, wxID_SAVE);
  this->Bind(wxEVT_MENU, &MainWindow::OnOpen, this, wxID_OPEN);
  this->Bind(wxEVT_MENU, &MainWindow::OnAbout, this, wxID_ABOUT);
  this->Bind(wxEVT_MENU, &MainWindow::OnExit, this, wxID_EXIT);
}

void MainWindow::CreateMenuBar() {
  wxMenu *menuApp = new wxMenu();
  menuApp->Append(wxID_EXIT);

  wxMenu *menuFile = new wxMenu();
  menuFile->Append(wxID_SAVE);
  menuFile->Append(wxID_OPEN);

  wxMenu *menuHelp = new wxMenu();
  menuHelp->Append(wxID_ABOUT);

  wxMenuBar *menuBar = new wxMenuBar();
  menuBar->Append(menuApp, "&App");
  menuBar->Append(menuFile, "&File");
  menuBar->Append(menuHelp, "&Help");

  this->SetMenuBar(menuBar);
}

void MainWindow::InitFields() {
  m_AppIdField = new wxTextCtrl(this, wxID_ANY);
  m_StateField = new wxTextCtrl(this, wxID_ANY);
  m_DetailsField = new wxTextCtrl(this, wxID_ANY);
  m_StartTimestampField = new wxTextCtrl(this, wxID_ANY);
  m_EndTimestampField = new wxTextCtrl(this, wxID_ANY);
  m_LargeImageKeyField = new wxTextCtrl(this, wxID_ANY);
  m_SmallImageKeyField = new wxTextCtrl(this, wxID_ANY);
  m_LargeImageTextField = new wxTextCtrl(this, wxID_ANY);
  m_SmallImageTextField = new wxTextCtrl(this, wxID_ANY);
  m_PartySizeField = new wxTextCtrl(this, wxID_ANY);
  m_PartyMaxField = new wxTextCtrl(this, wxID_ANY);

  m_AppIdField->SetHint("App ID");
  m_StateField->SetHint("State");
  m_DetailsField->SetHint("Details");
  m_StartTimestampField->SetHint("Start timestamp");
  m_EndTimestampField->SetHint("End timestamp");
  m_LargeImageKeyField->SetHint("Large image key");
  m_SmallImageKeyField->SetHint("Small image key");
  m_LargeImageTextField->SetHint("Large image text");
  m_SmallImageTextField->SetHint("Small image text");
  m_PartySizeField->SetHint("Party size");
  m_PartyMaxField->SetHint("Party max");

  // TODO: Stretch app id field to entire row
  container->Add(m_AppIdField, 2, wxALL | wxEXPAND, 5);
  container->Add(m_StateField, 1, wxALL | wxEXPAND, 5);
  container->Add(m_DetailsField, 1, wxALL | wxEXPAND, 5);
  container->Add(m_StartTimestampField, 1, wxALL | wxEXPAND, 5);
  container->Add(m_EndTimestampField, 1, wxALL | wxEXPAND, 5);
  container->Add(m_LargeImageKeyField, 1, wxALL | wxEXPAND, 5);
  container->Add(m_SmallImageKeyField, 1, wxALL | wxEXPAND, 5);
  container->Add(m_LargeImageTextField, 1, wxALL | wxEXPAND, 5);
  container->Add(m_SmallImageTextField, 1, wxALL | wxEXPAND, 5);
  container->Add(m_PartySizeField, 1, wxALL | wxEXPAND, 5);
  container->Add(m_PartyMaxField, 1, wxALL | wxEXPAND, 5);

  m_StartTimestampField->SetValidator(NumberValidator::Validator);
  m_EndTimestampField->SetValidator(NumberValidator::Validator);
  m_PartyMaxField->SetValidator(NumberValidator::Validator);
  m_PartySizeField->SetValidator(NumberValidator::Validator);
}

void MainWindow::OnSave(wxCommandEvent &event) {
  // TODO: Implement save
}

void MainWindow::OnOpen(wxCommandEvent &event) {
  // TODO: Implement load
}

void MainWindow::OnAbout(wxCommandEvent &event) {
  wxMessageBox("App still under development :)\n"
               "I'm trying to make good product",
               "About", wxOK | wxCENTRE | wxICON_NONE);
}

void MainWindow::ConnectToDiscord(wxCommandEvent &event) {
  std::unique_ptr<DiscordEventHandlers> eventHandlers = std::make_unique<DiscordEventHandlers>();
  // TODO: Implement ready callback
  Discord_Initialize(m_AppIdField->GetLineText(0), eventHandlers.get(), 1, nullptr);
}

void MainWindow::UpdatePresence(wxCommandEvent &event) {
  DiscordRichPresence presence;
  memset(&presence, 0, sizeof(DiscordRichPresence));

  presence.state = m_StateField->GetLineText(0).c_str();
  presence.details = m_DetailsField->GetLineText(0).c_str();

  if (wxAtoi(m_StartTimestampField->GetLineText(0)) > 0)
    presence.startTimestamp = std::time(0) + wxAtoi(m_StartTimestampField->GetLineText(0));
  if (wxAtoi(m_EndTimestampField->GetLineText(0)) > 0)
    presence.endTimestamp = std::time(0) + wxAtoi(m_EndTimestampField->GetLineText(0));

  presence.largeImageKey = m_LargeImageKeyField->GetLineText(0).c_str();
  presence.smallImageKey = m_SmallImageKeyField->GetLineText(0).c_str();

  presence.largeImageText = m_LargeImageTextField->GetLineText(0).c_str();
  presence.smallImageText = m_SmallImageTextField->GetLineText(0).c_str();

  if (wxAtoi(m_PartySizeField->GetLineText(0)) > 0)
    presence.partySize = wxAtoi(m_PartySizeField->GetLineText(0));
  if (wxAtoi(m_PartyMaxField->GetLineText(0)) > 0)
    presence.partyMax = wxAtoi(m_PartyMaxField->GetLineText(0));

  Discord_UpdatePresence(&presence);
}

void MainWindow::OnDiscordReady(const DiscordUser *connectedUser) {
  // TODO: Implement discord callback
}

void MainWindow::OnExit(wxCommandEvent &event) {
  Discord_Shutdown();
  Close(true);
}