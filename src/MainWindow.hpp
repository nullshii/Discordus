#pragma once

#include "FileSerializer.hpp"
#include <wx/wx.h>

class MainWindow : public wxFrame {
public:
  MainWindow();

private:
  void OnSave(wxCommandEvent &event);
  void OnOpen(wxCommandEvent &event);
  void OnExit(wxCommandEvent &event);

  wxStaticText *m_Text;
};
