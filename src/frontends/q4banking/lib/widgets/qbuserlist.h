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

#ifndef QBANKING_USERLIST_H
#define QBANKING_USERLIST_H


#include <Qt3Support/q3listview.h>
#include <aqbanking/user.h>
#include <q4banking/qbanking.h>

#include <list>

class QBUserListView;
class QBUserListViewItem;


class Q4BANKING_API QBUserListViewItem: public Q3ListViewItem {
private:
  AB_USER *_user;

  void _populate();

public:
  QBUserListViewItem(QBUserListView *parent, AB_USER *user);
  QBUserListViewItem(QBUserListView *parent,
		      Q3ListViewItem *after,
		      AB_USER *user);
  QBUserListViewItem(const QBUserListViewItem &item);

  virtual ~QBUserListViewItem();

  AB_USER *getUser();
};



class Q4BANKING_API QBUserListView: public Q3ListView {
private:
public:
  QBUserListView(QWidget *parent=0, const char *name=0);
  virtual ~QBUserListView();

  void addUser(AB_USER *user);
  void addUsers(const std::list<AB_USER*> &users);

  void removeUser(AB_USER *user);

  AB_USER *getCurrentUser();
  std::list<AB_USER*> getSelectedUsers();
  std::list<AB_USER*> getSortedUsers();
  AB_USER_LIST2 *getSortedUsersList2();

};




#endif /* QBANKING_USERLIST_H */



