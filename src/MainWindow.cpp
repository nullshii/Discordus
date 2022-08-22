#include "MainWindow.hpp"

#include "FileSerializer.hpp"
#include "PresenceData.hpp"

#include <cstring>

MainWindow::MainWindow() : wxFrame(NULL, wxID_ANY, "Discordus") {
  this->SetMinSize(wxSize(800, 500));

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

  m_Text = new wxStaticText(this, wxID_ANY, "AAAAAAAAAAAAAA");

  this->SetMenuBar(menuBar);

  Bind(wxEVT_MENU, &MainWindow::OnSave, this, wxID_SAVE);
  Bind(wxEVT_MENU, &MainWindow::OnOpen, this, wxID_OPEN);
  Bind(wxEVT_MENU, &MainWindow::OnExit, this, wxID_EXIT);
}

void MainWindow::OnSave(wxCommandEvent &event) {
  PresenceData data;
  data.number = 52;
  strcpy(data.text, "SomeText");
  FileSerializer::Serialize<PresenceData>(&data, "File.sav");
}

void MainWindow::OnOpen(wxCommandEvent &event) {
  PresenceData data;
  FileSerializer::Deserialize<PresenceData>(&data, "File.sav");
  m_Text->SetLabel(std::to_string(data.number) + " " + data.text);
}

void MainWindow::OnExit(wxCommandEvent &event) { Close(true); }