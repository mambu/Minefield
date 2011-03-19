#include "NewDialog.h"

NewDialog::NewDialog(QWidget* parent)
  : QDialog(parent)
{
  widget.setupUi(this);
}

NewDialog::~NewDialog() {
}

int NewDialog::getRows() const
{
  return widget.spinBoxRows->value();
}
int NewDialog::getColumns() const
{
  return widget.spinBoxColumns->value();
}
int NewDialog::getDifficulty() const
{
  return widget.comboBoxDifficulty->currentIndex();
}
