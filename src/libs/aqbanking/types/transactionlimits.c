/* This file is auto-generated from "transactionlimits.xml" by the typemaker
   tool of Gwenhywfar. 
   Do not edit this file -- all changes will be lost! */
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "transactionlimits_p.h"
#include <gwenhywfar/misc.h>
#include <gwenhywfar/db.h>
#include <gwenhywfar/debug.h>
#include <assert.h>
#include <stdlib.h>


GWEN_LIST_FUNCTIONS(AB_TRANSACTION_LIMITS, AB_TransactionLimits)
GWEN_LIST2_FUNCTIONS(AB_TRANSACTION_LIMITS, AB_TransactionLimits)


AB_TRANSACTION_LIMITS *AB_TransactionLimits_new() {
  AB_TRANSACTION_LIMITS *st;

  GWEN_NEW_OBJECT(AB_TRANSACTION_LIMITS, st)
  st->_usage=1;
  GWEN_LIST_INIT(AB_TRANSACTION_LIMITS, st)
  st->valuesTextKey=GWEN_StringList_new();
  return st;
}


void AB_TransactionLimits_free(AB_TRANSACTION_LIMITS *st) {
  if (st) {
    assert(st->_usage);
    if (--(st->_usage)==0) {
  if (st->valuesTextKey)
    GWEN_StringList_free(st->valuesTextKey);
  GWEN_LIST_FINI(AB_TRANSACTION_LIMITS, st)
  GWEN_FREE_OBJECT(st);
    }
  }

}


AB_TRANSACTION_LIMITS *AB_TransactionLimits_dup(const AB_TRANSACTION_LIMITS *d) {
  AB_TRANSACTION_LIMITS *st;

  assert(d);
  st=AB_TransactionLimits_new();
  st->maxLenLocalName=d->maxLenLocalName;
  st->minLenLocalName=d->minLenLocalName;
  st->maxLenRemoteName=d->maxLenRemoteName;
  st->minLenRemoteName=d->minLenRemoteName;
  st->maxLinesRemoteName=d->maxLinesRemoteName;
  st->minLinesRemoteName=d->minLinesRemoteName;
  st->maxLenLocalBankCode=d->maxLenLocalBankCode;
  st->minLenLocalBankCode=d->minLenLocalBankCode;
  st->maxLenLocalAccountNumber=d->maxLenLocalAccountNumber;
  st->minLenLocalAccountNumber=d->minLenLocalAccountNumber;
  st->maxLenLocalSuffix=d->maxLenLocalSuffix;
  st->minLenLocalSuffix=d->minLenLocalSuffix;
  st->maxLenRemoteBankCode=d->maxLenRemoteBankCode;
  st->minLenRemoteBankCode=d->minLenRemoteBankCode;
  st->maxLenRemoteAccountNumber=d->maxLenRemoteAccountNumber;
  st->minLenRemoteAccountNumber=d->minLenRemoteAccountNumber;
  st->maxLenRemoteSuffix=d->maxLenRemoteSuffix;
  st->minLenRemoteSuffix=d->minLenRemoteSuffix;
  st->maxLenRemoteIban=d->maxLenRemoteIban;
  st->minLenRemoteIban=d->minLenRemoteIban;
  st->maxLenTextKey=d->maxLenTextKey;
  st->minLenTextKey=d->minLenTextKey;
  if (d->valuesTextKey)
    st->valuesTextKey=GWEN_StringList_dup(d->valuesTextKey);
  st->maxLenCustomerReference=d->maxLenCustomerReference;
  st->minLenCustomerReference=d->minLenCustomerReference;
  st->maxLenBankReference=d->maxLenBankReference;
  st->minLenBankReference=d->minLenBankReference;
  st->maxLenPurpose=d->maxLenPurpose;
  st->minLenPurpose=d->minLenPurpose;
  st->maxLinesPurpose=d->maxLinesPurpose;
  st->minLinesPurpose=d->minLinesPurpose;
  return st;
}


