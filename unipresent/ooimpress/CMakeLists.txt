project(unipresentooimpress)

find_package(Qt4 REQUIRED)
include_directories(${QT_INCLUDES})

find_package(UNO REQUIRED)

UNO_ADD_TYPES(unipresentooimpress
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

message("include files:" ${UNO_INCLUDES})
include_directories(${UNO_INCLUDES})

set(unipresentooimpress_SRCS
    UpOoimpBackend.cpp
    UpOoimpBridge.cpp
    UpOoimpPresentation.cpp
)

QT4_AUTOMOC(${unipresentooimpress_SRCS})

set(unipresentooimpress_TYPE SHARED)
add_library(unipresentooimpress ${unipresentooimpress_TYPE}
            ${unipresentooimpress_SRCS}
            ${UNO_LIBS}
)

add_dependencies(unipresentooimpress ${UNO_TARGET})
