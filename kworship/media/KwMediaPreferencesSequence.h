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

#ifndef _KwMediaPreferencesSequence_h_
#define _KwMediaPreferencesSequence_h_

/**
 * @file KwMediaPreferencesSequence.h
 * @brief A media item's sequence preferences.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwAbstractMediaPreferences.h"

#include <QtGlobal>

/// A media item's sequence preferences.
/**
 * Basically this is time based preferences such as the range of the file to play.
 */
class KwMediaPreferencesSequence : public KwAbstractMediaPreferences
{
  public:

    /*
     * Types
     */

    /// The signed clock type.
    typedef qint64 Clock;

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwMediaPreferencesSequence();

    /// Destructor.
    virtual ~KwMediaPreferencesSequence();

    /*
     * Accessors
     */

    /// Has the sequence got an end?
    bool hasEnd() const;

    /// Get the start time in msecs.
    Clock getStartMsec() const;

    /// Get the end time in msecs.
    Clock getEndMsec() const;

    /// Get the length in msecs.
    Clock getLengthMsec() const;

    /*
     * Mutators
     */

    /// Set the start time in msecs.
    void setStartMsec(Clock startMsec, bool moveEnd);

    /// Set the end time in msecs.
    void setEndMsec(Clock endMsec);

    /// Set the length in msecs.
    void setLengthMsec(Clock lengthMsec);

  private:

    /*
     * Variables
     */

    /// Start time in msecs.
    Clock m_startMsec;

    /// End in msecs.
    Clock m_endMsec;

};

#endif // _KwMediaPreferencesSequence_h_

