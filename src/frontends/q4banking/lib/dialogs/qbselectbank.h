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


#ifndef QBANKING_SELBANK_H
#define QBANKING_SELBANK_H


class QBanking;

#include "qbselectbank.ui.h"
#include <aqbanking/bankinfo.h>
#include <q4banking/qbanking.h> /* For Q4BANKING_API */
#include <string>


class Q4BANKING_API QBSelectBank: public QDialog, public Ui_QBSelectBankUi {
  Q_OBJECT

private:
  QBanking *_app;
  AB_BANKINFO *_bankInfo;
  std::string _country;
  bool _changed;

  AB_BANKINFO *_getBankInfo();

public:
  QBSelectBank(QBanking *kb,
               QWidget* parent = 0,
               const char* name = 0,
               bool modal = FALSE,
               Qt::WFlags fl = 0);

  ~QBSelectBank();

  const AB_BANKINFO *selectedBankInfo() const;

  void accept();

  Q4BANKING_API static
      AB_BANKINFO *selectBank(QBanking *kb,
                              QWidget* parent=0,
                              const QString &title=QString::null,
                              const QString &country=QString("de"),
                              const QString &bankCode=QString::null,
                              const QString &swiftCode=QString::null,
                              const QString &bankName=QString::null,
                              const QString &location=QString::null);


public slots:
  void slotUpdate();
  void slotChanged(const QString &qs);
  void slotSelectionChanged();
  void slotDoubleClicked(Q3ListViewItem *lv,
                         const QPoint &,
                         int);
  void slotOnlineToggled(bool on);
  void slotHelpClicked();

};


#endif // QBANKING_SELBANK_H

