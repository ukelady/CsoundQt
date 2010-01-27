/*
    Copyright (C) 2008, 2009 Andres Cabrera
    mantaraya36@gmail.com

    This file is part of QuteCsound.

    QuteCsound is free software; you can redistribute it
    and/or modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    QuteCsound is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with Csound; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
    02111-1307 USA
*/

#ifndef DOCUMENTPAGE_H
#define DOCUMENTPAGE_H

#include <QWidget>
#include <QTextEdit>
#include <QDomElement>
#include <QStack>

#include "types.h"

class OpEntryParser;
class Highlighter;
class DocumentView;
class WidgetLayout;
class LiveEventFrame;
class CsoundEngine;

class Curve;

//FIXME when refactoring is done, organize the methods in the correct order

class DocumentPage : public QObject
{
  Q_OBJECT
  public:
    DocumentPage(QWidget *parent, OpEntryParser *opcodeTree);
    ~DocumentPage();

    int setTextString(QString text, bool autoCreateMacCsoundSections = true);
    QString getFullText();
    QString getBasicText();
    QString getOptionsText();
    QString getDotText();
    QString getMacWidgetsText();
    QString getMacPresetsText();
    QString getMacOptionsText();
    QString getMacOptions(QString option);
    QRect getWidgetPanelGeometry();
    void getToIn();
    void inToGet();
    void markErrorLines(QList<int> lines);
    void unmarkErrorLines();
    void updateCsladspaText(QString text);
    QString getFilePath();
    int currentLine();
    QStringList getScheduledEvents(unsigned long ksmpscount);
    void setModified(bool mod);
    bool isModified();

    void copy();  // This actions are passed here for distribution
    void cut();  // Can it be done better?
    void paste();
    void undo();
    void redo();

    DocumentView * view();

    QString fileName;
    QString companionFile;
    bool askForFile;
    bool readOnly; // Used for manual files and internal examples

    QVector<QString> widgetHistory;  // Undo/ Redo history
    int widgetHistoryIndex; // Current point in history

    QAction *runAct;

  public slots:
    void play();
    void pause();
    void stop();
    void render();
    void record();
    void recordBuffer();

    void keyPressForCsound(QString key);
    void keyReleaseForCsound(QString key);

    void setMacWidgetsText(QString widgetText);
    void setMacOptionsText(QString text);
    void setMacOption(QString option, QString newValue);
    void setWidgetPanelPosition(QPoint position);
    void setWidgetPanelSize(QSize size);
    void jumpToLine(int line);

    void opcodeFromMenu();
    void newLiveEventFrame(QString text = QString());
    LiveEventFrame * createLiveEventFrame(QString text = QString());
    void deleteLiveEventFrame(LiveEventFrame *frame);
    void showLiveEventFrames(bool visible);

  protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void contextMenuEvent(QContextMenuEvent *event);
    virtual void closeEvent(QCloseEvent *event);

  private:
    QStringList macOptions;
    QString macPresets;
//    QString macGUI;
    QDomElement widgetsXml;
    int refreshTime; // time in milliseconds for widget value updates (both directions)
    QTimer *queueTimer;

    WidgetLayout * m_widgetLayout;
    DocumentView *m_view;
    CsoundEngine *m_csEngine;
    QVector<LiveEventFrame *> m_liveFrames;


    Highlighter *m_highlighter;
    OpEntryParser *m_opcodeTree;
    bool errorMarked;
    bool saveLiveEvents;
    int bufferSize; // size of teh record buffer
    MYFLT *recBuffer; // for temporary copy of Csound output buffer when recording to file
    
    QMutex stringValueMutex;

    QStack<Curve *> newCurveBuffer;  // To store curves from Csound for widget panel Graph widgets
    QVector<WINDAT *> curveBuffer;  // TODO Should these be moved to the widget layout class?

    QMutex messageMutex;
    QStringList messageQueue;  // Messages from Csound execution
    QMutex keyMutex; // For keys pressed to pass to Csound from console and widget panel
    QStringList keyPressBuffer; // protected by keyMutex
    QStringList keyReleaseBuffer; // protected by keyMutex

  private slots:
    void changed();
    void liveEventFrameClosed();
    void dispatchQueues();
    void queueMessage(QString message);
    void clearMessageQueue();
//     void moved();

  signals:
    void currentLineChanged(int);
    void currentTextUpdated();
    void doCopy();
    void doCut();
    void doPaste();
    void registerLiveEvent(QWidget *e);
    void liveEventsVisible(bool);  // To change the action in the main window
};

#endif