int AB_TransactionLimits_toDb(const AB_TRANSACTION_LIMITS *st, GWEN_DB_NODE *db) {
  assert(st);
  assert(db);
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "maxLenLocalName", st->maxLenLocalName))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "minLenLocalName", st->minLenLocalName))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "maxLenRemoteName", st->maxLenRemoteName))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "minLenRemoteName", st->minLenRemoteName))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "maxLinesRemoteName", st->maxLinesRemoteName))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "minLinesRemoteName", st->minLinesRemoteName))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "maxLenLocalBankCode", st->maxLenLocalBankCode))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "minLenLocalBankCode", st->minLenLocalBankCode))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "maxLenLocalAccountNumber", st->maxLenLocalAccountNumber))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "minLenLocalAccountNumber", st->minLenLocalAccountNumber))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "maxLenLocalSuffix", st->maxLenLocalSuffix))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "minLenLocalSuffix", st->minLenLocalSuffix))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "maxLenRemoteBankCode", st->maxLenRemoteBankCode))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "minLenRemoteBankCode", st->minLenRemoteBankCode))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "maxLenRemoteAccountNumber", st->maxLenRemoteAccountNumber))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "minLenRemoteAccountNumber", st->minLenRemoteAccountNumber))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "maxLenRemoteSuffix", st->maxLenRemoteSuffix))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "minLenRemoteSuffix", st->minLenRemoteSuffix))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "maxLenRemoteIban", st->maxLenRemoteIban))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "minLenRemoteIban", st->minLenRemoteIban))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "maxLenTextKey", st->maxLenTextKey))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "minLenTextKey", st->minLenTextKey))
    return -1;
  if (st->valuesTextKey)
    {
      GWEN_STRINGLISTENTRY *se;

      GWEN_DB_DeleteVar(db, "valuesTextKey");
      se=GWEN_StringList_FirstEntry(st->valuesTextKey);
      while(se) {
        const char *s;

        s=GWEN_StringListEntry_Data(se);
        assert(s);
        if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_DEFAULT, "valuesTextKey", s))
          return -1;
        se=GWEN_StringListEntry_Next(se);
      } /* while */
    }
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "maxLenCustomerReference", st->maxLenCustomerReference))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "minLenCustomerReference", st->minLenCustomerReference))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "maxLenBankReference", st->maxLenBankReference))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "minLenBankReference", st->minLenBankReference))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "maxLenPurpose", st->maxLenPurpose))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "minLenPurpose", st->minLenPurpose))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "maxLinesPurpose", st->maxLinesPurpose))
    return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "minLinesPurpose", st->minLinesPurpose))
    return -1;
  return 0;
}


