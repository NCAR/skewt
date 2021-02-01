toolname = 'skewt'

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

env = Environment(tools=['default', 'doxygen'])

lib = env.Library(toolname, sources)
env.Default(lib)

doxref = env.Apidocs(sources + headers,
                     DOXYFILE_DICT={'PROJECT_NAME': toolname})

tooldir = env.Dir('.')


def skewt(env):
    env.Append(LIBS=[lib])
    # Headers should be included qualified by the directory name, so make
    # sure the parent directory is on CPPPATH.
    env.AppendUnique(CPPPATH=[tooldir.Dir('..')])


Export(toolname)
