test_libpcap:test_libpcap.c
	gcc -Wall -o $@ $^ -lpcap

clean:
	rm -f test_libpcap
