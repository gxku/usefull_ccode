#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/vmalloc.h>
#include <linux/mm.h>
#include <linux/version.h>
#include <asm/cacheflush.h>

#include <xen/xen.h>
#include <xen/events.h>
#include <xen/evtchn.h>
#include <xen/grant_table.h>
#include <asm/xen/hypervisor.h>
#include <asm/xen/page.h>

MODULE_LICENSE("Dual BSD/GPL"); 
static uint32_t reg = 0x0;
module_param(reg, uint, 0644);
MODULE_PARM_DESC(reg, "reg addr");

static uint32_t len = 0x1;
module_param(len, uint, 0644);
MODULE_PARM_DESC(len, "reg len to dump");

#define REG(addr) ((uint32_t *)(addr))
static inline uint32_t REG_READ32(volatile uint32_t *addr)
{
    uint32_t value;
    __asm__ __volatile__("ldr %0, [%1]":"=&r"(value):"r"(addr));
    return value;
}




 static int __init hello_init (void) 
 {
	int i=0;
 
	if(!reg){
		printk("uage : insmod XXX.ko reg=0x1234 len=n{default len=1}\n");
		return 0;
	}
	volatile uint32_t	*addr = ioremap(reg,len*4);
	printk("########################\n");
	for(i=0;i<len;i++){
		printk("{%x}--[%x]\n",reg,*addr);
		addr++;
		reg=reg+4;
    }
	printk("########################i>\n");

     return 0; 
 } 

 static void __exit hello_exit (void) 
 { 
     printk (KERN_INFO "char driver cleaned up\n"); 
 } 
 
 module_init (hello_init); 
 module_exit (hello_exit); 

