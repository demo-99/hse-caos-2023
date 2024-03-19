CC=gcc
CFLAGS=-Wall
PROF_OUT=gmon.out
TARGET=profile_example
GPERF_OUT=profile_example_gperftools.prof
CACHEGRIND_OUT=cachegrind.out

.PHONY: all clean gprof-run gperftools-run perf-run cachegrind-run

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET) $(PROF_OUT) $(GPERF_OUT) $(TARGET)_gprof $(TARGET)_gperftools $(CACHEGRIND_OUT)

gprof-run: $(TARGET).c
	$(CC) $(CFLAGS) -pg -o $(TARGET)_gprof $^
	./$(TARGET)_gprof
	gprof $(TARGET)_gprof $(PROF_OUT) > profile_analysis.txt

gperftools-run: $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET)_gperftools $^ -Wl,--no-as-needed,-lprofiler,--as-needed
	CPUPROFILE=$(GPERF_OUT) ./$(TARGET)_gperftools
	google-pprof --text $(TARGET)_gperftools $(GPERF_OUT) > gperftools_analysis.txt

perf-run: $(TARGET)
	perf stat ./$<
	perf record -g ./$<
	@echo "Run 'perf report' to view detailed performance analysis."

cachegrind-run: $(TARGET)
	valgrind --tool=cachegrind --cachegrind-out-file=$(CACHEGRIND_OUT) ./$<
	cg_annotate $(CACHEGRIND_OUT) > cachegrind_analysis.txt