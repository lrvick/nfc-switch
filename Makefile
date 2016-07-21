.PHONY: setup clean setup build upload


help:
	@echo "setup - setup build deps"
	@echo "clean - remove all build, test, coverage and Python artifacts"
	@echo "lint - check style of all source files"
	@echo "build - compile source files to binaries"
	@echo "upload - upload compiled code to device"

setup:
	pip2 install --user --upgrade platformio
	platformio platforms install atmelavr
	platformio lib install 29 # Adafruit-PN532

clean:
	rm src/authorized_ids.h
	platformio run --target clean

build: setup
ifneq ("$(wildcard authorized_ids.h)","")
	cp authorized_ids.h src/authorized_ids.h
	platformio run
else
	$(error Please create authorized_ids.h file from sample)
endif	
	

upload: build
	platformio run --target upload

monitor:
	platformio serialports monitor
