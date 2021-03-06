/* This file is auto-generated from "bankinfo.xml" by the typemaker
   tool of Gwenhywfar. 
   Do not edit this file -- all changes will be lost! */
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "bankinfo_p.h"
#include <gwenhywfar/misc.h>
#include <gwenhywfar/db.h>
#include <gwenhywfar/debug.h>
#include <assert.h>
#include <stdlib.h>
#include <strings.h>

#include <gwenhywfar/types.h>
#include <aqbanking/error.h>
#include <aqbanking/bankinfoservice.h>


GWEN_LIST_FUNCTIONS(AB_BANKINFO, AB_BankInfo)
GWEN_LIST2_FUNCTIONS(AB_BANKINFO, AB_BankInfo)




AB_BANKINFO *AB_BankInfo_new(void) {
  AB_BANKINFO *st;

  GWEN_NEW_OBJECT(AB_BANKINFO, st)
  st->_usage=1;
  GWEN_LIST_INIT(AB_BANKINFO, st)
  st->services=AB_BankInfoService_List_new();
  return st;
}


void AB_BankInfo_free(AB_BANKINFO *st) {
  if (st) {
    assert(st->_usage);
    if (--(st->_usage)==0) {
  if (st->country)
    free(st->country);
  if (st->branchId)
    free(st->branchId);
  if (st->bankId)
    free(st->bankId);
  if (st->bic)
    free(st->bic);
  if (st->bankName)
    free(st->bankName);
  if (st->location)
    free(st->location);
  if (st->street)
    free(st->street);
  if (st->zipcode)
    free(st->zipcode);
  if (st->city)
    free(st->city);
  if (st->region)
    free(st->region);
  if (st->phone)
    free(st->phone);
  if (st->fax)
    free(st->fax);
  if (st->email)
    free(st->email);
  if (st->website)
    free(st->website);
  if (st->services)
    AB_BankInfoService_List_free(st->services);
  GWEN_LIST_FINI(AB_BANKINFO, st)
  GWEN_FREE_OBJECT(st);
    }
  }

}


AB_BANKINFO *AB_BankInfo_dup(const AB_BANKINFO *d) {
  AB_BANKINFO *st;

  assert(d);
  st=AB_BankInfo_new();
  if (d->country)
    st->country=strdup(d->country);
  if (d->branchId)
    st->branchId=strdup(d->branchId);
  if (d->bankId)
    st->bankId=strdup(d->bankId);
  if (d->bic)
    st->bic=strdup(d->bic);
  if (d->bankName)
    st->bankName=strdup(d->bankName);
  if (d->location)
    st->location=strdup(d->location);
  if (d->street)
    st->street=strdup(d->street);
  if (d->zipcode)
    st->zipcode=strdup(d->zipcode);
  if (d->city)
    st->city=strdup(d->city);
  if (d->region)
    st->region=strdup(d->region);
  if (d->phone)
    st->phone=strdup(d->phone);
  if (d->fax)
    st->fax=strdup(d->fax);
  if (d->email)
    st->email=strdup(d->email);
  if (d->website)
    st->website=strdup(d->website);
  if (d->services)
    st->services=AB_BankInfoService_List_dup(d->services);
  return st;
}


