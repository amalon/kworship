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

////////////
// BSD... //
#include <stdio.h>
#include <wchar.h>

#include <cppuhelper/bootstrap.hxx>

#include <osl/file.hxx>
#include <osl/process.h>

#include <com/sun/star/bridge/XUnoUrlResolver.hpp>
#include <com/sun/star/frame/XComponentLoader.hpp>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/registry/XSimpleRegistry.hpp>
#include <com/sun/star/lang/XMultiComponentFactory.hpp>

#include <string.h>

using namespace rtl;
using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::beans;
using namespace com::sun::star::bridge;
using namespace com::sun::star::frame;
using namespace com::sun::star::registry;

// BSD... //
////////////

/*
 * Constructors + destructor
 */

#include <QtDebug>
#include <iostream>
/// Primary constructor.
UpOoimpBackend::UpOoimpBackend(QObject* parent)
: UpBackend(parent)
{
  qDebug() << __PRETTY_FUNCTION__;
}

/// Destructor.
UpOoimpBackend::~UpOoimpBackend()
{
  qDebug() << __PRETTY_FUNCTION__;
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
 * Presentation management
 */

QList<UpPresentation*> UpOoimpBackend::presentations()
{
  return QList<UpPresentation*>();
}

UpPresentation* UpOoimpBackend::openPresentation(const QUrl& url)
{
  QByteArray path = url.toLocalFile().toAscii();
  qDebug() << __PRETTY_FUNCTION__ << path;

  ////////////
  // BSD... //
  OUString sConnectionString(RTL_CONSTASCII_USTRINGPARAM("uno:socket,host=localhost,port=2083;urp;StarOffice.ServiceManager"));

  // Creates a simple registry service instance.
  Reference< XSimpleRegistry > xSimpleRegistry(
      ::cppu::createSimpleRegistry() );

  // Connects the registry to a persistent data source represented by an URL.
  xSimpleRegistry->open( OUString( RTL_CONSTASCII_USTRINGPARAM(
          "/home/james/src/kworship/master/unipresent/ooimpress/CMakeFiles/unipresentooimpress.rdb") ), sal_True, sal_False );

  /* Bootstraps an initial component context with service manager upon a given
     registry. This includes insertion of initial services:
     - (registry) service manager, shared lib loader,
     - simple registry, nested registry,
     - implementation registration
     - registry typedescription provider, typedescription manager (also
     installs it into cppu core)
     */
  Reference< XComponentContext > xComponentContext(
      ::cppu::bootstrap_InitialComponentContext( xSimpleRegistry ) );

  /* Gets the service manager instance to be used (or null). This method has
     been added for convenience, because the service manager is a often used
     object.
     */
  Reference< XMultiComponentFactory > xMultiComponentFactoryClient(
      xComponentContext->getServiceManager() );

  /* Creates an instance of a component which supports the services specified
     by the factory.
     */
  Reference< XInterface > xInterface =
    xMultiComponentFactoryClient->createInstanceWithContext( 
        OUString::createFromAscii( "com.sun.star.bridge.UnoUrlResolver" ),
        xComponentContext );

  Reference< XUnoUrlResolver > resolver( xInterface, UNO_QUERY );

  // Resolves the component context from the office, on the uno URL given by parameter.
  try
  {    
    xInterface = Reference< XInterface >( resolver->resolve(sConnectionString) );
  }
  catch ( Exception& e )
  {
    printf("Error: cannot establish a connection using '%s':\n       %s\n",
        OUStringToOString(sConnectionString, RTL_TEXTENCODING_ASCII_US).getStr(),
        OUStringToOString(e.Message, RTL_TEXTENCODING_ASCII_US).getStr());
    return 0;
  }

  // gets the server component context as property of the office component factory
  Reference< XPropertySet > xPropSet( xInterface, UNO_QUERY );
  xPropSet->getPropertyValue( OUString::createFromAscii("DefaultContext") ) >>= xComponentContext;

  // gets the service manager from the office
  Reference< XMultiComponentFactory > xMultiComponentFactoryServer(
      xComponentContext->getServiceManager() );

  /* Creates an instance of a component which supports the services specified
     by the factory. Important: using the office component context.
     */
  Reference < XComponentLoader > xComponentLoader(
      xMultiComponentFactoryServer->createInstanceWithContext( 
        OUString( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.frame.Desktop" ) ),
        xComponentContext ), UNO_QUERY );

  /* Loads a component specified by an URL into the specified new or existing
     frame.
     */
  OUString sAbsoluteDocUrl, sWorkingDir, sDocPathUrl;
  osl_getProcessWorkingDir(&sWorkingDir.pData);
  osl::FileBase::getFileURLFromSystemPath( OUString::createFromAscii(path), sDocPathUrl);
  osl::FileBase::getAbsoluteFileURL( sWorkingDir, sDocPathUrl, sAbsoluteDocUrl);

  Reference< XComponent > xComponent = xComponentLoader->loadComponentFromURL(
      sAbsoluteDocUrl, OUString( RTL_CONSTASCII_USTRINGPARAM("_blank") ), 0,
      Sequence < ::com::sun::star::beans::PropertyValue >() );

  // dispose the local service manager
  Reference< XComponent >::query( xMultiComponentFactoryClient )->dispose();

  // BSD... //
  ////////////

  return 0;
}

