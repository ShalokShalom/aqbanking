/***************************************************************************
 $RCSfile$
 -------------------
 cvs         : $Id$
 begin       : Fri Apr 02 2004
 copyright   : (C) 2004 by Martin Preuss
 email       : martin@libchipcard.de

 ***************************************************************************
 *          Please see toplevel file COPYING for license details           *
 ***************************************************************************/


#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "swift940_p.h"
#include "i18n_l.h"

/* #include <aqhbci/aqhbci.h> */
#include <aqbanking/error.h>
#include <aqbanking/imexporter_be.h>

#include <gwenhywfar/text.h>
#include <gwenhywfar/debug.h>
#include <gwenhywfar/gwentime.h>
#include <gwenhywfar/gui.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>


int AHB_SWIFT__SetCharValue(GWEN_DB_NODE *db,
                            uint32_t flags,
                            const char *name,
                            const char *s) {
  GWEN_BUFFER *vbuf;
  int rv;

  vbuf=GWEN_Buffer_new(0, strlen(s)+32, 0, 1);
  AB_ImExporter_Iso8859_1ToUtf8(s, -1, vbuf);
  rv=GWEN_DB_SetCharValue(db, flags, name, GWEN_Buffer_GetStart(vbuf));
  GWEN_Buffer_free(vbuf);
  return rv;
}



int AHB_SWIFT940_Parse_25(const AHB_SWIFT_TAG *tg,
                          uint32_t flags,
                          GWEN_DB_NODE *data,
                          GWEN_DB_NODE *cfg){
  const char *p;
  const char *p2;

  p=AHB_SWIFT_Tag_GetData(tg);
  assert(p);

  while(*p && *p==32)
    p++;
  if (*p==0) {
    DBG_WARN(AQBANKING_LOGDOMAIN, "Tag 25 is empty");
    return 0;
  }

  p2=strchr(p, '/');
  if (p2) {
    char *s;

    /* "BLZ/Konto" */
    s=(char*)GWEN_Memory_malloc(p2-p+1);
    memmove(s, p, p2-p+1);
    s[p2-p]=0;
    AHB_SWIFT__SetCharValue(data,
                            GWEN_DB_FLAGS_OVERWRITE_VARS,
                            "localBankCode", s);
    free(s);
    p=p2+1;
  }

  while(*p && *p==32)
    p++;

  if (*p) {
    p2=p;
    while(*p2 && isdigit(*p2))
      p2++;
    if (p2==p) {
      DBG_WARN(AQBANKING_LOGDOMAIN,
               "LocalAccountNumber starts with nondigits (%s)", p);
      AHB_SWIFT__SetCharValue(data,
                              GWEN_DB_FLAGS_OVERWRITE_VARS,
                              "localAccountNumber", p);
    }
    else {
      char *s;

      s=(char*)GWEN_Memory_malloc(p2-p+1);
      memmove(s, p, p2-p+1);
      s[p2-p]=0;
      AHB_SWIFT__SetCharValue(data,
                              GWEN_DB_FLAGS_OVERWRITE_VARS,
                              "localAccountNumber", s);
      free(s);
    }
  }
  return 0;
}



