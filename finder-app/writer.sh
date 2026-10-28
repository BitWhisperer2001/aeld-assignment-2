#!/bin/sh


if [ "$#" -lt 2 ]; then
	echo "ERROR: Missing required agrument"
	echo "Usage: $0 path_to_file content"
	exit 1
fi

path_to_file="$1"
content="$2"

dir=$(dirname "$path_to_file")

if ! mkdir -p "$dir"; then
	echo "ERROR: Cannot create '$dir' directory"
	exit 1
fi

if ! echo "$content" > "$path_to_file"; then
	echo "ERROR: Cannot write '$content' to '$path_to_file'"
	exit 1
fi


exit 0





