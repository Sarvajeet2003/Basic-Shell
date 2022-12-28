obj-m += print_process_info.o

all:
  	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
  	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean




obj-m += my_syscall.o

all:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
