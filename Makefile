.PHONY: all clean

all:
	$(MAKE) -C libmodel
	$(MAKE) -C myprogram

check: all
	$(MAKE) -C libmodel check
	$(MAKE) -C myprogram check

clean:
	$(MAKE) -C libmodel clean
	$(MAKE) -C myprogram clean