int AHB_SWIFT940_Parse_86(const AHB_SWIFT_TAG *tg,
                          uint32_t flags,
                          GWEN_DB_NODE *data,
                          GWEN_DB_NODE *cfg){
  const char *p;
  int isStructured;
  int code;

  p=AHB_SWIFT_Tag_GetData(tg);
  assert(p);
  isStructured=0;
  code=999;
  if (strlen(p)>3) {
    if (isdigit(p[0]) && isdigit(p[1]) && isdigit(p[2])) {
      /* starts with a three digit number */
      code=(((p[0]-'0')*100) + ((p[1]-'0')*10) + (p[2]-'0'));
      if (p[3]=='?')
	/* it is structured, get the code */
	isStructured=1;
      p+=3;
    }
  }

  if (isStructured) {
    const char *p2;
    char *s;
    int id;

    /* store code */
    GWEN_DB_SetIntValue(data, flags, "textkey", code);

    while(*p) {
      if (strlen(p)<3) {
	DBG_ERROR(AQBANKING_LOGDOMAIN, "Bad field in :86: tag (%s)", p);
	GWEN_Gui_ProgressLog(0, GWEN_LoggerLevel_Error,
                              "SWIFT: Bad field in :86: tag");
        return -1;
      }
      p++; /* skip '?' */
      /* read field id */
      if (*p==10)
        p++;
      if (!*p) {
	DBG_ERROR(AQBANKING_LOGDOMAIN, "Partial field id");
        GWEN_Gui_ProgressLog(0, GWEN_LoggerLevel_Error,
                              "SWIFT: Partial field id");
        return -1;
      }
      id=((*p-'0')*10);
      p++;

      if (*p==10)
        p++;
      if (!*p) {
        DBG_ERROR(AQBANKING_LOGDOMAIN, "Partial field id");
        GWEN_Gui_ProgressLog(0, GWEN_LoggerLevel_Error,
                              "SWIFT: Partial field id");
        return -1;
      }
      id+=(*p-'0');
      p++;

      p2=p;

      /* find end of field/beginning of next field */
      while(*p2 && *p2!='?') p2++;
      s=(char*)GWEN_Memory_malloc(p2-p+1);
      memmove(s, p, p2-p+1);
      s[p2-p]=0;
      AHB_SWIFT_Condense(s);
      DBG_DEBUG(AQBANKING_LOGDOMAIN, "Current field is %02d (%s)", id, s);
      /* now id is the field id, s points to the field content */
      if (*s) {
        switch(id) {
        case 0: /* Buchungstext */
          AHB_SWIFT__SetCharValue(data, flags, "transactionText", s);
          break;
        case 10: /* Primanota */
          AHB_SWIFT__SetCharValue(data, flags, "primanota", s);
          break;
    
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 60:
        case 61:
        case 62:
        case 63: /* Verwendungszweck */
          AHB_SWIFT__SetCharValue(data, flags, "purpose", s);
          break;
    
        case 30: /* BLZ Gegenseite */
          AHB_SWIFT__SetCharValue(data, flags, "remoteBankCode", s);
          break;
    
        case 31: /* Kontonummer Gegenseite */
          AHB_SWIFT__SetCharValue(data, flags, "remoteAccountNumber", s);
          break;
    
        case 32: 
        case 33: /* Name Auftraggeber */
          AHB_SWIFT__SetCharValue(data, flags, "remoteName", s);
          break;
    
        case 34: /* Textschluesselergaenzung */
	  break;

	case 38: /* IBAN */
	  AHB_SWIFT__SetCharValue(data, flags, "remoteIban", s);
          break;

        default: /* ignore all other fields (if any) */
          DBG_WARN(AQBANKING_LOGDOMAIN, "Unknown :86: field \"%02d\" (%s) (%s)", id, s,
                   AHB_SWIFT_Tag_GetData(tg));
          break;
        } /* switch */
      }
      p=p2;
      free(s);
    } /* while */
  } /* if structured */
  else {
    /* unstructured :86:, simply store as purpose line */
    AHB_SWIFT__SetCharValue(data, flags, "purpose", p);
  }

  return 0;
}



