make-clean:
    make clean && make

daisy:
    cd lib/DaisySP && make
    cd lib/libDaisy && make