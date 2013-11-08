DOWNLOAD:
http://www.microwindow.org/
ftp://microwindows.censoft.com/pub/microwindows/microwindows-full-0.92.tar.gz

FILENAME:
	/microwindows-0.92/src/demos/mwin/login_main.c

DESCRIPTION:
	this is login demo,user information in src/bin/usrfile.pwd,that file format:
	userName|pwd
	if you try running this script,you need check that file that is exist.
	that used MicroWindows win32API.
MAKE:
	1- update makefile
		cd /microwindows-0.92/src/demos/mwin/
		$vi Makefile
		/mine #find that demos
		add login_main
		DEMS = ...
			   $(MW_DIR_BIN)/mine\
			   $(MW_DIR_BIN)/login_main
	2- make
		cd /microwindows-0.92/src/
		$make
		if you have error this place,please more readding /microwindows-0.92/README.
		may be lack lib. eg:zlib, you must be install.

RUN:
	cd /microwindows-0.92/src/bin/
	$./login_main
	
	you will see a window.

SIZE:
	microwindows-full-0.92.tar.gz	13M
	src/bin login_main	1.1M
	src/bin userinfo.pwd