int AB_BankInfo_toDb(const AB_BANKINFO *st, GWEN_DB_NODE *db) {
  assert(st);
  assert(db);
  if (st->country)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "country", st->country))
      return -1;
  if (st->branchId)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "branchId", st->branchId))
      return -1;
  if (st->bankId)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "bankId", st->bankId))
      return -1;
  if (st->bic)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "bic", st->bic))
      return -1;
  if (st->bankName)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "bankName", st->bankName))
      return -1;
  if (st->location)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "location", st->location))
      return -1;
  if (st->street)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "street", st->street))
      return -1;
  if (st->zipcode)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "zipcode", st->zipcode))
      return -1;
  if (st->city)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "city", st->city))
      return -1;
  if (st->region)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "region", st->region))
      return -1;
  if (st->phone)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "phone", st->phone))
      return -1;
  if (st->fax)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "fax", st->fax))
      return -1;
  if (st->email)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "email", st->email))
      return -1;
  if (st->website)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "website", st->website))
      return -1;
  if (st->services)
  if (1) {
    GWEN_DB_NODE *dbT;
    AB_BANKINFO_SERVICE *e;

    dbT=GWEN_DB_GetGroup(db, GWEN_PATH_FLAGS_CREATE_GROUP, "services");
    assert(dbT);
    e=AB_BankInfoService_List_First(st->services);
    while(e) {
      if (AB_BankInfoService_toDb(e, GWEN_DB_GetGroup(dbT, GWEN_PATH_FLAGS_CREATE_GROUP, "element")))
        return -1;
      e=AB_BankInfoService_List_Next(e);
    } /* while */
  } /* if (1) */
  return 0;
}


int AB_BankInfo_ReadDb(AB_BANKINFO *st, GWEN_DB_NODE *db) {
  assert(st);
  assert(db);
  AB_BankInfo_SetCountry(st, GWEN_DB_GetCharValue(db, "country", 0, 0));
  AB_BankInfo_SetBranchId(st, GWEN_DB_GetCharValue(db, "branchId", 0, 0));
  AB_BankInfo_SetBankId(st, GWEN_DB_GetCharValue(db, "bankId", 0, 0));
  AB_BankInfo_SetBic(st, GWEN_DB_GetCharValue(db, "bic", 0, 0));
  AB_BankInfo_SetBankName(st, GWEN_DB_GetCharValue(db, "bankName", 0, 0));
  AB_BankInfo_SetLocation(st, GWEN_DB_GetCharValue(db, "location", 0, 0));
  AB_BankInfo_SetStreet(st, GWEN_DB_GetCharValue(db, "street", 0, 0));
  AB_BankInfo_SetZipcode(st, GWEN_DB_GetCharValue(db, "zipcode", 0, 0));
  AB_BankInfo_SetCity(st, GWEN_DB_GetCharValue(db, "city", 0, 0));
  AB_BankInfo_SetRegion(st, GWEN_DB_GetCharValue(db, "region", 0, 0));
  AB_BankInfo_SetPhone(st, GWEN_DB_GetCharValue(db, "phone", 0, 0));
  AB_BankInfo_SetFax(st, GWEN_DB_GetCharValue(db, "fax", 0, 0));
  AB_BankInfo_SetEmail(st, GWEN_DB_GetCharValue(db, "email", 0, 0));
  AB_BankInfo_SetWebsite(st, GWEN_DB_GetCharValue(db, "website", 0, 0));
  st->services=AB_BankInfoService_List_new();
  if (1) {/* just for local vars */
    GWEN_DB_NODE *dbT;
    AB_BANKINFO_SERVICE *e;

    dbT=GWEN_DB_GetGroup(db, GWEN_PATH_FLAGS_NAMEMUSTEXIST, "services");
    if (dbT) {
      GWEN_DB_NODE *dbT2;

      dbT2=GWEN_DB_FindFirstGroup(dbT, "element");
      while(dbT2) {
        e=AB_BankInfoService_fromDb(dbT2);
        if (!e) {
          DBG_ERROR(0, "Bad element for type \"AB_BANKINFO_SERVICE\"");
          if (GWEN_Logger_GetLevel(0)>=GWEN_LoggerLevel_Debug)
            GWEN_DB_Dump(dbT2, 2);
          AB_BankInfo_free(st);
          return 0;
        }
        AB_BankInfoService_List_Add(e, st->services);    dbT2=GWEN_DB_FindNextGroup(dbT2, "element");
      } /* while */
    } /* if (dbT) */
  } /* if (1) */
  return 0;
}


AB_BANKINFO *AB_BankInfo_fromDb(GWEN_DB_NODE *db) {
  AB_BANKINFO *st;

  assert(db);
  st=AB_BankInfo_new();
  AB_BankInfo_ReadDb(st, db);
  st->_modified=0;
  return st;
}