int AHB_SWIFT940_Parse_61(const AHB_SWIFT_TAG *tg,
                          uint32_t flags,
                          GWEN_DB_NODE *data,
                          GWEN_DB_NODE *cfg){
  const char *p;
  const char *p2;
  char *s;
  char buffer[32];
  unsigned int bleft;
  int d1a, d2a, d3a;
  int d1b, d2b, d3b;
  int neg;
  GWEN_TIME *ti;
  char curr3=0;
  const char *currency;

  p=AHB_SWIFT_Tag_GetData(tg);
  assert(p);
  bleft=strlen(p);

  /* valuata date (M) */
  if (bleft<6) {
    DBG_ERROR(AQBANKING_LOGDOMAIN, "Missing valuta date (%s)", p);
    GWEN_Gui_ProgressLog(0, GWEN_LoggerLevel_Error,
                          "SWIFT: Missing valuta date");
    return -1;
  }
  d1a=((p[0]-'0')*10) + (p[1]-'0');
  d1a+=2000;
  d2a=((p[2]-'0')*10) + (p[3]-'0');
  d3a=((p[4]-'0')*10) + (p[5]-'0');

  if (d3a==30 && d2a==2) {
    /* date is Feb 30, this date is invalid. However, some banks use this
     * to indicate the last day of February, so we move along */
    d3a=1;
    d2a=3;
    ti=GWEN_Time_new(d1a, d2a-1, d3a, 12, 0, 0, 1);
    assert(ti);
    /* subtract a day to get the last day in FEB */
    GWEN_Time_SubSeconds(ti, 60*60*24);
  }
  else {
    ti=GWEN_Time_new(d1a, d2a-1, d3a, 12, 0, 0, 1);
    assert(ti);
  }
  if (GWEN_Time_toDb(ti, GWEN_DB_GetGroup(data,
                                          GWEN_DB_FLAGS_OVERWRITE_GROUPS,
                                          "valutadate"))) {
    DBG_ERROR(AQBANKING_LOGDOMAIN, "Error saving valuta date");
  }
  p+=6;
  bleft-=6;

  /* booking date (K) */
  if (*p && isdigit(*p)) {
    if (bleft<4) {
      DBG_ERROR(AQBANKING_LOGDOMAIN, "Bad booking date (%s)", p);
      GWEN_Gui_ProgressLog(0, GWEN_LoggerLevel_Info,
                            "SWIFT: Bad booking date");
      return -1;
    }
    d2b=((p[0]-'0')*10) + (p[1]-'0');
    d3b=((p[2]-'0')*10) + (p[3]-'0');
    /* use year from valutaDate.
     * However: if valuta date and booking date are in different years
     * the booking year might be too high.
     * We detect this case by comparing the months: If the booking month
     * is and the valuta month differ by more than 10 months then the year
     * of the booking date will be adjusted.
     */
    if (d2b-d2a>10) {
      /* booked before actually withdrawn */
      d1b=d1a-1;
    }
    else if (d2a-d2b>10) {
      /* withdrawn and booked later */
      d1b=d1a+1;
    }
    else
      d1b=d1a;

    ti=GWEN_Time_new(d1b, d2b-1, d3b, 12, 0, 0, 1);
    assert(ti);
    if (GWEN_Time_toDb(ti, GWEN_DB_GetGroup(data,
					    GWEN_DB_FLAGS_OVERWRITE_GROUPS,
					    "date"))) {
      DBG_ERROR(AQBANKING_LOGDOMAIN, "Error saving date");
    }
    p+=4;
    bleft-=4;
  }

  /* credit/debit mark (M) */
  if (bleft<2) {
    DBG_ERROR(AQBANKING_LOGDOMAIN, "Bad value string (%s)", p);
    GWEN_Gui_ProgressLog(0, GWEN_LoggerLevel_Error,
                          "SWIFT: Bad value string");
    return -1;
  }
  neg=0;
  if (*p=='R') {
    if (p[1]=='C' || p[1]=='c')
      neg=1;
    p+=2;
    bleft-=2;
  }
  else {
    if (*p=='D' || *p=='d')
      neg=1;
    p++;
    bleft--;
  }

  /* third character of currency (K) */
  if (bleft<1) {
    DBG_ERROR(AQBANKING_LOGDOMAIN, "Bad data (%s)", p);
    GWEN_Gui_ProgressLog(0, GWEN_LoggerLevel_Error,
                          "SWIFT: Bad currency");
    return -1;
  }
  if (!isdigit(*p)) {
    /* found third character, skip it */
    curr3=*p;
    p++;
    bleft--;
  }

  /* value (M) */
  p2=p;
  while(*p2 && (isdigit(*p2) || *p2==','))
    p2++;
  if (p2==p) {
    DBG_ERROR(AQBANKING_LOGDOMAIN, "No value (%s)", p);
    GWEN_Gui_ProgressLog(0, GWEN_LoggerLevel_Error,
                          "SWIFT: Bad value");
    return -1;
  }
  s=(char*)GWEN_Memory_malloc(p2-p+1+(neg?1:0));
  if (neg) {
    s[0]='-';
    memmove(s+1, p, p2-p+1);
    s[p2-p+1]=0;
  }
  else {
    memmove(s, p, p2-p+1);
    s[p2-p]=0;
  }
  AHB_SWIFT__SetCharValue(data, flags, "value/value", s);
  currency=GWEN_DB_GetCharValue(cfg, "currency", 0, 0);
  if (currency)
    AHB_SWIFT__SetCharValue(data, flags,
			    "value/currency", currency);
  free(s);
  bleft-=p2-p;
  p=p2;

  /* skip 'N' */
  p++;
  bleft--;

  /* key (M) */
  if (bleft<3) {
    DBG_ERROR(AQBANKING_LOGDOMAIN, "Missing booking key (%s)", p);
    GWEN_Gui_ProgressLog(0, GWEN_LoggerLevel_Error,
                          "SWIFT: Missing booking key");
    return -1;
  }
  memmove(buffer, p, 3);
  buffer[3]=0;
  AHB_SWIFT__SetCharValue(data, flags, "transactionKey", buffer);
  p+=3;
  bleft-=3;

  /* customer reference (M) */
  if (bleft>1) {
    if (*p=='/' && p[1]!='/') {
      p++;
      bleft--;
    }

    p2=p;
    while(*p2 && *p2!='/' && *p2!=10) p2++;

    if (p2==p) {
      DBG_WARN(AQBANKING_LOGDOMAIN, "Missing customer reference (%s)", p);
      GWEN_Gui_ProgressLog(0, GWEN_LoggerLevel_Error,
			    "SWIFT: Missing customer reference");
    }
    else {
      s=(char*)GWEN_Memory_malloc(p2-p+1);
      memmove(s, p, p2-p);
      s[p2-p]=0;
      if (strcasecmp(s, "NONREF")!=0)
        AHB_SWIFT__SetCharValue(data, flags, "customerReference", s);
      free(s);
    }
    bleft-=p2-p;
    p=p2;
    assert(bleft>=0);
  }

  /* bank reference (K) */
  if (bleft>1) {
    if (*p=='/' && p[1]=='/') {
      /* found bank reference */
      p+=2;
      bleft-=2;

      p2=p;
      while(*p2 && *p2!='/' && *p2!=10) p2++;
      if (p2==p) {
	DBG_ERROR(AQBANKING_LOGDOMAIN, "Missing bank reference (%s)", p);
	GWEN_Gui_ProgressLog(0, GWEN_LoggerLevel_Error,
			      "SWIFT: Missing bank reference");
	return -1;
      }
      s=(char*)GWEN_Memory_malloc(p2-p+1);
      memmove(s, p, p2-p+1);
      s[p2-p]=0;
      AHB_SWIFT__SetCharValue(data, flags, "bankReference", s);
      free(s);
      bleft-=p2-p;
      p=p2;
      assert(bleft>=0);
    }
  }

  /* more information ? */
  if (*p==10) {
    /* yes... */
    p++;
    bleft--;

    while(*p) {
      /* read extra information */
      if (*p=='/') {
        if (p[1]==0)
          return 0;

        if (bleft<6) {
	  DBG_WARN(AQBANKING_LOGDOMAIN,
		   "Unknown extra data, ignoring (%s)", p);
	  return 0;
	}
	if (strncasecmp(p, "/OCMT/", 6)==0) {
          /* original value */
          p+=6;
          bleft-=6;
          /* get currency */
          memmove(buffer, p, 3);
          buffer[3]=0;
          AHB_SWIFT__SetCharValue(data, flags, "origvalue/currency", buffer);
          p+=3;
          bleft-=3;
          /* get value */
          p2=p;
          while(*p2 && *p2!='/') p2++;
          if (p2==p) {
            DBG_ERROR(AQBANKING_LOGDOMAIN, "Bad original value (%s)", p);
            GWEN_Gui_ProgressLog(0, GWEN_LoggerLevel_Error,
                                  "SWIFT: Bad original value");
            return -1;
          }
          s=(char*)GWEN_Memory_malloc(p2-p+1);
          memmove(s, p, p2-p+1);
          s[p2-p]=0;
          AHB_SWIFT__SetCharValue(data, flags, "origvalue/value", s);
          free(s);
          bleft-=p2-p;
          p=p2;
        }
        else if (strncasecmp(p, "/CHGS/", 6)==0) {
          /* charges */
          p+=6;
          bleft-=6;
          /* get currency */
          memmove(buffer, p, 3);
          buffer[3]=0;
          AHB_SWIFT__SetCharValue(data, flags, "charges/currency", buffer);
          p+=3;
          bleft-=3;
          /* get value */
          p2=p;
          while(*p2 && *p2!='/') p2++;
          if (p2==p) {
            DBG_ERROR(AQBANKING_LOGDOMAIN, "Bad charges value (%s)", p);
            GWEN_Gui_ProgressLog(0, GWEN_LoggerLevel_Error,
                                  "SWIFT: Bad charges value");
            return -1;
          }
	  s=(char*)GWEN_Memory_malloc(p2-p+1);
          memmove(s, p, p2-p+1);
          s[p2-p]=0;
          AHB_SWIFT__SetCharValue(data, flags, "charges/value", s);
          free(s);
          bleft-=p2-p;
          p=p2;
        }
        else {
	  DBG_WARN(AQBANKING_LOGDOMAIN,
		   "Unknown extra data, ignoring (%s)", p);
	  return 0;
        }
      }
      else {
	DBG_WARN(AQBANKING_LOGDOMAIN, "Bad extra data, ignoring (%s)", p);
	return 0;
      }
    } /* while */
  } /* if there is extra data */

  return 0;
}



