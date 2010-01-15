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

#ifndef QBANKING_IMPORTER_H
#define QBANKING_IMPORTER_H


class QBanking;
class QBImporter;

#include <q4banking/qbanking.h>

#include "qbimporter.ui.h"

#include <list>
#include <string>

#include <Qt/qstring.h>

#include <gwenhywfar/logger.h>


class Q4BANKING_API QBImporter: public Q3Wizard, public Ui_QBImporterUi {
  Q_OBJECT

private:

public:
  QBImporter(QBanking *kb,
             QWidget* parent=0,
             const char* name=0,
             bool modal=FALSE);
  QBImporter(QBanking *kb,
             uint32_t flags,
             QWidget* parent=0,
             const char* name=0,
             bool modal=FALSE);
  ~QBImporter();

  bool init();
  bool fini();

  static Q4BANKING_API bool import(QBanking *qb,
                                  uint32_t flags=
                                  Q4BANKING_IMPORTER_FLAGS_ASK_ALL_DUPES |
                                  Q4BANKING_IMPORTER_FLAGS_FUZZY,
                                  QWidget* parent=0);

public slots:
  void back();
  void next();
  void reject();
  void accept();

  void help();

  void slotSelectFile();
  void slotFileNameChanged(const QString &s);

  void slotProfileSelected();

  void slotProfileDetails();
  void slotProfileEdit();

private:
  QBanking *_app;
  uint32_t _flags;
  AB_IMEXPORTER_CONTEXT *_context;
  bool _aborted;
  GWEN_PLUGIN_DESCRIPTION_LIST2 *_importerList;
  QString _importerName;
  AB_IMEXPORTER *_importer;
  GWEN_DB_NODE *_profiles;
  GWEN_DB_NODE *_profile;
  std::list<QWidget*> _pagesDone;
  QString _logText;
  GWEN_DB_NODE *_dbData;
  GWEN_LOGGER_LEVEL _logLevel;

  bool _updateImporterList();
  bool _checkFileType(const QString &fname);
  bool _readFile(const QString &fname);
  bool _importData(AB_IMEXPORTER_CONTEXT *ctx);

  bool _doPage(QWidget *p);
  bool _undoPage(QWidget *p);

  bool enterPage(QWidget *p, bool back);
  bool leavePage(QWidget *p, bool back);

  bool initSelectSourcePage();
  bool doSelectSourcePage(QWidget *p);
  bool undoSelectSourcePage(QWidget *p);

  bool initSelectImporterPage();
  bool doSelectImporterPage(QWidget *p);
  bool undoSelectImporterPage(QWidget *p);

  bool initSelectProfilePage();
  bool doSelectProfilePage(QWidget *p);
  bool undoSelectProfilePage(QWidget *p);

  bool doWorkingPage(QWidget *p);
  bool undoWorkingPage(QWidget *p);

  bool doImportPage(QWidget *p);

  void save();


};



#endif // AQBANKING_KDE_EDITTRANS_H




