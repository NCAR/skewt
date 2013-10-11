toolname = 'skewt'

thisDir = Dir('.').abspath
upDir   = Dir('./../').abspath

# Define tool. This must match the value of toolname.
def skewt(env):
    env.Append(LIBS = [toolname])
    env.AppendUnique(CPPPATH = [upDir])
    env.AppendUnique(CPPPATH = [thisDir])
    env.AppendUnique(LIBPATH = [thisDir])
    env.Require(['prefixoptions'])
    
Export(toolname)

# Build library
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

env = Environment(tools = ['default', 'doxygen', toolname])

lib = env.Library(toolname, sources)
env.Default(lib)

# Create doxygen
doxref = env.Apidocs(sources + headers, DOXYFILE_DICT={'PROJECT_NAME':toolname, 'PROJECT_NUMBER':'1.0'})
