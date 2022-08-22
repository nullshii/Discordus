#pragma once

#include "FileSerializer.hpp"
#include <wx/wx.h>

class MainWindow : public wxFrame {
public:
  MainWindow();

private:
  void OnSave(wxCommandEvent &event);
  void OnOpen(wxCommandEvent &event);
  void OnAbout(wxCommandEvent &event);
  void OnExit(wxCommandEvent &event);

  wxTextCtrl *m_StatusText;
  wxTextCtrl *m_DescriptionText;
};
