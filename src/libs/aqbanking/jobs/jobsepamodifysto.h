/***************************************************************************
 begin       : Wed Jan 15 2014
 copyright   : (C) 2014 by Martin Preuss
 email       : martin@libchipcard.de

 ***************************************************************************
 * This file is part of the project "AqBanking".                           *
 * Please see toplevel file COPYING of that project for license details.   *
 ***************************************************************************/


#ifndef AQBANKING_JOBSEPAMODIFYSTO_H
#define AQBANKING_JOBSEPAMODIFYSTO_H


#include <aqbanking/job.h>
#include <aqbanking/transaction.h>
#include <aqbanking/transactionlimits.h>


/** @addtogroup G_AB_JOBS_SEPA_STO_MK Modify a SEPA Standing Order
 *
 */
/*@{*/


#ifdef __cplusplus
extern "C" {
#endif


AQBANKING_API
AB_JOB *AB_JobSepaModifyStandingOrder_new(AB_ACCOUNT *a);



#ifdef __cplusplus
}
#endif

/*@}*/ /* defgroup */


#endif

