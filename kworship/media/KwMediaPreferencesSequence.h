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

