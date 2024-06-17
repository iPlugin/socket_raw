# ============= Makefile ============= #

CC = g++
DIROBJS = obj
DIRLOGS = logs
DIRTOOLS = tools
CREATE_DIROBJS = mkdir -p $(DIROBJS)
CREATE_DIRLOGS = mkdir -p $(DIRLOGS)


all: folders runClient runServer runProxy

folders:
	$(CREATE_DIROBJS)
	$(CREATE_DIRLOGS)

runClient: client/runClient.cpp logger utils package linux 
	$(CC) client/runClient.cpp $(DIRTOOLS)/client.cpp \
		$(DIROBJS)/logger.o $(DIROBJS)/utils.o \
		$(DIROBJS)/package.o $(DIROBJS)/settingsOS.o \
		-o runClient -Wall -Werror -pedantic

runServer: server/runServer.cpp logger utils package linux searcher
	$(CC) server/runServer.cpp $(DIRTOOLS)/server.cpp \
		$(DIROBJS)/logger.o $(DIROBJS)/utils.o \
		$(DIROBJS)/package.o $(DIROBJS)/settingsOS.o \
		$(DIROBJS)/searcher.o \
		-o runServer -Wall -Werror -pedantic

runProxy: middleware/runProxy.cpp logger utils package linux
	$(CC) middleware/runProxy.cpp $(DIRTOOLS)/proxy.cpp \
		$(DIROBJS)/logger.o $(DIROBJS)/utils.o \
		$(DIROBJS)/package.o $(DIROBJS)/settingsOS.o \
		-o runProxy -Wall -Werror -pedantic

logger: tools/logger.cpp
	$(CC) -c tools/logger.cpp \
		-o $(DIROBJS)/logger.o

utils: tools/utils.cpp
	$(CC) -c tools/utils.cpp \
		-o $(DIROBJS)/utils.o

package: package/package.cpp
	$(CC) -c package/package.cpp \
		-o $(DIROBJS)/package.o

linux: linux/settingsOS.cpp
	$(CC) -c linux/settingsOS.cpp \
		-o $(DIROBJS)/settingsOS.o

searcher: sources/searcher.cpp
	$(CC) -c sources/searcher.cpp \
		-o $(DIROBJS)/searcher.o

clean:
	rm -f runClient runServer runProxy
	if [ -d $(DIROBJS) ]; then rm -r $(DIROBJS); fi
# if [ -d $(DIRLOGS) ]; then rm -r $(DIRLOGS); fi