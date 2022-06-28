#include <linux/init.h>
#include <linux/init_task.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

int for_each_init(void) {
    printk(KERN_INFO "Load For Each Module ...\n");

    struct task_struct *task = &init_task;


    for_each_process(task) {
        printk("name: %s, pid: [%d], state: %li\n", task->comm, task->pid, task->state);
    }
}

void for_each_exit(void) { printk(KERN_INFO "Unload for each Module ...\n"); }

module_init(for_each_init);
module_exit(for_each_exit);
