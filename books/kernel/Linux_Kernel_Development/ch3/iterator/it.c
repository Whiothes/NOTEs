#include <linux/init.h>
#include <linux/init_task.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

/**
 * Performs a iterator on a given task's children.
 *
 * @void
 */
void iterator(struct task_struct *task) {
    struct task_struct *child;
    struct list_head *  list;

    list_for_each(list, &task->children) {
        child = list_entry(list, struct task_struct, sibling);
        printk("name: %s, pid: [%d], state: %li\n", child->comm, child->pid,
               child->state);
    }
}

/**
 * This function is called when the module is loaded.
 *
 * @return 0  upon success
 */
int task_lister_init(void) {
    printk(KERN_INFO "Loading Task Lister Module...\n");
    iterator(&init_task);

    return 0;
}

/**
 * This function is called when the module is removed.
 *
 * @void
 */
void task_lister_exit(void) {
    printk(KERN_INFO "Removing Task Lister Module...\n");
}

// Macros for registering module entry and exit points.
module_init(task_lister_init);
module_exit(task_lister_exit);
