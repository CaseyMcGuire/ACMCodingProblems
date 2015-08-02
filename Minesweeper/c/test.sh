#!/bin/bash

if [ ! -f $1 ] ; then
    echo "no source file"
    exit 0
fi

if [ ! -f $2 ] ; then
    echo "No input file"
    exit 0
fi

if [ ! -f $3 ] ; then
    echo "No answer file"
    exit 0
fi

gcc $1

if [ $? -ne 0 ] ; then
    echo "compilation error"
    exit 0
fi

#OUTPUT = $(./a.out < $2 | diff $3 -)

#OUTPUT = ""
#if [ -z OUTPUT ] ; then
#    echo "PASS"
#else
#    echo "FAIL"
#fi
