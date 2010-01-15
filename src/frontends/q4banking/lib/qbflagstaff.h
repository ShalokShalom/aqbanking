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

#ifndef QBANKING_FLAGSTAFF_H
#define QBANKING_FLAGSTAFF_H

class QBFlagStaff;

#include <q4banking/qbanking.h>
#include <Qt/qobject.h>


class Q4BANKING_API QBFlagStaff: public QObject {
  Q_OBJECT
public:
  QBFlagStaff();
  virtual ~QBFlagStaff();

  void queueUpdated();
  void accountsUpdated();
  void outboxCountChanged(int count);
  void statusMessage(const QString &s);

signals:
  void signalQueueUpdated();
  void signalAccountsUpdated();
  void signalOutboxCountChanged(int count);
  void signalStatusMessage(const QString &s);
};




#endif /* QBANKING_FLAGSTAFF_H */

