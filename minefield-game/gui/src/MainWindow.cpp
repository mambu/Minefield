/*
 * File:   MainWindow.cpp
 * Author: Marco Ambu
 *
 * Created on August 22, 2010, 6:20 PM
 */

#include "MainWindow.h"
#include "NewDialog.h"
#include "AboutDialog.h"
#include "Minefield.h"
#if QT_VERSION >= 0x050000
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMessageBox>
#else
#include <QtGui/QPushButton>
#include <QtGui/QMessageBox>
#endif
#include <QSignalMapper>
#include <QLayout>
#include <sstream>

MainWindow::MainWindow()
  : signalMapper_(NULL), minefield_(NULL)
{
  widget.setupUi(this);
}

MainWindow::~MainWindow()
{
  if (!minefield_)
    delete minefield_;
}

std::string toString(int number)
{
  if (number == -1)
    return "*";
  if (number == 0)
    return "";
  std::ostringstream os;
  os << number;
  return os.str();
}

void MainWindow::newMineField()
{
  NewDialog dialog(this);
  if (dialog.exec() == QDialog::Accepted)
  {
    int cols = dialog.getColumns();
    int rows = dialog.getRows();
    int difficulty = dialog.getDifficulty();
    int bombs = 1;
    if (difficulty == NewDialog::Easy)
      bombs = cols*rows/8;
    else if (difficulty == NewDialog::Medium)
      bombs = cols*rows/6;
    else
      bombs = cols*rows/4;
    createMineField(cols, rows, bombs);
  }
}

void clearLayout(QLayout *l)
{
	QLayoutItem *child;
  while ((child = l->takeAt(0)) != 0) {
    if (child->layout() != 0)
      clearLayout(child->layout());
    delete child->widget();
    delete child;
  }
}

void MainWindow::createMineField(int width, int height, int bombs)
{
  if (!minefield_)
    delete minefield_;
  if (signalMapper_)
    delete signalMapper_;

  try {
    minefield_ = new Minefield(width, height, bombs);
  }
  catch(std::exception& e)
  {
    return;
  }

  signalMapper_ = new QSignalMapper(this);

  
  QGridLayout *grid = widget.gridLayout_minefield;
  clearLayout(grid);
  widget.widget_minefield->setMinimumSize(30*width, 30*height);
  
  for (std::size_t y = 0; y < height; ++y)
  {
    for (std::size_t x = 0; x < width; ++x)
    {
      QPushButton *btn = new QPushButton(
              (minefield_->isVisible(x, y) ? toString(minefield_->getValue(x, y)).c_str() : ""),
              this);
      btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
      btn->setSizeIncrement(0, 0);
      btn->setFixedSize(30, 30);

      grid->addWidget(btn, y, x);
      btn->setUserData(0, new MyQObjectUserData(x, y));
      signalMapper_->setMapping(btn, btn);
      connect(btn, SIGNAL(clicked()),
         signalMapper_, SLOT (map()));
    }
  }

  connect(signalMapper_, SIGNAL(mapped(QWidget *)),
    this, SLOT(test(QWidget *)));
}

void MainWindow::test(QWidget *widget)
{
  std::size_t x = dynamic_cast<MyQObjectUserData*>(widget->userData(0))->X;
  std::size_t y = dynamic_cast<MyQObjectUserData*>(widget->userData(0))->Y;

  bool bombFound = minefield_->test(x, y);
  bool complete = minefield_->isComplete();
  updateMinefield(bombFound || complete);
  if (bombFound)
  {
    QMessageBox msgBox(QMessageBox::Warning, "Ops...", "You have found a bomb!");
    msgBox.exec();
  }
  if (complete)
  {
    QMessageBox msgBox(QMessageBox::Information, "Congratulations", "Game succesfully completed!");
    msgBox.exec();
  }
}

void MainWindow::updateMinefield(bool showAll)
{
  const QObjectList& buttons = widget.widget_minefield->children();

  int index = 0;
  std::size_t pos = 0;
  for ( ;
          index < buttons.count() && pos < minefield_->getHeight()*minefield_->getWidth();
          ++index)
  {
    QPushButton* btn = dynamic_cast<QPushButton*>(buttons.at(index));
    if (btn)
    {
      std::size_t x = dynamic_cast<MyQObjectUserData*>(btn->userData(0))->X;
      std::size_t y = dynamic_cast<MyQObjectUserData*>(btn->userData(0))->Y;

      if (minefield_->isVisible(x, y) || showAll)
      {
        int value = minefield_->getValue(x, y);
        if (value == 1)
          btn->setStyleSheet("color: blue");
        if (value == 2)
          btn->setStyleSheet("color: green");
        if (value == 3)
          btn->setStyleSheet("color: red");
        if (value == 4)
          btn->setStyleSheet("color: brown");
        if (value == 5)
          btn->setStyleSheet("color: magenta");
        if (value == -1)
        {
          QFont bold;
          bold.setBold(true);
          btn->setFont(bold);
          btn->setStyleSheet("color: black");
        }
        btn->setText(toString(value).c_str());
        btn->setDisabled(true);
      }
      ++pos;
    }
  }
}

void MainWindow::about()
{
  AboutDialog dialog(this);
  dialog.exec();
}

void MainWindow::aboutQt()
{
  QApplication::aboutQt();
}
