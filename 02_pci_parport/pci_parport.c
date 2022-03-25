#include <linux/module.h>
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/jiffies.h>
#include <linux/timer.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Andrei");
MODULE_DESCRIPTION("A simple LKM for testing a PCIe to parallel port adapter");

#define VENDOR_ID 0x1c00
#define DEVICE_ID 0x3050

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

    /* Initialize timer */


    return 0;
}

/**
 * @brief This function is called when the module is removed from the kernel
 */
static void __exit ModuleExit(void) {
    printk("pci_parport - Unload Module\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);
