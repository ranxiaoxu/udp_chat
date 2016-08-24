ROOT_PATH=$(shell pwd)
BIN=$(ROOT_PATH)/server $(ROOT_PATH)/client
.PHONY:all
all:
	for name in `echo $(BIN)`;\
	do\
		cd $$name;\
		make;\
		cd -;\
	done

.PHONY:clean
clean:
	rm -rf output
	for name in `echo $(BIN)`;\
    do\
		cd $$name;\
	    make clean;\
	    cd -;\
    done
.PHONY:output
output:
	mkdir output
	cp -f $(ROOT_PATH)/server/udp_server output
	cp -f $(ROOT_PATH)/client/udp_client output
	cp -f $(ROOT_PATH)/pluging/server_ctl.sh output
	cp -f $(ROOT_PATH)/conf/server.conf output
