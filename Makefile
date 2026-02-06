CC = gcc
CFLAGS = -I.
DEPS = zones.h

UTZ_DATA_DIR = vendor/tzdata
UTZ_REGIONS = africa,asia,australasia,backward,europe,northamerica,southamerica
UTZ_WHITELIST = whitelist.txt
UTZ_INCLUDES = majormetros
UTZ_TZDATA_STAMP = $(UTZ_DATA_DIR)/.tzdata.stamp

export UTZ_DATA_DIR := $(UTZ_DATA_DIR)
export UTZ_REGIONS := $(UTZ_REGIONS)
export UTZ_INCLUDES := $(UTZ_INCLUDES)

ifeq ($(OS),Windows_NT)
	PYTHON = python
else
	PYTHON =
endif

.PHONY: all clean examples test fitzones update-tzdata

all: zones.h zones.c

$(UTZ_TZDATA_STAMP): utils/compile_tzdb.py
	@echo "==> Ensuring IANA tzdata is present"
	$(PYTHON) ./utils/compile_tzdb.py $(UTZ_DATA_DIR)
	touch $@

update-tzdata:
	rm -f $(UTZ_TZDATA_STAMP)
	$(MAKE) $(UTZ_TZDATA_STAMP)

zones.h: $(UTZ_TZDATA_STAMP) $(UTZ_INCLUDES) $(UTZ_WHITELIST) utils/generate_zones.py utils/utz.py
	$(PYTHON) ./utils/generate_zones.py

zones.c: zones.h

fitzones: zones.c
	$(PYTHON) ./utils/post_process_sensorwatch.py

whitelist.txt: vendor/android/timezones.xml majormetros utils/compile_whitelist.py
	$(PYTHON) ./utils/compile_whitelist.py

majormetros:
	$(PYTHON) ./utils/compile_tzlinks.py

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

examples: example/example

example/example: utz.o zones.o examples/utility.o examples/example.o
	$(CC) -o example utz.o zones.o examples/utility.o examples/example.o -I.

examples/utility.o: examples/utility.c
	$(CC) -c -o examples/utility.o examples/utility.c -I.

test: test/test_timezone
	./test/test_timezone

test/test_timezone: utz.o zones.o tests/test_timezone.o
	$(CC) -o test/test_timezone utz.o zones.o tests/test_timezone.o -I.

clean:
	rm -f zones.h zones.c whitelist.txt utz.o zones.o \
	      examples/example.o example \
	      test/test_timezone tests/test_timezone.o
