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


#include "a_finished.h"
#include "wizard.h"
#include <q4banking/qbanking.h>

#include <gwenhywfar/debug.h>

#include <assert.h>

#include <qlabel.h>



ActionFinished::ActionFinished(Wizard *w)
:WizardAction(w, "Finished", QWidget::tr("Finished")) {
  QLabel *tl;

  tl=new QLabel(this, "FinishedText");
  tl->setText(tr("<qt>"
              "The new user has now been setup. Have fun."
		 "</qt>"));
  addWidget(tl);
}



ActionFinished::~ActionFinished() {
}



