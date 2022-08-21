#include "App.h"
#include "MainWindow.h"

bool App::OnInit() {
  MainWindow *window = new MainWindow();
  window->Show(true);
  return true;
}

wxIMPLEMENT_APP(App);
