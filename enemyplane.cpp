#include "enemyplane.h"
#include "config.h"
EnemyPlane::EnemyPlane()
{
    m_enemy.load(ENEMY_PATH);

    m_x = 0;
    m_y = 0;

    m_free = true;

    m_speed = ENEMY_SPEED;

    m_rect.setWidth(m_enemy.width());
    m_rect.setHeight(m_enemy.height());
    m_rect.moveTo(m_x, m_y);

}

void EnemyPlane::updatePosition()
{
    if(m_free)
    {
        return;
    }

    m_y += ENEMY_SPEED;
    m_rect.moveTo(m_x, m_y);

    if (m_y >= GAME_HEIGHT + m_rect.height())
    {
        m_free = true;
    }
}
