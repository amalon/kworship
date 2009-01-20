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
 * @file UpOoBackend.cpp
 * @brief OpenOffice.org presentation manager.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpOoBackend.h"
#include "UpOoBridge.h"
#include "UpOoPresentation.h"

#include "compiler.h"

#include <KRun>
#include <KShell>
#include <KLocale>
#include <KGenericFactory>

#include <QThread>

#include <osl/file.hxx> 
#include <osl/process.h> 
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/container/XEnumeration.hpp>
#include <com/sun/star/container/XEnumerationAccess.hpp>
#include <com/sun/star/frame/XComponentLoader.hpp>
#include <com/sun/star/frame/XDesktop.hpp>
#include <com/sun/star/lang/XMultiComponentFactory.hpp>
#include <com/sun/star/presentation/XPresentationSupplier.hpp>
#include <com/sun/star/uno/XComponentContext.hpp>

using namespace com::sun::star::beans;
using namespace com::sun::star::container;
using namespace com::sun::star::frame;
using namespace com::sun::star::lang;
using namespace com::sun::star::presentation;
using namespace com::sun::star::uno;
using namespace rtl;

K_EXPORT_COMPONENT_FACTORY( unipresent_openoffice, KGenericFactory<UpOoBackend>("unipresent_openoffice") )

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpOoBackend::UpOoBackend(QObject* parent)
: UpBackend(parent)
, m_bridge(0)
, m_presentations()
{
  updatePresentations();
}

/// Destructor.
UpOoBackend::~UpOoBackend()
{
  delete m_bridge;
}

/*
 * General meta information
 */

QString UpOoBackend::id() const
{
  return "OpenOffice.org";
}

QString UpOoBackend::name() const
{
  return i18n("OpenOffice.org");
}

QString UpOoBackend::description() const
{
  return i18n("Controls a running OpenOffice.org presentation");
}

QStringList UpOoBackend::mimeTypes() const
{
  /// @todo Find mime types from open office if possible
  return QStringList()
    << "application/vnd.oasis.opendocument.presentation"
    ;
}

QIcon UpOoBackend::icon() const
{
  return QIcon();
}

/*
 * Activation
 */

bool UpOoBackend::isActive()
{
  /// @todo Gently try again
  return (0 != m_bridge);
}

bool UpOoBackend::activate()
{
  int tries = 0;
  while (0 == m_bridge)
  {
    m_bridge = new UpOoBridge();
    if (m_bridge->isValid())
    {
      activated();

      updatePresentations();
      return true;
    }
    else
    {
      delete m_bridge;
      m_bridge = 0;

      ++tries;
      if (tries == 1)
      {
        // First try : start OpenOffice.org
        bool starting = KRun::runCommand("openoffice.org " + KShell::quoteArg("-accept=socket,host=localhost,port=2083;urp;StarOffice.ServiceManager"), 0);
        if (!starting)
        {
          return false;
        }
      }
      else if (tries > 10)
      {
        // Second try + : give up
        return false;
      }
      /// @todo PORT
      usleep(500000);
    }
  }

  return (0 != m_bridge);
}

void UpOoBackend::deactivate()
{
  if (0 != m_bridge)
  {
    delete m_bridge;
    m_bridge = 0;
    deactivated();
  }
}

/*
 * Presentation management
 */

QList<UpPresentation*> UpOoBackend::presentations()
{
  return m_presentations;
}

bool UpOoBackend::openPresentation(const QUrl& url)
{
  OUString urlString = OUString::createFromAscii(url.toString().toAscii());

  if (activate())
  {
    Reference<XPropertySet> propertySet(m_bridge->serviceManager(), UNO_QUERY);
    Reference<XComponentContext> componentContext;
    propertySet->getPropertyValue(OUString::createFromAscii("DefaultContext")) >>= componentContext;
    Reference<XMultiComponentFactory> componentFactoryServer = componentContext->getServiceManager();

    Reference<XComponentLoader> componentLoader(componentFactoryServer->createInstanceWithContext(OUString::createFromAscii("com.sun.star.frame.Desktop"), componentContext), UNO_QUERY);

    Reference<XComponent> newComponent = componentLoader->loadComponentFromURL(urlString, OUString::createFromAscii("_blank"), 0, Sequence< ::com::sun::star::beans::PropertyValue>() );

    return true;
  }
  else
  {
    return false;
  }
}

/*
 * Other interfaces
 */

/// Update the list of presentations
void UpOoBackend::updatePresentations()
{
  if (0 == m_bridge)
  {
    m_bridge = new UpOoBridge();
    if (!m_bridge->isValid())
    {
      delete m_bridge;
      m_bridge = 0;
    }
  }

  if (0 != m_bridge && m_presentations.isEmpty())
  {
    // Find open documents.
    Reference<XPropertySet> propertySet(m_bridge->serviceManager(), UNO_QUERY);
    Reference<XComponentContext> componentContext;
    propertySet->getPropertyValue(OUString::createFromAscii("DefaultContext")) >>= componentContext;
    Reference<XMultiComponentFactory> componentFactoryServer = componentContext->getServiceManager();

    Reference<XDesktop> desktop(componentFactoryServer->createInstanceWithContext(OUString::createFromAscii("com.sun.star.frame.Desktop"), componentContext), UNO_QUERY);
    Reference<XEnumeration> documents = desktop->getComponents()->createEnumeration();

    while (documents->hasMoreElements())
    {
      Reference<XPresentationSupplier> presentationSupplier;
      documents->nextElement() >>= presentationSupplier;
      if (0 != presentationSupplier.get())
      {
        m_presentations.push_back(new UpOoPresentation(presentationSupplier.get(), this));
      }
    }
  }
}

