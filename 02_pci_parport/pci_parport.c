#include <linux/module.h>
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/jiffies.h>
#include <linux/timer.h>
#include <linux/moduleparam.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Andrei");
MODULE_DESCRIPTION("A simple LKM for testing a PCIe to parallel port adapter");

#define VENDOR_ID 0x1c00
#define DEVICE_ID 0x3050

static int delay_ak = 30;
module_param(delay_ak, int, 0644);
MODULE_PARM_DESC(delay_ak, "How many seconds to wait before timed mesages");

/** PCI device */
static struct pci_dev *ptr; 

/** Variable for timer */
static struct timer_list my_timer;

/**
 * @brief Timer Callback Function
 *
 * Reads in Inputs from Parport and 
 * writes value in 7 segment display
 */
void parport_timer_callback(unsigned long arg) {
    pr_info("%ld: par_port is back with delay %d\n", jiffies, delay_ak);
    mod_timer(&my_timer, jiffies + delay_ak);
}


/**
 * @brief This function is called when the module is loaded into the kernel
 */
static int __init ModuleInit(void) {
    u16 val;

    /* Check if a PCI device with vendor and device id is available */
    ptr = pci_get_device(VENDOR_ID, DEVICE_ID, ptr);
    if(ptr == NULL) {
        printk("pci_parport - PCI to parport adapter is not available!\n");
        return -1;
    }

    /* Enable the device */
    if(pci_enable_device(ptr) < 0) {
        printk("pci_parport - Could not enable the device!\n");
        return -1;
    }

    /* Access config space */
    pci_read_config_word(ptr, PCI_VENDOR_ID, &val);
    printk("pci_parport - VENDOR ID: 0x%x\n", val);
    pci_read_config_word(ptr, PCI_DEVICE_ID, &val);
    printk("pci_parport - VENDOR ID: 0x%x\n", val);

    pr_info("Delay set to %d\n", delay_ak);

    init_timer(&my_timer);
    my_timer.expires = jiffies + delay_ak;
    my_timer.function = parport_timer_callback;
    add_timer(&my_timer);

    /* Initialize timer */


    return 0;
}

/**
 * @brief This function is called when the module is removed from the kernel
 */
static void __exit ModuleExit(void) {
    del_timer(&my_timer);
    printk("pci_parport - Unload Module\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);
