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

#ifndef _KwBibleModuleSword_h_
#define _KwBibleModuleSword_h_

/**
 * @file KwBibleModuleSword.h
 * @brief A SWORD bible module.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwBibleModule.h"

namespace sword
{
  class SWModule;
}

/// A SWORD bible module.
class KwBibleModuleSword : public KwBibleModule
{
  public:
    
    /*
     * Constructors + destructor
     */

    /// Default constructor.
    KwBibleModuleSword(sword::SWModule* module);

    /// Destructor.
    virtual ~KwBibleModuleSword();

    /*
     * Main interface
     */

    // Reimplemented
    virtual QString name();

    // Reimplemented
    virtual QString description();

    // Reimplemented
    virtual int numChapters(int book);

    // Reimplemented
    virtual int numVerses(int book, int chapter);

    // Reimplemented
    virtual QString renderText(const KwBibleModule::Key& key);

  protected:

    /*
     * Protected virtual interface
     */

    // Reimplemented
    virtual void obtainBooks();

  private:

    /*
     * Variables
     */
    
    /// SWORD module object.
    sword::SWModule* m_module;
};

#endif // _KwBibleModuleSword_h_

