#include <linux/init.h>
#include <linux/init_task.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

void do_goback(struct task_struct *curr) {
    struct task_struct *task = NULL;

    for (task = curr; task != &init_task; task = task->parent)
        ;

    printk("name: %s, pid: [%d], state: %li\n", task->comm, task->pid, task->state);
}

int goback_init(void) {
    printk(KERN_INFO "Load Go Back Module ...\n");

    struct task_struct *task = get_current();
    /* do_goback(task); */
    printk("name: %s, pid: [%d], state: %li\n", task->comm, task->pid, task->state);
}

void goback_exit(void) { printk(KERN_INFO "Unload Go back Module ...\n"); }

module_init(goback_init);
module_exit(goback_exit);
