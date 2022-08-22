#include "MainWindow.hpp"

#include "FileSerializer.hpp"
#include "PresenceData.hpp"
#include "wx/textctrl.h"

#include <cstring>

enum ID {
  StatusText,
  DescriptionText,
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

MainWindow::MainWindow() : wxFrame(NULL, wxID_ANY, "Discordus") {
  this->SetMinSize(wxSize(800, 500));
  this->SetMenuBar(CreateMenuBar());

  m_StatusText = new wxTextCtrl(this, ID::StatusText);
  m_StatusText->SetMaxLength(sizeof(PresenceData::Status));

  m_DescriptionText = new wxTextCtrl(this, ID::DescriptionText);
  m_DescriptionText->SetMaxLength(sizeof(PresenceData::Description));

  Bind(wxEVT_MENU, &MainWindow::OnSave, this, wxID_SAVE);
  Bind(wxEVT_MENU, &MainWindow::OnOpen, this, wxID_OPEN);
  Bind(wxEVT_MENU, &MainWindow::OnAbout, this, wxID_ABOUT);
  Bind(wxEVT_MENU, &MainWindow::OnExit, this, wxID_EXIT);
}

void MainWindow::OnSave(wxCommandEvent &event) {
  PresenceData data;
  memset(&data, 0, sizeof(data));

  m_DescriptionText->SaveFile("File.dat");

  strcpy(data.Status, m_StatusText->GetLineText(0).data());
  strcpy(data.Description, m_DescriptionText->GetLineText(0).data());

  FileSerializer::Serialize<PresenceData>(&data, "File.sav");
}

void MainWindow::OnOpen(wxCommandEvent &event) {
  PresenceData data;
  FileSerializer::Deserialize<PresenceData>(&data, "File.sav");

  m_StatusText->SetValue(data.Status);
  m_DescriptionText->SetValue(data.Description);
}

void MainWindow::OnAbout(wxCommandEvent &event) {
  wxMessageBox("App still under development :)\n"
               "I'm trying to make good product",
               "About");
}

void MainWindow::OnExit(wxCommandEvent &event) { Close(true); }