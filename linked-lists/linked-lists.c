#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Listat e lidhura ne Linux Kernel");

struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;
} birthday;

static LIST_HEAD(birthday_list);

static int __init projekti1_pjesa2_init(void) {
	struct birthday *ptr;
	printk(KERN_INFO "Moduli po ngarkohet...");
	
	int i = 1;
	while(i <= 5) {
		birthday *person;
		person = (birthday *) kmalloc(sizeof (*person), GFP_KERNEL);
		person->day = 2 + i;
		person->month = 8 + i;
		person->year = 1995 + i;
		
		INIT_LIST_HEAD (&person->list);
		list_add_tail(&person->list, &birthday_list);
		
		i++;
	}
	
	list_for_each_entry(ptr, &birthday_list, list){
		printk("Ditelindja: %d / %d / %d\n", ptr->day, ptr->month, ptr->year);
	}
	
	return 0;
}

static void __exit projekti1_pjesa2_exit(void){
	struct birthday *ptr;
	struct birthday *next;
	printk(KERN_INFO "Moduli po c'ngarkohet...\n");
	
	list_for_each_entry_safe(ptr, next, &birthday_list, list){
		printk(KERN_INFO "Ditelindja: %d / %d / %d\n", ptr->day, ptr->month, ptr->year);
		list_del(&ptr->list);
		kfree(ptr);
	}
}

module_init(projekti1_pjesa2_init);
module_exit(projekti1_pjesa2_exit);
