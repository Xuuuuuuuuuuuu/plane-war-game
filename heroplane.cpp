#include "heroplane.h"
#include "config.h"
HeroPlane::HeroPlane()
{
    //加载飞机图片资源
    m_plane.load(HERO_PATH);

    //初始化飞机坐标，考虑到飞机图片面积，将飞机设置在底端中央位置
    m_x = GAME_WIDTH * 0.5 - m_plane.width() * 0.5;
    m_y = GAME_HEIGHT - m_plane.height();

    //设置边框与飞机图片重合
    m_rect.setWidth(m_plane.width());
    m_rect.setHeight(m_plane.height());
    m_rect.moveTo(m_x,m_y);

    //初始化发射间隔记录
    m_recorder = 0;

}

void HeroPlane::setPosition(int x, int y)
{
    m_x = x;
    m_y = y;
    m_rect.moveTo(m_x,m_y);

}

void HeroPlane::shoot()
{
    //累加间隔变量，控制子弹射出间隔
    m_recorder++;

    //当前调用shoot时不满足射出条件
    if (m_recorder < BULLET_INTERVAL)
    {
        return;
    }

    //射出后清零间隔记录变量
    m_recorder = 0;


    for (int i = 0; i < BULLET_NUM; i++){
        if (m_bullets[i].m_free){
            m_bullets[i].m_free = false;
            //根据飞机坐标设置当前射出子弹的坐标
            m_bullets[i].m_x = m_x + m_rect.width() * 0.5 - 10;
            m_bullets[i].m_y = m_y - 25;
            break;
        }
    }

}
