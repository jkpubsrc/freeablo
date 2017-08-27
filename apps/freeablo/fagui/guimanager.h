#ifndef GUIMANAGER_H
#define GUIMANAGER_H
#include <string>
#include <chrono>
#include <queue>
#include <functional>
#include "../engine/enginemain.h"


#include <fa_nuklear.h>
#include "../faworld/inventory.h"
#include <boost/variant/variant_fwd.hpp>

namespace Rocket
{
namespace Core
{
class ElementDocument;
}
}

namespace Render
{
    enum class CursorHotspotLocation;
}

namespace FAWorld
{
    class Player;
}

namespace FAGui
{
    // move all this to better place since cursor state is also dependent on spells etc.
    extern std::string cursorPath;
    extern Render::CursorHotspotLocation cursorHotspot;
    extern uint32_t cursorFrame;

    enum class PanelType {
        none,
        inventory,
        spells,
        character,
        quests,
    };

    enum class PanelPlacement
    {
        none,
        left,
        right,
    };

    PanelPlacement panelPlacementByType (PanelType type);
    const char *bgImgPath (PanelType type);
    const char *panelName (PanelType type);

    class ScrollBox;
    class GuiManager
    {
    public:
        GuiManager(Engine::EngineMain& engine, FAWorld::Player &player);
        void update(bool paused, nk_context* ctx);

    private:
        void togglePanel (PanelType type);
        template <class Function>
        void drawPanel(nk_context* ctx, PanelType panelType, Function op);
        void item(nk_context* ctx, FAWorld::EquipTarget target, boost::variant<struct nk_rect, struct nk_vec2> placement);
        void inventoryPanel(nk_context* ctx);
        void characterPanel(nk_context* ctx);
        void questsPanel(nk_context* ctx);
        void spellsPanel(nk_context* ctx);
        void belt(nk_context* ctx);
        void bottomMenu(nk_context* ctx);
        PanelType* panel(PanelPlacement placement);

    private:
        Engine::EngineMain& mEngine;
        FAWorld::Player& mPlayer;
        PanelType mCurRightPanel = PanelType::none, mCurLeftPanel = PanelType::none;
    };
}

#endif
