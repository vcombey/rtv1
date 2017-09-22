#!/bin/sh

	rm -rf $1\.h
	printf "#ifndef " > $1\.h
	echo "$1_H" | tr "[:lower:]" "[:upper:]" | xargs echo >> $1\.h
	printf "# define " >> $1\.h
	echo "$1_H" | tr "[:lower:]" "[:upper:]" | xargs echo >> $1\.h
	if [[ -n "$2" ]] ; then
		cat srcs/base.h >> $1\.h
	else
		cat base.h >> $1\.h
	fi
	echo >> $1\.h
	if [[ ! -n "$2" ]] ; then
		find . -name "*\.c" | xargs cat | grep -iOE "^[a-zA-Z_ ]{1,}" | grep -iOEv "^static" | sed 's/$/;/g' >> $1\.h
	else
		find srcs -name "*\.c" | xargs cat | grep -iOE "^[a-zA-Z_ ]{1,}" | grep -iOEv "^static" | sed 's/$/;/g' >> $1\.h
	fi
	echo "#endif" >> $1\.h    
	if [[ -n "$2" ]] ; then
		mv $1\.h include/$1\.h
	fi
