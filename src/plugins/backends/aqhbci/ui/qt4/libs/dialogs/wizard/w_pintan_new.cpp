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

#include "w_pintan_new.h"
#include "a_edituser.h"
#include "a_getcert.h"
#include "a_getsysid.h"
#include "a_finished.h"
#include "a_getaccounts.h"

#include <aqhbci/user.h>

#include <qtimer.h>



WizardPinTanNew::WizardPinTanNew(QBanking *qb,
                                 WizardInfo *wInfo,
                                 QWidget* parent, const char* name,
                                 bool modal)
:Wizard(qb, wInfo,
        tr("Create a new PIN/TAN user"),
        parent, name, modal) {
  WizardAction *wa;

  setDescription(tr("<qt>"
                    "This wizard creates a new <b>PIN/TAN</b> user."
                    "</qt>"));
  wa=new ActionEditUser(this);
  addAction(wa);

  wa=new ActionGetCert(this);
  addAction(wa);

  wa=new ActionGetSysId(this);
  addAction(wa);

  wa=new ActionGetAccounts(this);
  addAction(wa);

  wa=new ActionFinished(this);
  addAction(wa);

  QTimer::singleShot(0, this, SLOT(adjustSize()));
}



WizardPinTanNew::~WizardPinTanNew() {

}



int WizardPinTanNew::exec() {
  int rv;

  rv=Wizard::exec();
  if (rv==QDialog::Accepted) {
    AB_USER *u;

    u=getWizardInfo()->getUser();
    assert(u);
    /* import, so always activate the user */
    AH_User_SetStatus(u, AH_UserStatusEnabled);
  }
  return rv;
}



