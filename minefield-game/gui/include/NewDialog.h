/* 
 * File:   NewDialog.h
 * Author: Marco Ambu
 *
 * Created on September 5, 2010, 12:49 PM
 */

#ifndef _NEWDIALOG_H
#define	_NEWDIALOG_H

#include "ui_NewDialog.h"

class NewDialog : public QDialog {
  Q_OBJECT
public:
  NewDialog(QWidget* parent);
  virtual ~NewDialog();

  enum Difficulty
  {
    Easy = 0,
    Medium = 1,
    Difficult = 2
  };

public:
  int getRows() const;
  int getColumns() const;
  int getDifficulty() const;

private:
  Ui::NewDialog widget;
};

#endif	/* _NEWDIALOG_H */