int AHB_SWIFT940_Parse_6_0_2(const AHB_SWIFT_TAG *tg,
                             uint32_t flags,
                             GWEN_DB_NODE *data,
                             GWEN_DB_NODE *cfg){
  const char *p;
  const char *p2;
  char *s;
  char buffer[32];
  unsigned int bleft;
  int d1, d2, d3;
  int neg;
  GWEN_TIME *ti;

  p=AHB_SWIFT_Tag_GetData(tg);
  assert(p);
  bleft=strlen(p);

  /* credit/debit mark (M) */
  if (bleft<2) {
    DBG_ERROR(AQBANKING_LOGDOMAIN, "Bad value string (%s)", p);
    GWEN_Gui_ProgressLog(0, GWEN_LoggerLevel_Error,
                          "SWIFT: Bad value string");
    return -1;
  }
  neg=0;
  if (*p=='D' || *p=='d')
    neg=1;
  p++;
  bleft--;

  /* date (M) */
  if (bleft<6) {
    DBG_ERROR(AQBANKING_LOGDOMAIN, "Missing date (%s)", p);
    GWEN_Gui_ProgressLog(0, GWEN_LoggerLevel_Error,
                          "SWIFT: Missing date");
    return -1;
  }
  d1=((p[0]-'0')*10) + (p[1]-'0');
  d1+=2000;
  d2=((p[2]-'0')*10) + (p[3]-'0');
  d3=((p[4]-'0')*10) + (p[5]-'0');

  ti=GWEN_Time_new(d1, d2-1, d3, 12, 0, 0, 1);
  assert(ti);
  if (GWEN_Time_toDb(ti, GWEN_DB_GetGroup(data,
                                          GWEN_DB_FLAGS_OVERWRITE_GROUPS,
					  "date"))) {
    DBG_ERROR(AQBANKING_LOGDOMAIN, "Error saving date");
  }

  p+=6;
  bleft-=6;

  /* currency (M) */
  if (!isdigit(*p)) {
    /* only read currency if this is not part of the value (like in some
     * swiss MT940) */
    if (bleft<3) {
      DBG_ERROR(AQBANKING_LOGDOMAIN, "Missing currency (%s)", p);
      GWEN_Gui_ProgressLog(0, GWEN_LoggerLevel_Error,
			    "SWIFT: Missing currency");
      return -1;
    }
    memmove(buffer, p, 3);
    buffer[3]=0;
    AHB_SWIFT__SetCharValue(data, flags, "value/currency", buffer);
    p+=3;
    bleft-=3;
  }

  /* value (M) */
  if (bleft<1) {
    DBG_ERROR(AQBANKING_LOGDOMAIN, "Missing value (%s)", p);
    GWEN_Gui_ProgressLog(0, GWEN_LoggerLevel_Error,
			  "SWIFT: Missing value");
    return -1;
  }

  p2=p;
  while(*p2 && (isdigit(*p2) || *p2==',')) p2++;
  if (p2==p) {
    DBG_ERROR(AQBANKING_LOGDOMAIN, "Bad value (%s)", p);
    GWEN_Gui_ProgressLog(0, GWEN_LoggerLevel_Error,
                          "SWIFT: Bad value");
    return -1;
  }
  s=(char*)GWEN_Memory_malloc(p2-p+1+(neg?1:0));
  if (neg) {
    s[0]='-';
    memmove(s+1, p, p2-p+1);
    s[p2-p+1]=0;
  }
  else {
    memmove(s, p, p2-p+1);
    s[p2-p]=0;
  }
  AHB_SWIFT__SetCharValue(data, flags, "value/value", s);
  free(s);
  bleft-=p2-p;
  p=p2;

  return 0;
}



