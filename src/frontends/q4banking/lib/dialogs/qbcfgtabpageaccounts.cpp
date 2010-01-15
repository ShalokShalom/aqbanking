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
#include "qbcfgtabpageaccounts.h"
#include "qbeditaccount.h"
#include "qbaccountlist.h"
#include "qbselectbackend.h"
#include "qbcfgmodule.h"
#include "qbanking.h"

// Gwenhywfar includes
#include <gwenhywfar/debug.h>

// QT includes
#include <qlineedit.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qmessagebox.h>
#include <qlayout.h>
#include <qtextcodec.h>




QBCfgTabPageAccounts::QBCfgTabPageAccounts(QBanking *qb,
                                           QWidget *parent,
                                           const char *name,
                                           Qt::WFlags f)
:QBCfgTabPage(qb, tr("Accounts"), parent, name, f){
  _realPage.setupUi(this);

  setHelpSubject("QBCfgTabPageAccounts");
  setDescription(tr("This page allows you to map, create, edit and remove"
                    " accounts from AqBanking."));

  QObject::connect(_realPage.accountNewButton, SIGNAL(clicked()),
                   this, SLOT(slotAccountNew()));
  QObject::connect(_realPage.accountEditButton, SIGNAL(clicked()),
                   this, SLOT(slotAccountEdit()));
  QObject::connect(_realPage.accountDeleteButton, SIGNAL(clicked()),
                   this, SLOT(slotAccountDel()));
}



QBCfgTabPageAccounts::~QBCfgTabPageAccounts() {
}



void QBCfgTabPageAccounts::_accountRescan(){
  _realPage.accountList->clear();
  _realPage.accountList->addAccounts(getBanking()->getAccounts());
}



bool QBCfgTabPageAccounts::toGui() {
  GWEN_DB_NODE *dbConfig=NULL;
  int rv;

  rv=getBanking()->loadSharedSubConfig("qbanking",
				       "settings/gui/accountList",
				       &dbConfig,
				       0);
  if (rv==0) {
    int i, j;

    assert(dbConfig);

    /* setup account list view */
    _realPage.accountList->setResizeMode(Q3ListView::NoColumn);
    for (i=0; i<_realPage.accountList->columns(); i++) {
      _realPage.accountList->setColumnWidthMode(i, Q3ListView::Manual);
      j=GWEN_DB_GetIntValue(dbConfig, "columns", i, -1);
      if (j!=-1)
	_realPage.accountList->setColumnWidth(i, j);
    } /* for */
    _realPage.accountList->setSelectionMode(Q3ListView::Single);

    _accountRescan();
    GWEN_DB_Group_free(dbConfig);
    return true;
  }
  else {
    DBG_INFO(0, "here (%d)", rv);
    return false;
  }
}



bool QBCfgTabPageAccounts::fromGui() {
  GWEN_DB_NODE *dbConfig;
  int i, j;
  int rv;

  dbConfig=GWEN_DB_Group_new("config");
  assert(dbConfig);

  /* save account list view settings */
  for (i=0; i<_realPage.accountList->columns(); i++) {
    j=_realPage.accountList->columnWidth(i);
    GWEN_DB_SetIntValue(dbConfig, GWEN_DB_FLAGS_DEFAULT,
			"columns", j);
  } /* for */

  rv=getBanking()->saveSharedSubConfig("qbanking",
				       "settings/gui/accountList",
				       dbConfig,
				       0);
  if (rv<0) {
    DBG_INFO(0, "here (%d)", rv);
    GWEN_DB_Group_free(dbConfig);
    return false;
  }
  GWEN_DB_Group_free(dbConfig);
  return true;
}



void QBCfgTabPageAccounts::slotAccountNew() {
  QString backend;
  QString preBackend;
  const char *l;

  l=QTextCodec::locale();
  if (l) {
    QString ql;

    ql=QString::fromUtf8(l).lower();
    if (ql=="de" || ql=="de_de")
      preBackend="aqhbci";
  }
  backend=QBSelectBackend::selectBackend(getBanking(),
                                         preBackend,
                                         this);
  if (backend.isEmpty()) {
    DBG_INFO(0, "Aborted");
  }
  else {
    AB_ACCOUNT *a;
    std::string s;

    s=QBanking::QStringToUtf8String(backend);
    DBG_ERROR(0, "Selected backend: %s", s.c_str());

    a=AB_Banking_CreateAccount(getBanking()->getCInterface(),
                               s.c_str());
    assert(a);
    if (QBEditAccount::editAccount(getBanking(), a, false, this)) {
      DBG_INFO(0, "Accepted, adding account");
      AB_Banking_AddAccount(getBanking()->getCInterface(), a);
      updateView();
      emit signalUpdate();
    }
    else {
      DBG_INFO(0, "Rejected");
      AB_Account_free(a);
    }
  }
}



void QBCfgTabPageAccounts::slotAccountEdit() {
  std::list<AB_ACCOUNT*> al;
  AB_ACCOUNT *a;

  al=_realPage.accountList->getSelectedAccounts();
  if (al.empty()) {
    QMessageBox::critical(this,
                          tr("Selection Error"),
                          tr("No account selected."),
                          QMessageBox::Retry,QMessageBox::NoButton);
    return;
  }
  a=al.front();

  if (QBEditAccount::editAccount(getBanking(), a, true, this)) {
    DBG_INFO(0, "Accepted");
  }
  else {
    DBG_INFO(0, "Rejected");
  }

  emit signalUpdate();
  updateView();
}



void QBCfgTabPageAccounts::slotAccountDel() {
  std::list<AB_ACCOUNT*> al =
    _realPage.accountList->getSelectedAccounts();
  if (al.empty()) {
    QMessageBox::critical(this,
                          tr("Selection Error"),
                          tr("No account selected."),
                          QMessageBox::Retry,QMessageBox::NoButton);
    return;
  }
  AB_ACCOUNT *a = al.front();
  int r = QMessageBox::warning(this,
				tr("Really delete account?"),
				tr("You are about to delete an account. This action will "
				   "take effect immediately and cannot be undone. "
				   "(You can add the account later again, of course.)\n\n"
				   "Do you want to delete this account?"),
				QMessageBox::Yes,QMessageBox::Abort);
  if (r != 0 && r != QMessageBox::Yes) {
    return;
  }
  int rv = AB_Banking_DeleteAccount(getBanking()->getCInterface(), a);
  if (rv == 0) {
    DBG_INFO(0, "Accepted");
  }
  else {
    DBG_INFO(0, "Rejected");
  }
  emit signalUpdate();
  updateView();
}



void QBCfgTabPageAccounts::updateView() {
  _accountRescan();
}



void QBCfgTabPageAccounts::slotUpdate() {
  DBG_INFO(AQBANKING_LOGDOMAIN, "Updating accounts view");
  updateView();
}



#include "qbcfgtabpageaccounts.moc"

