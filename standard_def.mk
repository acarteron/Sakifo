#### Common variables for Makefiles

## Directories
ROOT=$(shell pwd)
DIR_BIN=bin
DIR_SRC=src
DIR_OBJ=obj
DIR_LIB=lib
DIR_HDR=includes
DIR_DOC=doc
DIR_IN=libSakifo
DIR_LK=/home/adcarter/Documents/these/ServicesKabare/AlainPeters

## Compilation
GXX=g++
# Flags for linking
CFLAGS= -L$(DIR_LK)/$(DIR_LIB) -ldl -lPocoFoundation -lPocoNet -lPocoJSON -lPocoXML  -lPocoUtil -lPocoMongoDB -lAlainPeters -Wl,-rpath,$(DIR_LK)/$(DIR_LIB)
# Flags for objects
CFLAGS_OBJ=-I $(ROOT)/$(DIR_HDR) -I $(DIR_LK)/$(DIR_HDR) -O2 -Wall -Wextra -std=c++11 
# Flags for libraries objects
CFLAGS_DYNAMIC_LIBS_OBJ=-fPIC
# Flags for libraries linkins
CFLAGS_DYNAMIC_LIBS=-shared

