// gerencia as colisões

#include "collision-controller.hpp"

#include "system/global.hpp"
#include "app/global.hpp"

#include "core/entity/entity.hpp"

#include "utils/math/math.hpp"

void CollisionController::MobToMobCollision(double deltaTime) {
    for (int n = 0; n < globals.mobs.size(); ++n) {
        for (int k = n + 1; k < globals.mobs.size(); ++k) {
            std::shared_ptr<Entity>& mob1 = globals.mobs[n];
            std::shared_ptr<Entity>& mob2 = globals.mobs[k];

            if (mob1 == nullptr || mob2 == nullptr) {
                continue;
            }

            if (Entity::IsColliding(mob1, mob2)) {
                double angle = GetAngleBetween(mob1->pos, mob2->pos);

                double offset = (mob1->size + mob2->size) / 2.0f + COLLISION_OFFSET_BASE;

                double xOffset = offset * cos(angle) * deltaTime;
                double yOffset = offset * sin(angle) * deltaTime;

                mob1->pos.Set(0, mob1->pos.Get(0) - xOffset);
                mob1->pos.Set(1, mob1->pos.Get(1) - yOffset);

                mob2->pos.Set(0, mob2->pos.Get(0) + xOffset);
                mob2->pos.Set(1, mob2->pos.Get(1) + yOffset);
            }
        }
    }
}

void CollisionController::MobToObjectCollision(double deltaTime) {

}
