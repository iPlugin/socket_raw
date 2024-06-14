# ============= Makefile ============= #

CC = g++
DIROBJS = obj
DIRLOGS = logs
CREATE_DIROBJS = mkdir -p $(DIROBJS)
CREATE_DIRLOGS = mkdir -p $(DIRLOGS)


all: folders runClient

folders:
	$(CREATE_DIROBJS)
	$(CREATE_DIRLOGS)

runClient: client/runClient.cpp logger utils package
	$(CC) client/runClient.cpp tools/client.cpp \
		$(DIROBJS)/logger.o $(DIROBJS)/utils.o \
			$(DIROBJS)/package.o \
			-o runClient -Wall -Werror -pedantic

runServer: server/runServer.cpp logger utils package
	$(CC) server/runServer.cpp tools/server.cpp \
		$(DIROBJS)/logger.o $(DIROBJS)/utils.o \
			$(DIROBJS)/package.o \
			-o runServer -Wall -Werror -pedantic

logger: tools/logger.cpp
	$(CC) -c tools/logger.cpp \
		-o $(DIROBJS)/logger.o

utils: tools/utils.cpp
	$(CC) -c tools/utils.cpp \
		-o $(DIROBJS)/utils.o

package: package/package.cpp
	$(CC) -c package/package.cpp \
		-o $(DIROBJS)/package.o


clean:
	rm -f runClient runServer
	if [ -d $(DIROBJS) ]; then rm -r $(DIROBJS); fi
# if [ -d $(DIRLOGS) ]; then rm -r $(DIRLOGS); fi