========================
Linux Kernel Development
========================

:Author: whiothes

.. role:: raw-latex(raw)
   :format: latex
..

:raw-latex:`\usepackage{ulem}`

:raw-latex:`\usepackage{ctex}`

:raw-latex:`\sectionfont{\normalfont\scshape}`

:raw-latex:`\subsectionfont{\normalfont\itshape}`

.. raw:: org

   #+setupfile: ~/Documents/style.setup

.. raw:: org

   #+startup: align

.. _linux-kernel-development-1:

Linux Kernel Development
========================

2 Getting Started with the kernel
---------------------------------

A beast of a Different Nature
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#. GNU C

   #. Inline Functions

      inserted inline into each function call site. optimize both the
      caller and the called function as one. code size increased because
      the contents copied into the callers, increases memory consumption
      and instruction cache footprint.

      Kernel developers use inline functions for small time-critical
      functions.

      .. code:: c

         static inline void wolf(unsigned long tail_size);

#. No Memory Protection

   user-space allication attempts an illegal memory access, the kernel
   can trap the error, send the SIGSEGV signal, and kill the process. If
   the kernel attempts an illegal memory access, the results are less
   controlled.

#. No (Easy) Use of Floating Point

   when a user-space process uses floating-point instructions, the
   kernel manages the transition from integer to floating point mode.

   Using a floating point inside the kernel requires manually saving and
   restoring the floating point registers ( DON'T DO IT !)

#. Small, Fixed-Size Stack

   The kernel stack is neither large nor dynamic; it is small and fixed
   in size. On x86, the stack size can be either 4KB or 8KB. is two
   pages, 8KB on 32-bit architectures and 16KB on 64-bit architectures.

#. Synchronixation and Concurrency

3 Process Management
--------------------

The Process
~~~~~~~~~~~

process includes: a set of resources such as open files and pending
signals, inter kernal data, processor state, a memory address space with
one or more memory mappings, one or more threads of execution, and a
data section containing global variables.

thread includes a unique program counter, process stack, and sets of
processor registers.

kernel schedules individual threads, not process.

-  virtualized processor : process alone monopolizes the system
-  virtualized memory: allocate and manage memory as if process owned
   all the memory in the system.

threads share the virtual memory abstraction.

a program itself is not a process; a process is an **active** program
and related resources.

Process Descriptor and the Task Structure
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The kernel stores the list of processes in a circular doubly linked list
called *task list*.

.. code:: c

   #include <linux/sched.h>

   /*
    * contains all the information that kernel has and needs about a process
    **/
   struct task_struct {
           volatile long state; /* -1 unrunnable, 0 runnable, >0 stopped */
           void *        stack;
           atomic_t      usage;
           unsigned int  flags; /* per process flags, defined below */
           unsigned int  ptrace;

           int lock_depth; /* BKL lock depth */

   #ifdef CONFIG_SMP
   #ifdef __ARCH_WANT_UNLOCKED_CTXSW
           int oncpu;
   #endif
   #endif

           int                       prio, static_prio, normal_prio;
           unsigned int              rt_priority;
           const struct sched_class *sched_class;
           struct sched_entity       se;
           struct sched_rt_entity    rt;

   #ifdef CONFIG_PREEMPT_NOTIFIERS
           /* list of struct preempt_notifier: */
           struct hlist_head preempt_notifiers;
   #endif

           /*
            * fpu_counter contains the number of consecutive context switches
            * that the FPU is used. If this is over a threshold, the lazy fpu
            * saving becomes unlazy to save the trap. This is an unsigned char
            * so that after 256 times the counter wraps and the behavior turns
            * lazy again; this to deal with bursty apps that only use FPU for
            * a short time
            */
           unsigned char fpu_counter;
   #ifdef CONFIG_BLK_DEV_IO_TRACE
           unsigned int btrace_seq;
   #endif

           unsigned int policy;
           cpumask_t    cpus_allowed;

   #ifdef CONFIG_PREEMPT_RCU
           int              rcu_read_lock_nesting;
           char             rcu_read_unlock_special;
           struct list_head rcu_node_entry;
   #endif /* #ifdef CONFIG_PREEMPT_RCU */
   #ifdef CONFIG_TREE_PREEMPT_RCU
           struct rcu_node *rcu_blocked_node;
   #endif /* #ifdef CONFIG_TREE_PREEMPT_RCU */
   #ifdef CONFIG_RCU_BOOST
           struct rt_mutex *rcu_boost_mutex;
   #endif /* #ifdef CONFIG_RCU_BOOST */

   #if defined(CONFIG_SCHEDSTATS) || defined(CONFIG_TASK_DELAY_ACCT)
           struct sched_info sched_info;
   #endif

           struct list_head tasks;
   #ifdef CONFIG_SMP
           struct plist_node pushable_tasks;
   #endif

           struct mm_struct *mm, *active_mm;
   #ifdef CONFIG_COMPAT_BRK
           unsigned brk_randomized : 1;
   #endif
   #if defined(SPLIT_RSS_COUNTING)
           struct task_rss_stat rss_stat;
   #endif
           /* task state */
           int exit_state;
           int exit_code, exit_signal;
           int pdeath_signal; /*  The signal sent when the parent dies  */
           /* ??? */
           unsigned int personality;
           unsigned     did_exec : 1;
           unsigned     in_execve : 1; /* Tell the LSMs that the process is doing an
                                        * execve */
           unsigned in_iowait : 1;

           /* Revert to default priority/policy when forking */
           unsigned sched_reset_on_fork : 1;

           pid_t pid;
           pid_t tgid;

   #ifdef CONFIG_CC_STACKPROTECTOR
           /* Canary value for the -fstack-protector gcc feature */
           unsigned long stack_canary;
   #endif

           /*
            * pointers to (original) parent process, youngest child, younger sibling,
            * older sibling, respectively.  (p->father can be replaced with
            * p->real_parent->pid)
            */
           struct task_struct *real_parent; /* real parent process */
           struct task_struct *parent;      /* recipient of SIGCHLD, wait4() reports */
           /*
            * children/sibling forms the list of my natural children
            */
           struct list_head    children;     /* list of my children */
           struct list_head    sibling;      /* linkage in my parent's children list */
           struct task_struct *group_leader; /* threadgroup leader */

           /*
            * ptraced is the list of tasks this task is using ptrace on.
            * This includes both natural children and PTRACE_ATTACH targets.
            * p->ptrace_entry is p's link on the p->parent->ptraced list.
            */
           struct list_head ptraced;
           struct list_head ptrace_entry;

           /* PID/PID hash table linkage. */
           struct pid_link  pids[PIDTYPE_MAX];
           struct list_head thread_group;

           struct completion *vfork_done; /* for vfork() */
           int __user *set_child_tid;     /* CLONE_CHILD_SETTID */
           int __user *clear_child_tid;   /* CLONE_CHILD_CLEARTID */

           cputime_t utime, stime, utimescaled, stimescaled;
           cputime_t gtime;
   #ifndef CONFIG_VIRT_CPU_ACCOUNTING
           cputime_t prev_utime, prev_stime;
   #endif
           unsigned long   nvcsw, nivcsw;   /* context switch counts */
           struct timespec start_time;      /* monotonic time */
           struct timespec real_start_time; /* boot based time */
           /* mm fault and swap info: this can arguably be seen as either mm-specific
            * or thread-specific */
           unsigned long min_flt, maj_flt;

           struct task_cputime cputime_expires;
           struct list_head    cpu_timers[3];

           /* process credentials */
           const struct cred __rcu *real_cred; /* objective and real subjective task
                                                * credentials (COW) */
           const struct cred __rcu *cred; /* effective (overridable) subjective task
                                           * credentials (COW) */
           struct cred *replacement_session_keyring; /* for KEYCTL_SESSION_TO_PARENT */

           char comm[TASK_COMM_LEN]; /* executable name excluding path
                                        - access with [gs]et_task_comm (which lock
                                        it with task_lock())
                                        - initialized normally by setup_new_exec */
           /* file system info */
           int link_count, total_link_count;
   #ifdef CONFIG_SYSVIPC
           /* ipc stuff */
           struct sysv_sem sysvsem;
   #endif
   #ifdef CONFIG_DETECT_HUNG_TASK
           /* hung task detection */
           unsigned long last_switch_count;
   #endif
           /* CPU-specific state of this task */
           struct thread_struct thread;
           /* filesystem information */
           struct fs_struct *fs;
           /* open file information */
           struct files_struct *files;
           /* namespaces */
           struct nsproxy *nsproxy;
           /* signal handlers */
           struct signal_struct * signal;
           struct sighand_struct *sighand;

           sigset_t blocked, real_blocked;
           sigset_t saved_sigmask; /* restored if set_restore_sigmask() was used */
           struct sigpending pending;

           unsigned long sas_ss_sp;
           size_t        sas_ss_size;
           int (*notifier)(void *priv);
           void *                notifier_data;
           sigset_t *            notifier_mask;
           struct audit_context *audit_context;
   #ifdef CONFIG_AUDITSYSCALL
           uid_t        loginuid;
           unsigned int sessionid;
   #endif
           seccomp_t seccomp;

           /* Thread group tracking */
           u32 parent_exec_id;
           u32 self_exec_id;
           /* Protection of (de-)allocation: mm, files, fs, tty, keyrings,
            * mems_allowed, mempolicy */
           spinlock_t alloc_lock;

   #ifdef CONFIG_GENERIC_HARDIRQS
           /* IRQ handler threads */
           struct irqaction *irqaction;
   #endif

           /* Protection of the PI data structures: */
           raw_spinlock_t pi_lock;

   #ifdef CONFIG_RT_MUTEXES
           /* PI waiters blocked on a rt_mutex held by this task */
           struct plist_head pi_waiters;
           /* Deadlock detection and priority inheritance handling */
           struct rt_mutex_waiter *pi_blocked_on;
   #endif

   #ifdef CONFIG_DEBUG_MUTEXES
           /* mutex deadlock detection */
           struct mutex_waiter *blocked_on;
   #endif
   #ifdef CONFIG_TRACE_IRQFLAGS
           unsigned int  irq_events;
           unsigned long hardirq_enable_ip;
           unsigned long hardirq_disable_ip;
           unsigned int  hardirq_enable_event;
           unsigned int  hardirq_disable_event;
           int           hardirqs_enabled;
           int           hardirq_context;
           unsigned long softirq_disable_ip;
           unsigned long softirq_enable_ip;
           unsigned int  softirq_disable_event;
           unsigned int  softirq_enable_event;
           int           softirqs_enabled;
           int           softirq_context;
   #endif
   #ifdef CONFIG_LOCKDEP
   #define MAX_LOCK_DEPTH 48UL
           u64              curr_chain_key;
           int              lockdep_depth;
           unsigned int     lockdep_recursion;
           struct held_lock held_locks[MAX_LOCK_DEPTH];
           gfp_t            lockdep_reclaim_gfp;
   #endif

           /* journalling filesystem info */
           void *journal_info;

           /* stacked block device info */
           struct bio_list *bio_list;

   #ifdef CONFIG_BLOCK
           /* stack plugging */
           struct blk_plug *plug;
   #endif

           /* VM state */
           struct reclaim_state *reclaim_state;

           struct backing_dev_info *backing_dev_info;

           struct io_context *io_context;

           unsigned long             ptrace_message;
           siginfo_t *               last_siginfo; /* For ptrace use.  */
           struct task_io_accounting ioac;
   #if defined(CONFIG_TASK_XACCT)
           u64       acct_rss_mem1; /* accumulated rss usage */
           u64       acct_vm_mem1;  /* accumulated virtual memory usage */
           cputime_t acct_timexpd;  /* stime + utime since last update */
   #endif
   #ifdef CONFIG_CPUSETS
           nodemask_t mems_allowed; /* Protected by alloc_lock */
           int        mems_allowed_change_disable;
           int        cpuset_mem_spread_rotor;
           int        cpuset_slab_spread_rotor;
   #endif
   #ifdef CONFIG_CGROUPS
           /* Control Group info protected by css_set_lock */
           struct css_set __rcu *cgroups;
           /* cg_list protected by css_set_lock and tsk->alloc_lock */
           struct list_head cg_list;
   #endif
   #ifdef CONFIG_FUTEX
           struct robust_list_head __user *robust_list;
   #ifdef CONFIG_COMPAT
           struct compat_robust_list_head __user *compat_robust_list;
   #endif
           struct list_head       pi_state_list;
           struct futex_pi_state *pi_state_cache;
   #endif
   #ifdef CONFIG_PERF_EVENTS
           struct perf_event_context *perf_event_ctxp[perf_nr_task_contexts];
           struct mutex               perf_event_mutex;
           struct list_head           perf_event_list;
   #endif
   #ifdef CONFIG_NUMA
           struct mempolicy *mempolicy; /* Protected by alloc_lock */
           short             il_next;
           short             pref_node_fork;
   #endif
           atomic_t        fs_excl; /* holding fs exclusive resources */
           struct rcu_head rcu;

           /*
            * cache last used pipe for splice
            */
           struct pipe_inode_info *splice_pipe;
   #ifdef CONFIG_TASK_DELAY_ACCT
           struct task_delay_info *delays;
   #endif
   #ifdef CONFIG_FAULT_INJECTION
           int make_it_fail;
   #endif
           struct prop_local_single dirties;
   #ifdef CONFIG_LATENCYTOP
           int                   latency_record_count;
           struct latency_record latency_record[LT_SAVECOUNT];
   #endif
           /*
            * time slack values; these are used to round up poll() and
            * select() etc timeout values. These are in nanoseconds.
            */
           unsigned long timer_slack_ns;
           unsigned long default_timer_slack_ns;

           struct list_head *scm_work_list;
   #ifdef CONFIG_FUNCTION_GRAPH_TRACER
           /* Index of current stored address in ret_stack */
           int curr_ret_stack;
           /* Stack of return addresses for return function tracing */
           struct ftrace_ret_stack *ret_stack;
           /* time stamp for last schedule */
           unsigned long long ftrace_timestamp;
           /*
            * Number of functions that haven't been traced
            * because of depth overrun.
            */
           atomic_t trace_overrun;
           /* Pause for the tracing */
           atomic_t tracing_graph_pause;
   #endif
   #ifdef CONFIG_TRACING
           /* state flags for use by tracers */
           unsigned long trace;
           /* bitmask of trace recursion */
           unsigned long trace_recursion;
   #endif                            /* CONFIG_TRACING */
   #ifdef CONFIG_CGROUP_MEM_RES_CTLR /* memcg uses this to do batch job */
           struct memcg_batch_info {
                   int do_batch;             /* incremented when batch uncharge started */
                   struct mem_cgroup *memcg; /* target memcg of uncharge */
                   unsigned long      nr_pages;       /* uncharged usage */
                   unsigned long      memsw_nr_pages; /* uncharged mem+swap usage */
           } memcg_batch;
   #endif
   #ifdef CONFIG_HAVE_HW_BREAKPOINT
           atomic_t ptrace_bp_refcnt;
   #endif
   };

.. raw:: org

   #+caption: Figure 3.1 The process descriptor and task list

`Figure 3.1 <ch3/fig-3-1.jpg>`__

#. Allocating the Process Descriptor

   ``task_struct`` is allocated via *slab allocator*. Prior to the 2.6
   kernel series, was stored at the end of the kernel stack of each
   process.

   ``struct task_struct`` was stored at the end of the kernel stack of
   each process.

   .. code:: c

      struct thread_info {
              struct task_struct   *task;
              struct exec_domain   *exec_domain;
              __u32                 flags;
              __u32                 status;
              __u32                 cpu;
              int                   preept_count;
              mm_segment_t          addr_limit;
              struct restart_block  restart_block;
              void                 *sysenter_return;
              int                   uaccess_err;
      };

#. Storing the Process Descriptor

   maximum value of *PID*: ``/proc/sys/kernel/pid_max/``

   most kernel code deals with processes works directly with
   ``strcut task_struct``

   some architectures save a pointer to the ``task_struct`` of the
   currently running process in a register, others use
   ``struct thread_info`` to calculate the location of ``thread_info``
   and ``task_struct``.

#. Process State

      -  TASK\ :sub:`RUNNING` - runnable, either running or on a
         runqueue waiting to run
      -  TASK\ :sub:`INTERRUPTIBLE` - sleeping,
      -  TASK\ :sub:`UNINTERRUPTIBLE` - **DOES NOT** wake up and become
         runnable if it receives a signal. used when the process must
         wait without interruption or when the event is excepted to
         occur quite quickly.
      -  \_\ :sub:`TASKTRACED` - being traced by another process, such
         as a debugger, via *ptrace*
      -  \_\ :sub:`TASKSTOPED` - is not running nor eligible to run.
         ``SIGSTOP, SIGTSTP, SIGTTIN, SIGTTOU`` or *any* signal while it
         is being debugged.

#. Manipulating the Current Process State

   ``set_task_state(task, state)`` to change process's state. is
   equivalent to ``task->state = state;``

#. Process Context

   normal in *user-space*. enters *kernel-space* when executes a system
   call or triggers an exception.

#. The Process Family Tree

   ALl processes are descendants of ``init`` process, PID=1.

   The ``init`` process reads the system *initscripts* and executes more
   programs, eventually completing the boot process.

   obtain process descriptor of current process's parent:

   .. code:: c

      struct task_struct *my_parent = current->parent;

   iterate over a process's children:

   .. code:: c

      struct task_struct *task;
      struct list_head *list;

      list_for_each(list, &current->children) {
              task = list_entry(list, struct task_struct, sibling);
      }

   `iterator for init
   process <ch3/iterator/it.c::include <linux/init.h>>`__

   a good example of the relationship between all processes :

   .. code:: c

      struct task_struct *task;

      for (task = current; task != &init_task; task = task->parent)
              ;

      /* task now points to init */

   obtain the next task in the list:

   .. code:: c

      list_entry(task->tasks.next, struct task_struct, tasks)

   obtain the previous task in the list:

   .. code:: c

      list_entry(tasks.prev, struct task_struct, tasks)

   macro for iterating entire task list:

   .. code:: c

      struct task_struct *task;

      for_each_process(task) { printk("%s[%d]\n", task->comm, task->pid); }

Process Creation
~~~~~~~~~~~~~~~~

``fork()``, differs from the parent only in its PID, its PPID and
certain resources and statistics, which are no inherited.

``exec()``, loads a new executable into the addres space and begins
executing it.

#. Copy-on-Write

   -  `Copy-on-write -
      Wikipedia <https://en.wikipedia.org/wiki/Copy-on-write>`__

   Copy only when modified, share the same one if readonly. A resource
   is duplicated but not modified, it is not necessary to create a new
   resource.

#. Forking

   ``clone`` calls with requisite flags, calls ``do_fork()``

#. ``vfork``

   the page table entries of the parent process are not copied.

   implemented via a special flag to ``clone()`` system call:

      #. In ``copy_process()``, the task\ :sub:`struct` member
         ``vfork_done()`` is set to NULL
      #. In ``do_fork()``, if the special flag was given,
         ``vfork_done()`` is pointed to a specific address
      #. After the child is first run, the parent waits for the child to
         signal it through the ``vfork_done()`` pointer.
      #. In the ``mm_release()`` function, ``vfork_done()`` is checked
         to see if it is NULL, then the parent is signaled.
      #. Back in ``do_fork()``, the parents wakes up and returns.

The Linux Implementation of Threads
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Threads share open files and other resources. Threads enable *concurrent
programming* and, on multiple processor systems, true *parallelism*.

**A thread is merely a process that shares certain resources with other
processes.**

**Each thread has a unique ``task_struct`` and appears to the kernel as
a normal process - threads just happen to share resources.**

#. Creating Threads

   the same as normal tasks, but passed flags corresponding to the
   specific resources to be shared

   .. code:: c

      clone (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND, 0);

   -  ``fork()``

      .. code:: c

         clone(SIGCHLD, 0);

   -  ``vfork()``

      .. code:: c

         clone(CLONE_VFORK | CLONE_VM | SIGCHLD, 0);

   .. table:: Table 1: Table 3.1. ``clone()`` Flags

      +-----------------------------+---------------------------------------+
      | Flag                        | Meaning                               |
      +=============================+=======================================+
      | CLONE\ :sub:`FILES`         | Parent and child share open files     |
      +-----------------------------+---------------------------------------+
      | CLONE\ :sub:`FS`            | Parent and child share filesystem     |
      |                             | information                           |
      +-----------------------------+---------------------------------------+
      | CLONE\ :sub:`IDLETASK`      | Set PID to zero (used only by the     |
      |                             | idle tasks)                           |
      +-----------------------------+---------------------------------------+
      | CLONE\ :sub:`NEWS`          | Create a new namespace for the child  |
      +-----------------------------+---------------------------------------+
      | CLONE\ :sub:`PARENT`        | Child is to have some parent as its   |
      |                             | parent                                |
      +-----------------------------+---------------------------------------+
      | CLONE\ :sub:`PTRACE`        | Continuing tracing child              |
      +-----------------------------+---------------------------------------+
      | CLONE\ :sub:`SETTID`        | Write the TID back to user-space      |
      +-----------------------------+---------------------------------------+
      | CLONE\ :sub:`SETTLS`        | Create a new TLS for the child        |
      +-----------------------------+---------------------------------------+
      | CLONE\ :sub:`SIGHAND`       | Parent and child share signal handler |
      |                             | and blocked signals                   |
      +-----------------------------+---------------------------------------+
      | CLONE\ :sub:`SYSVSEM`       | Parent and child share System V       |
      |                             | ``SEM_UNDO`` semantics                |
      +-----------------------------+---------------------------------------+
      | CLONE\ :sub:`THREAD`        | Parent and child are in the same      |
      |                             | thread group                          |
      +-----------------------------+---------------------------------------+
      | CLONE\ :sub:`VFORK`         | ``vfork()`` was used and the parent   |
      |                             | will sleep until the child wakes it   |
      +-----------------------------+---------------------------------------+
      | CLONE\ :sub:`UNTRACED`      | Do not let the tracing process force  |
      |                             | CLONE\ :sub:`PTRACE` on the child     |
      +-----------------------------+---------------------------------------+
      | CLONE\ :sub:`STOP`          | Start process in the ``TASK_STOPPED`` |
      |                             | state.                                |
      +-----------------------------+---------------------------------------+
      | CLONE\ :sub:`SETTLS`        | Create a new TLS (thread-local        |
      |                             | storage) for the child                |
      +-----------------------------+---------------------------------------+
      | CLONE\ :sub:`CHILDCLEARTID` | Clear the TID int he child            |
      +-----------------------------+---------------------------------------+
      | CLONE\ :sub:`CHILDSETTID`   | Set the TID in the child.             |
      +-----------------------------+---------------------------------------+
      | CLONE\ :sub:`PARENTSETTID`  | Set the TID in the parent.            |
      +-----------------------------+---------------------------------------+
      | CLONE\ :sub:`VM`            | Parent and child share address space. |
      +-----------------------------+---------------------------------------+

#. Kernel Threads

      The significant difference between kernel threads and normal
      processes is that kernel threads do not have an address space.
      (Their ``mm`` pointer, which points at their address space, is
      ``NULL``).

   interface declared in ``<linux/kthread.h>``

   .. code:: c

      struct task_struct *kthread_create(int (*threadfn)(void *data), void *data,
                                         const char namefmt[], ...);

      /**
       * kthread_create - create a kthread on the current node
       * @threadfn: the function to run in the thread
       * @data: data pointer for @threadfn()
       * @namefmt: printf-style format string for the thread name
       * @arg...: arguments for @namefmt.
       *
       * This macro will create a kthread on the current node, leaving it in
       * the stopped state.  This is just a helper for kthread_create_on_node();
       * see the documentation there for more details.
       */
      #define kthread_create(threadfn, data, namefmt, arg...)                 \
              kthread_create_on_node(threadfn, data, NUMA_NO_NODE, namefmt, ##arg)

      struct task_struct *kthread_run(int (*threadfn)(void *data), void *data,
                                      const char namefmt[], ...);

      /**
       * kthread_run - create and wake a thread.
       * @threadfn: the function to run until signal_pending(current).
       * @data: data ptr for @threadfn.
       * @namefmt: printf-style name for the thread.
       *
       * Description: Convenient wrapper for kthread_create() followed by
       * wake_up_process().  Returns the kthread or ERR_PTR(-ENOMEM).
       */
      #define kthread_run(threadfn, data, namefmt, ...)                       \
              ({                                                              \
                      struct task_struct *__k =                               \
                              kthread_create(threadfn, data, namefmt, ##__VA_ARGS__); \
                      if (!IS_ERR(__k)) wake_up_process(__k);                 \
                      __k;                                                    \
              })


      int kthread_stop(struct task_struct *k);

Process Termination
~~~~~~~~~~~~~~~~~~~

``do_exit()``

#. ``PF_EXITING`` for ``flags`` of the ``struct task_struct``
#. calls ``del_timer_sync()``
#. ``if (BSD process accounting) { acct_update_integrals(); }``
#. calls ``exit_mm()`` to release the ``mm_struct``
#. calls ``exit_sem()`` to dequeue IPC semaphore.
#. calls ``exit_files()`` and ``exit_fs()`` to decrement the usage count
   of file descriptors and filesystem data.
#. set exit code stored ``exit_code`` in the ``task_struct``
#. calls ``exit_notify()`` to send signals to the task's parent,
   reparents any of the task's chidren to another thread in their thread
   group or the init process, and sets ``exit_state=EXIT_ZOMBIE``
#. calls ``schedule()`` to switch to a new process. ``do_exit()`` never
   returns.

#. Removing the Process Descriptor

   ``release_task()``

   #. calls ``__exit_signal()``, which calls ``__unhash_process()``,
      which in turns calls ``detach_pid()`` to remove the process from
      the pidhash and task\ :sub:`list`.
   #. ``__eixt_signal()`` releases any remaining resources used by
   #. ``if (last member && leader == zombie) { release_task(); }``
   #. ``release_task()`` calls ``put_task_struct()`` to free the pages
      for ``thread_info`` and deallocate the slab cache for
      ``task_struct``

#. The Dilemma of the Parentless Task

   ``exit_notify()`` -> ``forget_original_parent()`` ->
   ``find_new_reaper()`` to perform the reparenting.

4 Process Scheduling
--------------------

The process scheduler decides which process runs, when, and for how
long.

Multitaksing
~~~~~~~~~~~~

A *multitasking* operating system is one that can simultaneously
interleave execution of more than one process.

two flavors: *coorperative multitasking* and *preemptive multitasking*.

-  *preemptive multitasking*, the scheduler decides when a process is to
   cease running and a new process is to begin running.
-  *coorperative multitasking*, a process does not stop running until it
   voluntary decides to do so.

Timeslice: gives each runnable process a *slice* of the processor's time

Linux's Process Scheduler
~~~~~~~~~~~~~~~~~~~~~~~~~

CFS: Completely Fair Scheduler.

Policy
~~~~~~

#. I/O-Bound Versus Processor-Bound Processes

   -  I/O-bound process, spends much of its time submitting and waiting
      on I/O requests.
   -  processor-bound process, spends much of their time executing code.

#. Process Priority

   priorty-based scheduling: A common type of scheduling algrithm. The
   goal is to rank processes based on their worth and need for processor
   time.

   The Linux kernel implements two seperate two priority ranges:

   -  *nice* value: -20 to +19, with a default of 0.

      .. raw:: org

   #+caption: correspondence between value and priority


   +----------+-----------------+-------+
   | column   | from -> to      | hello |
   +==========+=================+=======+
   | value    | larger->smaller         |
   +----------+-----------------+-------+
   | priority | lower->higher   |       |
   +----------+-----------------+-------+


   .. code:: bash

      ps -eo state,uid,pid,ppid,rtprio,time,comm

   -  *real-time* priority (*RTPRIO*):

      opposite from nice values, higher real-time priority values
      correspond to a greater priority.

      .. code:: bash

         ps -eo state,uid,pid,ppid,rtprio,time,comm

#. Timeslice

   The timesilce is the number value that represents how long a task can
   run until it is preempted.

   -  Too long timeslice causes the system doesn't know if the process
      executed.
   -  Too short timeslice causes the system wastes too much processor
      time switching between processes.
   -  I/O-bound processes do not need longer timeslices
   -  processor-bound processes crave long timeslices.

   In a novel approach, Linux's CFS Scheduler assigns processes a
   *proportion* of the processor.

   Processes with higher nice values (a lower priority) receive a
   deflationary weight, yielding them a smaller proportion of the
   processor; processes with smaller nice values (a higher priority)
   receive an inflationary weight, netting them a larger proportion of
   the processor.

   The Linux operating system is preemptive.

#. The Scheduling Policy in Action

The Linux Scheduling Algorithm
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#. Scheduler Classes

   Scheduler classes enable different, pluggable alogirhtms to coexist,
   scheduling their own types of processes.

#. Process Scheduling in Unix Systems

   scheduler common concepts: processes priority and timeslice.

   pathological problems:

   -  mapping nice values onto timeslices requires a decision about what
      absolute timeslice to allot each nice value.
   -  concers relative nice values and again the nice value to timeslice
      mapping.
   -  if performing a nice value to timeslice mapping, we need the
      ability to assign an absolute timeslice.
   -  concerns handling process wake up in a priority based scheduler
      that wants to optimize for interactive tasks.

#. Fair Scheduling

   CFS uses the nice value to *weight* the proportion of processor a
   process is to receive: Higher valued (lower priority) processes
   receive a fractional weight relative to the default nice value,
   whereas lower valued (higher priority) processes receive a larger
   weight.

The Linux Scheduling Implementation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#. Time Accounting

   All processes schedulers must account for the time that a process
   runs.

   #. The scheduler Entity Structure

      CFS does not have the notion of a timeslice, but it must still
      keep account for the time that each process runs.

      **It's quite different from the book, that should be the version
      upgrade changes**

      .. code:: c

         struct sched_entity {
                 /* For load-balancing: */
                 struct load_weight              load;
                 unsigned long                   runnable_weight; /* not in book */
                 struct rb_node                  run_node;
                 struct list_head                group_node;
                 unsigned int                    on_rq;

                 u64                             exec_start;
                 u64                             sum_exec_runtime;
                 u64                             vruntime;
                 u64                             prev_sum_exec_runtime;

         #if 0
                 u64                             last_wakeup;        /* only in book */
                 u64                             avg_overlap;        /* only in book */
         #endif

                 u64                             nr_migrations;

         #if 0
                 u64                             start_runtime;      /* only in book */
                 u64                             avg_wakeup;         /* only in book */
         #endif

                 struct sched_statistics         statistics;

         #ifdef CONFIG_FAIR_GROUP_SCHED
                 int                             depth;
                 struct sched_entity             *parent;
                 /* rq on which this entity is (to be) queued: */
                 struct cfs_rq                   *cfs_rq;
                 /* rq "owned" by this entity/group: */
                 struct cfs_rq                   *my_q;
         #endif

         #ifdef CONFIG_SMP
                 /*
                  * Per entity load average tracking.
                  *
                  * Put into separate cache line so it does not
                  * collide with read-mostly values above.
                  */
                 struct sched_avg                avg;
         #endif
         };

   #. The Virtual Runtime

      The ``vruntime`` variable stores the *virtual runtime* of a
      process, which is the actual runtime normarized by the number of
      runnable processes.

      CFS uses ``vruntime`` to account for how long a process has run
      and thus how much longer it ought to run.

      The function ``update_curr()``, manages this accounting (**Also,
      it changes a lot from the book**):

      .. code:: c

         static void update_curr(struct cfs_rq *cfs_rq)
         {
                 struct sched_entity *curr = cfs_rq->curr;
                 u64 now = rq_clock_task(rq_of(cfs_rq));
                 u64 delta_exec;

                 if (unlikely(!curr))
                         return;

                 delta_exec = now - curr->exec_start;
                 if (unlikely((s64)delta_exec <= 0))
                         return;
                 curr->exec_start = now;
                 schedstat_set(curr->statistics.exec_max,
                               max(delta_exec, curr->statistics.exec_max));

                 curr->sum_exec_runtime += delta_exec;
                 schedstat_add(cfs_rq->exec_clock, delta_exec);
                 curr->vruntime += calc_delta_fair(delta_exec, curr);
                 update_min_vruntime(cfs_rq);
                 if (entity_is_task(curr)) {
                         struct task_struct *curtask = task_of(curr);

                         trace_sched_stat_runtime(curtask, delta_exec, curr->vruntime);
                         cgroup_account_cputime(curtask, delta_exec);
                         account_group_exec_runtime(curtask, delta_exec);
                 }

                 account_cfs_rq_runtime(cfs_rq, delta_exec);
         }

#. Process Selection

#. The Scheduler Entry Point

#. Sleeping and Waking up

6 Kernel Data Structures
------------------------

Linked List
~~~~~~~~~~~

.. code:: c

   struct list_head {
           struct list_head *next;
           struct list_head *prev;
   };

-  TEST: `container\ of <ch6/container_of.c::include <stdio.h>>`__

.. code:: c

   #define container_of(ptr, type, member)                                 \
           ({                                                              \
                   const typeof(((type *)0)->member) *__mptr = (ptr);      \
                   (type *)((char *)__mptr - offsetof(type, member));      \
           })

12 Memory Management
--------------------

Zones
~~~~~

Linux: two shortcomings of hardware with respect to memory addressing:

-  Some hardware devices can perform DMA (direct memory access) to only
   certain memory addresses.
-  Some architectures can physically addressing larger amounts of memory
   than they can virtually address. Consequently, some memory is not
   permanently mapped into the kernel address space.

Linux has four primary memory zones:

-  ZONE\ :sub:`DMA`: This zone contains pages that can undergo DMA
-  ZONE\ :sub:`DMA32`: unlike ZONE\ :sub:`DMA`, these pages are
   accessible only by 32-bit devices.
-  ZONE\ :sub:`NORMAL`: This zone contains normal, regularly mapped,
   pages.
-  ZONE\ :sub:`HIGHMEM`: This zone contains "high memory", which are
   pages not permanently mapped into the kernel's address space.

.. table:: Table 2: Table 12.1 Zones on x86-32

   ==================== ========================== ===============
   Zone                 Description                Physical Memory
   ==================== ========================== ===============
   ZONE\ :sub:`DMA`     DMA-able pages             < 16MB
   ZONE\ :sub:`NORMAL`  Normally addressable pages 16-896 MB
   ZONE\ :sub:`HIGHMEM` Dynamically mapped pages   > 896 MBP
   ==================== ========================== ===============
