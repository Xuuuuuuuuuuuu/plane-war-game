#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include <QTimer>
#include <QPaintEvent>
#include <QMouseEvent>
#include "map.h"
#include "heroplane.h"
#include "bullet.h"
#include "enemyplane.h"
#include "bomb.h"
class MainScene : public QWidget
{
    Q_OBJECT



public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    //初始化游戏场景
    void initScene();

    //启动游戏 启用定时器对象
    void playGame();

    //更新地图坐标，调用地图类的接口
    void updatePosition();

    //绘图事件
    void paintEvent(QPaintEvent * event);

    //鼠标拖拽飞机事件
    void mouseMoveEvent(QMouseEvent * event);

    //类子弹的敌机出场
    void enemyToScene();

    void collisionDetection();



public:

    QTimer m_Timer;

    Map m_map;

    HeroPlane m_hero;

    EnemyPlane m_enemys[ENEMY_NUM];

    int m_recorder;

    Bomb m_bombs[BOMB_NUM];



};
#endif // MAINSCENE_H
