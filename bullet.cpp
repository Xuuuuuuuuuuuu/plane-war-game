#include "bullet.h"

#include "config.h"
Bullet::Bullet()
{
    //加载子弹图片资源
    m_bullet.load(BULLET_PATH);

    //初始化子弹坐标
    m_x = GAME_WIDTH * 0.5 - m_bullet.width() * 0.5;
    m_y = GAME_HEIGHT;

    //初始化子弹状态，子弹闲置不射出
    m_free = true;

    //初始化子弹速度
    m_speed = BULLET_SPEED;

    //设置子弹边框，用于碰撞检测
    m_rect.setWidth(m_bullet.width());
    m_rect.setHeight(m_bullet.height());
    m_rect.moveTo(m_x,m_y);
}

void Bullet::updatePosition()
{
    //子弹空闲不射出
    if (m_free)
    {
        return;
    }

    //子弹向上移动
    m_y -= m_speed;
    m_rect.moveTo(m_x, m_y);

    //子弹超出边界，就不计算了？感觉子弹射出后应该要delete才对
    if (m_y <= -m_rect.height())
    {
        m_free = true;
    }
}
