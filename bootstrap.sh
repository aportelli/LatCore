#!/usr/bin/env bash

mkdir -p .buildutils/m4
./update_eigen.sh eigen-3.2.4.tar.bz2
autoreconf -fvi
