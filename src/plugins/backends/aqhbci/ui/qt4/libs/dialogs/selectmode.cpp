/***************************************************************************
 $RCSfile$
 -------------------
 cvs         : $Id$
 begin       : Mon Mar 01 2004
 copyright   : (C) 2004 by Martin Preuss
 email       : martin@libchipcard.de

 ***************************************************************************
 *          Please see toplevel file COPYING for license details           *
 ***************************************************************************/


#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "selectmode.h"

#include <qradiobutton.h>
#include <qtimer.h>
#include <qlabel.h> // for qt4 setWordWrap(true)
#include <gwenhywfar/debug.h>




SelectMode::SelectMode(QWidget* parent, const char* name,
                       bool modal, Qt::WFlags fl)
:QDialog(parent, name, modal, fl)
,Ui_SelectModeUi()
,_mode(ModeUnknown) {
  setupUi(this);

  QTimer::singleShot(0, this, SLOT(adjustSize()));
#if (QT_VERSION >= 0x040000)
  // In qt4, QLabel has word-wrap disabled by default
  textLabel1->setWordWrap(true);
#endif // QT_VERSION >= 4
}


SelectMode::~SelectMode() {
}



void SelectMode::accept() {
  if (importCardRadio->isOn())
    _mode=ModeImportCard;
  if (initCardRadio->isOn())
    _mode=ModeInitCard;
  if (importFileRadio->isOn())
    _mode=ModeImportFile;
  if (createFileRadio->isOn())
    _mode=ModeCreateFile;
  if (pinTanRadio->isOn())
    _mode=ModePinTan;
  QDialog::accept();
}



SelectMode::Mode SelectMode::getMode() const {
  return _mode;
}



SelectMode::Mode SelectMode::selectMode(QWidget* parent) {
  SelectMode w(parent, "SelectMode", TRUE);

  if (w.exec()==QDialog::Accepted) {
    DBG_INFO(0, "Selected %d", w.getMode());
    return w.getMode();
  }
  else {
    DBG_ERROR(0, "Not accepted");
  }

  return ModeUnknown;
}






