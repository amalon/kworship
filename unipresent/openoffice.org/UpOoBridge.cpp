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
 * @file UpOoBridge.cpp
 * @brief Bridge to OpenOffice.org.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpOoBridge.h"
#include "compiler.h"

#include <KStandardDirs>
#include <KLocale>
#include <KDebug>

#include <QByteArray>

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
  QByteArray connectionBaCore = "socket,host=localhost,port=2083;urp;StarOffice.ServiceManager";
  QByteArray connectionBa = "uno:" + connectionBaCore;
#define TYPESDB "unipresent/openoffice.org/types.rdb"
#define BACKEND_NAME i18n("OpenOffice.org backend:")
  QString rdbFileBa = KStandardDirs::locate("data", TYPESDB);
  if (rdbFileBa.isNull())
  {
    kdError() << BACKEND_NAME << i18n("couldn't find data %1").arg(TYPESDB);
    return;
  }

  OUString connectionString(OUString::createFromAscii(connectionBa));
  OUString rdbFile(OUString::createFromAscii(rdbFileBa.toAscii()));
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
    if (!resolver.is())
    {
      kdError() << BACKEND_NAME << i18n("could not create instance of XUnoUrlResolver");
      return;
    }
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
        kdDebug() << BACKEND_NAME << QString::fromUtf16((const sal_Unicode*)message, message.getLength()) << i18n("(start OpenOffice.org with %1)").arg(QString()+"soffice \"-accept=" + connectionBaCore + "\"");
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

