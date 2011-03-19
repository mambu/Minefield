#include "AboutDialog.h"

AboutDialog::AboutDialog(QWidget* parent)
  : QDialog(parent)
{
  widget.setupUi(this);
}

AboutDialog::~AboutDialog() {
}
