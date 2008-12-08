TEMPLATE = vclib

HEADERS += SkewTdoxygen.h

HEADERS += Adiabats.h
HEADERS += IsoMR.h
HEADERS += IsoPleth.h
HEADERS += IsoPress.h
HEADERS += Isotherms.h
HEADERS += PAdiabats.h
HEADERS += PresRect.h
HEADERS += Rect.h
HEADERS += SkewT.h
HEADERS += SkewTAdapter.h
HEADERS += SkewTAdapterSVG.h
HEADERS += SkewTdefs.h
HEADERS += SkewTMetFormulas.h
HEADERS += SkewTRect.h
HEADERS += SkewTtrace.h
HEADERS += WindBarb.h
HEADERS += WindBarbs.h

SOURCES += Adiabats.cpp
SOURCES += IsoMR.cpp
SOURCES += IsoPleth.cpp
SOURCES += IsoPress.cpp
SOURCES += Isotherms.cpp
SOURCES += PAdiabats.cpp
SOURCES += PresRect.cpp
SOURCES += Rect.cpp
SOURCES += SkewT.cpp
SOURCES += SkewTAdapter.cpp
SOURCES += SkewTAdapterSVG.cpp
SOURCES += SkewTMetFormulas.cpp
SOURCES += SkewTRect.cpp
SOURCES += SkewTtrace.cpp
SOURCES += WindBarb.cpp
SOURCES += WindBarbs.cpp

DEFINES +=

CONFIG += build_all
CONFIG += warn_on 
CONFIG += staticlib
config += exceptions

INCLUDEPATH += ../

