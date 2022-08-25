#include "MainWindow.hpp"

#include "FileSerializer.hpp"
#include "PresenceData.hpp"
#include "wx/event.h"
#include "wx/wxcrt.h"

#include <cstring>
#include <string>

enum ID {
  ButtonLaunch,
  ButtonUpdate,
};

wxMenuBar *CreateMenuBar() {
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

  return menuBar;
}

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame) EVT_BUTTON(ButtonLaunch, MainWindow::LaunchPresence)
    EVT_BUTTON(ButtonUpdate, MainWindow::UpdatePresence) wxEND_EVENT_TABLE();

MainWindow::MainWindow() : wxFrame(NULL, wxID_ANY, "Discordus") {
  this->SetMenuBar(CreateMenuBar());
  m_textFields = new wxTextCtrl *[8];

  wxGridSizer *fieldsContainer = new wxGridSizer(2);
  this->SetSizer(fieldsContainer);
  fieldsContainer->Layout();

  for (int i = 0; i < 8; i++) {
    m_textFields[i] = new wxTextCtrl(this, i);
    fieldsContainer->Add(m_textFields[i], 1, wxEXPAND | wxALL, 5);
  }

  m_textFields[0]->SetMaxLength(sizeof(PresenceData::AppId));
  m_textFields[0]->SetHint("App ID");
  m_textFields[1]->SetMaxLength(sizeof(PresenceData::Status));
  m_textFields[1]->SetHint("Status");
  m_textFields[2]->SetMaxLength(sizeof(PresenceData::Description));
  m_textFields[2]->SetHint("Description");
  m_textFields[3]->SetMaxLength(sizeof(PresenceData::LargeImageKey));
  m_textFields[3]->SetHint("Large image key");
  m_textFields[4]->SetMaxLength(sizeof(PresenceData::LargeImageText));
  m_textFields[4]->SetHint("Large image text");
  m_textFields[5]->SetMaxLength(sizeof(PresenceData::SmallImageKey));
  m_textFields[5]->SetHint("Small image key");
  m_textFields[6]->SetMaxLength(sizeof(PresenceData::SmallImageText));
  m_textFields[6]->SetHint("Small image text");
  m_textFields[7]->SetMaxLength(9);
  m_textFields[7]->SetHint("time");

  wxButton *LaunchButton = new wxButton(this, ID::ButtonLaunch, "Launch");
  wxButton *UpdateButton = new wxButton(this, ID::ButtonUpdate, "Update");

  wxBoxSizer *buttonsContainer = new wxBoxSizer(wxHORIZONTAL);
  buttonsContainer->Add(LaunchButton, 1, wxALL | wxEXPAND, 5);
  buttonsContainer->Add(UpdateButton, 1, wxALL | wxEXPAND, 5);
  fieldsContainer->Add(buttonsContainer, 1, wxALL | wxEXPAND);
  buttonsContainer->Layout();

  this->Bind(wxEVT_MENU, &MainWindow::OnSave, this, wxID_SAVE);
  this->Bind(wxEVT_MENU, &MainWindow::OnOpen, this, wxID_OPEN);
  this->Bind(wxEVT_MENU, &MainWindow::OnAbout, this, wxID_ABOUT);
  this->Bind(wxEVT_MENU, &MainWindow::OnExit, this, wxID_EXIT);
}

MainWindow::~MainWindow() { delete[] m_textFields; }

void MainWindow::OnSave(wxCommandEvent &event) {
  PresenceData data;
  memset(&data, 0, sizeof(data));

  data.AppId = wxAtoi(m_textFields[0]->GetLineText(0));
  strcpy(data.Status, m_textFields[1]->GetLineText(0).data());
  strcpy(data.Description, m_textFields[2]->GetLineText(0).data());
  strcpy(data.LargeImageKey, m_textFields[3]->GetLineText(0).data());
  strcpy(data.LargeImageText, m_textFields[4]->GetLineText(0).data());
  strcpy(data.SmallImageKey, m_textFields[5]->GetLineText(0).data());
  strcpy(data.SmallImageText, m_textFields[6]->GetLineText(0).data());
  data.time = wxAtol(m_textFields[7]->GetLineText(0));

  FileSerializer::Serialize<PresenceData>(&data, "File.sav");
}

void MainWindow::OnOpen(wxCommandEvent &event) {
  PresenceData data;
  FileSerializer::Deserialize<PresenceData>(&data, "File.sav");

  m_textFields[0]->SetValue(std::to_string(data.AppId));
  m_textFields[1]->SetValue(data.Status);
  m_textFields[2]->SetValue(data.Description);
  m_textFields[3]->SetValue(data.LargeImageKey);
  m_textFields[4]->SetValue(data.LargeImageText);
  m_textFields[5]->SetValue(data.SmallImageKey);
  m_textFields[6]->SetValue(data.SmallImageText);
  m_textFields[7]->SetValue(std::to_string(data.time));
}

void MainWindow::OnAbout(wxCommandEvent &event) {
  wxMessageBox("App still under development :)\n"
               "I'm trying to make good product",
               "About");
}

void MainWindow::LaunchPresence(wxCommandEvent &event) { wxMessageBox("Launched!"); }
void MainWindow::UpdatePresence(wxCommandEvent &event) { wxMessageBox("Updated!"); }

void MainWindow::OnExit(wxCommandEvent &event) { Close(true); }