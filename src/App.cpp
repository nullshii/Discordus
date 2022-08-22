#include "App.hpp"
#include "MainWindow.hpp"

bool App::OnInit() {
  MainWindow *window = new MainWindow();
  window->Show(true);
  return true;
}

wxIMPLEMENT_APP(App);
