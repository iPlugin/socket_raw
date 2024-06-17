GL_BaseCamp
Hi everyone, I get the test №3:

[ Client/Server application to search files on remote HOST ]

Implement Packets checker application.
- Create simple TCP based client-server applications.
- Create a proxy application (that is in the middle).
- Application logic:
	- Client sends data to Proxy. 
	- Option1: Proxy just forwards it to the server.
	- Option2: Proxy does modifications in payload and resend them to server.

For Option2: Server must figure out that data has been changed in the middle (calculating packet checksum).


===========================================================

[ For start, you need: ]

*For compiling software code*
- $ make
*For start the server*
- $ ./runServer 2000 2001
*For start the proxy*
- $ ./runProxy proxy 2001 2000 2002
*For start the client*
- $ ./runClient 2002 2001 test.txt
*For delete files created during compilation*
- $ make clean

===========================================================

[ Sources of information used: ]

- socket 1 = https://www.youtube.com/watch?v=KEiur5aZnIM&t=448s
- socket 2 = https://www.youtube.com/watch?v=_lQ-3S4fJ0U&list=PLPyaR5G9aNDvs6TtdpLcVO43_jvxp4emI
- thread (repeated) = https://www.youtube.com/watch?v=ZqIUDTZRx5s