AB_TRANSACTION_LIMITS *AB_TransactionLimits_fromDb(GWEN_DB_NODE *db) {
AB_TRANSACTION_LIMITS *st;

  assert(db);
  st=AB_TransactionLimits_new();
  AB_TransactionLimits_SetMaxLenLocalName(st, GWEN_DB_GetIntValue(db, "maxLenLocalName", 0, 0));
  AB_TransactionLimits_SetMinLenLocalName(st, GWEN_DB_GetIntValue(db, "minLenLocalName", 0, 0));
  AB_TransactionLimits_SetMaxLenRemoteName(st, GWEN_DB_GetIntValue(db, "maxLenRemoteName", 0, 0));
  AB_TransactionLimits_SetMinLenRemoteName(st, GWEN_DB_GetIntValue(db, "minLenRemoteName", 0, 0));
  AB_TransactionLimits_SetMaxLinesRemoteName(st, GWEN_DB_GetIntValue(db, "maxLinesRemoteName", 0, 0));
  AB_TransactionLimits_SetMinLinesRemoteName(st, GWEN_DB_GetIntValue(db, "minLinesRemoteName", 0, 0));
  AB_TransactionLimits_SetMaxLenLocalBankCode(st, GWEN_DB_GetIntValue(db, "maxLenLocalBankCode", 0, 0));
  AB_TransactionLimits_SetMinLenLocalBankCode(st, GWEN_DB_GetIntValue(db, "minLenLocalBankCode", 0, 0));
  AB_TransactionLimits_SetMaxLenLocalAccountNumber(st, GWEN_DB_GetIntValue(db, "maxLenLocalAccountNumber", 0, 0));
  AB_TransactionLimits_SetMinLenLocalAccountNumber(st, GWEN_DB_GetIntValue(db, "minLenLocalAccountNumber", 0, 0));
  AB_TransactionLimits_SetMaxLenLocalSuffix(st, GWEN_DB_GetIntValue(db, "maxLenLocalSuffix", 0, 0));
  AB_TransactionLimits_SetMinLenLocalSuffix(st, GWEN_DB_GetIntValue(db, "minLenLocalSuffix", 0, 0));
  AB_TransactionLimits_SetMaxLenRemoteBankCode(st, GWEN_DB_GetIntValue(db, "maxLenRemoteBankCode", 0, 0));
  AB_TransactionLimits_SetMinLenRemoteBankCode(st, GWEN_DB_GetIntValue(db, "minLenRemoteBankCode", 0, 0));
  AB_TransactionLimits_SetMaxLenRemoteAccountNumber(st, GWEN_DB_GetIntValue(db, "maxLenRemoteAccountNumber", 0, 0));
  AB_TransactionLimits_SetMinLenRemoteAccountNumber(st, GWEN_DB_GetIntValue(db, "minLenRemoteAccountNumber", 0, 0));
  AB_TransactionLimits_SetMaxLenRemoteSuffix(st, GWEN_DB_GetIntValue(db, "maxLenRemoteSuffix", 0, 0));
  AB_TransactionLimits_SetMinLenRemoteSuffix(st, GWEN_DB_GetIntValue(db, "minLenRemoteSuffix", 0, 0));
  AB_TransactionLimits_SetMaxLenRemoteIban(st, GWEN_DB_GetIntValue(db, "maxLenRemoteIban", 0, 0));
  AB_TransactionLimits_SetMinLenRemoteIban(st, GWEN_DB_GetIntValue(db, "minLenRemoteIban", 0, 0));
  AB_TransactionLimits_SetMaxLenTextKey(st, GWEN_DB_GetIntValue(db, "maxLenTextKey", 0, 0));
  AB_TransactionLimits_SetMinLenTextKey(st, GWEN_DB_GetIntValue(db, "minLenTextKey", 0, 0));
  if (1) {
    int i;

    for (i=0; ; i++) {
      const char *s;

      s=GWEN_DB_GetCharValue(db, "valuesTextKey", i, 0);
      if (!s)
        break;
      AB_TransactionLimits_AddValuesTextKey(st, s, 0);
    } /* for */
  }
  AB_TransactionLimits_SetMaxLenCustomerReference(st, GWEN_DB_GetIntValue(db, "maxLenCustomerReference", 0, 0));
  AB_TransactionLimits_SetMinLenCustomerReference(st, GWEN_DB_GetIntValue(db, "minLenCustomerReference", 0, 0));
  AB_TransactionLimits_SetMaxLenBankReference(st, GWEN_DB_GetIntValue(db, "maxLenBankReference", 0, 0));
  AB_TransactionLimits_SetMinLenBankReference(st, GWEN_DB_GetIntValue(db, "minLenBankReference", 0, 0));
  AB_TransactionLimits_SetMaxLenPurpose(st, GWEN_DB_GetIntValue(db, "maxLenPurpose", 0, 0));
  AB_TransactionLimits_SetMinLenPurpose(st, GWEN_DB_GetIntValue(db, "minLenPurpose", 0, 0));
  AB_TransactionLimits_SetMaxLinesPurpose(st, GWEN_DB_GetIntValue(db, "maxLinesPurpose", 0, 0));
  AB_TransactionLimits_SetMinLinesPurpose(st, GWEN_DB_GetIntValue(db, "minLinesPurpose", 0, 0));
  st->_modified=0;
  return st;
}


int AB_TransactionLimits_GetMaxLenLocalName(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->maxLenLocalName;
}


