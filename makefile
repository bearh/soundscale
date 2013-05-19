#
# Makefile for Soundscale
#

SRCS =		soundscale.c
OUTPUT_BIN =	bin/soundscale

FRAMEWORKS = 	include/portaudio/libportaudio.a \
		-framework CoreAudio \
		-framework AudioUnit \
	        -framework carbon \
	        -framework AudioToolbox 

build:
	CC $(SRCS) -o $(OUTPUT_BIN) $(FRAMEWORKS)

run:
	./$(OUTPUT_BIN)
