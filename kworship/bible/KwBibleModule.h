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

#ifndef _KwBibleModule_h_
#define _KwBibleModule_h_

/**
 * @file KwBibleModule.h
 * @brief A bible module (analagous to a SWORD module).
 * @author James Hogan <james@albanarts.com>
 */

#include <QString>

namespace sword
{
  class SWModule;
}

/// A bible module (analagous to a SWORD module).
class KwBibleModule
{
  public:
    
    /*
     * Constructors + destructor
     */

    /// Default constructor.
    KwBibleModule(sword::SWModule* module);

    /// Destructor.
    virtual ~KwBibleModule();

    /*
     * Main interface
     */

    /// Get the name of the module.
    QString name() const;

    /// Get the description of the module.
    QString description() const;

    /// Get rendered text for a given passage.
    QString renderText(const QString& key) const;

  private:

    /*
     * Variables
     */
    
    /// SWORD module object.
    sword::SWModule* m_module;
};

#endif // _KwBibleModule_h_

