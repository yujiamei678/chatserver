#########################################################################
# File Name: autobuild.sh
# Author: myj
# mail: meiyujia224@163.com
#########################################################################
#!/bin/bash

set -x

rm -rf `pwd`/build/*
cd `pwd`/build &&
	cmake .. &&
	make
