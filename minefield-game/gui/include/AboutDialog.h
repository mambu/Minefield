/* 
 * File:   AboutDialog.h
 * Author: Marco Ambu
 *
 * Created on September 6, 2010, 12:49 PM
 */

#ifndef _ABOUTDIALOG_H
#define	_ABOUTDIALOG_H

#include "ui_AboutDialog.h"

class AboutDialog : public QDialog {
  Q_OBJECT
public:
  AboutDialog(QWidget* parent);
  virtual ~AboutDialog();

private:
  Ui::AboutDialog widget;
};

#endif	/* _ABOUTDIALOG_H */

