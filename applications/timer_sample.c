#include <rtthread.h>

/* ��ʱ���Ŀ��ƿ� */
static rt_timer_t timer1;
static rt_timer_t timer2;
static int cnt = 0;

/* ��ʱ��1��ʱ���� */
static void timeout1(void *parameter)
{
    rt_kprintf("periodic timer is timeout %d\n", cnt);

    /* ����5�κ�ֹͣ���ڶ�ʱ�� */
    if (cnt++ >= 4)
    {
        rt_timer_stop(timer1);
        rt_kprintf("periodic timer was stopped! \n");
    }
}

/* ��ʱ��2��ʱ���� */
static void timeout2(void *parameter)
{
    rt_kprintf("one shot timer is timeout\n");
}


int timer_sample(void)
{
    /* ������ʱ��1  ���ڶ�ʱ�� */
    timer1 = rt_timer_create("timer1", timeout1,
                             RT_NULL, 5,
                             RT_TIMER_FLAG_PERIODIC);

    /* ������ʱ��1 */
    if (timer1 != RT_NULL) rt_timer_start(timer1);

    /* ������ʱ��2 ���ζ�ʱ�� */
    timer2 = rt_timer_create("timer2", timeout2,
                             RT_NULL,  15,
                             RT_TIMER_FLAG_ONE_SHOT);

    /* ������ʱ��2 */
    if (timer2 != RT_NULL) rt_timer_start(timer2);
    return 0;
}

/* ������ msh �����б��� */
MSH_CMD_EXPORT(timer_sample, timer sample);


