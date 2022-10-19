#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H


#include <QPixmap>
#include <QRect>
class EnemyPlane
{
public:
    EnemyPlane();

    //更新坐标
    void updatePosition();

public:
    //敌机资源对象
    QPixmap m_enemy;

    //敌机坐标
    int m_x;
    int m_y;

    //状态
    bool m_free;

    //速度
    int m_speed;


    //敌机的矩形边框
    QRect m_rect;
};

#endif // ENEMYPLANE_H
