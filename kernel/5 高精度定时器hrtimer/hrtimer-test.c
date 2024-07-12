#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>  /* pr_info(() */
#include <linux/delay.h>  /* msleep() */
#include <linux/version.h> /* Linux vresion */

#include <linux/hrtimer.h>

static struct hrtimer my_timer;

enum hrtimer_restart my_timer_callback(struct hrtimer *timer)
{
    /* 在这里执行定时操作 */
    /* 返回 HRTIMER_NORESTART 表示定时器不需要重新启动，返回 HRTIMER_RESTART 表示需要重新启动定时器 */
     printk("chendening yyds\n");
     hrtimer_forward_now(timer, ms_to_ktime(1000)); //HRTIMER_RESTART需要这条语句
    return HRTIMER_RESTART;
}

int chendening_test_init(void)
{
     int ret = 0;
    
     ktime_t duration = ktime_set(1, 0);  // 设置定时器超时时间为 1 秒
     //ktime_t duration = ktime_set(0, 1000000000);  // 设置定时器超时时间为 1 秒
    
     hrtimer_init(&my_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);  
     my_timer.function = my_timer_callback;
     hrtimer_start(&my_timer, duration, HRTIMER_MODE_REL);
     
     printk("chendening test success\n");
     
     return ret;
}

void chendening_test_exit(void)
{
     printk("chendening test exit\n");
}

module_init(chendening_test_init);
module_exit(chendening_test_exit);
MODULE_DESCRIPTION("chendening");
MODULE_LICENSE("GPL");
