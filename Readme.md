 SkewT provides a generic implementation of the aerological diagram 
 which utilizes a skewed temperature scale for the horizontal axis and 
 an inverted logrithmic pressure scale for the vertical axis. For a
 good reference on aerological diagrams, see:
 
 *J. V. Iribarne and W. L. Godson, <i>Atmospheric Thermodynamics</i>,
 D. Reidel, Boston (1973)*
 
SkewT formulates the diagram in a virtual coordinate space, and then
calls a class derived from SkewTAdapter, to render the diagram 
for a particular graphics environment. Example enviroments might be
Trolltech Qt, or a Microsoft Windows graphing component.

The only data required by SkewT are pressure, temperature, 
relative humidity, wind speed and wind direction.

The functionality of SkewT is somewhat dependent upon the SkewTAdapter,
which is correspondingly dependent on the graphics subsystem that it is
designed for. In some cases, all of the graph data must be provided at 
construction time, and a static graph will be created. In other cases, 
a "real-time" update mode is possible, where data points may be incrementally
added to the graph. 

The included SkewTAdapterSVG provides an example adapter which will render
the graph to SVG text. [skewtqt](https://github.com/ncareol/skewtqt.git) is an
adapter that will render the graph as a Qt widget.
