#ifndef _KwAbstractMediaPreferences_h_
#define _KwAbstractMediaPreferences_h_

/**
 * @file KwAbstractMediaPreferences.h
 * @brief A media item's preferences.
 * @author James Hogan <james@albanarts.com>
 */

#include <QObject>

class KwMediaManager;

/// A media item's preferences.
/**
 * To allow live updating of outputs.
 */
class KwAbstractMediaPreferences : public QObject
{
  public:

    /*
     * Constructors + destructors
     */

    /// Default constructor.
    KwAbstractMediaPreferences();

    /// Destructor.
    virtual ~KwAbstractMediaPreferences();

    /*
     * Main interface
     */

    /// Set the manager.
    void setManager(KwMediaManager* manager);

  private:

    /*
     * Variables
     */

    /// Manager to control.
    KwMediaManager* m_manager;

};

#endif // _KwAbstractMediaPreferences_h_

