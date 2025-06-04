#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "raylib.h"
#include "raymath.h"
#include "../src/core/Pool.h"
#include "../src/entities/Bullet.h"

TEST_CASE(PoolBasic)
{
    Pool<Bullet> pool(2);
    Bullet* b1 = pool.getObject();
    CHECK(b1 != nullptr);
    Bullet* b2 = pool.getObject();
    CHECK(b2 != nullptr);
    CHECK(pool.getObject() == nullptr);
    pool.releaseObject(b1);
    Bullet* b3 = pool.getObject();
    CHECK(b3 == b1);
    CHECK(pool.getObject() == nullptr);
}
