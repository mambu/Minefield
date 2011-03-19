/* 
 * File:   MainWindow.h
 * Author: Marco Ambu
 *
 * Created on August 22, 2010, 6:20 PM
 */

#ifndef _MAINWINDOW_H
#define	_MAINWINDOW_H

#include "ui_MainWindow.h"
#include <QObjectUserData>

class Minefield;
class QSignalMapper;

class MyQObjectUserData : public QObjectUserData
{
public:
  MyQObjectUserData(std::size_t x, std::size_t y)
    : X(x), Y(y)
  {}

public:
  std::size_t X;
  std::size_t Y;
};

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow();
  virtual ~MainWindow();

public slots:
  Q_SLOT void newMineField();
  Q_SLOT void test(QWidget *widget);
  Q_SLOT void about();
  Q_SLOT void aboutQt();


private:
  void createMineField(int width, int height, int bombs);
  void updateMinefield(bool showAll);

private:
  Ui::MainWindow widget;

  QSignalMapper *signalMapper_;
  Minefield* minefield_;
};

#endif	/* _MAINWINDOW_H */
