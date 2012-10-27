#include "world/ent/EntityEnums.h"
#include "world/ent/Entity.h"
#include "world/World.h"
#include "util/Vector2d.h"
#include "util/ObjectFactory.h"

#include "world/ent/act/char/Rocketman.h"
#include "world/ent/act/char/Runner.h"
#include "world/ent/act/char/Healer.h"

// Add Entity type registrations here.
// Don't forget to add the entity
// types in EntityEnums.h and the header
// file above!
void EntityEnums::pre_init( ObjectFactory<Entity *(World*, Vector2d*), int> &factory )
{
    // Format: factory.Register<ClassName>( ENUM_NAME );
    //factory.Register<>(  );
    factory.Register<Rocketman>( ENTITY_ROCKETMAN );
    factory.Register<Runner>( ENTITY_RUNNER );
    factory.Register<Healer>( ENTITY_HEALER );
}
