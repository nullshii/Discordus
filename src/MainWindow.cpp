#include "MainWindow.hpp"

#include <cstdlib>
#include <fstream>
#include <string>

#define TEXT_CTRL_COUNT 8

enum ID {
  ButtonConnect,
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

const char *hints[] = {
    "App ID",           "Status",          "Description",      "Large image key",
    "Large image text", "Small image key", "Small image text", "Time",
};

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame) EVT_BUTTON(ButtonConnect, MainWindow::ConnectToDiscord)
    EVT_BUTTON(ButtonUpdate, MainWindow::UpdatePresence) wxEND_EVENT_TABLE();

MainWindow::MainWindow() : wxFrame(NULL, wxID_ANY, "Discordus") {
  this->SetMinSize(wxSize(400, 310));
  this->SetMenuBar(CreateMenuBar());
  this->CreateStatusBar();

  m_textFields = new wxTextCtrl *[TEXT_CTRL_COUNT];

  wxGridSizer *container = new wxGridSizer(2);
  this->SetSizer(container);
  container->Layout();

  wxTextValidator numberValidator(wxFILTER_INCLUDE_CHAR_LIST);
  wxArrayString list;
  wxString valid_chars(wxT("0123456789"));
  size_t len = valid_chars.Length();
  for (size_t i = 0; i < len; i++)
    list.Add(wxString(valid_chars.GetChar(i)));
  numberValidator.SetIncludes(list);

  for (int i = 0; i < TEXT_CTRL_COUNT; i++) {
    if (i == 0 || i == TEXT_CTRL_COUNT - 1)
      m_textFields[i] = new wxTextCtrl(this, i, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, numberValidator);
    else
      m_textFields[i] = new wxTextCtrl(this, i);

    m_textFields[i]->SetHint(hints[i]);
    container->Add(m_textFields[i], 1, wxEXPAND | wxALL, 5);
  }

  wxButton *LaunchButton = new wxButton(this, ID::ButtonConnect, "Connect");
  wxButton *UpdateButton = new wxButton(this, ID::ButtonUpdate, "Update");

  container->Add(LaunchButton, 1, wxALL | wxEXPAND, 5);
  container->Add(UpdateButton, 1, wxALL | wxEXPAND, 5);

  this->Bind(wxEVT_MENU, &MainWindow::OnSave, this, wxID_SAVE);
  this->Bind(wxEVT_MENU, &MainWindow::OnOpen, this, wxID_OPEN);
  this->Bind(wxEVT_MENU, &MainWindow::OnAbout, this, wxID_ABOUT);
  this->Bind(wxEVT_MENU, &MainWindow::OnExit, this, wxID_EXIT);
}

MainWindow::~MainWindow() { delete[] m_textFields; }

void MainWindow::OnSave(wxCommandEvent &event) {
  for (int i = 0; i < TEXT_CTRL_COUNT; i++) {
    if (m_textFields[i]->GetLineText(0).IsEmpty()) {
      wxMessageBox("Fill all fields to save!", "Warning", wxOK | wxCENTRE | wxICON_WARNING);
      return;
    }
  }

  std::ofstream file("File.sav", std::ios::binary | std::ios::out);
  if (!file)
    return;

  for (int i = 0; i < TEXT_CTRL_COUNT; i++) {
    file << m_textFields[i]->GetLineText(0) << std::endl;
  }

  file.close();
}

void MainWindow::OnOpen(wxCommandEvent &event) {
  std::string tmpString;

  std::ifstream file("File.sav", std::ios::binary | std::ios::in);
  if (!file)
    return;

  for (int i = 0; i < TEXT_CTRL_COUNT; i++) {
    file >> tmpString;
    m_textFields[i]->SetValue(tmpString);
  }

  file.close();
}

void MainWindow::OnAbout(wxCommandEvent &event) {
  wxMessageBox("App still under development :)\n"
               "I'm trying to make good product",
               "About", wxOK | wxCENTRE | wxICON_NONE);
}

void MainWindow::ConnectToDiscord(wxCommandEvent &event) { SetStatusText("Connected"); }
void MainWindow::UpdatePresence(wxCommandEvent &event) {
  SetStatusText(std::to_string(this->GetSize().GetX()) + ", " + std::to_string(this->GetSize().GetY()));
}

void MainWindow::OnExit(wxCommandEvent &event) { Close(true); }