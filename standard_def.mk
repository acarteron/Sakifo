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

DIR_AP=/opt/AlainPeters
DIR_ZZ=/opt/Zamzama
#DIR_AP=/home/adcarter/Documents/these/ServicesKabare/AlainPeters
#DIR_ZZ=/home/adcarter/Documents/these/ServicesKabare/zamzama
## Compilation
GXX=g++
# Flags for linking
CFLAGS= -L$(DIR_AP)/$(DIR_LIB) -L$(DIR_ZZ)/$(DIR_LIB) -ldl -lPocoFoundation -lPocoNet -lPocoJSON -lPocoXML  -lPocoUtil -lPocoMongoDB -lAlainPeters -lZamzama -Wl,-rpath,$(DIR_AP)/$(DIR_LIB) -Wl,-rpath,$(DIR_ZZ)/$(DIR_LIB)
# Flags for objects
CFLAGS_OBJ=-I $(ROOT)/$(DIR_HDR) -I $(DIR_AP)/$(DIR_HDR) -I $(DIR_ZZ)/$(DIR_HDR) -O2 -Wall -Wextra -std=c++14 
# Flags for libraries objects
CFLAGS_DYNAMIC_LIBS_OBJ=-fPIC
# Flags for libraries linkins
CFLAGS_DYNAMIC_LIBS=-shared