void AB_TransactionLimits_SetMaxLenLocalName(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->maxLenLocalName=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMinLenLocalName(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->minLenLocalName;
}


void AB_TransactionLimits_SetMinLenLocalName(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->minLenLocalName=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMaxLenRemoteName(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->maxLenRemoteName;
}


void AB_TransactionLimits_SetMaxLenRemoteName(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->maxLenRemoteName=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMinLenRemoteName(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->minLenRemoteName;
}


void AB_TransactionLimits_SetMinLenRemoteName(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->minLenRemoteName=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMaxLinesRemoteName(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->maxLinesRemoteName;
}


void AB_TransactionLimits_SetMaxLinesRemoteName(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->maxLinesRemoteName=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMinLinesRemoteName(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->minLinesRemoteName;
}


void AB_TransactionLimits_SetMinLinesRemoteName(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->minLinesRemoteName=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMaxLenLocalBankCode(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->maxLenLocalBankCode;
}


void AB_TransactionLimits_SetMaxLenLocalBankCode(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->maxLenLocalBankCode=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMinLenLocalBankCode(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->minLenLocalBankCode;
}


void AB_TransactionLimits_SetMinLenLocalBankCode(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->minLenLocalBankCode=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMaxLenLocalAccountNumber(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->maxLenLocalAccountNumber;
}


void AB_TransactionLimits_SetMaxLenLocalAccountNumber(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->maxLenLocalAccountNumber=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMinLenLocalAccountNumber(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->minLenLocalAccountNumber;
}


void AB_TransactionLimits_SetMinLenLocalAccountNumber(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->minLenLocalAccountNumber=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMaxLenLocalSuffix(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->maxLenLocalSuffix;
}


void AB_TransactionLimits_SetMaxLenLocalSuffix(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->maxLenLocalSuffix=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMinLenLocalSuffix(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->minLenLocalSuffix;
}


void AB_TransactionLimits_SetMinLenLocalSuffix(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->minLenLocalSuffix=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMaxLenRemoteBankCode(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->maxLenRemoteBankCode;
}


void AB_TransactionLimits_SetMaxLenRemoteBankCode(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->maxLenRemoteBankCode=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMinLenRemoteBankCode(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->minLenRemoteBankCode;
}


void AB_TransactionLimits_SetMinLenRemoteBankCode(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->minLenRemoteBankCode=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMaxLenRemoteAccountNumber(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->maxLenRemoteAccountNumber;
}


void AB_TransactionLimits_SetMaxLenRemoteAccountNumber(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->maxLenRemoteAccountNumber=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMinLenRemoteAccountNumber(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->minLenRemoteAccountNumber;
}


void AB_TransactionLimits_SetMinLenRemoteAccountNumber(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->minLenRemoteAccountNumber=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMaxLenRemoteSuffix(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->maxLenRemoteSuffix;
}


void AB_TransactionLimits_SetMaxLenRemoteSuffix(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->maxLenRemoteSuffix=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMinLenRemoteSuffix(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->minLenRemoteSuffix;
}


void AB_TransactionLimits_SetMinLenRemoteSuffix(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->minLenRemoteSuffix=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMaxLenRemoteIban(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->maxLenRemoteIban;
}


void AB_TransactionLimits_SetMaxLenRemoteIban(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->maxLenRemoteIban=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMinLenRemoteIban(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->minLenRemoteIban;
}


void AB_TransactionLimits_SetMinLenRemoteIban(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->minLenRemoteIban=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMaxLenTextKey(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->maxLenTextKey;
}


void AB_TransactionLimits_SetMaxLenTextKey(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->maxLenTextKey=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMinLenTextKey(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->minLenTextKey;
}


void AB_TransactionLimits_SetMinLenTextKey(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->minLenTextKey=d;
  st->_modified=1;
}


const GWEN_STRINGLIST *AB_TransactionLimits_GetValuesTextKey(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->valuesTextKey;
}


void AB_TransactionLimits_SetValuesTextKey(AB_TRANSACTION_LIMITS *st, const GWEN_STRINGLIST *d) {
  assert(st);
  if (st->valuesTextKey)
    GWEN_StringList_free(st->valuesTextKey);
  if (d)
    st->valuesTextKey=GWEN_StringList_dup(d);
  else
    st->valuesTextKey=0;
  st->_modified=1;
}


void AB_TransactionLimits_AddValuesTextKey(AB_TRANSACTION_LIMITS *st, const char *d, int chk){
  assert(st);
  assert(d);
  if (GWEN_StringList_AppendString(st->valuesTextKey, d, 0, chk))
    st->_modified=1;
}


void AB_TransactionLimits_RemoveValuesTextKey(AB_TRANSACTION_LIMITS *st, const char *d) {
  if (GWEN_StringList_RemoveString(st->valuesTextKey, d))
    st->_modified=1;
}


void AB_TransactionLimits_ClearValuesTextKey(AB_TRANSACTION_LIMITS *st) {
  if (GWEN_StringList_Count(st->valuesTextKey)) {
    GWEN_StringList_Clear(st->valuesTextKey);
    st->_modified=1;
  }
}


int AB_TransactionLimits_HasValuesTextKey(const AB_TRANSACTION_LIMITS *st, const char *d) {
  return GWEN_StringList_HasString(st->valuesTextKey, d);
}


int AB_TransactionLimits_GetMaxLenCustomerReference(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->maxLenCustomerReference;
}


void AB_TransactionLimits_SetMaxLenCustomerReference(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->maxLenCustomerReference=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMinLenCustomerReference(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->minLenCustomerReference;
}


void AB_TransactionLimits_SetMinLenCustomerReference(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->minLenCustomerReference=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMaxLenBankReference(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->maxLenBankReference;
}


void AB_TransactionLimits_SetMaxLenBankReference(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->maxLenBankReference=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMinLenBankReference(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->minLenBankReference;
}


void AB_TransactionLimits_SetMinLenBankReference(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->minLenBankReference=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMaxLenPurpose(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->maxLenPurpose;
}


void AB_TransactionLimits_SetMaxLenPurpose(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->maxLenPurpose=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMinLenPurpose(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->minLenPurpose;
}


void AB_TransactionLimits_SetMinLenPurpose(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->minLenPurpose=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMaxLinesPurpose(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->maxLinesPurpose;
}


void AB_TransactionLimits_SetMaxLinesPurpose(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->maxLinesPurpose=d;
  st->_modified=1;
}


int AB_TransactionLimits_GetMinLinesPurpose(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->minLinesPurpose;
}


void AB_TransactionLimits_SetMinLinesPurpose(AB_TRANSACTION_LIMITS *st, int d) {
  assert(st);
  st->minLinesPurpose=d;
  st->_modified=1;
}


int AB_TransactionLimits_IsModified(const AB_TRANSACTION_LIMITS *st) {
  assert(st);
  return st->_modified;
}


void AB_TransactionLimits_SetModified(AB_TRANSACTION_LIMITS *st, int i) {
  assert(st);
  st->_modified=i;
}


void AB_TransactionLimits_Attach(AB_TRANSACTION_LIMITS *st) {
  assert(st);
  st->_usage++;
}
AB_TRANSACTION_LIMITS *AB_TransactionLimits_List2__freeAll_cb(AB_TRANSACTION_LIMITS *st, void *user_data) {
  AB_TransactionLimits_free(st);
return 0;
}


void AB_TransactionLimits_List2_freeAll(AB_TRANSACTION_LIMITS_LIST2 *stl) {
  if (stl) {
    AB_TransactionLimits_List2_ForEach(stl, AB_TransactionLimits_List2__freeAll_cb, 0);
    AB_TransactionLimits_List2_free(stl); 
  }
}




AB_TRANSACTION_LIMITS_LIST *AB_TransactionLimits_List_dup(const AB_TRANSACTION_LIMITS_LIST *stl) {
  if (stl) {
    AB_TRANSACTION_LIMITS_LIST *nl;
    AB_TRANSACTION_LIMITS *e;

    nl=AB_TransactionLimits_List_new();
    e=AB_TransactionLimits_List_First(stl);
    while(e) {
      AB_TRANSACTION_LIMITS *ne;

      ne=AB_TransactionLimits_dup(e);
      assert(ne);
      AB_TransactionLimits_List_Add(ne, nl);
      e=AB_TransactionLimits_List_Next(e);
    } /* while (e) */
    return nl;
  }
  else
    return 0;
}



