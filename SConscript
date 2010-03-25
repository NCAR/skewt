# -*- python -*-

sources = Split("""
Adiabats.cpp
IsoMR.cpp
IsoPleth.cpp
IsoTherms.cpp
IsoPress.cpp
PAdiabats.cpp
PresRect.cpp
Rect.cpp
SkewT.cpp
SkewTAdapter.cpp
SkewTMetFormulas.cpp
SkewTRect.cpp
SkewTtrace.cpp
WindBarb.cpp
WindBarbs.cpp
SkewTAdapterSVG.cpp
""")

headers = Split("""
Adiabats.h
IsoMR.h
IsoPleth.h
IsoPress.h
IsoTherms.h
PAdiabats.h
PresRect.h
Rect.h
SkewT.h
SkewTAdapter.h
SkewTAdapterSVG.h
SkewTMetFormulas.h
SkewTRect.h
SkewTdefs.h
SkewTdoxygen.h
SkewTtrace.h
WindBarb.h
WindBarbs.h
""")


if Dir('.').path.startswith('plotlib'):

    print("SkewT being built for plotlib library...")
    # If building plotlib, pass the sources on to the plotlib library.
    Import('library')
    library.addSources(sources)
    library.addHeaders(headers)

else:

    # Build a basic SkewT library. Note that this SConscript 
    # is not used by Aeros, which builds everything for plotlib 
    # in ../SConscript
    Import('env')
    lib = env.Library('#/lib/libskewt', sources)

