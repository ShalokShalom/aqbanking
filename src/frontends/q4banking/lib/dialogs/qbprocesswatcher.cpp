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


// QBanking includes
#include "qbprocesswatcher.h"

// Gwenhywfar includes
#include <gwenhywfar/debug.h>

// QT includes
#include <q3process.h>
#include <qapplication.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qmessagebox.h>




QBProcessWatcher::QBProcessWatcher(Q3Process* process,
                                   const QString &txt,
                                   QWidget* parent,
                                   const char* name,
                                   bool modal,
                                   Qt::WFlags fl)
:QDialog(parent, name, modal, fl)
,Ui_QBProcessWatcherUi()
,_process(process)
,_result(-1)
,_closeEnabled(false)
,_startTime((time_t)0)
,_duration(0){
  _startTime=time(0);
  if (txt.isEmpty())
    tLabel->setText(tr("Process running..."));
  else
    tLabel->setText(txt);

  QObject::connect(process, SIGNAL(processExited()),
                   this, SLOT(slotProcessFinished()));
  QObject::connect(terminateButton, SIGNAL(clicked()),
                   this, SLOT(slotTerminate()));
  QObject::connect(killButton, SIGNAL(clicked()),
                   this, SLOT(slotKill()));
}



QBProcessWatcher::~QBProcessWatcher(){
}



void QBProcessWatcher::slotTerminate(){
  _process->tryTerminate();
  terminateButton->setEnabled(false);
}



void QBProcessWatcher::slotKill(){
  _process->kill();
  terminateButton->setEnabled(false);
  killButton->setEnabled(false);
  _closeEnabled=true;
}



void QBProcessWatcher::slotProcessFinished() {
  int rv;
  time_t endTime;

  endTime=time(0);
  _duration=(int)difftime(endTime, _startTime);
  _closeEnabled=true;
  rv=_process->exitStatus();
  _result=rv;
  if (rv) {
    QMessageBox::critical(this,
                          tr("Process Error"),
                          QWidget::tr("<qt>"
				      "<p>"
				      "Process exited with status %1"
				      "</p>"
				      "</qt>").arg(rv),
                          QMessageBox::Ok,Qt::NoButton);
    QDialog::reject();
  }
  else
    QDialog::accept();
}



void QBProcessWatcher::accept(){
  if (_closeEnabled)
    QDialog::accept();
}



int QBProcessWatcher::getStatus() const{
  return _process->exitStatus();
}



int QBProcessWatcher::getDuration() const{
  return _duration;
}



void QBProcessWatcher::languageChange(){
  QString txt=tLabel->text();
  QDialog::languageChange();
  tLabel->setText(txt);
}




#include "qbprocesswatcher.moc"




