/**
 * @file KwAbstractMediaPreferences.cpp
 * @brief A media item's preferences.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwAbstractMediaPreferences.h"

/*
 * Constructors + destructors
 */

/// Default constructor.
KwAbstractMediaPreferences::KwAbstractMediaPreferences()
: m_manager(0)
{
}

/// Destructor.
KwAbstractMediaPreferences::~KwAbstractMediaPreferences()
{
}

/*
 * Main interface
 */

/// Set the manager.
void KwAbstractMediaPreferences::setManager(KwMediaManager* manager)
{
  m_manager = manager;
}

