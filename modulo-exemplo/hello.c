#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>

struct proc_dir_entry *file;

ssize_t proc_read(char *buffer, char **buffer_location,
		  off_t offset, int buffer_length, int *eof, void *data) {
  int len = 0; 

  if (offset > 0) {
    *eof = 1;
    return len;
  }

  len = sprintf(buffer, "Hello, World!\n");
  return len;
}


int init_module(void) {
  int rv = 0;
  file = create_proc_entry("hello", 0644, NULL);
  file->read_proc = proc_read;
  file->mode = S_IFREG | S_IRUGO;
  file->uid = 0;
  file->gid = 0;
  file->size = 37;

  if (file == NULL) {
    rv = -ENOMEM;
    remove_proc_entry("hello", NULL);
    printk("Problema com o módulo!\n");
  } else {
    printk("Módulo carregado!\n");
  }

  return rv;
}

void cleanup_module(void) {
  remove_proc_entry("hello", NULL);
  printk("Módulo descarregado!\n");
}

MODULE_LICENSE("GPL");
