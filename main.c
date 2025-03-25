#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <wctype.h>
#include <string.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <sys/stat.h>
#include <linux/limits.h>
#include "state_machine.h"
#include "process_file.h"
#include "transition.h"
#include "process_input.h"


#define MAX_LINE_LENGTH 1023

#define BUFF_LEN (10* (sizeof(struct inotify_event) + NAME_MAX + 1))

void handle_event(struct inotify_event *event, char *src, int flag) {
    if (event->mask & IN_MODIFY) {
        printf("File modified: %s\n", event->name);

        char src_path[PATH_MAX];
        char dest_dir[PATH_MAX];
        char dest_path[PATH_MAX];

        sprintf(src_path, "%s/%s", src, event->name);

        // Create destination directory with "_trans" suffix
        sprintf(dest_dir, "%s_trans", src);
        mkdir(dest_dir, 0777);

        if (strlen(dest_dir) + strlen(event->name) + 2 <= PATH_MAX) {  
			snprintf(dest_path, PATH_MAX, "%s/%s", dest_dir, event->name);
		} else {
			fprintf(stderr, "Path too long: %s/%s\n", dest_dir, event->name);
			return;
		}
		
        process_file_input(flag,src_path,dest_path);

        
    }
}

int main(int argc,char *argv[]){

    setlocale(LC_ALL, ""); // Set locale for wide character support
    initialize_states();
    process_file(argv[1]);
    sort_states();
    //print_states();

    char *source_dir1 = "english_dir";
    char *source_dir2 = "marathi_dir";
    int flag;

    int inotify_fd = inotify_init();
    if (inotify_fd == -1) {
        perror("inotify_init");
        exit(EXIT_FAILURE);
    }
   

    int wd1 = inotify_add_watch(inotify_fd, source_dir1, IN_CREATE | IN_MODIFY | IN_DELETE);
    if (wd1 == -1) {
        perror("inotify_add_watch for source_dir1");
        exit(EXIT_FAILURE);
    }

    int wd2 = inotify_add_watch(inotify_fd, source_dir2, IN_CREATE | IN_MODIFY | IN_DELETE);
    if (wd2 == -1) {
        perror("inotify_add_watch for source_dir2");
        exit(EXIT_FAILURE);
    }

    printf("Monitoring directories: %s and %s\n", source_dir1, source_dir2);

    char buff[BUFF_LEN] __attribute__((aligned(8)));
    ssize_t num_read;

    while (1) {
        num_read = read(inotify_fd, buff, BUFF_LEN);
        if (num_read == 0) {
            fprintf(stderr, "read() from inotify fd returned 0!");
            exit(EXIT_FAILURE);
        }
        if (num_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        char *ptr = buff;

        while (ptr < buff + num_read) {
            struct inotify_event *event = (struct inotify_event *)ptr;

            if (event->wd == wd1) {
                flag = 1;   // english to hindi
                handle_event(event, source_dir1, flag);
            } else if (event->wd == wd2) {
                flag = 0;   // hindi to english
                handle_event(event, source_dir2, flag);
            }

            ptr += sizeof(struct inotify_event) + event->len;
        }
    }

    return 0;
}

