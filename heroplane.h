#ifndef HEROPLANE_H
#define HEROPLANE_H

#include <QPixmap>
#include "bullet.h"
#include "config.h"
class HeroPlane
{
public:
    HeroPlane();

    //发射子弹
    void shoot();

    //设置飞机坐标
    void setPosition(int x, int y);

public:
    //飞机资源对象
    QPixmap m_plane;

    //飞机坐标
    int m_x;
    int m_y;

    //飞机边框
    QRect m_rect;

    //飞机发射子弹的配置
    Bullet m_bullets[BULLET_NUM];
    int m_recorder;


};

#endif // HEROPLANE_H