const char *AB_BankInfo_GetCountry(const AB_BANKINFO *st) {
  assert(st);
  return st->country;
}


void AB_BankInfo_SetCountry(AB_BANKINFO *st, const char *d) {
  assert(st);
  if (st->country)
    free(st->country);
  if (d && *d)
    st->country=strdup(d);
  else
    st->country=0;
  st->_modified=1;
}




const char *AB_BankInfo_GetBranchId(const AB_BANKINFO *st) {
  assert(st);
  return st->branchId;
}


void AB_BankInfo_SetBranchId(AB_BANKINFO *st, const char *d) {
  assert(st);
  if (st->branchId)
    free(st->branchId);
  if (d && *d)
    st->branchId=strdup(d);
  else
    st->branchId=0;
  st->_modified=1;
}




const char *AB_BankInfo_GetBankId(const AB_BANKINFO *st) {
  assert(st);
  return st->bankId;
}


void AB_BankInfo_SetBankId(AB_BANKINFO *st, const char *d) {
  assert(st);
  if (st->bankId)
    free(st->bankId);
  if (d && *d)
    st->bankId=strdup(d);
  else
    st->bankId=0;
  st->_modified=1;
}




const char *AB_BankInfo_GetBic(const AB_BANKINFO *st) {
  assert(st);
  return st->bic;
}


void AB_BankInfo_SetBic(AB_BANKINFO *st, const char *d) {
  assert(st);
  if (st->bic)
    free(st->bic);
  if (d && *d)
    st->bic=strdup(d);
  else
    st->bic=0;
  st->_modified=1;
}




const char *AB_BankInfo_GetBankName(const AB_BANKINFO *st) {
  assert(st);
  return st->bankName;
}


void AB_BankInfo_SetBankName(AB_BANKINFO *st, const char *d) {
  assert(st);
  if (st->bankName)
    free(st->bankName);
  if (d && *d)
    st->bankName=strdup(d);
  else
    st->bankName=0;
  st->_modified=1;
}




const char *AB_BankInfo_GetLocation(const AB_BANKINFO *st) {
  assert(st);
  return st->location;
}


void AB_BankInfo_SetLocation(AB_BANKINFO *st, const char *d) {
  assert(st);
  if (st->location)
    free(st->location);
  if (d && *d)
    st->location=strdup(d);
  else
    st->location=0;
  st->_modified=1;
}




const char *AB_BankInfo_GetStreet(const AB_BANKINFO *st) {
  assert(st);
  return st->street;
}


void AB_BankInfo_SetStreet(AB_BANKINFO *st, const char *d) {
  assert(st);
  if (st->street)
    free(st->street);
  if (d && *d)
    st->street=strdup(d);
  else
    st->street=0;
  st->_modified=1;
}




const char *AB_BankInfo_GetZipcode(const AB_BANKINFO *st) {
  assert(st);
  return st->zipcode;
}


void AB_BankInfo_SetZipcode(AB_BANKINFO *st, const char *d) {
  assert(st);
  if (st->zipcode)
    free(st->zipcode);
  if (d && *d)
    st->zipcode=strdup(d);
  else
    st->zipcode=0;
  st->_modified=1;
}




const char *AB_BankInfo_GetCity(const AB_BANKINFO *st) {
  assert(st);
  return st->city;
}


void AB_BankInfo_SetCity(AB_BANKINFO *st, const char *d) {
  assert(st);
  if (st->city)
    free(st->city);
  if (d && *d)
    st->city=strdup(d);
  else
    st->city=0;
  st->_modified=1;
}




const char *AB_BankInfo_GetRegion(const AB_BANKINFO *st) {
  assert(st);
  return st->region;
}


void AB_BankInfo_SetRegion(AB_BANKINFO *st, const char *d) {
  assert(st);
  if (st->region)
    free(st->region);
  if (d && *d)
    st->region=strdup(d);
  else
    st->region=0;
  st->_modified=1;
}




