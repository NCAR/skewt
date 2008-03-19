# -*- python -*-

# Build a basic SkewT library. Note that this SConscript 
# is not used by Aeros, which builds everything for plotlib 
# in ../SConscript
 
Import('env')

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

lib = env.Library('#/lib/libskewt', sources)
