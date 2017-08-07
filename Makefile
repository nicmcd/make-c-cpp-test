.PHONY: all clean

all:
	$(MAKE) -C libmodel
	$(MAKE) -C myprogram

check: all
	$(MAKE) -C libmodel check
	$(MAKE) -C myprogram check

checkm: all
	$(MAKE) -C libmodel checkm
	$(MAKE) -C myprogram checkm

count:
	$(MAKE) -C libmodel count
	$(MAKE) -C myprogram count

clean:
	$(MAKE) -C libmodel clean
	$(MAKE) -C myprogram clean
