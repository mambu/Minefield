/*
 * File:   main.cpp
 * Author: Marco Ambu
 *
 * Created on August 22, 2010, 6:01 PM
 */

#include "MainWindow.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[]) {
  // initialize resources, if needed
  // Q_INIT_RESOURCE(resfile);

  QApplication app(argc, argv);

  // create and show your widgets here

  QMainWindow* mainWindow = new MainWindow();
  mainWindow->show();

  return app.exec();
}
