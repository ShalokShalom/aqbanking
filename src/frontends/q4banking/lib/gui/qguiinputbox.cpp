/***************************************************************************
 $RCSfile$
                             -------------------
    cvs         : $Id: qbinputbox.cpp 881 2006-01-27 14:12:06Z cstim $
    begin       : Mon Mar 01 2004
    copyright   : (C) 2004 by Martin Preuss
    email       : martin@libchipcard.de

 ***************************************************************************
 *          Please see toplevel file COPYING for license details           *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif


#include <qlabel.h>
#include <qapplication.h>
#include <qpushbutton.h>
#include <q3textbrowser.h>
#include <qlineedit.h>
#include <q3simplerichtext.h>
#include <qvalidator.h>
#include <qlayout.h>
#include <qtimer.h>
//Added by qt3to4:
#include <Q3GridLayout>
#include <Q3BoxLayout>
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>
#include <Q3Frame>

#include <gwenhywfar/debug.h>
#include <gwenhywfar/gui.h>

#include <ctype.h>

#include "qguiinputbox.h"



QGuiInputBox::Validator::Validator(QObject *parent, const char *name,
                                 uint32_t flags,
                                 int minLen, int maxLen)
:QValidator(parent, name), _flags(flags), _minLen(minLen), _maxLen(maxLen) {
}



QGuiInputBox::Validator::~Validator(){
}



QValidator::State
QGuiInputBox::Validator::validate(QString& input, int &pos) const{
  int i;
  // The input argument "pos" is unused, but due to the abstract
  // function in the parent class it has to be declared anyway.

  if (_flags & GWEN_GUI_INPUT_FLAGS_NUMERIC) {
    unsigned stringlength = input.length();
    for (unsigned k = 0; k < stringlength; ++k) {
      if (!(input[k].isDigit())) {
	  DBG_DEBUG(0, "Not a digit.\n");
          return QValidator::Invalid;
      }
    } /* if there is input */
  }
  i=input.length();
  if (i>=_minLen && i<=_maxLen)
    return Acceptable;
  else {
    DBG_DEBUG(0, "Bad length (%d).\n", i);
    return Intermediate;
  }
}





QGuiInputBox::QGuiInputBox(const QString& title,
                       const QString& text,
                       uint32_t flags,
                       int minLen,
                       int maxLen,
                       QWidget* parent,
                       const char* name,
                       bool modal,
                       Qt::WFlags fl)