int AHB_SWIFT940_Parse_NS(const AHB_SWIFT_TAG *tg,
                          uint32_t flags,
                          GWEN_DB_NODE *data,
                          GWEN_DB_NODE *cfg){
  const char *p;
  const char *p2;

  p=AHB_SWIFT_Tag_GetData(tg);
  assert(p);

  while(*p) {
    int code;

    code=0;
    /* read code */
    if (strlen(p)>2) {
      if (isdigit(p[0]) && isdigit(p[1])) {
	/* starts with a two digit number */
	code=(((p[0]-'0')*10) + (p[1]-'0'));
	p+=2;
      }
    }

    /* search for end of line */
    p2=p;
    while(*p2 && *p2!=10 && *p2!=13)
      p2++;

    if (code==0) {
      DBG_WARN(AQBANKING_LOGDOMAIN, "No code in line");
      p=p2;
    }
    else {
      int len;

      len=p2-p;
      if (len<1 || (len==1 && *p=='/')) {
	DBG_DEBUG(AQBANKING_LOGDOMAIN, "Empty field %02d", code);
      }
      else {
	char *s;

	s=(char*)GWEN_Memory_malloc(len+1);
	memmove(s, p, len);
	s[len]=0;
	DBG_DEBUG(AQBANKING_LOGDOMAIN, "Got his field: %02d: %s", code, s);

	switch(code) {
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	  AHB_SWIFT__SetCharValue(data, flags, "purpose", s);
	  break;

	case 15: /* Auftraggeber1 */
	case 16: /* Auftraggeber2 */
	  AHB_SWIFT__SetCharValue(data, flags, "localName", s);
	  break;

	case 17: /* Buchungstext */
	  AHB_SWIFT__SetCharValue(data, flags, "transactionText", s);
	  break;

	case 18: /* Primanota */
	  AHB_SWIFT__SetCharValue(data, flags, "primanota", s);
	  break;

	case 19: /* Uhrzeit der Buchung */
	case 20: /* Anzahl der Sammlerposten */
	case 33: /* BLZ Auftraggeber */
	case 34: /* Konto Auftraggeber */
	  break;

	default: /* ignore all other fields (if any) */
	  DBG_WARN(AQBANKING_LOGDOMAIN,
		   "Unknown :NS: field \"%02d\" (%s) (%s)",
		   code, s,
		   AHB_SWIFT_Tag_GetData(tg));
	  break;
	}
        free(s);
      }
      p=p2;
    }

    if (*p==10)
      p++;
    if (*p==13)
      p++;
    if (*p==10)
      p++;
  } /* while */

  return 0;
}



