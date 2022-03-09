#include <linux/module.h>
#include <linux/init.h>
#include <linux/pci.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Andrei");
MODULE_DESCRIPTION("A simple LKM for testing a PCIe to parallel port adapter");

#define VENDOR_ID
#define DEVICE_ID

/**
 * @brief This function is called when the module is loaded into the kernel
 */
static int __init ModuleInit(void) {
    printk("Hello, kernel!\n");
    return 0;
}

/**
 * @brief This function is called when the module is removed from the kernel
 */
static void __exit ModuleExit(void) {
    printk("Goodbye, kernel\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);