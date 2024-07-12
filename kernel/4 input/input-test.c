#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>  /* pr_info(() */
#include <linux/delay.h>  /* msleep() */
#include <linux/version.h> /* Linux vresion */

#include <linux/input.h>
#include <linux/input-event-codes.h>

struct input_dev *key_input;
static struct hrtimer my_timer;

enum hrtimer_restart my_timer_callback(struct hrtimer *timer)
{
    /* 在这里执行定时操作 */
    /* 返回 HRTIMER_NORESTART 表示定时器不需要重新启动，返回 HRTIMER_RESTART 表示需要重新启动定时器 */
    input_report_key(key_input, KEY_S, 1);
	input_sync(key_input);
    hrtimer_forward_now(timer, ms_to_ktime(1000)); //HRTIMER_RESTART需要这条语句
    return HRTIMER_RESTART;
}

int input_init(void)
{
    int result = 0;
	ktime_t duration;
	printk("chendening module init \n");
	
	/* 1、申请 input_dev */
    key_input = input_allocate_device();
    key_input->name = "chendening_key_input";
    
    /* 2、初始化 input_dev，设置产生哪些事件 */
    __set_bit(EV_KEY, key_input->evbit);
    __set_bit(EV_REP, key_input->evbit);

    /* 3、初始化 input_dev，设置产生哪些按键 */
    __set_bit(KEY_L, key_input->keybit);
    __set_bit(KEY_S, key_input->keybit);

    /* 4、注册输入设备 */
    if(input_register_device(key_input) < 0) {
		printk("input_register_device error.\n");
		result = -1;
	}
	
	duration = ktime_set(1, 0);  // 设置定时器超时时间为 1 秒
	hrtimer_init(&my_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);  
    my_timer.function = my_timer_callback;
    hrtimer_start(&my_timer, duration, HRTIMER_MODE_REL);

    return result;
}

void input_exit(void)
{
	printk("chendening module exit \n");
}

module_init(input_init);
module_exit(input_exit);
MODULE_DESCRIPTION("chendening");
MODULE_LICENSE("GPL");
