#***************************************************************************
#*   Autoversion makefile              v.20250427.140120 (target.version)  *
#*   Copyright (C) 2014-2026 by Ruben Carlo Benante <rcb@beco.cc>          *
#*                                                                         *
#*   This makefile sets BUILD and allows to set MAJOR.MINOR version,       *
#*   DEBUG and OBJ to compile a range of different targets                 *
#***************************************************************************
#*   This program is free software; you can redistribute it and/or modify  *
#*   it under the terms of the GNU General Public License as published by  *
#*   the Free Software Foundation; version 2 of the License.               *
#*                                                                         *
#*   This program is distributed in the hope that it will be useful,       *
#*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
#*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
#*   GNU General Public License for more details.                          *
#*                                                                         *
#*   You should have received a copy of the GNU General Public License     *
#*   along with this program; if not, write to the                         *
#*   Free Software Foundation, Inc.,                                       *
#*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
#***************************************************************************
#*   To contact the author, please write to:                               *
#*   Ruben Carlo Benante                                                   *
#*   Email: rcb@beco.cc                                                    *
#*   Webpage: http://drbeco.github.io/                                     *
#***************************************************************************
#
# Usage:
#        $ make
#        $ make vistar.x
#        $ make clean
#        $ make wipe
#

# disable builtin rules with MAKEFLAGS and .SUFFIXES
MAKEFLAGS += --no-builtin-rules
.SUFFIXES:
.PHONY: all clean wipe nomatch
.PRECIOUS: %.o %.c %.h %.x %.version %.build
.SECONDARY:
SHELL=/bin/bash -o pipefail

# assure functions that return values are not ignored
FORTIFY ?= 2
# turn on/off debug mode
DEBUG ?= 1
# version major number
MAJOR ?= 0
# version minor number
MINOR ?= 1
# object files to compile with the source
OBJ ?= libvistar.o
# other source files to be compiled together
SRC ?= 
# colorize output
CCCOLOR ?= always
# create a define
D ?= D_

# build date
BUILD = $(shell date +"%Y%m%d.%H%M%S")
# build date inside binary code
DEFSYM = $(subst .,_,$(BUILD))
# automatic version number
VERSION = "\"$(MAJOR).$(MINOR).$(BUILD)\""

# C Compiler
CC = gcc

# C Compiler FLAGS (CFLAGS)
CFLAGS = -Wall -Wextra -Wno-unused-result -fdiagnostics-color=$(CCCOLOR) -std=gnu17

ifeq "$(DEBUG)" "0"
CFLAGS += -Ofast
else ifeq "$(DEBUG)" "1"
CFLAGS += -g -Og
else
CFLAGS += -g -Og -pg -fprofile-arcs -Wpedantic
endif

# c pre-processor flags
CPPFLAGS = -DBUILD="\"$(BUILD)\"" -DDEBUG=$(DEBUG) -D$(D) -D_FORTIFY_SOURCE=$(FORTIFY)
ifeq "$(DEBUG)" "2"
CPPFLAGS += -D_XOPEN_SOURCE=700
endif

# libraries to link. no-as-needed: any order is fine
LDLIBS = -Wl,-no-as-needed -Wl,--defsym,BUILD_$(DEFSYM)=0 -lm -lpthread -lncurses -lcurl -lcrypto

# Alvo padrão para compilar o editor automaticamente
all: vistar.x

# Regra para compilar objetos separados (.c -> .o)
%.o : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Programa principal (vistar.x) com o motor de auto-versionamento do Dr. Beco
vistar.x : vistar.c $(OBJ) $(SRC)
	@VERSION_FILE=vistar.version; \
	BUILD_FILE=vistar.build; \
	if [ -f "$$VERSION_FILE" ] && [ "$$(grep -oP '^\S+' "$$VERSION_FILE")" = "vistar" ]; then \
		CURRENT_FULL_VERSION=$$(grep -oP '"\K[^"]+' "$$VERSION_FILE"); \
		CURRENT_VERSION=$$(echo "$$CURRENT_FULL_VERSION" | grep -oP '^\d+.\d+'); \
	else \
		CURRENT_VERSION="0.1"; \
		CURRENT_FULL_VERSION="0.1.$(BUILD)"; \
	fi; \
	PROVIDED_VERSION=$(MAJOR).$(MINOR); \
	IS_GREATER=$$(printf "%s\n" "$$PROVIDED_VERSION > $$CURRENT_VERSION" | bc -l); \
	if [ "$$IS_GREATER" -eq 1 ]; then \
		USE_VERSION="$(MAJOR).$(MINOR).$(BUILD)"; \
		echo "Upgrading vistar from $$CURRENT_FULL_VERSION to $$USE_VERSION"; \
	else \
		USE_VERSION="$$(echo "$$CURRENT_VERSION" | cut -d. -f1).$$(echo "$$CURRENT_VERSION" | cut -d. -f2).$(BUILD)"; \
		echo "Building vistar version $$USE_VERSION"; \
	fi; \
	echo $(CC) $(CFLAGS) $(CPPFLAGS) -DVERSION=\"$$USE_VERSION\" vistar.c $(OBJ) $(SRC) $(LDLIBS) -o $@ ; \
	$(CC) $(CFLAGS) $(CPPFLAGS) -DVERSION=\"$$USE_VERSION\" vistar.c $(OBJ) $(SRC) $(LDLIBS) -o $@ 2>&1 | tee errors.err; \
	if [ "$(CCCOLOR)" = "always" ]; then \
		sed -i -r "s/\x1B\[(([0-9]+)(;[0-9]+)*)?[m,K,H,f,J]//g" errors.err; \
	fi; \
	if [ ! -s errors.err ]; then \
		echo "vistar version \"$$USE_VERSION\"" > $$VERSION_FILE; \
		cp $$VERSION_FILE $$BUILD_FILE; \
	else \
		echo "vistar build \"$$USE_VERSION\"" > $$BUILD_FILE; \
	fi

nomatch :
	@echo 'makefile error: no rules for the given goal(s)' $(warning nomatch)

# Apaga todos os executáveis, relatórios e arquivos de metadados de versão
wipe :
	rm -f *.x *.so *.o errors.err tags a.out *.version *.build

# Apaga apenas os arquivos de compilação temporários (.o)
clean :
	rm -f *.o errors.err
	rm -f *.version *.build

# Gera arquivo de índice <tags> para navegação avançada de funções no Vim
tags :
	ctags -R
	ctags -R -x | less -F

#* ------------------------------------------------------------------- *
#* makefile config for Vim modeline                                    *
#* vi: set ai noet ts=4 sw=4 tw=0 wm=0 fo=croqlt list :                *
#* Template by Dr. Beco <rcb at beco dot cc> Version 20220521.001405   *
