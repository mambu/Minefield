/*
 * File:   main.cpp
 * Author: Marco Ambu
 *
 * Created on August 22, 2010, 6:01 PM
 */

#include "MainWindow.h"
#if QT_VERSION >= 0x050000
#include <QtWidgets/QApplication>
#else
#include <QtGui/QApplication>
#endif

int main(int argc, char *argv[]) {
  // initialize resources, if needed
  // Q_INIT_RESOURCE(resfile);

  QApplication app(argc, argv);

  // create and show your widgets here

  QMainWindow* mainWindow = new MainWindow();
  mainWindow->show();

  return app.exec();
}