int AHB_SWIFT940_Import(AHB_SWIFT_TAG_LIST *tl,
			GWEN_DB_NODE *data,
			GWEN_DB_NODE *cfg,
			uint32_t flags,
			uint32_t guiid,
			int msecs) {
  AHB_SWIFT_TAG *tg;
  GWEN_DB_NODE *dbDay=NULL;
  GWEN_DB_NODE *dbTemplate=NULL;
  GWEN_DB_NODE *dbTransaction=NULL;
  GWEN_DB_NODE *dbDate=NULL;
  uint32_t progressId;
  const char *acceptTag20="*";
  const char *rejectTag20=NULL;
  int ignoreCurrentReport=0;

  acceptTag20=GWEN_DB_GetCharValue(cfg, "acceptTag20", 0, NULL);
  if (acceptTag20 && *acceptTag20==0)
    acceptTag20=NULL;
  rejectTag20=GWEN_DB_GetCharValue(cfg, "rejectTag20", 0, NULL);
  if (rejectTag20 && *rejectTag20==0)
    rejectTag20=NULL;

  dbTemplate=GWEN_DB_Group_new("template");

  progressId=GWEN_Gui_ProgressStart(GWEN_GUI_PROGRESS_DELAY |
				    GWEN_GUI_PROGRESS_ALLOW_EMBED |
				    GWEN_GUI_PROGRESS_SHOW_PROGRESS |
				    GWEN_GUI_PROGRESS_SHOW_ABORT,
				    I18N("Importing SWIFT tags..."),
				    NULL,
				    AHB_SWIFT_Tag_List_GetCount(tl),
				    guiid);

  tg=AHB_SWIFT_Tag_List_First(tl);
  while(tg) {
    const char *id;

    id=AHB_SWIFT_Tag_GetId(tg);
    assert(id);

    if (strcasecmp(id, "20")==0) {
      if (acceptTag20 || rejectTag20) {
	const char *p;

	p=AHB_SWIFT_Tag_GetData(tg);
	assert(p);
	if (rejectTag20) {
	  if (-1!=GWEN_Text_ComparePattern(p, rejectTag20, 0)) {
	    DBG_INFO(AQBANKING_LOGDOMAIN, "Ignoring report [%s]", p);
	    ignoreCurrentReport=1;
	  }
	  else {
	    ignoreCurrentReport=0;
	  }
	}
	else if (acceptTag20) {
	  if (-1==GWEN_Text_ComparePattern(p, acceptTag20, 0)) {
	    DBG_INFO(AQBANKING_LOGDOMAIN,
		     "Ignoring report [%s] (not matching [%s])",
		     p, acceptTag20);
	    ignoreCurrentReport=1;
	  }
	  else {
	    ignoreCurrentReport=0;
	  }
	}

      }
    }
    else {
      if (!ignoreCurrentReport) {
	if (strcasecmp(id, "25")==0) { /* LocalAccount */
	  if (AHB_SWIFT940_Parse_25(tg, flags, dbTemplate, cfg)) {
	    DBG_INFO(AQBANKING_LOGDOMAIN, "Error in tag");
	    GWEN_DB_Group_free(dbTemplate);
	    GWEN_Gui_ProgressEnd(progressId);
	    return -1;
	  }
	}
	else if (strcasecmp(id, "60F")==0) { /* StartSaldo */
	  GWEN_DB_NODE *dbSaldo;
	  const char *curr;
    
	  /* start a new day */
	  dbDay=GWEN_DB_GetGroup(data, GWEN_PATH_FLAGS_CREATE_GROUP, "day");
    
	  dbTransaction=0;
	  DBG_INFO(AQBANKING_LOGDOMAIN, "Starting new day");
	  dbSaldo=GWEN_DB_GetGroup(dbDay, GWEN_PATH_FLAGS_CREATE_GROUP,
				   "StartSaldo");
	  GWEN_DB_AddGroupChildren(dbSaldo, dbTemplate);
	  if (AHB_SWIFT940_Parse_6_0_2(tg, flags, dbSaldo, cfg)) {
	    DBG_INFO(AQBANKING_LOGDOMAIN, "Error in tag");
	    GWEN_DB_Group_free(dbTemplate);
	    GWEN_Gui_ProgressEnd(progressId);
	    return -1;
	  }
	  else {
	    dbDate=GWEN_DB_GetGroup(dbSaldo, GWEN_PATH_FLAGS_NAMEMUSTEXIST,
				    "date");
	  }
    
	  curr=GWEN_DB_GetCharValue(dbSaldo, "value/currency", 0, 0);
	  if (curr) {
	    AHB_SWIFT__SetCharValue(dbTemplate, flags,
				    "value/currency", curr);
	  }
	}
	else if (strcasecmp(id, "62F")==0) { /* EndSaldo */
	  GWEN_DB_NODE *dbSaldo;
    
	  /* end current day */
	  dbTransaction=0;
	  if (!dbDay) {
	    DBG_WARN(AQBANKING_LOGDOMAIN, "Your bank does not send an opening saldo");
	    dbDay=GWEN_DB_GetGroup(data, GWEN_PATH_FLAGS_CREATE_GROUP, "day");
	  }
	  dbSaldo=GWEN_DB_GetGroup(dbDay, GWEN_PATH_FLAGS_CREATE_GROUP,
				   "EndSaldo");
	  GWEN_DB_AddGroupChildren(dbSaldo, dbTemplate);
	  if (AHB_SWIFT940_Parse_6_0_2(tg, flags, dbSaldo, cfg)) {
	    DBG_INFO(AQBANKING_LOGDOMAIN, "Error in tag");
	    GWEN_DB_Group_free(dbTemplate);
	    GWEN_Gui_ProgressEnd(progressId);
	    return -1;
	  }
	  dbDay=0;
	}
	else if (strcasecmp(id, "61")==0) {
	  if (!dbDay) {
	    DBG_WARN(AQBANKING_LOGDOMAIN,
		     "Your bank does not send an opening saldo");
	    dbDay=GWEN_DB_GetGroup(data, GWEN_PATH_FLAGS_CREATE_GROUP, "day");
	  }
    
	  DBG_INFO(AQBANKING_LOGDOMAIN, "Creating new transaction");
	  dbTransaction=GWEN_DB_GetGroup(dbDay, GWEN_PATH_FLAGS_CREATE_GROUP,
					 "transaction");
	  GWEN_DB_AddGroupChildren(dbTransaction, dbTemplate);
	  if (dbDate) {
	    GWEN_DB_NODE *dbT;
    
	    /* dbDate is set upon parsing of tag 60F, use it as a default
	     * if possible */
	    dbT=GWEN_DB_GetGroup(dbTransaction, GWEN_DB_FLAGS_OVERWRITE_GROUPS,
				 "date");
	    assert(dbT);
	    GWEN_DB_AddGroupChildren(dbT, dbDate);
	  }
	  if (AHB_SWIFT940_Parse_61(tg, flags, dbTransaction, cfg)) {
	    DBG_INFO(AQBANKING_LOGDOMAIN, "Error in tag");
	    GWEN_DB_Group_free(dbTemplate);
	    GWEN_Gui_ProgressEnd(progressId);
	    return -1;
	  }
	}
	else if (strcasecmp(id, "86")==0) {
	  if (!dbTransaction) {
	    DBG_WARN(AQBANKING_LOGDOMAIN,
		     "Bad sequence of tags (86 before 61), ignoring");
	  }
	  else {
	    if (AHB_SWIFT940_Parse_86(tg, flags, dbTransaction, cfg)) {
	      DBG_INFO(AQBANKING_LOGDOMAIN, "Error in tag");
	      GWEN_DB_Group_free(dbTemplate);
	      GWEN_Gui_ProgressEnd(progressId);
	      return -1;
	    }
	  }
	}
	else if (strcasecmp(id, "NS")==0) {
	  if (!dbTransaction) {
	    DBG_DEBUG(AQBANKING_LOGDOMAIN,
		      "Ignoring NS tags outside transactions");
	  }
	  else {
	    if (AHB_SWIFT940_Parse_NS(tg, flags, dbTransaction, cfg)) {
	      DBG_INFO(AQBANKING_LOGDOMAIN, "Error in tag");
	      GWEN_DB_Group_free(dbTemplate);
	      GWEN_Gui_ProgressEnd(progressId);
	      return -1;
	    }
	  }
	}
      }
    }

    if (GWEN_Gui_ProgressAdvance(progressId, GWEN_GUI_PROGRESS_ONE)==
	GWEN_ERROR_USER_ABORTED) {
      GWEN_Gui_ProgressLog(0, GWEN_LoggerLevel_Error,
			   I18N("Aborted by user"));
      GWEN_Gui_ProgressEnd(progressId);
      GWEN_DB_Group_free(dbTemplate);
      return GWEN_ERROR_USER_ABORTED;
    }

    tg=AHB_SWIFT_Tag_List_Next(tg);
  } /* while */

  GWEN_DB_Group_free(dbTemplate);
  GWEN_Gui_ProgressEnd(progressId);

  return 0;
}








