gvdpgen is a modification of the dpgen program that will create output a script suitable for use with graphviz.
Usage:
    mkdir build
    cd build
    cmake ../
    make
    gvdpgen <inputfile> > <graphfile>
    dot <graphfile> -Tpdf > <outputfile>.pdf