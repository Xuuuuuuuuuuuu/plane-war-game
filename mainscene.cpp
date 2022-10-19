#include "mainscene.h"
#include "config.h"
#include <QIcon>
#include <QPainter>
#include <ctime>
#include <QSound>
MainScene::MainScene(QWidget *parent)
    : QWidget(parent)
{
    initScene();
}

MainScene::~MainScene()
{
}

void MainScene::initScene()
{
    srand((unsigned int)time(NULL));

    setFixedSize(GAME_WIDTH+150,GAME_HEIGHT);

    setWindowTitle(GAME_TITLE);

    setWindowIcon(QIcon(GAME_ICON));

    //设置定时器
    m_Timer.setInterval(GAME_RATE);

    playGame();

    m_recorder = 0;
}

void MainScene::playGame()
{
    QSound::play(SOUND_BACKGROUND);
    //启动定时器
    m_Timer.start();

    //监听定时器
    connect(&m_Timer, &QTimer::timeout, [=](){
        //敌机出场
        enemyToScene();
        //更新游戏中的坐标值
        updatePosition();
        //重新绘制图片
        update();

        collisionDetection();
    });

}

void MainScene::updatePosition()
{
    //更新地图坐标 实现地图滚动
    m_map.mapPosition();

    //
    m_hero.shoot();

    for (int i = 0; i < BULLET_NUM; i++)
    {
        if (!m_hero.m_bullets[i].m_free)
        {
            m_hero.m_bullets[i].updatePosition();
        }
    }

    for (int  i = 0; i < ENEMY_NUM; i++)
    {
        if(!m_enemys[i].m_free)
        {
            m_enemys[i].updatePosition();
        }
    }

    for(int i = 0 ; i < BOMB_NUM;i++)
    {
        if(m_bombs[i].m_Free == false)
        {
           m_bombs[i].updateInfo();
        }
    }

}



void MainScene::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    //绘制地图
    painter.drawPixmap(0, m_map.m_map1_posY, m_map.m_map1);
    painter.drawPixmap(0, m_map.m_map2_posY, m_map.m_map2);

    //绘制飞机
    painter.drawPixmap(m_hero.m_x, m_hero.m_y, m_hero.m_plane);

    //绘制子弹
    for (int i = 0; i < BULLET_NUM; i++)
    {
        if (!m_hero.m_bullets[i].m_free)
        {
            painter.drawPixmap(m_hero.m_bullets[i].m_x,m_hero.m_bullets[i].m_y,m_hero.m_bullets[i].m_bullet);
        }
    }

    for (int i = 0; i < ENEMY_NUM; i++)
    {
        if(!m_enemys[i].m_free)
        {
            painter.drawPixmap(m_enemys[i].m_x, m_enemys[i].m_y, m_enemys[i].m_enemy);
        }
    }

    //绘制爆炸图片
    for(int i = 0 ; i < BOMB_NUM;i++)
    {
        if(m_bombs[i].m_Free == false)
        {
           painter.drawPixmap(m_bombs[i].m_X,m_bombs[i].m_Y,m_bombs[i].m_pixArr[m_bombs[i].m_index]);


        }
    }

}

void MainScene::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x() - m_hero.m_rect.width() * 0.5;
    int y = event->y() - m_hero.m_rect.height() * 0.5;

    if (x <= 0)
    {
        x = 0;
    }
    if (x >= GAME_WIDTH - m_hero.m_rect.width())
    {
        x = GAME_WIDTH - m_hero.m_rect.width();
    }
    if (y <= 0)
    {
        y = 0;
    }
    if (y >= GAME_HEIGHT - m_hero.m_rect.height())
    {
        y = GAME_HEIGHT - m_hero.m_rect.height();
    }

    m_hero.setPosition(x,y);
}

void MainScene::enemyToScene()
{
    m_recorder++;

    if (m_recorder < ENEMY_INTERVAL)
    {
        return;
    }

    m_recorder = 0;

    for (int i = 0; i < ENEMY_NUM; i++)
    {
        if (m_enemys[i].m_free)
        {
            m_enemys[i].m_free = false;

            m_enemys[i].m_x = rand() % (GAME_WIDTH - m_enemys[i].m_rect.width());
            m_enemys[i].m_y = -m_enemys[i].m_rect.height();
            break;
        }
    }
}

void MainScene::collisionDetection()
{
        //遍历所有非空闲的敌机
        for(int i = 0 ;i < ENEMY_NUM;i++)
        {
            if(m_enemys[i].m_free)
            {
                //空闲飞机 跳转下一次循环
                continue;
            }

            //遍历所有 非空闲的子弹
            for(int j = 0 ; j < BULLET_NUM;j++)
            {
                if(m_hero.m_bullets[j].m_free)
                {
                    //空闲子弹 跳转下一次循环
                    continue;
                }

                //如果子弹矩形框和敌机矩形框相交，发生碰撞，同时变为空闲状态即可
                if(m_enemys[i].m_rect.intersects(m_hero.m_bullets[j].m_rect))
                {
                    m_enemys[i].m_free = true;
                    m_hero.m_bullets[j].m_free = true;

                    for(int k = 0 ; k < BOMB_NUM;k++)
                    {
                        if(m_bombs[k].m_Free)
                        {
                            //爆炸状态设置为非空闲
                            m_bombs[k].m_Free = false;
                            //更新坐标

                            m_bombs[k].m_X = m_enemys[i].m_x;
                            m_bombs[k].m_Y = m_enemys[i].m_y;
                            QSound::play(SOUND_BOMB);
                            break;
                        }
                    }
                }
            }
        }

}
