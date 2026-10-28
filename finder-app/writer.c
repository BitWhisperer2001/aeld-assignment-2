#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int main(int agrc, char *agrv[])  // argv: hold number of agruments passed program include program name itself as the first agrument | argc: is array of string that actual argument passed with agrv[0] always is name of program
{
	char* path = agrv[1];
	char* content = agrv[2];
	int total_written = 0;
	size_t len;
	
	openlog("writer", LOG_PID, LOG_USER);

	if(agrc < 3){
		syslog(LOG_ERR, "Expected 2 agruments: <path_write_file> <content_to_write>\n");
		closelog();
		printf("ERROR: Expected 2 agruments: <path_write_file> <content_to_write>\n");
		return 1;
	}
	
	int fd;
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	int saved_errno = errno;
	if(fd == -1){
		syslog(LOG_ERR, "Cannot open file: %s\n", strerror(saved_errno));
		printf("ERROR: Fail open file\n");
		closelog();
		return 1;
	}
	
	len = strlen(content);
	while(total_written < len){
		size_t bytes_written = write(fd, content + total_written, len - total_written);
		if(bytes_written == -1){
			saved_errno = errno;
			printf("ERROR: Error while write content into %s\n", path);
			syslog(LOG_ERR, "Cannot write content to file: %s\n", strerror(saved_errno));
			if(close(fd) == -1){
                  		saved_errno = errno;
                  		syslog(LOG_ERR, "Cannot close file: %s\n", strerror(saved_errno));
         		}
			closelog();
			return 1;
		}				
		total_written += bytes_written;
	}
	printf(" Write %s into %s successfully\n", content, path);
	syslog(LOG_DEBUG, "Write %s to %s\n", content, path);
	if(close(fd) == -1){
		saved_errno = errno;
		syslog(LOG_ERR, "Cannot close file: %s\n", strerror(saved_errno));
		closelog();
		return 1;
	}
	closelog();
	return 0;
}









