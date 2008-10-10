/***************************************************************************
 *   This file is part of KWorship.                                        *
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   KWorship is free software: you can redistribute it and/or modify      *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   KWorship is distributed in the hope that it will be useful,           *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with KWorship.  If not, write to the Free Software Foundation,  *
 *   Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.   *
 ***************************************************************************/

/**
 * @file KwPlaylistPresentation.h
 * @brief An image playlist item.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwPlaylistPresentation.h"
#include "KwDisplayManager.h"

#include "UpManager.h"

#include <KLocale>
#include <KMimeType>
#include <KMessageBox>

/*
 * Constructors + destructor.
 */

/// Default constructor.
KwPlaylistPresentation::KwPlaylistPresentation(const QUrl& url)
: KwPlaylistFile(url)
{
}

/// Destructor.
KwPlaylistPresentation::~KwPlaylistPresentation()
{
}

/*
 * Main interface.
 */

void KwPlaylistPresentation::activate(KwDisplayManager* manager)
{
  manager->text.clear();
  // Just load the presentation file for the minute
  bool attemptFailed;
  bool presentation = UpManager::self()->openPresentation(getUrl(), &attemptFailed);
  if (!presentation)
  {
    if (attemptFailed)
    {
      KMessageBox::sorry(0,
          i18n("The presentation could not be opened by any of the presentation backends."),
          i18n("Presentation could not be opened")
          );
    }
    else
    {
      KMessageBox::information(0,
          i18n("No presentation backend is known to be able to open files of the MIME type \"%1\". Please install an appropriate presentation backend or associate this MIME type with an existing backend in the configuration.").arg(KMimeType::findByUrl(getUrl())->name()),
          i18n("Presentation could not be opened")
          );
    }
  }
}