:QDialog(parent, name, modal, fl)
,_flags(flags)
,_edit1(0)
,_edit2(0)
{
#if QT_VERSION < 0x040000
  // this crashes in qt-4 and is unused anyway
  Q3SimpleRichText rt(text, font());
#endif
  int width = 0;
  int height = 0;
  int max_textwidth=400;
  int max_textheight=400;
  QLabel *l;

  _validator=new Validator(this, "Validator", flags, minLen, maxLen);
#if QT_VERSION < 0x040000
  rt.setWidth(max_textwidth);
  width=rt.widthUsed();
  height=rt.height();
#endif

  setCaption(title);

  Q3BoxLayout *layout = new Q3VBoxLayout( this, 10, 6, "layout" );

  if (width > max_textwidth || height > max_textheight) {
    Q3TextEdit *t;

    /* use QTextBrowser instead of QTextLabel */
    t=new Q3TextEdit(this, "TextBox");
    t->setText(text);
    t->setReadOnly(true);
    t->setPaper(this->backgroundBrush());
    //t->setFrameStyle(QFrame::Box | QFrame::Sunken );
    layout->addWidget(t);
  }
  else {
    QLabel *t;

    /* use QLabel for short text */
    t=new QLabel(text, this, "TextBox");
    t->setAlignment(Qt::WordBreak); // the others were already default
    layout->addWidget(t);
  }

  /* The first label and input box: add label */
  Q3GridLayout *gridlayout = new Q3GridLayout( layout, 1, 2, 6, "gridlayout" );
  _edit1=new QLineEdit(this, "EditBox1");
  _edit1->setValidator(_validator);
  QObject::connect(_edit1, SIGNAL(returnPressed()),
                   this, SLOT(returnPressedOn1()));
  QObject::connect(_edit1, SIGNAL(textChanged(const QString&)),
                   this, SLOT(textChanged(const QString&)));
  if (flags & GWEN_GUI_INPUT_FLAGS_SHOW)
    _edit1->setEchoMode(QLineEdit::Normal);
  else
    _edit1->setEchoMode(QLineEdit::Password);
  gridlayout->addWidget(_edit1, 0, 1);

  l=new QLabel(_edit1, tr("&Input")+":", this, "input_Label");
  gridlayout->addWidget(l, 0, 0);

  if (flags & GWEN_GUI_INPUT_FLAGS_CONFIRM) {
    /* add QLineEdit */
    _edit2=new QLineEdit(this, "EditBox2");
    _edit2->setValidator(_validator);
    QObject::connect(_edit2, SIGNAL(returnPressed()),
                     this, SLOT(returnPressedOn2()));
    QObject::connect(_edit2, SIGNAL(textChanged(const QString&)),
                     this, SLOT(textChanged(const QString&)));
    if (flags & GWEN_GUI_INPUT_FLAGS_SHOW)
      _edit2->setEchoMode(QLineEdit::Normal);
    else
      _edit2->setEchoMode(QLineEdit::Password);
    gridlayout->addWidget(_edit2, 1, 1);

    /* add label for second input box (used as confirmation) */
    l=new QLabel(_edit2, tr("&Confirm")+":", this, "Label2");
    gridlayout->addWidget(l, 1, 0);
  }

  // Separator between input boxes and buttons
  Q3Frame* line1 = new Q3Frame( this, "line1" );
  line1->setFrameShape( Q3Frame::HLine );
  line1->setFrameShadow( Q3Frame::Sunken );
  layout->addWidget( line1 );

  // Buttons
  Q3BoxLayout *buttonlayout = new Q3HBoxLayout( layout, -1, "buttonlayout" );
  buttonlayout->addStretch();
  _okButton=new QPushButton(tr("&Ok"), this, "OkButton");
  _abortButton=new QPushButton(tr("&Abort"), this, "AbortButton");
  
  // Force buttons to be of same size. Copied from
  // QInputDialog::getText() code.
  QSize bs = _okButton->sizeHint().expandedTo( _abortButton->sizeHint() );
  _okButton->setFixedSize( bs );
  _abortButton->setFixedSize( bs );
  buttonlayout->addWidget(_okButton);
  buttonlayout->addWidget(_abortButton);

  QObject::connect(_okButton, SIGNAL(clicked()),
                   this, SLOT(accept()));
  QObject::connect(_abortButton, SIGNAL(clicked()),
                   this, SLOT(reject()));

  _edit1->setFocus();
  _okButton->setEnabled(false);

  show();
  QTimer::singleShot(0, this, SLOT(adjustSize()));
}



QGuiInputBox::~QGuiInputBox(){
}



bool QGuiInputBox::acceptableInput() {
  if (_edit1->hasAcceptableInput()) {
    if (_flags & GWEN_GUI_INPUT_FLAGS_CONFIRM) {
      if (!_edit2->hasAcceptableInput())
        return false;
      if (_edit1->text().compare(_edit2->text())==0)
        return true;
      else
        return false;
    }
    return true;
  }
  return false;
}



QString QGuiInputBox::getInput() {
  return _edit1->text();
}



void QGuiInputBox::returnPressedOn1(){
  if (!(_flags & GWEN_GUI_INPUT_FLAGS_CONFIRM)) {
    accept();
  }
  else
    _edit2->setFocus();
}



void QGuiInputBox::returnPressedOn2(){
  accept();
}



void QGuiInputBox::accept() {
  if (acceptableInput())
    QDialog::accept();
}



void QGuiInputBox::textChanged(const QString &t) {
  _okButton->setEnabled(acceptableInput());
}



#include "qguiinputbox.moc"