const char *AB_BankInfo_GetPhone(const AB_BANKINFO *st) {
  assert(st);
  return st->phone;
}


void AB_BankInfo_SetPhone(AB_BANKINFO *st, const char *d) {
  assert(st);
  if (st->phone)
    free(st->phone);
  if (d && *d)
    st->phone=strdup(d);
  else
    st->phone=0;
  st->_modified=1;
}




const char *AB_BankInfo_GetFax(const AB_BANKINFO *st) {
  assert(st);
  return st->fax;
}


void AB_BankInfo_SetFax(AB_BANKINFO *st, const char *d) {
  assert(st);
  if (st->fax)
    free(st->fax);
  if (d && *d)
    st->fax=strdup(d);
  else
    st->fax=0;
  st->_modified=1;
}




const char *AB_BankInfo_GetEmail(const AB_BANKINFO *st) {
  assert(st);
  return st->email;
}


void AB_BankInfo_SetEmail(AB_BANKINFO *st, const char *d) {
  assert(st);
  if (st->email)
    free(st->email);
  if (d && *d)
    st->email=strdup(d);
  else
    st->email=0;
  st->_modified=1;
}




const char *AB_BankInfo_GetWebsite(const AB_BANKINFO *st) {
  assert(st);
  return st->website;
}


void AB_BankInfo_SetWebsite(AB_BANKINFO *st, const char *d) {
  assert(st);
  if (st->website)
    free(st->website);
  if (d && *d)
    st->website=strdup(d);
  else
    st->website=0;
  st->_modified=1;
}




AB_BANKINFO_SERVICE_LIST *AB_BankInfo_GetServices(const AB_BANKINFO *st) {
  assert(st);
  return st->services;
}


void AB_BankInfo_SetServices(AB_BANKINFO *st, AB_BANKINFO_SERVICE_LIST *d) {
  assert(st);
  if (st->services)
    AB_BankInfoService_List_free(st->services);
  if (d) {
    AB_BANKINFO_SERVICE *e;

  st->services=AB_BankInfoService_List_new();
    e=AB_BankInfoService_List_First(d);
    while(e) {
      AB_BANKINFO_SERVICE *ne;

      ne=AB_BankInfoService_dup(e);
      assert(ne);
      AB_BankInfoService_List_Add(ne, st->services);
      e=AB_BankInfoService_List_Next(e);
    } /* while (e) */
  } /* if LIST */
  else
    st->services=0;
  st->_modified=1;
}




int AB_BankInfo_IsModified(const AB_BANKINFO *st) {
  assert(st);
  return st->_modified;
}


void AB_BankInfo_SetModified(AB_BANKINFO *st, int i) {
  assert(st);
  st->_modified=i;
}


void AB_BankInfo_Attach(AB_BANKINFO *st) {
  assert(st);
  st->_usage++;
}
AB_BANKINFO *AB_BankInfo_List2__freeAll_cb(AB_BANKINFO *st, void *user_data) {
  AB_BankInfo_free(st);
return 0;
}


void AB_BankInfo_List2_freeAll(AB_BANKINFO_LIST2 *stl) {
  if (stl) {
    AB_BankInfo_List2_ForEach(stl, AB_BankInfo_List2__freeAll_cb, 0);
    AB_BankInfo_List2_free(stl); 
  }
}


AB_BANKINFO_LIST *AB_BankInfo_List_dup(const AB_BANKINFO_LIST *stl) {
  if (stl) {
    AB_BANKINFO_LIST *nl;
    AB_BANKINFO *e;

    nl=AB_BankInfo_List_new();
    e=AB_BankInfo_List_First(stl);
    while(e) {
      AB_BANKINFO *ne;

      ne=AB_BankInfo_dup(e);
      assert(ne);
      AB_BankInfo_List_Add(ne, nl);
      e=AB_BankInfo_List_Next(e);
    } /* while (e) */
    return nl;
  }
  else
    return 0;
}




