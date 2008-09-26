project(unipresentopenoffice)

find_package(Qt4 REQUIRED)
include_directories(${QT_INCLUDES})

find_package(UNO REQUIRED)

UNO_ADD_TYPES(unipresentopenoffice
    com.sun.star.beans.XPropertySet
    com.sun.star.bridge.XUnoUrlResolver
    com.sun.star.container.XEnumeration
    com.sun.star.container.XEnumerationAccess
    com.sun.star.container.XHierarchicalNameAccess
    com.sun.star.frame.XComponentLoader
    com.sun.star.frame.XDesktop
    com.sun.star.lang.XComponent
    com.sun.star.lang.XMultiComponentFactory
    com.sun.star.lang.XMultiServiceFactory
    com.sun.star.presentation.XPresentationSupplier
    com.sun.star.registry.XSimpleRegistry
)

include_directories(${UNO_INCLUDES})

set(unipresentopenoffice_SRCS
    UpOoBackend.cpp
    UpOoBridge.cpp
    UpOoPresentation.cpp
)

QT4_AUTOMOC(${unipresentopenoffice_SRCS})

set(unipresentopenoffice_TYPE SHARED)
add_library(unipresentopenoffice ${unipresentopenoffice_TYPE}
            ${unipresentopenoffice_SRCS}
            ${UNO_LIBS}
)

add_dependencies(unipresentopenoffice ${UNO_TARGET})
