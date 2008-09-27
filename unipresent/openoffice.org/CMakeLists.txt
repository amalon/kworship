project(unipresentopenoffice)

find_package(Qt4 REQUIRED)
include_directories(${QT_INCLUDES})

find_package(UNO REQUIRED)

UNO_ADD_TYPES(unipresentopenoffice
    com.sun.star.beans.XPropertySet
    com.sun.star.bridge.XUnoUrlResolver
    com.sun.star.container.XEnumeration
    com.sun.star.container.XEnumerationAccess
    com.sun.star.container.XIndexAccess
    com.sun.star.container.XHierarchicalNameAccess
    com.sun.star.drawing.XDrawPagesSupplier
    com.sun.star.drawing.XDrawPages
    com.sun.star.drawing.XDrawPage
    com.sun.star.drawing.XShapes
    com.sun.star.text.XText
    com.sun.star.frame.XComponentLoader
    com.sun.star.frame.XDesktop
    com.sun.star.lang.XComponent
    com.sun.star.lang.XMultiComponentFactory
    com.sun.star.lang.XMultiServiceFactory
    com.sun.star.presentation.XPresentationSupplier
    com.sun.star.presentation.XPresentation
    com.sun.star.registry.XSimpleRegistry
)

include_directories(${UNO_INCLUDES})

set(unipresentopenoffice_SRCS
    UpOoBackend.cpp
    UpOoBridge.cpp
    UpOoPresentation.cpp
    UpOoSlide.cpp
)

QT4_AUTOMOC(${unipresentopenoffice_SRCS})

add_library(unipresentopenoffice STATIC ${unipresentopenoffice_SRCS})

target_link_libraries(unipresentopenoffice
                      ${UNO_LIBS}
)

add_dependencies(unipresentopenoffice ${UNO_TARGET})
