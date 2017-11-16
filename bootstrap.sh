#!/usr/bin/env bash

mkdir -p .buildutils/m4
./update_eigen.sh eigen-3.3.4.tar.bz2
autoreconf -fvi
