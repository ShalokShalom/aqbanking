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
#include "qbjobview.h"
#include "qbanking.h"

// AqBanking includes
#include <aqbanking/jobgetbalance.h>
#include <aqbanking/jobgettransactions.h>

// Gwenhywfar includes
#include <gwenhywfar/debug.h>

// QT includes
#include <qevent.h>
#include <qpushbutton.h>
#include <qgroupbox.h>
#include <qmessagebox.h>
#include <qlayout.h>





QBJobView::QBJobView(QBanking *kb,
                     QWidget* parent,
                     const char* name,
                     WFlags fl)
:QBJobViewUi(parent, name, fl), _app(kb) {
  assert(kb);

  QObject::connect(_app->flagStaff(), SIGNAL(signalQueueUpdated()),
                   this, SLOT(slotQueueUpdated()));
  QObject::connect(executeButton, SIGNAL(clicked()),
                   this, SLOT(slotExecute()));
  QObject::connect(dequeueButton, SIGNAL(clicked()),
                   this, SLOT(slotDequeue()));

}



QBJobView::~QBJobView(){
}


bool QBJobView::init(){
  GWEN_DB_NODE *db;

  db=_app->getSharedData("qbanking");
  assert(db);
  db=GWEN_DB_GetGroup(db, GWEN_PATH_FLAGS_NAMEMUSTEXIST,
                      "gui/views/jobview");
  if (db) {
    int i, j;

    /* found settings */
    for (i=0; i<jobList->columns(); i++) {
      jobList->setColumnWidthMode(i, QListView::Manual);
      j=GWEN_DB_GetIntValue(db, "columns", i, -1);
      if (j!=-1)
        jobList->setColumnWidth(i, j);
    } /* for */
  } /* if settings */

  jobList->addJobs(_app->getEnqueuedJobs());
  _app->outboxCountChanged(jobList->childCount());

  return true;
}



bool QBJobView::fini(){
  GWEN_DB_NODE *db;
  int i, j;

  db=_app->getSharedData("qbanking");
  assert(db);
  assert(db);
  GWEN_DB_ClearGroup(db, "gui/views/jobview");
  for (i=0; i<jobList->columns(); i++) {
    j=jobList->columnWidth(i);
    GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_DEFAULT,
                        "gui/views/jobview/columns", j);
  } /* for */

  return true;
}


void QBJobView::slotQueueUpdated(){
  DBG_DEBUG(0, "Job queue updated");
  jobList->clear();
  jobList->addJobs(_app->getEnqueuedJobs());
  _app->outboxCountChanged(jobList->childCount());
}



void QBJobView::slotExecute(){
  std::list<AB_JOB*> jl;
  int rv;
  bool updated;
  AB_IMEXPORTER_CONTEXT *ctx;

  updated=false;
  jl=_app->getEnqueuedJobs();
  if (jl.size()==0) {
    QMessageBox::warning(this,
                         tr("No Jobs"),
                         tr("There are no jobs in the queue."),
                         QMessageBox::Ok,QMessageBox::NoButton);
    return;
  }

  DBG_INFO(0, "Executing queue");
  ctx=AB_ImExporterContext_new();
  rv=_app->executeQueue(ctx);
  if (!rv) {
    _app->importContext(ctx,
                        QBANKING_IMPORTER_FLAGS_COMPLETE_DAYS /*|
                        QBANKING_IMPORTER_FLAGS_OVERWRITE_DAYS */);
  }
  else {
    DBG_NOTICE(0, "Error %d", rv);
  }
  AB_ImExporterContext_free(ctx);
}



void QBJobView::slotDequeue(){
  std::list<AB_JOB*> jl;
  std::list<AB_JOB*>::iterator jit;

  jl=jobList->getSelectedJobs();
  if (jl.empty()) {
    DBG_DEBUG(0, "No job selected");
    QMessageBox::warning(this,
			 tr("No Selection"),
                         tr("Please select a job first."),
			 QMessageBox::Retry,QMessageBox::NoButton);
    return;
  }

  int r = QMessageBox::warning(this,
			   tr("Delete job"),
			   tr("Do you really want to delete the "
			      "selected job(s)?"),
			   QMessageBox::Yes,QMessageBox::No);
  if (r !=0 && r != QMessageBox::Yes)
    return;

  for (jit=jl.begin(); jit!=jl.end(); jit++) {
    int rv;

    rv=AB_Banking_DequeueJob(_app->getCInterface(), *jit);
    if (rv) {
      DBG_ERROR(0, "Error dequeing job (%d)", rv);
    }
  } // for
  slotQueueUpdated();
}




#include "qbjobview.moc"





