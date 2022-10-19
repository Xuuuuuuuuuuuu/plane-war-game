#ifndef BULLET_H
#define BULLET_H

#include <QPixmap>
#include <QRect>

class Bullet
{
public:
    Bullet();

    void updatePosition();

public:
    //子弹资源对象
    QPixmap m_bullet;
    //子弹坐标
    int m_x;
    int m_y;
    //子弹移动速度
    int m_speed;
    //子弹是否闲置？
    bool m_free;
    //子弹边框，用于碰撞检测
    QRect m_rect;
};

#endif // BULLET_H
