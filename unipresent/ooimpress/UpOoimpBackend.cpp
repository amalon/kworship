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
 * @file UpOoimpBackend.cpp
 * @brief OpenOffice.org Impress presentation manager.
 * @author James Hogan <james@albanarts.com>
 */

#include "UpOoimpBackend.h"
#include "UpOoimpBridge.h"
#include "UpOoimpPresentation.h"

#include "compiler.h"

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

/*
 * Constructors + destructor
 */

/// Primary constructor.
UpOoimpBackend::UpOoimpBackend(QObject* parent)
: UpBackend(parent)
, m_bridge(0)
, m_presentations()
{
  activate();
}

/// Destructor.
UpOoimpBackend::~UpOoimpBackend()
{
  delete m_bridge;
}

/*
 * General meta information
 */

QString UpOoimpBackend::name() const
{
  return "OpenOffice.org Impress";
}

QString UpOoimpBackend::description() const
{
  return "Controls a running Impress";
}

QStringList UpOoimpBackend::mimeTypes() const
{
  /// @todo Find mime types from open office if possible
  return QStringList()
    << "application/vnd.oasis.opendocument.presentation"
    ;
}

/*
 * Activation
 */

bool UpOoimpBackend::activate()
{
  if (0 == m_bridge)
  {
    m_bridge = new UpOoimpBridge();
    if (likely(m_bridge->isValid()))
    {
      activated();

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
          m_presentations.push_back(new UpOoimpPresentation(presentationSupplier.get(), this));
        }
      }
    }
    else
    {
      m_bridge = 0;
      return false;
    }
  }
  return true;
}

void UpOoimpBackend::deactivate()
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

QList<UpPresentation*> UpOoimpBackend::presentations()
{
  return m_presentations;
}

UpPresentation* UpOoimpBackend::openPresentation(const QUrl& url)
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
  }
  else
  {
    return 0;
  }
}

