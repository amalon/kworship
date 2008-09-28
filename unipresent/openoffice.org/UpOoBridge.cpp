/***************************************************************************
 *   This file is part of KWorship.                                        *
 *   Copyright 2008 James Hogan <james@albanarts.com>                      *
 *                                                                         *
 *   KWorship is free software: you can redistribute it and/or modify      *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   KWorship is distributed in the hope that it will be useful,           *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with KWorship.  If not, see <http://www.gnu.org/licenses/>.     *
 ***************************************************************************/

/**
 * @file UpOoBridge.cpp
 * @brief Bridge to OpenOffice.org.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpOoBridge.h"
#include "compiler.h"

#include <QByteArray>
#include <QtDebug>

#include <cppuhelper/bootstrap.hxx>
#include <osl/file.hxx>
#include <osl/process.h>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/bridge/XUnoUrlResolver.hpp>
#include <com/sun/star/frame/XComponentLoader.hpp>
#include <com/sun/star/lang/XMultiComponentFactory.hpp>
#include <com/sun/star/registry/XSimpleRegistry.hpp>

using namespace com::sun::star::beans;
using namespace com::sun::star::bridge;
using namespace com::sun::star::frame;
using namespace com::sun::star::lang;
using namespace com::sun::star::registry;
using namespace com::sun::star::uno;
using namespace rtl;

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpOoBridge::UpOoBridge()
: m_valid(false)
{
  QByteArray connectionBa = "uno:socket,host=localhost,port=2083;urp;StarOffice.ServiceManager";
  QByteArray rdbFileBa = "/home/james/src/kworship/master/unipresent/openoffice.org/CMakeFiles/unipresentopenoffice.rdb";

  OUString connectionString(OUString::createFromAscii(connectionBa));
  OUString rdbFile(OUString::createFromAscii(rdbFileBa));
  bool tryAgain = false;
  do
  {
    // Connect
    Reference<XSimpleRegistry> registry = ::cppu::createSimpleRegistry();
    registry->open(rdbFile, sal_True, sal_False);
    Reference<XComponentContext> componentContext = ::cppu::bootstrap_InitialComponentContext(registry);
    Reference<XMultiComponentFactory> componentFactory = componentContext->getServiceManager();
    Reference<XUnoUrlResolver> resolver(componentFactory->createInstanceWithContext(
                                        OUString::createFromAscii("com.sun.star.bridge.UnoUrlResolver"),
                                        componentContext), UNO_QUERY);
    try
    {
      m_serviceManager = resolver->resolve(connectionString);
      tryAgain = false;
    }
    catch (Exception& exception)
    {
      // If we've already tried it again, just give up.
      if (unlikely(tryAgain))
      {
        // not valid
        OUString message = exception.Message;
        qDebug() << __PRETTY_FUNCTION__ << ":" << QString::fromUtf16((const sal_Unicode*)message, message.getLength());
        return;
      }
      else
      {
        // Start openoffice
        tryAgain = true;
        continue;
      }
    }
  } while (tryAgain);
  
  m_valid = true;
}

/// Destructor.
UpOoBridge::~UpOoBridge()
{
}

/*
 * Main interface
 */

/// Find whether the bridge is valid.
bool UpOoBridge::isValid() const
{
  return m_valid;
}

/// Get the service manager.
XInterface* UpOoBridge::serviceManager()
{
  return m_serviceManager.get();
}

