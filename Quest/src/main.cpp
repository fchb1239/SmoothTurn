#include "main.hpp"
#include "modloader/shared/modloader.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

static ModInfo modInfo;

#define INFO(value...) getLogger().info(value)
#define ERROR(value...) getLogger().error(value)


Logger &getLogger()
{
    static Logger *logger = new Logger(modInfo);
    return *logger;
}

MAKE_HOOK_FIND_CLASS_UNSAFE_INSTANCE(PlayerController_Start, "HexabodyVR.PlayerController", "HexaBodyPlayer3", "Start", void, Il2CppObject* self) {
    PlayerController_Start(self);
    CRASH_UNLESS(il2cpp_utils::SetFieldValue(self, "SmoothTurn", true));
    CRASH_UNLESS(il2cpp_utils::SetFieldValue(self, "SmoothTurnSpeed", 200.0f));
}

extern "C" void setup(ModInfo &info)
{
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
}

extern "C" void load()
{
    il2cpp_functions::Init();
    Logger& logger = getLogger();
    logger.info("Installing hooks...");
    
    INSTALL_HOOK(getLogger(), PlayerController_Start);

    logger.info("Installed all hooks!");
}