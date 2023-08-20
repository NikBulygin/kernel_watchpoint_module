#include <linux/module.h>
#include <linux/kprobes.h>

static unsigned long target_addr = 0x12345678;
module_param(target_addr, ulong, S_IRUGO);
MODULE_PARM_DESC(target_addr, "Target address for the watchpoint");

static int handler_pre(struct kprobe *p, struct pt_regs *regs) {
    if (regs->ip == target_addr) {
        printk(KERN_INFO "Access detected at address: %lx\n", target_addr);
        dump_stack();
    }
    return 0;
}

static struct kprobe kp = {
    .symbol_name = "some_suspected_function",
    .pre_handler = handler_pre,
};

static int __init watchpoint_init(void) {
    int ret;
    ret = register_kprobe(&kp);
    if (ret < 0) {
        printk(KERN_INFO "register_kprobe failed, returned %d\n", ret);
        return ret;
    }
    printk(KERN_INFO "kprobe registered on %s\n", kp.symbol_name);
    return 0;
}

static void __exit watchpoint_exit(void) {
    unregister_kprobe(&kp);
    printk(KERN_INFO "kprobe unregistered\n");
}

module_init(watchpoint_init);
module_exit(watchpoint_exit);
MODULE_LICENSE("GPL");
