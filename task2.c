#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David");
MODULE_DESCRIPTION("Receiving input from a user.");
MODULE_VERSION("0.01");

static char* input = "world";
module_param(input, charp, 0);
static int __init input_from_user(void) {
	printk(KERN_INFO "Hello %s\n", input);
	return 0;
}

static void __exit input_exit(void) {
	printk(KERN_INFO "Goodbye %s!\n", input);
}

module_init(input_from_user);
module_exit(input_exit);
