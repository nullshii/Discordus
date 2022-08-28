#include "App.hpp"
#include "MainWindow.hpp"
#include "NumberValidator.hpp"

bool App::OnInit() {
  NumberValidator::Init();
  MainWindow *window = new MainWindow();
  window->Show(true);
  return true;
}

wxIMPLEMENT_APP(App);
