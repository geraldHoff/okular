/***************************************************************************
 *   Copyright (C) 2002 by Wilco Greven <greven@kde.org>                   *
 *   Copyright (C) 2003-2004 by Christophe Devriese                        *
 *                         <Christophe.Devriese@student.kuleuven.ac.be>    *
 *   Copyright (C) 2003 by Andy Goossens <andygoossens@telenet.be>         *
 *   Copyright (C) 2003 by Laurent Montel <montel@kde.org>                 *
 *   Copyright (C) 2004 by Dominique Devriese <devriese@kde.org>           *
 *   Copyright (C) 2004 by Albert Astals Cid <tsdgeos@terra.es>            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _KPDF_PART_H_
#define _KPDF_PART_H_

#include <kparts/browserextension.h>
#include <kparts/part.h>

class QWidget;
class QSplitter;
class QToolBox;

class KURL;
class KAction;
class KToggleAction;
class KSelectAction;
class KAboutData;
class KPrinter;

class LinkAction;
class LinkDest;

class ThumbnailList;
class PageView;
class SearchWidget;
class KPDFDocument;

namespace KPDF
{
  class BrowserExtension;

  /**
   * This is a "Part".  It that does all the real work in a KPart
   * application.
   *
   * @short Main Part
   * @author Wilco Greven <greven@kde.org>
   * @version 0.2
   */
  class Part : public KParts::ReadOnlyPart
  {
	Q_OBJECT

  public:

	/**
	* Default constructor
	*/
	Part(QWidget* parentWidget, const char* widgetName,
	     QObject* parent, const char* name, const QStringList& args);

	/**
	* Destructor
	*/
	virtual ~Part();

	static KAboutData* createAboutData();

	// reimplemented from KParts::ReadOnlyPart
	bool closeURL();
	void displayPage(int pageNumber ); //TODO REMOVE ME!

  protected:
	// reimplemented from KParts::ReadOnlyPart
	virtual bool openFile();
	// reimplemented from KParts::ReadOnlyPart
	virtual bool openURL(const KURL &url);

	void updateAction();
	void doPrint( KPrinter& printer );

  protected slots:
	// connected to actions
	void slotGoToPage();
	void slotPreviousPage();
	void slotNextPage();
	void slotGotoFirst();
	void slotGotoLast();
	void slotFind();
	void slotFindNext();
	void slotSaveFileAs();
	void slotPrintPreview();
	// can be connected to widget elements
	void updateActions();
	void enableTOC(bool enable);

  public slots:
	// connected to Shell action (and browserExtension), not local one
	void slotPrint();

  private:
	// the document
	KPDFDocument * document;

	// main widgets
	QSplitter *m_splitter;
	ThumbnailList *m_thumbnailList;
	PageView *m_pageView;
	SearchWidget *m_searchWidget;

	// static instances counter
	static unsigned int m_count;

	QToolBox *m_toolBox;

	// actions
	KAction *m_gotoPage;
	KAction *m_prevPage;
	KAction *m_nextPage;
	KAction *m_firstPage;
	KAction *m_lastPage;
	KAction *m_find;
	KAction *m_findNext;
  };

  class BrowserExtension : public KParts::BrowserExtension
  {
	Q_OBJECT

  public:
	BrowserExtension(Part*);

  public slots:
	// Automatically detected by the host.
	void print();
  };

}

#endif

// vim:ts=2:sw=2:tw=78:et
