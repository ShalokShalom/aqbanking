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


#ifndef AQBANKING_JOBSINGLETRANSFER_L_H
#define AQBANKING_JOBSINGLETRANSFER_L_H


#include <aqbanking/jobsingletransfer_be.h>


AB_JOB *AB_JobSingleTransfer_fromDb(AB_ACCOUNT *a, GWEN_DB_NODE *db);
int AB_JobSingleTransfer_toDb(const AB_JOB *j, GWEN_DB_NODE *db);


#endif
