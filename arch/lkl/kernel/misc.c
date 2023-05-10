#include <linux/kallsyms.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/seq_file.h>
#include <asm/ptrace.h>
#include <asm/host_ops.h>
#include <asm/kasan_asan.h>

#ifdef CONFIG_PRINTK
static char stack_buf[2048];
void dump_stack(void)
{
	// Note(feli): use asan functions, to deal with modules
   int a = __asan_get_allocation_context();
   pr_err("++++++++++++++++++++++++++++++++++++++++\n");
   if(a > 0) {
      __asan_print_allocation_context_buf(a, stack_buf, sizeof(stack_buf));
      pr_err("%s\n", stack_buf);
   } else {
      pr_err("ERROR: could not get alloc context %d\n", a);
   }
   pr_err("++++++++++++++++++++++++++++++++++++++++\n");

#if 0
	unsigned long dummy;
	unsigned long *stack = &dummy;
	unsigned long addr;

	pr_info("Call Trace:\n");
	while (((long)stack & (THREAD_SIZE - 1)) != 0) {
		addr = *stack;
		if (__kernel_text_address(addr)) {
			pr_info("%p:  [<%08lx>] %pS", stack, addr,
				(void *)addr);
			pr_cont("\n");
		}
		stack++;
	}
	pr_info("\n");
#endif
}
#endif

void show_regs(struct pt_regs *regs)
{
}

#ifdef CONFIG_PROC_FS
static void *cpuinfo_start(struct seq_file *m, loff_t *pos)
{
	return NULL;
}

static void *cpuinfo_next(struct seq_file *m, void *v, loff_t *pos)
{
	return NULL;
}

static void cpuinfo_stop(struct seq_file *m, void *v)
{
}

static int show_cpuinfo(struct seq_file *m, void *v)
{
	return 0;
}

const struct seq_operations cpuinfo_op = {
	.start	= cpuinfo_start,
	.next	= cpuinfo_next,
	.stop	= cpuinfo_stop,
	.show	= show_cpuinfo,
};
#endif
